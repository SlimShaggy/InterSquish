//---------------------------------------------------------------------------
#ifndef CfgH
#define CfgH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
//#include <Controls.hpp>
#include <Classes.hpp>
//#include <Forms.hpp>
#include <inifiles.hpp>
#include <stdio.h>
#include "FTNBasics.h"
#include "..\..\comp\include\XxxList.h"
#include "iuScriptControl.h"
//#include "iuInterSquishServer.h"

//#include "Kludges.h"
//---------------------------------------------------------------------------
#define MAX_LINE_SIZE 4096
#define AREAS_SCAN_LEN      12
//---------------------------------------------------------------------------
//enum TAreaFormat {afUnknown=0,afMsg,afSquish,afJAM};
//enum TAreasConfig {acUnknown=0,acSquish,acFastEcho};
//---------------------------------------------------------------------------
//struct TAreaInfo: public TObject
//---------------------------------------------------------------------------




struct TUserInfo
//class TUserInfo
{//FTNAddress,ReplyAddr,ReplyTo,Groups,ROGroups
public:
  TFTNAddress Address;
  AnsiString FName;
  AnsiString NAME; //Имя в верхнем регистре
  AnsiString Login; //login юзера
  AnsiString Groups;
  AnsiString ROGroups;
  AnsiString Password;
  AnsiString ReplyAddr;
  AnsiString ReplyTo;
  AnsiString CharsetName;
  bool Posting;

//  TUserInfo(TiuCustomNNTPServer *server,AnsiString login); //конструктор класса

  __property AnsiString Name={read=FName,write=SetName};

  inline void __fastcall SetName(AnsiString Value)
  {
    FName=Value;
    NAME=FName.UpperCase();
  };
  inline void __fastcall ImportLine(AnsiString Line)
  {
  char *pcBegin;
  char *pcEnd;
    Line.Unique();
    pcBegin=Line.c_str();
    pcEnd=strchr(pcBegin,',');
    if (pcEnd)
      *pcEnd=0;
    Address=AnsiString(pcBegin).Trim();
    if(!pcEnd)
      return;
    pcBegin=pcEnd+1;

    pcEnd=strchr(pcBegin,',');
    if (pcEnd)
      *pcEnd=0;
    ReplyAddr=AnsiString(pcBegin).Trim();
    if(!pcEnd)
      return;
    pcBegin=pcEnd+1;

    pcEnd=strchr(pcBegin,',');
    if (pcEnd)
      *pcEnd=0;
    ReplyTo=AnsiString(pcBegin).Trim();
    if(!pcEnd)
      return;
    pcBegin=pcEnd+1;

    pcEnd=strchr(pcBegin,',');
    if (pcEnd)
      *pcEnd=0;
    Groups=AnsiString(pcBegin).Trim();
    if(!pcEnd)
      return;
    pcBegin=pcEnd+1;

    pcEnd=strchr(pcBegin,',');
    if (pcEnd)
      *pcEnd=0;
    ROGroups=AnsiString(pcBegin).Trim();
    if(!pcEnd)
      return;
    pcBegin=pcEnd+1;




/*
    TStringList *slParams=new TStringList;
    try
    {
      slParams->CommaText=Line;
      Address=slParams->Strings[0];
      ReplyAddr=slParams->Strings[1];
      ReplyTo=slParams->Strings[2];
      Groups=slParams->Strings[3];
      ROGroups=slParams->Strings[4];
    }
    __finally
    {
      delete slParams;
    }
*/
  }

};


enum TAreaFormat {afUnknown=0,afMsg,afSquish,afJAM};
enum TAreasConfig {acUnknown=0,acSquish,acFastEcho};
//---------------------------------------------------------------------------


class TAreaInfo: public TObject
{
    private:
  public:
    AnsiString MaskFileName;
    AnsiString Tag;
    AnsiString InternalTag;
    AnsiString Path;
    AnsiString Description;
    TAreaFormat Format;
    char Group;
    int MaxCount;
    int MaxAge;
    bool IsPassthru;

    __fastcall TAreaInfo();

    AnsiString __fastcall getInternalName(AnsiString /*postingName*/, AnsiString , TUserInfo &);
    AnsiString __fastcall getExternalName(AnsiString /*tagName*/, AnsiString);
    bool __fastcall isPosting(TIniFile *,TUserInfo &, AnsiString );
};


//---------------------------------------------------------------------------
AnsiString PACKAGE __fastcall GetToSpace(char *Line);
AnsiString PACKAGE __fastcall GetToSpaceOrQuoted(char *Line,char sym);

//---------------------------------------------------------------------------
class PACKAGE TCustomCfg : public TComponent
{
private:
  AnsiString FPath;
protected:
  FILE *FCfg;
  AnsiString FFileMode;
  AnsiString FDiskLetter;
  BY_HANDLE_FILE_INFORMATION ByHandleFileInformation;
  __int64 iLastWriteTime;
  bool FScanNeed;
  virtual void __fastcall OpenFile(void);
  virtual void __fastcall CloseFile(void);
  virtual bool __fastcall TrimComments(char* &Line);

