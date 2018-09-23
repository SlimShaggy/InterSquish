/*
**  JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
**
**  C API
**
**  Written by Mats Wallin
**
**  ----------------------------------------------------------------------
**
**  jamsys.c (JAMmb)
**
**  Platform/compiler dependant functions
**
**  See jamsys.h for information about assumptions made about compilers
**  and platforms
**
**  Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
**  Mats Wallin. ALL RIGHTS RESERVED.
**
**  93-06-28    MW
**  Initial coding
*/
#define JAMCAPI 1

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__MSDOS__) || defined(_WINDOWS)
    #include <fcntl.h>
    #include <io.h>
    #include <share.h>
    #include <dos.h>
#endif

#if defined(__TURBOC__) || defined(__BORLANDC__) || \
        defined(__ZTC__) || defined(_MSC_VER) || defined(_QC)
    #include <sys\types.h>
    #include <sys\stat.h>
#endif

#if defined(__ZTC__) || defined(_MSC_VER) || defined(_QC)
    #include <sys\locking.h>
#endif

#if defined(__TSC__)
    #include <stat.h>
    #include <locking.h>
#endif

#if defined(__sparc__)
    #include <fcntl.h>
    #include <sys/file.h>
    #include <memory.h>
    #include <sys/time.h>
#endif

#if defined(__50SERIES)
    #define unlink delete
#endif

#if defined(_MSC_VER)
    #define locking _locking
    #define unlink  _unlink
#endif

#include "jammb.h"

/*
**  Number of days since January 1, the 1st of each month
*/
static int _mdays [13] =
            {
/* Jan */   0,
/* Feb */   31,
/* Mar */   31+28,
/* Apr */   31+28+31,
/* May */   31+28+31+30,
/* Jun */   31+28+31+30+31,
/* Jul */   31+28+31+30+31+30,
/* Aug */   31+28+31+30+31+30+31,
/* Sep */   31+28+31+30+31+30+31+31,
/* Oct */   31+28+31+30+31+30+31+31+30,
/* Nov */   31+28+31+30+31+30+31+31+30+31,
/* Dec */   31+28+31+30+31+30+31+31+30+31+30,
/* Jan */   31+28+31+30+31+30+31+31+30+31+30+31
            };

/*
**  JAMsysInitApiRec
**
**  Initializes the JAMAPIREC structure with all needed information
**
**      Parameters:     JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                      CHAR8ptr pFile      - Name of JAM messagebase
**                      UINT32 Size         - Size of workbuffer to allocate
**
**         Returns:     0                   - Failure to allocate workbuffer
**                      1                   - Success
*/
int _JAMPROC JAMsysInitApiRec(JAMAPIRECptr apirec, CHAR8ptr pFile, UINT32 Size)
{
    memset(apirec, 0, sizeof(JAMAPIREC));

#if defined(_WINDOWS)
        {
        HGLOBAL   hMem;

        if ((hMem = GlobalAlloc (GPTR, Size)) != (HGLOBAL) NULL)
            if ((apirec->WorkBuf = GlobalLock (hMem)) == NULL)
                GlobalFree (hMem);
        }
#else
    apirec->WorkBuf=malloc((unsigned int)Size);
#endif
    if (apirec->WorkBuf==NULL)
        return (0);

    strcpy(apirec->BaseName, pFile);
    apirec->WorkLen=Size;

    apirec->HdrHandle=
        apirec->TxtHandle=
            apirec->IdxHandle=
                apirec->LrdHandle=-1;

    apirec->CreateFunc = JAMsysCreate;
    apirec->OpenFunc   = JAMsysOpen;
    apirec->CloseFunc  = JAMsysClose;
    apirec->ReadFunc   = JAMsysRead;
    apirec->WriteFunc  = JAMsysWrite;
    apirec->SeekFunc   = JAMsysSeek;
    apirec->LockFunc   = JAMsysLock;
    apirec->UnlinkFunc = JAMsysUnlink;

#if defined(_WINDOWS)
        {
        UINT16  WinVer;

        WinVer = LOWORD (GetVersion ());
        if (LOBYTE (WinVer) > 3 ||
            (LOBYTE (WinVer) == 3 && HIBYTE (WinVer) >= 10))
            {
            apirec->ReadFunc  = JAMsysReadHuge;
            apirec->WriteFunc = JAMsysWriteHuge;
            }
        }
#endif

    return (1);
}

