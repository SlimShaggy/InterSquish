//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "fConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfSetup *fSetup;
AnsiString asExePath;
//---------------------------------------------------------------------------
__fastcall TfSetup::TfSetup(TComponent* Owner)
  : TForm(Owner)
{
  asExePath=ParamStr(0);
  asExePath.Delete(asExePath.LastDelimiter("\\"),300);
  asExePath+="\\IS.exe";

}
//---------------------------------------------------------------------------
void __fastcall TfSetup::Button1Click(TObject *Sender)
{
SC_HANDLE hSCManager,hSCService;

  hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
  if(hSCManager)
  { 
    hSCService=CreateService(
    hSCManager,	// handle to service control manager database  
    "InterSquish",	// pointer to name of service to start 
    "InterSquish",	// pointer to display name 
    SERVICE_START	| SERVICE_STOP | SERVICE_INTERROGATE |STANDARD_RIGHTS_REQUIRED,	// type of access to service 
    SERVICE_WIN32_OWN_PROCESS,	// type of service 
    SERVICE_DEMAND_START,	// when to start service 
    SERVICE_ERROR_NORMAL,	// severity if service fails to start 
    asExePath.c_str(),	// pointer to name of binary file 
    NULL,	// pointer to name of load ordering group 
    NULL,	// pointer to variable to get tag identifier 
    NULL,	// pointer to array of dependency names 
    NULL,	// pointer to account name of service 
    NULL 	// pointer to password for service account 
   );	
    CloseServiceHandle(hSCService);
    CloseServiceHandle(hSCManager);
  }                                     
    if(hSCService)
      MessageBox(Handle,"Service succefully installed","Install complete",0);
    else
      MessageBox(Handle,"Unable install service","Error",0);
}
//---------------------------------------------------------------------------
void __fastcall TfSetup::Button2Click(TObject *Sender)
{
SC_HANDLE hSCManager,hSCService;
bool Result=false;

  hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
  if(hSCManager)
  { 
    hSCService=OpenService(
    hSCManager,	// handle to service control manager database  
    "InterSquish",	// pointer to name of service to start 
    SERVICE_ALL_ACCESS	// type of access to service 
   );
    if(hSCService)
    {
      SERVICE_STATUS ServiceStatus;
      ControlService(hSCService,SERVICE_CONTROL_SHUTDOWN,&ServiceStatus);
      Result=DeleteService(hSCService);
      CloseServiceHandle(hSCService);
    }
    CloseServiceHandle(hSCManager);
  }                                     
    if(Result)
      MessageBox(Handle,"Service succefully uninstalled","Uninstall complete",0);
    else
      MessageBox(Handle,"Unable uninstall service","Error",0);
  
}
//---------------------------------------------------------------------------
