/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Joaquim Homrighausen.
**
**  ----------------------------------------------------------------------
**
**  jamscan.c (JAMmb)
**
**  Scan message headers and call user comparison routine
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    JoHo
**  Initial coding. No decryption or unescaping supported yet.
*/
#define JAMCAPI 1

#include "jammb.h"

/*
**  Scan message headers starting at the specified number (WhatMsg). For
**  each header found, the function calls USERCOMPARE. The ScanFwd parameter
**  determines the direction of the scan. The Hdr record will contain the
**  newly read message header and if the header had any subfields, WorkBuf
**  will contain as much subfield data as will fit. If all of the subfield
**  data didn't fit and the USERCOMPARE function returns ScanMsgHdrDiscard,
**  the function will read the remaining subfield data and call the user
**  function again. Returns 1 if user function returned ScanMsgHdrStop and
**  FALSE otherwise.
*/
int _JAMPROC JAMmbScanForMsgHdr(JAMAPIRECptr apirec, UINT32 WhatMsg,
                        int ScanFwd, ScanMsgHdrComp UserCompare)
{
    int     UserResult;
    INT32   JunkL, MaxBlockToRead;
    UINT32  ReadBytes;

    /* Make sure the message number is valid */
    if (WhatMsg<apirec->HdrInfo.BaseMsgNum)
        {
        apirec->APImsg=JAMAPIMSG_INVMSGNUM;
        return (0);
        }

    while (1)
        {
        /* Seek to position for current message */
        if (!JAMmbFetchMsgIdx(apirec, WhatMsg))
            return (0);
        if (apirec->SeekFunc(apirec, apirec->HdrHandle, JAMSEEK_SET, apirec->Idx.HdrOffset)!=(INT32)apirec->Idx.HdrOffset)
            {
            apirec->APImsg=JAMAPIMSG_SEEKERROR;
            return (0);
            }

        JunkL=apirec->ReadFunc(apirec, apirec->HdrHandle, &apirec->Hdr, (INT32)sizeof(JAMHDR));
        if (JunkL==(INT32)sizeof(JAMHDR))
            {
            apirec->LastMsgNum=WhatMsg;

            /* If all subfield data will fit, read it all and call user function */
            if (apirec->Hdr.SubfieldLen<=apirec->WorkLen)
                {
                if (apirec->Hdr.SubfieldLen>0)
                    {
                    if (apirec->ReadFunc(apirec, apirec->HdrHandle, &apirec->WorkBuf, (INT32)apirec->Hdr.SubfieldLen)!=(INT32)apirec->Hdr.SubfieldLen)
                        {
                        apirec->APImsg=JAMAPIMSG_CANTRDFILE;
                        return (0);
                        }
                    }
                /* Call user function and process result */
                UserResult=UserCompare(apirec);
                if (UserResult==ScanMsgHdrStop)
                    {
                    return (1);
                    }
                else
                    {
                    if (ScanFwd)
                        WhatMsg++;
                    else
                        {
                        if (WhatMsg==apirec->HdrInfo.BaseMsgNum)
                            {
                            apirec->APImsg=JAMAPIMSG_NOMOREMSGS;
                            return (0);
                            }
                        else
                            WhatMsg--;
                        }
                    }
                }
            else
                /* All subfield data won't fit, do segmented read/calls */
                {
                ReadBytes=0L;
                MaxBlockToRead=(INT32)apirec->WorkLen;

                do
                    {
                    if (apirec->ReadFunc(apirec, apirec->HdrHandle, &apirec->WorkBuf, MaxBlockToRead)!=MaxBlockToRead)
                        {
                        apirec->APImsg=JAMAPIMSG_CANTRDFILE;
                        return (0);
                        }

                    if (MaxBlockToRead>0L)
                        UserResult=UserCompare(apirec);

                    ReadBytes+=MaxBlockToRead;
                    if ((INT32)(apirec->Hdr.SubfieldLen-ReadBytes)<MaxBlockToRead)
                        MaxBlockToRead=(INT32)(apirec->Hdr.SubfieldLen-ReadBytes);
                    }
                while (ReadBytes<apirec->Hdr.SubfieldLen &&
                            MaxBlockToRead>0L &&
                                UserResult==ScanMsgHdrDiscard);

                /* We've read all subfield data or got told to proceed */

                if (UserResult==ScanMsgHdrStop)
                    {
                    return (1);
                    }
                else
                    {
                    if (ScanFwd)
                        WhatMsg++;
                    else
                        {
                        if (WhatMsg==apirec->HdrInfo.BaseMsgNum)
                            {
                            apirec->APImsg=JAMAPIMSG_NOMOREMSGS;
                            return (0);
                            }
                        else
                            WhatMsg--;
                        }
                    }
                }
            }
        else
            {
            /* Check for end of file, otherwise error */
            if (JunkL==0L && ScanFwd)
                apirec->APImsg=JAMAPIMSG_NOMOREMSGS;
            else 
                apirec->APImsg=JAMAPIMSG_CANTRDFILE;
            return (0);
            }
        }/*while*/

    /* Dummy return to avoid warnings from some compilers */
    return (0);
}