/*
**  JAMsysDeinitApiRec
**
**  Deinitializes the JAMAPIREC structure. If the message base still is
**  opened, it is closed
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**
**         Returns:   0                   - Failure to allocate workbuffer
**                    1                   - Success
*/
int _JAMPROC JAMsysDeinitApiRec(JAMAPIRECptr apirec)
{
    /*This will release any locks we might has as well*/
    if (apirec->isOpen)
        JAMmbClose(apirec);

    if (apirec->WorkBuf!=NULL)
        {
#if defined(_WINDOWS)
        HGLOBAL     hMem;

        hMem = (HGLOBAL) LOWORD (GlobalHandle (SELECTOROF (apirec->WorkBuf)));
        GlobalUnlock (hMem);
        GlobalFree (hMem);
#else
        free(apirec->WorkBuf);
#endif
        }

    apirec->WorkBuf=NULL;
    apirec->WorkLen=0L;

    apirec->BaseName[0]='\0';

    return (1);
}

/*
**  JAMsysClose
**
**  Closes the specified filehandle
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle
**
**         Returns:   0 on success, or -1 in the case of an error
*/
int _JAMPROC JAMsysClose(JAMAPIRECptr apirec, FHANDLE fh)
{
#if defined(_WINDOWS)
    if (_lclose(fh)==HFILE_ERROR)
#elif defined(__MSDOS__) && \
        (defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__))
    if (_close(fh)<0)
#else
    if (close(fh)<0)
#endif
        {
        if (apirec)
            apirec->Errno=errno;
        return (-1);
        }

    return (0);
}

/*
**  JAMsysCreate
**
**  Creates the specified file, closes it, and then reopens it in the
**  correct mode.
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    CHAR8ptr pFileName  - Name of file to create
**
**         Returns:   The filehandle when successful, -1 if it fails
*/
FHANDLE _JAMPROC JAMsysCreate(JAMAPIRECptr apirec, CHAR8ptr pFileName)
{
    FHANDLE fh;

#if defined(__50SERIES)
    fh=creat(pFileName, 2);
#elif defined(_WINDOWS)
    fh=_lcreat(pFileName, 0);
#elif defined(__MSDOS__) && \
        (defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__))
    fh=_creat(pFileName, 0);
#else
    fh=creat(pFileName, S_IREAD|S_IWRITE);
#endif
    if (fh<0)
        {
        if (apirec)
            apirec->Errno = errno;
        return (-1);
        }

    if (JAMsysClose(apirec, fh)<0)
        return (-1);

#if defined(__sparc__) || defined(__50SERIES)
    return (fh);
#else
    return (JAMsysOpen(apirec, pFileName));
#endif
}

/*
**  JAMsysLock
**
**  Sets or resets the lock on the JAM messagebase. This is done with
**  a lock on the first byte in the header file
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    int DoLock          - 1 if messagebase should be locked
**                                        - 0 to unlock messagebase
**
**         Returns:   0 on success, and -1 on failure
*/
int _JAMPROC JAMsysLock(JAMAPIRECptr apirec, int DoLock)
{
#if defined(__MSDOS__) || defined(_WINDOWS)
    #if defined(__TURBOC__) || defined(__BORLANDC__)
        int stat;

        if (DoLock)
            stat=lock(apirec->HdrHandle, 0L, 1L);
        else 
            stat=unlock(apirec->HdrHandle, 0L, 1L);

        if (stat==-1)
            apirec->Errno=errno;

        return (stat);
    #elif defined(__TSC__) || defined(__ZTC__) || \
              defined(_MSC_VER) || defined(_QC)
        int   stat;
        INT32 OldPos;

        /*Get old position*/
        OldPos=JAMsysSeek(apirec, apirec->HdrHandle, JAMSEEK_CUR, 0L);
        if (OldPos<0L)
            return (-1);

        /*Move to beginning of file*/
        if (JAMsysSeek(apirec, apirec->HdrHandle, JAMSEEK_SET, 0L)<0L)
            return (-1);

        stat=locking(apirec->HdrHandle, DoLock ? LK_NBLCK:LK_UNLCK, 1L);

        /*Restore position*/
        JAMsysSeek(apirec, apirec->HdrHandle, JAMSEEK_SET, OldPos);

        return (stat);
    #else
        #error Unsupported compiler
    #endif
#elif defined(__sparc__)
    DoLock = DoLock ? LOCK_EX : LOCK_UN;
    if (flock(apirec->HdrHandle, DoLock) == -1)
        {
        apirec->Errno = errno;
        return (-1);
        }
    return (0);
#elif defined(__50SERIES)
    return (0);
#else
    #error Unsupported platform
#endif
}

