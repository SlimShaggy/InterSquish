//---------------------------------------------------------------------------

#ifndef iuScriptControlH
#define iuScriptControlH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "MSScriptControl_OCX.h"
#include <OleCtrls.hpp>
#include "Xxxlist.h"
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOnLogEvent)(TObject* Sender,AnsiString sEvent);
class PACKAGE TiuScriptControl : public TScriptControl
{
private:
  
protected:
  TNotifyEvent                   FOnError;
  TNotifyEvent                   FOnTimeout;
  TOnLogEvent FOnLogEvent;
  AnsiString FCurrentFilename;
public:
  void __fastcall LoadFromFile(AnsiString FileName);

  __fastcall TiuScriptControl(TComponent* Owner);
  __property AnsiString CurrentFilename={read=FCurrentFilename};
__published:
  __property TNotifyEvent OnError={ read=FOnError, write=FOnError };
  __property TNotifyEvent OnTimeout={ read=FOnTimeout, write=FOnTimeout };
  __property TOnLogEvent OnLogEvent={read=FOnLogEvent, write=FOnLogEvent};

};
//---------------------------------------------------------------------------
struct TScriptArgItem
{
  AnsiString Name;
  Variant Value;
  __fastcall TScriptArgItem(AnsiString AName, Variant AValue)
  {
    Name=AName;
    Value=AValue;
  };
};
//---------------------------------------------------------------------------
class PACKAGE TiuScriptArgsList : public TListOfX<TScriptArgItem>
{
public:
  Variant & __fastcall ParamByName(AnsiString ParamName);
};
//---------------------------------------------------------------------------
class PACKAGE TScriptInstruction
{
  AnsiString FInstructionName;
  AnsiString FEngine;
  AnsiString FFileName;
  AnsiString FFunctionName;
  TStringList *FParamList;
  void __fastcall ImportTaskLine(AnsiString TaskLine);
public:
  __fastcall TScriptInstruction(AnsiString TaskLine);
  virtual __fastcall ~TScriptInstruction(void);
  Variant __fastcall Execute(TiuScriptControl *ScriptControl, TiuScriptArgsList *ArgsList);
  __property AnsiString InstructionName={read=FInstructionName};
};

//---------------------------------------------------------------------------

inline Variant __fastcall ExecInstruction(TScriptInstruction *Instruction,TiuScriptControl *ScriptControl,TiuScriptArgsList *ArgsList,Variant Default=varEmpty)
{
    if(Instruction)
    {
      return Instruction->Execute(ScriptControl,ArgsList);
    }
    return Default;
}

//---------------------------------------------------------------------------
/*
class PACKAGE TScriptInstructionList : public TListOfX<TScriptInstruction>
{
public:
  TScriptInstruction* __fastcall InstructionByName(AnsiString InstructionName);
};
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

