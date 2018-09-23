/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Joaquim Homrighausen.
**
**  ----------------------------------------------------------------------
**
**  jamfield.c (JAMmb)
**
**  Subfield functions
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    JoHo
**  Initial coding. No decryption or unescaping supported yet.
*/
#define JAMCAPI 1

#include "jammb.h"
#include <string.h>

/*
**  Find specified field in passed buffer. It requires that POSITION has
**  been reset to zero (0) prior to the first call. the POSITION parameter
**  is updated to point to the beginning of the found field.
**  Returns 1 if the field is found and 0 if the field is not found.
*/
int _JAMPROC JAMmbFindField(JAMAPIRECptr apirec, UINT32 WhatField, UINT32ptr Position)
{
    *Position=JAMsysAlign(*Position);
    while (1)
        {
        apirec->SubFieldPtr=(JAMSUBFIELD *) JAMsysAddPtr(apirec->WorkBuf, *Position);
        if (apirec->SubFieldPtr->LoID==(UINT16)WhatField)
            /* Found it */
            return (1);
        else
            /* Get next subfield */
            {
            *Position+=(apirec->SubFieldPtr->DatLen+(UINT32)sizeof(JAMSUBFIELD));
            *Position=JAMsysAlign(*Position);
            if (*Position>=apirec->WorkLen)
                return (0);
            }
        }/*while*/

    /* Dummy return to avoid warnings from some compilers */
    return (0);
}

/*
**  Add specified field to WorkBuf. It requires that POSITION has been
**  reset to zero (0) prior to the first call. The POSITION parameter is
**  updated to point to the first position after the newly added field.
**  The FIRST parameter determines if the DatLen/ID fields should be
**  copied. This allows multiple calls to this function to add more than
**  64kb to a subfield. Returns 1 on success or 0 if the requested field
**  does not fit into WorkBuf
*/
int _JAMPROC JAMmbAddField(JAMAPIRECptr apirec, UINT32 WhatField,
                            int First, unsigned int DatLen,
                            UINT32ptr Position, CHAR8ptr Data)
{
    if (First)
        {
        *Position=JAMsysAlign(*Position);
        if (((UINT32)sizeof(JAMBINSUBFIELD)+(*Position)+DatLen)>apirec->WorkLen)
            return (0);
        apirec->SubFieldPtr=(JAMSUBFIELD *)JAMsysAddPtr(apirec->WorkBuf,*Position);
        apirec->SubFieldPtr->LoID=(UINT16)WhatField;
        apirec->SubFieldPtr->HiID=0;
        apirec->SubFieldPtr->DatLen=0L;
        *Position+=(UINT32)sizeof(JAMBINSUBFIELD);
        }
    else
        {
        if ((DatLen+(*Position))>apirec->WorkLen)
            return (0);
        }

    memcpy(JAMsysAddPtr(apirec->WorkBuf,*Position), Data, DatLen);
    apirec->SubFieldPtr->DatLen+=DatLen;
    *Position+=(UINT32)DatLen;
    return (1);
}

/* end of file "jamfield.c" */