/*
**  JAMsysOpen
**
**  Opens the specified file in ReadWrite/DenyNone mode
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    CHAR8ptr pFileName  - Name of file to open
**
**         Returns:   The filehandle when successful, -1 if it fails
*/
FHANDLE _JAMPROC JAMsysOpen(JAMAPIRECptr apirec, CHAR8ptr pFileName)
{
    FHANDLE fh;

    fh=JAMsysSopen (apirec, pFileName, JAMO_RDWR, JAMSH_DENYNO);
    return (fh);
}

/*
**  JAMsysRead
**
**  Reads the specified number of bytes from the specified filehandle
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle of file to read from
**                    VOIDptr pBuf        - Buffer where read data are stored
**                    INT32               - Number of bytes to read
**
**         Returns: The number of bytes read, or -1 in the case of error
**
**  NOTE! In small and medium memory model, the maximum size that can
**        be read is 0xFF00 bytes
*/
INT32 _JAMPROC JAMsysRead(JAMAPIRECptr apirec, FHANDLE fh, VOIDptr pBuf, INT32 Len)
{
    INT32       TotalRead = 0;

#if defined(__MSDOS__) || defined(_WINDOWS)
    UCHAR8    * Ptr       = pBuf;

    while(Len)
        {
        UINT16  ToRead,
                BytesRead;

        ToRead = (UINT16) ((Len > 0xFF00L) ? 0xFF00u : (UINT16) Len);

#if defined(_WINDOWS)
        if((BytesRead = (UINT16) _lread(fh, Ptr, ToRead)) == (UINT16) HFILE_ERROR)
#elif defined(__MSDOS__) && \
          (defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__))
        if((BytesRead = (UINT16) _read(fh, Ptr, ToRead)) == (UINT16) -1)
#else
        if((BytesRead = (UINT16) read(fh, Ptr, ToRead)) == (UINT16) -1)
#endif
            {
            if (apirec)
                apirec->Errno = errno;
            return(-1);
            }

        TotalRead += BytesRead;
        if(BytesRead != ToRead)
            return(TotalRead);

#if defined(__SMALL__) || defined(__MEDIUM__)
        return(TotalRead);
#else
        Len -= BytesRead;
        Ptr = JAMsysAddPtr(Ptr, (INT32) BytesRead);
#endif
        }

    return(TotalRead);

#else   /* #if defined(__MSDOS__) || defined(_WINDOWS) */

    if((TotalRead = read(fh, pBuf, Len )) == -1)
        {
        if (apirec)
            apirec->Errno = errno;
        }

    return(TotalRead);

#endif  /* #ifdef __MSDOS__ */
}

#if defined(_WINDOWS)
/*
**  JAMsysReadHuge
**
**  Reads the specified number of bytes from the specified filehandle
**
**  _WINDOWS specific function
**
**  This function uses the Windows 3.1 function _hread to be able to
**  read blocks larger then 64 Kb.
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle of file to read from
**                    VOIDptr pBuf        - Buffer where read data are stored
**                    INT32               - Number of bytes to read
**
**         Returns: The number of bytes read, or -1 in the case of error
*/
INT32 _JAMPROC JAMsysReadHuge(JAMAPIRECptr apirec, FHANDLE fh, VOIDptr pBuf, INT32 Len)
{
    INT32       TotalRead;

    if((TotalRead = _hread(fh, (void _HUGE *) pBuf, Len )) == -1)
        {
        if (apirec)
            apirec->Errno = errno;
        }

    return(TotalRead);
}
#endif /* #if defined(_WINDOWS) */

/*
**  JAMsysSeek
**
**  Move the file pointer for the filehandle to the specified location.
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle
**                    int FromWhere       - From where should the seek start
**                    INT32 Offset        - Which position to seek to
**
**         Returns:   The new offset of the file pointer, from the beginning
**                    of the file, or -1L in the case of error
*/
INT32 _JAMPROC JAMsysSeek(JAMAPIRECptr apirec, FHANDLE fh, int FromWhere, INT32 Offset)
{
    INT32   NewOffset;

#if defined(_WINDOWS)
    if((NewOffset = _llseek(fh, Offset, FromWhere)) == HFILE_ERROR)
#else
    if((NewOffset = lseek(fh, Offset, FromWhere)) == -1L)
#endif
        {
        if (apirec)
            apirec->Errno = errno;
        }

    return(NewOffset);
}

