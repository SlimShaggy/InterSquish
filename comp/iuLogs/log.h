//------------------------------------------------------------------------------
#ifndef LogH
#define LogH
#include <stdio.h>
#include <dir.h>
#include <time.h>
#include <windows.h>
#include <sysutils.hpp>
//------------------------------------------------------------------------------
#ifdef _DEBUG
class PACKAGE TLog
{
private:
static  FILE *fLog;
static int InstanceCount;
public:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  __fastcall TLog(char *LogFileName)
  {
    if(!fLog)
    {
      fLog=fopen(LogFileName,"a+");
      if(!fLog)
        throw Exception("Unable open/create a log file");
        fputs("\n\n", fLog);
        Write(__LINE__,__FILE__,"Trace system started");
//      fputs("Trace system started\n", fLog);
    }
    InstanceCount++;
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  __fastcall ~TLog(void)
  {
    InstanceCount--;
    if(!InstanceCount)
      fclose(fLog);
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static  inline void __fastcall Write(int Line, char *ModuleName, char *Message="")
{// Example:   14.08.2000 12:19:37 [1268]....
  if(fLog)
  {
    char cWorkBuff[1024];
    char cShortModuleName[MAXDIR+MAXEXT];
    char cExt[MAXEXT];
    SYSTEMTIME systime;

    GetLocalTime(&systime);

      fnsplit(ModuleName,cWorkBuff,cWorkBuff,cShortModuleName,cExt);
      strcat(cShortModuleName,cExt);
//      sprintf(cWorkBuff,"%2.2u.%2.2u.%4.4u %2.2u:%2.2u:%2.2u:%03.3u [%u] %u %-2.64s %-16.255s\n",
//      systime.wDay,systime.wMonth,systime.wYear,
//      systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds,
//      GetCurrentThreadId(),Line,cShortModuleName,Message);
//      fputs(cWorkBuff, fLog);
      fflush(fLog);
      Sleep(0);
    }
  }
};
//#define TraceD(LogObject, Message) (TLol->Write(__LINE__,__FILE__,Message))
#define TraceS(Message) (TLog::Write(__LINE__,__FILE__,Message))
#else
#define TraceS(Message)
#endif
//------------------------------------------------------------------------------
//FILE * TLog::fLog=NULL;
//int TLog::InstanceCount=0;
//------------------------------------------------------------------------------
#endif

