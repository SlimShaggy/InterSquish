#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#include <forms.hpp>
#include <stdio.h>
#include "log.h"
#include "isControlWindow.h"

#define App    Forms::Application
#define SrvApp Svcmgr::Application
USEFORM("isNNTP.cpp", ISsNNTP);
USEFORM("isControlWindow.cpp", fDisplay);
USEFORM("isSMTP.cpp", ISsSMTP);
USEFORM("isPOP3.cpp", ISsPOP3);
//---------------------------------------------------------------------------
#ifdef _DEBUG
//USELIB("d:\Program Files\Borland\CBuilder5\Projects\Lib\iuUtils.lib");
#endif
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
TSysCharSet SwitchSyms;
#ifdef _DEBUG
TLog *isDebugLog=0;
#endif
  SwitchSyms<<'/';
  SwitchSyms<<'-';
  DecimalSeparator='.';
  ShortMonthNames[0]="Jan";
  ShortMonthNames[1]="Feb";
  ShortMonthNames[2]="Mar";
  ShortMonthNames[3]="Apr";
  ShortMonthNames[4]="May";
  ShortMonthNames[5]="Jun";
  ShortMonthNames[6]="Jul";
  ShortMonthNames[7]="Aug";
  ShortMonthNames[8]="Sep";
  ShortMonthNames[9]="Oct";
  ShortMonthNames[10]="Nov";
  ShortMonthNames[11]="Dec";
  AnsiString asDebugLogPath=ParamStr(0);
  asDebugLogPath.Delete(asDebugLogPath.LastDelimiter("\\"),asDebugLogPath.Length());
  asDebugLogPath+="\\is_debug.log";
  SetCurrentDir(ExtractFilePath(ParamStr(0)));
#ifdef _DEBUG
  if(FindCmdLineSwitch("debuglog",SwitchSyms,true))
    isDebugLog=new TLog(asDebugLogPath.c_str());
#endif
  try
  {
    if(FindCmdLineSwitch("Win9X",SwitchSyms,true))
    {
      TraceS("switch to Win9x mode");
      App->Initialize();
      App->UpdateFormatSettings=false;
      App->CreateForm(__classid(TfDisplay), &fDisplay);
      fDisplay->tmrInfo->Enabled=!FindCmdLineSwitch("notimer",SwitchSyms,true);
      App->Run();
    }
    else
    {
      SrvApp->Initialize();
      App->UpdateFormatSettings=false;
      SrvApp->CreateForm(__classid(TISsNNTP), &ISsNNTP);
      SrvApp->CreateForm(__classid(TISsSMTP), &ISsSMTP);
      SrvApp->CreateForm(__classid(TISsPOP3), &ISsPOP3);
      SrvApp->Run();
    }
  }
	catch (Exception &exception)
	{
#ifdef _DEBUG
      TraceS(exception.Message.c_str());
#else

    FILE *fh=fopen(asDebugLogPath.c_str(),"a");
    if(fh)
    {
      fputs(exception.Message.c_str(),fh);
      fputc('\n',fh);
      fclose(fh);
    }
#endif
		//Sysutils::ShowException(&exception, Sysutils::ExceptAddr());


	}
#ifdef _DEBUG
  delete isDebugLog;
#endif
	return 0;
}