/*
**  JAMsysSopen
**
**  Opens the specified file in the specified access and sharing mode
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    CHAR8ptr pFileName  - Name of file to open
**                    int AccessMode      - AccessMode
**                    int ShareMode       - ShareMode
**
**         Returns:   The filehandle when successful, -1 if it fails
*/
FHANDLE _JAMPROC JAMsysSopen(JAMAPIRECptr apirec, CHAR8ptr pFileName, int AccessMode, int ShareMode)
{
    FHANDLE fh;

#if defined(__sparc__) || defined(__50SERIES)
    fh=open(pFileName, AccessMode);
#elif defined(_WINDOWS)
    fh=_lopen(pFileName, AccessMode|ShareMode);
#elif defined(__MSDOS__) && \
        (defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__))
    fh=_open(pFileName, AccessMode|ShareMode);
#else
    fh=sopen(pFileName, AccessMode, ShareMode, S_IREAD|S_IWRITE);
#endif
    if (fh<0)
        {
        if (apirec)
            apirec->Errno=errno;
        }

    return (fh);
}

/*
**  JAMsysUnlink
**
**  Deletes the specified file
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    CHAR8PTR pFileName   - Name of file to delete
**
**         Returns:   0 if successful, -1 in the case of error
*/
int _JAMPROC JAMsysUnlink(JAMAPIRECptr apirec, CHAR8ptr pFileName)
{
    if(unlink(pFileName) == -1)
        {
        if (apirec)
            apirec->Errno = errno;
        return(-1);
        }

    return(0);
}

/*
**  JAMsysWrite
**
**  Writes the specified number of bytes from the specified filehandle
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle of file to write to
**                    VOIDptr pBuf        - Buffer with data to write
**                    INT32 Len           - Number of bytes to write
**
**         Returns:   The number of bytes written, or -1 in the case of error
**
**  NOTE! In small and medium memory model, the maximum size that can
**        be written is 0xFF00 bytes
*/
INT32 _JAMPROC JAMsysWrite(JAMAPIRECptr apirec, FHANDLE fh, VOIDptr pBuf, INT32 Len)
{
    INT32       TotalWrit = 0L;

#if defined(__MSDOS__) || defined(_WINDOWS)
    UCHAR8    * Ptr       = pBuf;

    while(Len)
        {
        UINT16  ToWrit,
                BytesWrit;

        ToWrit = (UINT16) ((Len > 0xFF00L) ? 0xFF00u : (UINT16) Len);

#if defined(_WINDOWS)
        if((BytesWrit = (UINT16) _lwrite(fh, Ptr, ToWrit)) == (UINT16) HFILE_ERROR)
#elif defined(__MSDOS__) && \
          (defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__))
        if((BytesWrit = (UINT16) _write(fh, Ptr, ToWrit)) == (UINT16) -1)
#else
        if((BytesWrit = (UINT16) write(fh, Ptr, ToWrit)) == (UINT16) -1)
#endif
            {
            if (apirec)
                apirec->Errno = errno;
            return(-1L);
            }

        TotalWrit += BytesWrit;
        if(BytesWrit != ToWrit)
            return(TotalWrit);

#if defined(__SMALL__) || defined(__MEDIUM__)
        return(TotalWrit);
#else
        Len -= BytesWrit;
        Ptr = JAMsysAddPtr(Ptr, (INT32) BytesWrit);
#endif
        }

    return(TotalWrit);

#else   /* #if defined(__MSDOS__) || defined(_WINDOWS) */

    if((TotalWrit = write(fh, pBuf, Len)) == -1)
        {
        if (apirec)
            apirec->Errno = errno;
        }
  
    return(TotalWrit);

#endif  /* #ifdef __MSDOS__ */
}

