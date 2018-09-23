//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "stdio.h"
#include "iuScriptControl.h"
#pragma link "MSScriptControl_OCX"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TiuScriptControl *)
{
  new TiuScriptControl(NULL);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TiuScriptControl::TiuScriptControl(TComponent* Owner)
  : TScriptControl(Owner)
{
  AllowUI=false;
}
//---------------------------------------------------------------------------
void __fastcall TiuScriptControl::LoadFromFile(AnsiString FileName)
{
  //Reset();
  int hFile=FileOpen(FileName, fmShareDenyNone);
  if(hFile!=-1)
  {
    DWORD dwFileSize=GetFileSize((void*)hFile,NULL);
    if (dwFileSize != 0xFFFFFFFF)
    {                  
      FCurrentFilename=FileName;
      char *pcSourceBuffer=new char[dwFileSize+4];
      try
      {
        dwFileSize=FileRead(hFile,pcSourceBuffer,dwFileSize);
        pcSourceBuffer[dwFileSize]=NULL;
        AddCode(WideString(pcSourceBuffer).Detach());
      }
      __finally
      {
        delete [] pcSourceBuffer;
      }
    }
  }
  else
    throw Exception("Unable open script file: "+FileName);
}
//---------------------------------------------------------------------------
Variant & __fastcall TiuScriptArgsList::ParamByName(AnsiString ParamName)
{
  for(int i=0;i<Count;i++)
  {
    if(!Items[i]->Name.AnsiCompareIC(ParamName))
    {
      return Items[i]->Value;
    }
  }
  return Items[Add(new TScriptArgItem(ParamName, varEmpty))]->Value;
}
//---------------------------------------------------------------------------
__fastcall TScriptInstruction::TScriptInstruction(AnsiString TaskLine)
{
  FParamList=new TStringList;
  ImportTaskLine(TaskLine);
}
//---------------------------------------------------------------------------
__fastcall TScriptInstruction::~TScriptInstruction(void)
{
  delete FParamList;
}
//---------------------------------------------------------------------------
void __fastcall TScriptInstruction::ImportTaskLine(AnsiString TaskLine)
{

//wshIsIpValid VBScript,iss.vbs,CheckIpAddress,SERVICENAME,REMOTE_IP
  FParamList->Clear();
  FParamList->CommaText=TaskLine;
  if (FParamList->Count<4)
    throw Exception("Bad Script command!");
  FInstructionName=FParamList->Strings[0];
  FEngine=FParamList->Strings[1];
  FFileName=FParamList->Strings[2];
  FFunctionName=FParamList->Strings[3];
  for(int i=0;i<4;i++)
    FParamList->Delete(0);
}
//---------------------------------------------------------------------------
Variant __fastcall TScriptInstruction::Execute(TiuScriptControl *ScriptControl, TiuScriptArgsList *ArgsList)
{
Variant varResult;
Variant varTemp;
int Bounds[2] = {0,FParamList->Count-1};

  try
  {
//    ScriptControl->Reset();
    ScriptControl->Language=FEngine;
    ScriptControl->LoadFromFile(FFileName);
    
    
    Variant varArguments = VarArrayCreate(Bounds,1, varVariant);
    for(int i=0;i<=Bounds[1];i++)
    {
      varTemp=ArgsList->ParamByName(FParamList->Strings[i]);
      varArguments.PutElement(varTemp,i);
    }
    varResult=ScriptControl->Run(WideString(FFunctionName).Detach(), &varArguments.parray);
  }
  catch(Exception &exception)
  {
    varResult.Clear();
    if(ScriptControl->OnLogEvent)
    {
    char Buffer[1024];
      ExceptionErrorMessage(&exception, ExceptAddr(), Buffer, sizeof(Buffer));
      ScriptControl->OnLogEvent(ScriptControl,AnsiString(Buffer));
    }
  }
  return varResult;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*
namespace Iuscriptcontrol
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TiuScriptControl)};
     RegisterComponents("FIDO Tech", classes, 0);
  }
}
*/
//---------------------------------------------------------------------------
