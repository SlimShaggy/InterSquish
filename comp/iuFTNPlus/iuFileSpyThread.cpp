//---------------------------------------------------------------------------
#include <vcl.h>
#include <classes.hpp>
#pragma hdrstop

#include "iuFileSpyThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TFileSpyThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TFileSpyThread::TFileSpyThread(bool CreateSuspended) : TThread(true)
{
  FHandle=INVALID_HANDLE_VALUE;
  Resume();
}
//---------------------------------------------------------------------------
__fastcall TFileSpyThread::~TFileSpyThread(void)
{
  if(FHandle!=INVALID_HANDLE_VALUE)
    FindCloseChangeNotification(FHandle);
}
//---------------------------------------------------------------------------
void __fastcall TFileSpyThread::Execute()
{
DWORD dwResult;
  while(!Terminated)
  {

    FHandle=FindFirstChangeNotification(FPathName.c_str(),false,
         FILE_NOTIFY_CHANGE_SIZE+FILE_NOTIFY_CHANGE_LAST_WRITE);
    if(FHandle!=INVALID_HANDLE_VALUE)
    {
        do
        {
          dwResult=WaitForSingleObjectEx(FHandle,2000,false);
        }while((dwResult!=WAIT_OBJECT_0) && !Terminated);

        if (dwResult==WAIT_OBJECT_0) FindCloseChangeNotification(WAIT_OBJECT_0);
            
        //if (CreateProcess(/*PChar(*/ParamStr(2)/*)*/,NULL,NULL,NULL,False, CREATE_NEW_CONSOLE+IDLE_PRIORITY_CLASS,NULL,NULL,&this->StartUpInfo,&this->ProcessInfo)

    }
    Sleep(1000);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFileSpyThread::SetFileName(AnsiString value)
{
    FFileName = value;
}
