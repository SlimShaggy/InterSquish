//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef KludgesH
#define KludgesH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
//#include "FTNDataSet.h"
//#include <Controls.hpp>
#include <Classes.hpp>
#include "..\..\comp\include\XxxList.h"
//#include <Forms.hpp>
//---------------------------------------------------------------------------
/*enum TAreaFormat {afUnknown=0,afMsg,afSquish,afJAM};
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

    AnsiString __fastcall getInternalName(AnsiString postingName);
    AnsiString __fastcall getExternalName(AnsiString tagName);
};
*/


class  PACKAGE TKludge
{
private:
  AnsiString FName;
  AnsiString FValue;
  void __fastcall SetName(AnsiString Value);
  AnsiString __fastcall GetName(void);
  AnsiString __fastcall GetKludgeString(void);
  void __fastcall SetAsString(AnsiString Value);
public:
  __fastcall TKludge(AnsiString KludgeLine);
  __fastcall TKludge(AnsiString Name,AnsiString Value);
  TKludge& __fastcall operator = (const AnsiString &KludgeData);
  __property AnsiString Name={read=GetName,write=SetName};
  __property AnsiString AsString={read=FValue,write=FValue};
  __property AnsiString AsKludgeString={read=GetKludgeString};
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class PACKAGE TCustomKludges //: public TPersistent
{
private:
  AnsiString FBody;
  TListOfX<TKludge> *FKludgeList;
protected:
  virtual void __fastcall Import(AnsiString ABody);
  virtual AnsiString __fastcall Export(void);
  __property  AnsiString Body={read=Export, write=Import};
public:
  __fastcall TCustomKludges(void);
  __fastcall TCustomKludges(AnsiString ABody);
  virtual __fastcall ~TCustomKludges(void);
  TKludge * __fastcall KludgeByName(AnsiString Name);
  virtual void __fastcall Add(TKludge *Kludge);
  virtual void __fastcall Delete(AnsiString Name);
  virtual void __fastcall SaveToStream(TStream *Stream);
  void __fastcall Clear(void);
  __property TListOfX<TKludge> *KludgeList={read=FKludgeList};
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString  PACKAGE __fastcall MSGID2MessageId(AnsiString MSGID);
AnsiString  PACKAGE __fastcall ExtractFTNAddr(AnsiString MSGID);
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class PACKAGE TKludges : public TCustomKludges
{
private:
protected:
  AnsiString __fastcall GetMsgId(void);
  AnsiString __fastcall GetReply(void);
  AnsiString __fastcall GetPID(void);
  AnsiString __fastcall GetTID(void);
  AnsiString __fastcall GetRFC_Message_ID(void);
  AnsiString __fastcall GetRFC_References(void);
  AnsiString __fastcall GetReplyAddr(void);
  AnsiString __fastcall getFlags(void);
  void __fastcall setFlags(AnsiString fl);
public:
  __fastcall TKludges(void);
  __fastcall TKludges(AnsiString ABody);
  __property Body;
  __property AnsiString MSGID={read=GetMsgId};
  __property AnsiString RFC_Message_ID={read=GetRFC_Message_ID};
  __property AnsiString RFC_References={read=GetRFC_References};
  __property AnsiString REPLY={read=GetReply};
  __property AnsiString REPLYADDR={read=GetReplyAddr};
  __property AnsiString PID={read=GetPID};
  __property AnsiString TID={read=GetTID};
  __property AnsiString FLAGS={read=getFlags,write=setFlags};

//__published:
};

#endif
 