/*
**  Scan message index records starting at the specified number (STARTNUM).
**  For each record found, the function calls USERCOMPARE. The ScanFwd
**  parameter determines the direction of the scan. The Idx record will
**  contain the newly read index record. Returns 1 if user function returned
**  ScanMsgHdrStop and FALSE otherwise.
*/
int _JAMPROC JAMmbScanForMsgIdx(JAMAPIRECptr apirec, UINT32 WhatMsg,
                        int ScanFwd, ScanMsgIdxComp UserCompare)
{
    int   UserResult;
    INT32 WhatOffset, ReadCount;

    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Make sure the message number is valid */
    if (WhatMsg<apirec->HdrInfo.BaseMsgNum)
        {
        apirec->APImsg=JAMAPIMSG_INVMSGNUM;
        return (0);
        }

    WhatOffset=(INT32)((WhatMsg-apirec->HdrInfo.BaseMsgNum) * (INT32)sizeof(JAMIDXREC));

    /* Seek to position if we're going forward */
    if (ScanFwd)
        {
        if (apirec->SeekFunc(apirec, apirec->IdxHandle, JAMSEEK_SET, WhatOffset)!=WhatOffset)
            {
            apirec->APImsg=JAMAPIMSG_SEEKERROR;
            return (0);
            }
        }

    /* Fetch index records */
    while (1)
        {
        /* Seek to position if we're going backward */
        if (!ScanFwd)
            {
            if (apirec->SeekFunc(apirec, apirec->IdxHandle, JAMSEEK_SET, WhatOffset)!=WhatOffset)
                {
                apirec->APImsg=JAMAPIMSG_SEEKERROR;
                return (0);
                }
            }

        ReadCount=apirec->ReadFunc(apirec, apirec->IdxHandle, &apirec->Idx, (INT32)sizeof(JAMIDXREC));
        if (ReadCount==(INT32)sizeof(JAMIDXREC))
            {
            apirec->LastMsgNum=WhatMsg;

            /* Call user function and process result */
            UserResult=UserCompare(apirec);
            if (UserResult==ScanMsgIdxStop)
                {
                return (1);
                }
            else
                {
                if (ScanFwd)
                    WhatMsg++;
                else
                    {
                    if (WhatMsg==apirec->HdrInfo.BaseMsgNum)
                        {
                        apirec->APImsg=JAMAPIMSG_NOMOREMSGS;
                        return (0);
                        }
                    else
                        {
                        WhatMsg--;
                        WhatOffset-=(INT32)sizeof(JAMIDXREC);
                        }
                    }
                }
            }
        else
            {
            /* Check for end of file, otherwise error */
            if (ReadCount==0L && ScanFwd)
                apirec->APImsg=JAMAPIMSG_NOMOREMSGS;
            else 
                apirec->APImsg=JAMAPIMSG_CANTRDFILE;
            return (0);
            }
        }/* while */

    /* Dummy return to avoid warnings from some compilers */
    return (0);
}

/* end of file "jamscan.c" */