  virtual void __fastcall SetPath(AnsiString Value);

  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall Clear(void)=0;
  virtual void __fastcall ImportCfgLine(char *Line)=0;
  __property AnsiString Path={read=FPath, write=SetPath};
  TNotifyEvent FOnRefresh;
  __property TNotifyEvent OnRefresh={read=FOnRefresh, write=FOnRefresh};
public:
  __fastcall TCustomCfg(TComponent* Owner);
   virtual __fastcall~TCustomCfg();
  virtual void __fastcall Refresh(void);
  __property __int64 LastWriteTime={read=iLastWriteTime};
__published:
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TTextCfg : public TCustomCfg
{
private:
  TStringList *FLines;
  TStringList *FParamLists;
  void __fastcall ClearParamLists();
protected:
//  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall Clear();
  virtual void __fastcall ImportCfgLine(char *Line);

  //  virtual void __fastcall Refresh(void);

public:
  __fastcall TTextCfg(TComponent* Owner);
   virtual __fastcall ~TTextCfg();
  int __fastcall ExistParam(AnsiString ParamName);
  AnsiString __fastcall ParamAsString(AnsiString ParamName);
  int __fastcall ParamAsInt(AnsiString ParamName);
  TStringList* __fastcall ParamsList(AnsiString ListName);
__published:
  __property Path;
  __property OnRefresh;
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class PACKAGE TCustomUsersCfg : public TCustomCfg
{
private:
  TListOfX<TUserInfo> *FUsers;
protected:
  virtual void __fastcall Clear();
//  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall ImportCfgLine(char *Line);

public:
  __fastcall TCustomUsersCfg(TComponent* Owner);
   virtual __fastcall~TCustomUsersCfg();

  __property TListOfX<TUserInfo> *Users={read=FUsers};
__published:
  __property Path;
  __property OnRefresh;
};
//---------------------------------------------------------------------------
class PACKAGE TCustomAreasCfg : public TCustomCfg
{
private:
  TAreaInfo *FBadArea;
  TAreaInfo *FDupeArea;
  TListOfX<TAreaInfo> *FNetAreas;
  TListOfX<TAreaInfo> *FLocalAreas;
  TListOfX<TAreaInfo> *FEchoAreas;
//  bool __fastcall Open(void);
//  void __fastcall Close(void);
protected:
  virtual void __fastcall Clear();
public:
  __fastcall TCustomAreasCfg(TComponent* Owner);
   virtual __fastcall ~TCustomAreasCfg();
  __property Path;

  __property TAreaInfo *BadArea={read=FBadArea};
  __property TAreaInfo *DupeArea={read=FDupeArea};
  __property TListOfX<TAreaInfo> *NetAreas={read=FNetAreas};
  __property TListOfX<TAreaInfo> *LocalAreas={read=FLocalAreas};
  __property TListOfX<TAreaInfo> *EchoAreas={read=FEchoAreas};
__published:
};
//---------------------------------------------------------------------------
class PACKAGE TSquishCfg : public TCustomAreasCfg
{
private:
  bool FTagLowerCase;
  void __fastcall AddArea(TListOfX<TAreaInfo> *AreaList, char * pcLine);
  void __fastcall SetArea(TAreaInfo *Area, char * pcLine);

protected:
//  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall ImportCfgLine(char *Line);

public:
  __fastcall TSquishCfg(TComponent* Owner);
  virtual __fastcall ~TSquishCfg();
//  __property BadArea;
//  __property DupeArea;
//  __property NetAreas;
//  __property LocalAreas;
//  __property EchoAreas;
__published:
  __property Path;
  __property OnRefresh;
  __property bool TagLowerCase={read=FTagLowerCase,write=FTagLowerCase};
};
//---------------------------------------------------------------------------
class PACKAGE TFastechoCfg : public TCustomAreasCfg
{
private:
  bool FTagLowerCase;
//  void __fastcall AddArea(TListOfX<TAreaInfo> *AreaList, char * pcLine);
//  void __fastcall SetArea(TAreaInfo *Area, char * pcLine);
protected:
  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall ImportCfgLine(char *Line){};
public:
  __fastcall TFastechoCfg(TComponent* Owner);
  virtual __fastcall ~TFastechoCfg();
  __property BadArea;
  __property DupeArea;
  __property NetAreas;
  __property LocalAreas;
  __property EchoAreas;
__published:
  __property Path;
  __property OnRefresh;
  __property bool TagLowerCase={read=FTagLowerCase,write=FTagLowerCase};
};
//---------------------------------------------------------------------------
class PACKAGE TScriptCfg : public TCustomCfg
{
private:
  TListOfX<TScriptInstruction> *FInstructionList;
protected:
  virtual void __fastcall Clear();
  virtual void __fastcall ImportCfgLine(char *Line);
public:
  __fastcall TScriptCfg(TComponent* Owner);
   virtual __fastcall ~TScriptCfg();
     TScriptInstruction* __fastcall InstructionByName(AnsiString InstructionName);
  __property TListOfX<TScriptInstruction> *InstructionList={read=FInstructionList};
__published:
  __property Path;
  __property OnRefresh;
};
//---------------------------------------------------------------------------


bool CheckUserLogin(TUserInfo *ui,AnsiString users,AnsiString login);

#endif
