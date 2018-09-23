
#include <vcl.h>
#include <condefs.h>
#include <windows.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma argsused
USEFORM("isForm1.cpp", Form1);

SERVICE_STATUS_HANDLE hServiceStatus=0;
SERVICE_STATUS ssStatus;

//---------------------------------------------------------------------------
void WINAPI Handler(DWORD fdwControl)
{
  switch(fdwControl)
  {
    case SERVICE_CONTROL_STOP:
      ssStatus.dwCurrentState=SERVICE_STOP_PENDING;
      SetServiceStatus(hServiceStatus,&ssStatus);
      SendMessage(Application->MainForm->Handle,WM_CLOSE,0,0);
      Application->ProcessMessages();
      MessageBeep(-1);
    break;
    case SERVICE_CONTROL_PAUSE:
    break;
    case SERVICE_CONTROL_CONTINUE:
    break;
    case SERVICE_CONTROL_INTERROGATE:
      SetServiceStatus(hServiceStatus,&ssStatus);
    break;
    case SERVICE_CONTROL_SHUTDOWN:
      ssStatus.dwCurrentState=SERVICE_STOP_PENDING;
      SetServiceStatus(hServiceStatus,&ssStatus);
      Application->Terminate();
      Application->ProcessMessages();
    break;
  }
}
//---------------------------------------------------------------------------
void WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpszArgv)
{
  MessageBeep(-1);
  hServiceStatus=RegisterServiceCtrlHandler("IServer",Handler);
  if(hServiceStatus)
  {
    ssStatus.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
    ssStatus.dwCurrentState=SERVICE_START_PENDING;
    ssStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP;
    ssStatus.dwWin32ExitCode=NO_ERROR;
    ssStatus.dwServiceSpecificExitCode=NO_ERROR;
    ssStatus.dwCheckPoint=0;
    ssStatus.dwWaitHint=5000;
    if(SetServiceStatus(hServiceStatus,&ssStatus))
    {
      Application->Initialize();
      Application->CreateForm(__classid(TForm1), &Form1);

      ssStatus.dwCurrentState=SERVICE_RUNNING;
      SetServiceStatus(hServiceStatus,&ssStatus);

      Application->ShowMainForm=false; //иначе сервис не будет работать
      Application->Run();

      ssStatus.dwCurrentState=SERVICE_STOPPED;
      SetServiceStatus(hServiceStatus,&ssStatus);
    }
  }
}

