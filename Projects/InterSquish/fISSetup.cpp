//---------------------------------------------------------------------------
#include <vcl.h>
#include <registry.hpp>

#pragma hdrstop

#include "fISSetup.h"
#include "fConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSpin"
#pragma resource "*.dfm"
TisMainForm *isMainForm;
//---------------------------------------------------------------------------
__fastcall TisMainForm::TisMainForm(TComponent* Owner)
  : TForm(Owner)
{
TRegistry *Registry;

  Registry=new TRegistry();
  try
  {
    Registry->RootKey=HKEY_LOCAL_MACHINE;
    if(Registry->OpenKey("Software\\IvUs\\InterSquish", true))
    {  
      if(Registry->ValueExists("SquishCfg"))
        feSquishCfg->Text=Registry->ReadString("SquishCfg");
      if(Registry->ValueExists("LogFileName"))
        feLogFile->Text=Registry->ReadString("LogFileName");
      if(Registry->ValueExists("LogLevel"))
        seLogLevel->Value=Registry->ReadInteger("LogLevel");
      if(Registry->ValueExists("Port"))
        sePort->Value=Registry->ReadInteger("Port");
      if(Registry->ValueExists("ThreadTimeout"))
        seTimeout->Value=Registry->ReadInteger("ThreadTimeout");
      if(Registry->ValueExists("ThreadCacheSize"))
        seCacheSize->Value=Registry->ReadInteger("ThreadCacheSize");
    }
  }
  __finally
  {
    Registry->Free();
  }
}
//---------------------------------------------------------------------------
__fastcall TisMainForm::~TisMainForm(void)
{
//  iuInterSquishServer1->CfgFileName=ParamStr(0).Delete(ParamStr(0).Length()-2,3)+"cfg";
}
//---------------------------------------------------------------------------
void __fastcall TisMainForm::Button1Click(TObject *Sender)
{
  fSetup=new TfSetup(this);
  try
  {
    fSetup->ShowModal();
  }
  __finally
  {
    fSetup->Free();
  }
}
//---------------------------------------------------------------------------
void __fastcall TisMainForm::Button2Click(TObject *Sender)
{
TRegistry *Registry;

  Registry=new TRegistry();
  try
  {
    Registry->RootKey=HKEY_LOCAL_MACHINE;
    if(Registry->OpenKey("Software\\IvUs\\InterSquish", true))
    {  
      Registry->WriteString("SquishCfg",feSquishCfg->Text);
      Registry->WriteString("LogFileName",feLogFile->Text);
      Registry->WriteInteger("LogLevel",seLogLevel->Value);
      Registry->WriteInteger("Port",sePort->Value);
      Registry->WriteInteger("ThreadTimeout",seTimeout->Value);
      Registry->WriteInteger("ThreadCacheSize",seCacheSize->Value);
    }
  }
  __finally
  {
    Registry->Free();
  }

  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TisMainForm::Button3Click(TObject *Sender)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------

