/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Joaquim Homrighausen.
**
**  ----------------------------------------------------------------------
**
**  jamstore.c (JAMmb)
**
**  Store messages and texts
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    JoHo
**  Initial coding. No encryption or escaping supported yet.
*/
#define JAMCAPI 1

#include <string.h>
#include "jammb.h"

/*
**  Store message header with specified number. Returns 1 upon success
**  and 0 upon failure. The HdrHandle's file offset will point to the
**  end of the fixed-length header when the function returns (if
**  successful) so the application can write any subfields directly to
**  the file.
*/
int _JAMPROC JAMmbStoreMsgHdr(JAMAPIRECptr apirec, UINT32 WhatMsg)
{
    /* Fetch index record, checks for IsOpen and valid msg number */
    if (!JAMmbFetchMsgIdx(apirec, WhatMsg))
        return (0);

    /* Make sure it's locked */
    if (!apirec->HaveLock)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTLOCKED;
        return (0);
        }

    /* Update structure, even if below fails */
    apirec->Hdr.MsgNum=WhatMsg;

    /* Make sure subfield len is has the correct length, if the platform */
    /* requires alignment */
    apirec->Hdr.SubfieldLen=JAMsysAlign(apirec->Hdr.SubfieldLen);

    /* Make sure header signature and revision is OK */
    strcpy(apirec->Hdr.Signature, HEADERSIGNATURE);
    apirec->Hdr.Revision=CURRENTREVLEV;

    /* Write header */
    if (apirec->SeekFunc(apirec, apirec->HdrHandle, JAMSEEK_SET, (INT32)apirec->Idx.HdrOffset)!=(INT32)apirec->Idx.HdrOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }
    if (apirec->WriteFunc(apirec, apirec->HdrHandle, &apirec->Hdr, (INT32)sizeof(JAMHDR))!=(INT32)sizeof(JAMHDR))
        {
        apirec->APImsg=JAMAPIMSG_CANTWRFILE;
        return (0);
        }

    /* Wrote it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/*
**  Store message index record with specified number. Returns 1 upon
**  success and 0 upon failure. The IdxHandle's file offset will point
**  to the end of the fixed-length index record when the function
**  returns (if successful).
*/
int _JAMPROC JAMmbStoreMsgIdx(JAMAPIRECptr apirec, UINT32 WhatMsg)
{
    INT32 WhatOffset;

    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Make sure it's locked */
    if (!apirec->HaveLock)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTLOCKED;
        return (0);
        }

    /* Make sure the message number is valid */
    if (WhatMsg<apirec->HdrInfo.BaseMsgNum)
        {
        apirec->APImsg=JAMAPIMSG_INVMSGNUM;
        return (0);
        }

    /* Store index record */
    WhatOffset=(INT32)((WhatMsg-apirec->HdrInfo.BaseMsgNum) * (INT32)sizeof(JAMIDXREC));
    if (apirec->SeekFunc(apirec, apirec->IdxHandle, JAMSEEK_SET, WhatOffset)!=WhatOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }
    if (apirec->WriteFunc(apirec, apirec->IdxHandle, &apirec->Idx, (INT32)sizeof(JAMIDXREC))!=(INT32)sizeof(JAMIDXREC))
        {
        apirec->APImsg=JAMAPIMSG_CANTWRFILE;
        return (0);
        }

    /* Wrote it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/*
**  Store message text at current header's text position. Returns 1 upon
**  success and 0 upon failure. The TxtHandle's file offset will point to
**  the end of the written text block when the function returns (if
**  successful). This assumes that the entire message text is stored in
**  the internal buffer. See JAMMBSTOREMSGTXTBUF() for a function that
**  takes an external parameter and length specifier.
*/
int _JAMPROC JAMmbStoreMsgTxt(JAMAPIRECptr apirec)
{
    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Make sure it's locked */
    if (!apirec->HaveLock)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTLOCKED;
        return (0);
        }

    /* Write text */
    if (apirec->SeekFunc(apirec, apirec->TxtHandle, JAMSEEK_SET, (INT32)apirec->Hdr.TxtOffset)!=(INT32)apirec->Hdr.TxtOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }
    if (apirec->WriteFunc(apirec, apirec->TxtHandle, apirec->WorkBuf, (INT32)apirec->Hdr.TxtLen)!=(INT32)apirec->Hdr.TxtLen)
        {
        apirec->APImsg=JAMAPIMSG_CANTWRFILE;
        return (0);
        }

    /* Wrote it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/*
**  Store message text at current header's text position. Returns 1 upon
**  success and 0 upon failure. The TxtHandle's file offset will point to
**  the end of the written text block when the function returns (if
**  successful). The ISFIRST parameter determines if the function should
**  seek to the position specified in the header before writing. This
**  allows multiple calls to write large message texts.
*/
int _JAMPROC JAMmbStoreMsgTxtBuf(JAMAPIRECptr apirec, CHAR8ptr Buffer,
                                  INT32 BufLen, int IsFirst)
{
    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Make sure it's locked */
    if (!apirec->HaveLock)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTLOCKED;
        return (0);
        }

    /* Seek if we're told to */
    if (IsFirst)
        {
        if (apirec->SeekFunc(apirec, apirec->TxtHandle, JAMSEEK_SET, (INT32)apirec->Hdr.TxtOffset)!=(INT32)apirec->Hdr.TxtOffset)
            {
            apirec->APImsg=JAMAPIMSG_SEEKERROR;
            return (0);
            }
        }

    /* Write the text */
    if (apirec->WriteFunc(apirec, apirec->TxtHandle, Buffer, BufLen)!=BufLen)
        {
        apirec->APImsg=JAMAPIMSG_CANTWRFILE;
        return (0);
        }

    /* Wrote it OK */
    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/* end of file "jamstore.c" */
