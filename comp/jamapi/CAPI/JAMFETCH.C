/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Joaquim Homrighausen.
**
**  ----------------------------------------------------------------------
**
**  jamfetch.c (JAMmb)
**
**  Fetch messages and texts
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    JoHo
**  Initial coding. No decryption or unescaping supported yet.
*/
#define JAMCAPI 1

#include <string.h>
#include "jammb.h"

/*
**  Fetch specified message number. Returns 1 upon success and 0 upon
**  failure.
*/
int _JAMPROC JAMmbFetchMsgHdr(JAMAPIRECptr apirec, UINT32 WhatMsg, int WithSubFields)
{
    INT32 ReadCount;

    /* Fetch index record, checks for IsOpen */
    if (!JAMmbFetchMsgIdx(apirec, WhatMsg))
        return (0);

    /* Fetch header */
    if (apirec->SeekFunc(apirec, apirec->HdrHandle, JAMSEEK_SET, (INT32)apirec->Idx.HdrOffset)!=(INT32)apirec->Idx.HdrOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }
    if (apirec->ReadFunc(apirec, apirec->HdrHandle, &apirec->Hdr, (INT32)sizeof(JAMHDR))!=(INT32)sizeof(JAMHDR))
        {
        apirec->APImsg=JAMAPIMSG_CANTRDFILE;
        return (0);
        }

    /* Check header */
    if (strcmp(apirec->Hdr.Signature, HEADERSIGNATURE)!=0)
        {
        apirec->APImsg=JAMAPIMSG_BADHEADERSIG;
        return (0);
        }
    if (apirec->Hdr.Revision!=CURRENTREVLEV)
        {
        apirec->APImsg=JAMAPIMSG_BADHEADERREV;
        return (0);
        }

    /* Fetch subfields if told to */
    if (WithSubFields)
        {
        if (apirec->Hdr.SubfieldLen>apirec->WorkLen)
            ReadCount=(INT32)apirec->WorkLen;
        else
            ReadCount=(INT32)apirec->Hdr.SubfieldLen;
        }
    else
        ReadCount=0L;

    if (ReadCount)
        {
        if (apirec->ReadFunc(apirec, apirec->HdrHandle, apirec->WorkBuf, ReadCount)!=ReadCount)
            {
            apirec->APImsg=JAMAPIMSG_CANTRDFILE;
            return (0);
            }
        }

    /* Got it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/*
**  Fetch index record with specified message number. Returns 1 upon success
**  and 0 upon failure.
*/
int _JAMPROC JAMmbFetchMsgIdx(JAMAPIRECptr apirec, UINT32 WhatMsg)
{
    INT32 WhatOffset;

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

    /* Fetch index record */
    WhatOffset=(INT32)((WhatMsg-apirec->HdrInfo.BaseMsgNum) * (INT32)sizeof(JAMIDXREC));
    if (apirec->SeekFunc(apirec, apirec->IdxHandle, JAMSEEK_SET, WhatOffset)!=WhatOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }
    if (apirec->ReadFunc(apirec, apirec->IdxHandle, &apirec->Idx, (INT32)sizeof(JAMIDXREC))!=(INT32)sizeof(JAMIDXREC))
        {
        apirec->APImsg=JAMAPIMSG_CANTRDFILE;
        return (0);
        }

    /* Update structure, even if below fails */
    apirec->LastMsgNum=WhatMsg;

    /* Got it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/*
**  Fetch message following APIREC->LastMsgNum. Returns 1 upon success and
**  0 upon failure.
*/
int _JAMPROC JAMmbFetchNextMsgHdr(JAMAPIRECptr apirec, int WithSubFields)
{
    return (JAMmbFetchMsgHdr(apirec, (apirec->LastMsgNum+1L), WithSubFields));
}

/*
**  Fetch message preceding APIREC->LastMsgNum. Returns 1 upon success and
**  0 upon failure.
*/
int _JAMPROC JAMmbFetchPrevMsgHdr(JAMAPIRECptr apirec, int WithSubFields)
{
    if (apirec->LastMsgNum)
        {
        return (JAMmbFetchMsgHdr(apirec, (apirec->LastMsgNum-1L), WithSubFields));
        }
    else
        {
        apirec->APImsg=JAMAPIMSG_FIRSTMSG;
        return (0);
        }
}

/*
**  Fetch text for specified message number. Returns 1 upon success and
**  0 upon failure. FirstFetch determines if the function seeks to the
**  actual text position or simply keeps reading.
*/
int _JAMPROC JAMmbFetchMsgTxt(JAMAPIRECptr apirec, int FirstFetch)
{
    INT32 RemainToRead, ReadCount;

    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Seek to appropriate text position if this is first fetch */
    if (FirstFetch)
        {
        if (apirec->SeekFunc(apirec, apirec->TxtHandle, JAMSEEK_SET, (INT32)apirec->Hdr.TxtOffset)!=(INT32)apirec->Hdr.TxtOffset)
            {
            apirec->APImsg=JAMAPIMSG_SEEKERROR;
            return (0);
            }
        else
            /* Haven't read anything yet */
            apirec->WorkPos=0L;
        }

    /* Make sure we don't read more than we have */
    if (apirec->WorkPos>=apirec->Hdr.TxtLen)
        {
        apirec->APImsg=JAMAPIMSG_NOMORETEXT;
        return (1);
        }

    /* Figure out how much to get */
    RemainToRead=(INT32)(apirec->Hdr.TxtLen-apirec->WorkPos);
    if ((INT32)RemainToRead>(INT32)apirec->WorkLen)
        ReadCount=apirec->WorkLen;
    else
        ReadCount=RemainToRead;

    /* Get it from disk */
    if (apirec->ReadFunc(apirec, apirec->TxtHandle, apirec->WorkBuf, ReadCount)!=ReadCount)
        {
        apirec->APImsg=JAMAPIMSG_CANTRDFILE;
        return (0);
        }

    /* Update how much data we've read */
    apirec->WorkPos+=(UINT32)ReadCount;
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/* end of file "jamfetch.c" */