#if defined(_WINDOWS)
/*
**  JAMsysWriteHuge
**
**  Writes the specified number of bytes from the specified filehandle
**
**  _WINDOWS specific function
**
**  This function uses the Windows 3.1 function _hwrite to be able to
**  write blocks larger then 64 Kb.
**
**      Parameters:   JAMAPIRECptr apirec - Ptr to JAMAPIREC to initiate
**                    FHANDLE fh          - Filehandle of file to write to
**                    VOIDptr pBuf        - Buffer with data to write
**                    INT32 Len           - Number of bytes to write
**
**         Returns:   The number of bytes written, or -1 in the case of error
*/
INT32 _JAMPROC JAMsysWriteHuge(JAMAPIRECptr apirec, FHANDLE fh, VOIDptr pBuf, INT32 Len)
{
    INT32       TotalWrit;

    if((TotalWrit = _hwrite(fh, (void _HUGE *) pBuf, Len)) == -1)
        {
        if (apirec)
            apirec->Errno = errno;
        }
  
    return(TotalWrit);

}
#endif /* #if defined(_WINDOWS) */

#if defined(__MSDOS__)
/*
**  JAMsysAddPtr            [ When compiling in a far  data model ]
**  JAMsysAddFarPtr         [ When compiling in a near data model ]
**
**  __MSDOS__ specific function
**
**  Adds a long offset to a far (huge) pointer. Supports situations
**  when more then 0xFFFF bytes are added to the pointer.
**  The resulting pointer is "normalized", e.g. the offset part will
**  have a value between 0x0000 and 0x000F
**
**      Parameters:   void _JAMFAR * Ptr  - Ptr to increase
**                    INT32 Offset        - Offset to add to pointer
**
**         Returns:   The new pointer after the offset has been added
*/
#if defined(__SMALL__) || defined(__MEDIUM__)
void _JAMFAR * _JAMPROC JAMsysAddFarPtr(void _JAMFAR *Ptr, INT32 Offset)
#else
void _JAMFAR * _JAMPROC JAMsysAddPtr(void _JAMFAR *Ptr, INT32 Offset)
#endif
{
    INT32   lPtr;

    lPtr = ((INT32) *((UINT16 *) &Ptr)) +
           ((INT32) (*((UINT16 *) &Ptr + 1)) << 4) +
           Offset;

    return((void _JAMFAR *) (((INT32) ((UINT16) lPtr & 0x000F)) | ((lPtr & 0x000FFFF0uL) << 12)));
}
#endif  /* #if defined(__MSDOS__) */

/*
**  JAMsysTime
**
**  Calculates the number of seconds that has passed from January 1, 1970
**  until the current date and time.
**
**      Parameters:   UINT32ptr pTime     - Ptr to buffer where the number
**                                          number of seconds will be stored
**
**         Returns:   Number of seconds since 1970 to specified date/time
*/
UINT32 _JAMPROC JAMsysTime(UINT32ptr pTime)
{
#if defined(__MSDOS__) || defined(_WINDOWS)
    #if defined(__ZTC__) || defined(_MSC_VER) || defined(_QC)
        #if defined(__ZTC__)
            struct dos_date_t   d;
            struct dos_time_t   t;
        #elif defined (_MSC_VER) || defined(_QC)
            struct _dosdate_t   d;
            struct _dostime_t   t;
        #endif

        struct JAMtm  m;
        UINT32        ti;

        #if defined(__ZTC__)
            dos_getdate(&d);
            dos_gettime(&t);
        #elif defined (_MSC_VER) || defined(_QC)
            _dos_getdate(&d);
            _dos_gettime(&t);
        #endif

        m.tm_year = d.year - 1900;
        m.tm_mon  = d.month - 1;
        m.tm_mday = d.day;
        m.tm_hour = t.hour;
        m.tm_min  = t.minute;
        m.tm_sec  = t.second;
    #elif defined(__TURBOC__) || defined(__BORLANDC__) || defined(__TSC__)
        struct date   d;
        struct time   t;
        struct JAMtm  m;
        UINT32        ti;

        getdate(&d);
        gettime(&t);

        m.tm_year = d.da_year - 1900;
        m.tm_mon  = d.da_mon - 1;
        m.tm_mday = d.da_day;
        m.tm_hour = t.ti_hour;
        m.tm_min  = t.ti_min;
        m.tm_sec  = t.ti_sec;
    #endif
#elif defined(__OS2__)
          DATETIME      DT;
    struct JAMtm  m;
    UINT32        ti;

    DosGetDateTime(&DT);

    m.tm_year = DT.year - 1900;
    m.tm_mon  = DT.month - 1;
    m.tm_day  = DT.day;
    m.tm_hour = DT.hours;
    m.tm_min  = DT.minutes;
    m.tm_sec  = DT.seconds;
#endif

#if defined(__MSDOS__) || defined(_WINDOWS) || defined(__OS2__)
    ti = JAMsysMkTime(&m);
    if(pTime)
        *pTime = ti;

    return(ti);
#else
    return(time(pTime));
#endif
}

