/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Joaquim Homrighausen.
**
**  ----------------------------------------------------------------------
**
**  jamlread.c (JAMmb)
**
**  LastRead handling
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    JoHo
**  Initial coding.
*/
#define JAMCAPI 1

#include "jammb.h"

/*
**  Fetch LastRead for passed UserID. Returns 1 upon success and 0 upon
**  failure.
*/
int _JAMPROC JAMmbFetchLastRead(JAMAPIRECptr apirec, UINT32 UserID)
{
    INT32 ReadCount;
    UINT32 LastReadRec;

    /* Make sure it's open */
    if (!apirec->isOpen)
        {
        apirec->APImsg=JAMAPIMSG_ISNOTOPEN;
        return (0);
        }

    /* Seek to beginning of file */
    if (apirec->SeekFunc(apirec, apirec->LrdHandle, JAMSEEK_SET, 0L)!=0L)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }

    /* Read file from top to bottom */
    LastReadRec=0L;
    while (1)
        {
        ReadCount=apirec->ReadFunc(apirec, apirec->LrdHandle, &apirec->LastRead, (INT32)sizeof(JAMLREAD));
        if (ReadCount!=(INT32)sizeof(JAMLREAD))
            {
            if (!ReadCount)
                /* End of file */
                apirec->APImsg=JAMAPIMSG_CANTFINDUSER;
            else
                /* Read error */
                apirec->APImsg=JAMAPIMSG_CANTRDFILE;
            return (0);
            }

        /* See if it matches what we want */
        if (apirec->LastRead.UserID==UserID)
            {
            apirec->LastLRDnum=LastReadRec;
            apirec->APImsg=JAMAPIMSG_NOTHING;
            return (1);
            }

        /* Next record number */
        LastReadRec++;
        }/*while*/

    /* Dummy return to avoid warnings from some compilers */
    return (0);
}

/*
**  Store LastRead record and if successful, optionally updates the header
**  info block (and its ModCounter) at the beginning of the header file.
**  Returns 1 upon success and 0 upon failure.
*/
int _JAMPROC JAMmbStoreLastRead(JAMAPIRECptr apirec, int UpdateHdrInfo)
{
    INT32 UserOffset;

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

    /* Seek to the appropriate position */
    UserOffset=(INT32)(apirec->LastLRDnum * (INT32)sizeof(JAMLREAD));
    if (apirec->SeekFunc(apirec, apirec->LrdHandle, JAMSEEK_SET, UserOffset)!=UserOffset)
        {
        apirec->APImsg=JAMAPIMSG_SEEKERROR;
        return (0);
        }

    /* Write record */
    if (apirec->WriteFunc(apirec, apirec->LrdHandle, &apirec->LastRead, (INT32)sizeof(JAMLREAD))!=(INT32)sizeof(JAMLREAD))
        {
        apirec->APImsg=JAMAPIMSG_CANTWRFILE;
        return (0);
        }

    /* Update header info if told to */
    if (UpdateHdrInfo && !JAMmbUpdateHeaderInfo(apirec, 1))
        return (0);

    apirec->APImsg=JAMAPIMSG_NOTHING;
    return (1);
}

/* end of file "jamlread.c" */