/*
**  JAMsysMkTime
**
**  Calculates the number of seconds that has passed from January 1, 1970
**  until the specified date and time.
**
**      Parameters:   JAMTMptr pTm        - Ptr to structure containing time
**
**         Returns:   Number of seconds since 1970 to specified date/time
*/
UINT32 _JAMPROC JAMsysMkTime(JAMTMptr pTm)
{
    UINT32  Days;
    int     Years;

    /*Get number of years since 1970*/
    Years = pTm->tm_year - 70;

    /*Calculate number of days during these years,*/
    /*including extra days for leap years         */
    Days = Years * 365 + ((Years + 1) / 4);

    /*Add the number of days during this year*/
    Days += _mdays [pTm->tm_mon] + pTm->tm_mday - 1;
    if((pTm->tm_year & 3) == 0 && pTm->tm_mon > 1)
        Days++;

    /*Convert to seconds, and add the number of seconds this day*/
    return(((UINT32) Days * 86400L) + ((UINT32) pTm->tm_hour * 3600L) +
           ((UINT32) pTm->tm_min * 60L) + (UINT32) pTm->tm_sec);
}

/*
**  JAMsysLocalTime
**
**  Converts the specified number of seconds since January 1, 1970, to
**  the corresponding date and time.
**
**      Parameters:   UINT32ptr pt        - Number of seconds since Jan 1, 1970
**
**         Returns:   Ptr to struct JAMtm area containing date and time
*/
JAMTMptr _JAMPROC JAMsysLocalTime(UINT32ptr pt)
{
    static struct JAMtm   m;
    INT32                 t = *pt;
    int                   LeapDay;

    m.tm_sec  = (int) (t % 60); t /= 60;
    m.tm_min  = (int) (t % 60); t /= 60;
    m.tm_hour = (int) (t % 24); t /= 24;
    m.tm_wday = (int) ((t + 4) % 7);

    m.tm_year = (int) (t / 365 + 1);
    do
        {
        m.tm_year--;
        m.tm_yday = (int) (t - m.tm_year * 365 - ((m.tm_year + 1) / 4));
        }
    while(m.tm_yday < 0);
    m.tm_year += 70;

    LeapDay = ((m.tm_year & 3) == 0 && m.tm_yday >= _mdays [2]);

    for(m.tm_mon = m.tm_mday = 0; m.tm_mday == 0; m.tm_mon++)
        if(m.tm_yday < _mdays [m.tm_mon + 1] + LeapDay)
            m.tm_mday = m.tm_yday + 1 - (_mdays [m.tm_mon] + (m.tm_mon != 1 ? LeapDay : 0));

    m.tm_mon--;

    m.tm_isdst = -1;

    return(&m);
}

#if defined(_WINDOWS)
/*
**  LibMain
**
**  Called by the Windows DLL startup code
**
**      Parameters:   HANDLE hInst      - DLL instance handle
**                    WORD wDataSeg     - ?
**                    WORD cbHeapSize   - Size of the heap
**                    LPSTR lpszCmdLine - Command line used when loading DLL
**
**         Returns:   TRUE to continue, FALSE to abort load of DLL
*/
#if defined (__BORLANDC__)
#pragma warn -par
#endif
int FAR PASCAL LibMain( HANDLE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine )
{
/*
**  Unlock the data segment, that LocalInit() locks
**  (LocalInit() is called from the assembler routine LibEntry()
*/
  if( cbHeapSize != 0 )
    UnlockData( 0 );

  return( TRUE );           /* Return success */
}
#if defined (__BORLANDC__)
#pragma warn .par
#endif

/*
**  WEP
**
**  Called by Windows when DLL is unloaded
**
**      Parameters:   int nParameter    - Reason to unload DLL
**
**         Returns:   TRUE
*/
#if defined (__BORLANDC__)
#pragma warn -par
#endif
int _JAMFAR _PASCAL _EXPORT WEP( int nParameter )
{
  return( TRUE );
}
#if defined (__BORLANDC__)
#pragma warn .par
#endif

#endif /* #if defined(_WINDOWS) */

/* end of file "jamsys.c" */
