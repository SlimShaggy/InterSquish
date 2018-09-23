//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef FTNMsgH
#define FTNMsgH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <dir.h>
#include "FTNBasics.h"
#include "Kludges.h"
#include "API_SQ.H"
#include <log.h>
//---------------------------------------------------------------------------
#pragma pack (push,1)
struct TMsgInfo;
struct TMsgAttr
{
  bool Private  : 1;     //Private message
  bool Crash    : 1;     //High priority
  bool Read     : 1;     //Read by addressee
  bool Sent     : 1;     //Has been sent
  bool File     : 1;     //File attached to msg
  bool Transit  : 1;     //In transit
  bool Orpah    : 1;     //Unknown node
  bool Kill     : 1;     //Kill after mailing
  bool Local    : 1;     //Message was entered here
  bool Hold     : 1;     //Hold for pickup
  bool NotUsed  : 1;     //
  bool Freq     : 1;     //File request
  bool Rrreq    : 1;     //Return receipt request
  bool Isrr     : 1;     //Is return receipt
  bool Areq     : 1;     //Audit request
  bool Updreq   : 1;     //File update request
};
//---------------------------------------------------------------------------
struct TFTNMsgHeader
{
  char FromUser[36];     //Name in By: field
  char ToUser[36];       //Name in To: field
  char Subject[72];      //Name in Re: field
  char DateTime[20];     //ASCIIz creation date
  Word TimesRead;        //Number of times message read
  Word DestNode;         //Destination node
  Word OrigNode;         //Originating node
  Word Cost;             //Cost to send message
  Word OrigNet;          //Originating net
  Word DestNet;          //Destination net
  Word DestZone;         //Destination zone
  Word OrigZone;         //Originating zone
  Word DestPoint;        //Destination point
  Word OrigPoint;        //Originating point
  Word ReplyTo;          //This is a reply to "ReplyTo"
  union{
  TMsgAttr Attr;         //Attribute bits
  WORD wAttr;
  };
  Word ReplyNext;        //Next reply in thread
  TFTNMsgHeader& __fastcall operator =(const TMsgInfo &MsgInfo);
};
//---------------------------------------------------------------------------
struct TPackedMsgHeader
{
  WORD PacketType;  //=0x0002
  WORD OrigNode;
  WORD DestNode;
  WORD OrigNet;
  WORD DestNet;
  TMsgAttr Attr;
  WORD Cost;
  char DateTime[20];
/*
  char ToUser[37];
  char FromUser[37];
  char Subject[73];
*/
  TPackedMsgHeader(){ZeroMemory(this,sizeof(TPackedMsgHeader)); PacketType=2;};
};
/*
//---------------------------------------------------------------------------
struct TNetAddr
{
  WORD Zone;
  WORD Net;
  WORD Node;
  WORD Point;
};
*/
//---------------------------------------------------------------------------
struct TStamp   // DOS-style datestamp
{
  struct
  {
    unsigned int da : 5;
    unsigned int mo : 4;
    unsigned int yr : 7;
  } date;

  struct
  {
    unsigned int ss : 5;
    unsigned int mm : 6;
    unsigned int hh : 5;
  } time;
};
//---------------------------------------------------------------------------
struct TXMsgAttr
{
  unsigned int Private  : 1;     //Private message
  unsigned int Crash    : 1;     //High priority
  unsigned int Read     : 1;     //Read by addressee
  unsigned int Sent     : 1;     //Has been sent
  unsigned int File     : 1;     //File attached to msg
  unsigned int Transit  : 1;     //In transit
  unsigned int Orpah    : 1;     //Unknown node
  unsigned int Kill     : 1;     //Kill after mailing
  unsigned int Local    : 1;     //Message was entered here
  unsigned int Hold     : 1;     //Hold for pickup
  unsigned int Xx2      : 1;     //
  unsigned int Freq     : 1;     //File request
  unsigned int Rrreq    : 1;     //Return receipt request
  unsigned int Isrr     : 1;     //Is return receipt
  unsigned int Areq     : 1;     //Audit request
  unsigned int Updreq   : 1;     //File update request
  unsigned int Scanned  : 1;
  unsigned int NotUsed  :15; 
};

//---------------------------------------------------------------------------
struct TFTNXMsgHeader
{
  TXMsgAttr attr;

  char from[36];
  char to[36];
  char subj[72];

  TNetAddr orig;        /* Origination and destination addresses             */
  TNetAddr dest;

  TStamp date_written;   /* When user wrote the msg (UTC)            */
  TStamp date_arrived;   /* When msg arrived on-line (UTC)           */
  signed short  utc_ofs; /* Offset from UTC of message writer, in    *
                          * minutes.                                 */

  #define MAX_REPLY 10   /* Max number of stored replies to one msg  */

  DWORD replyto;
  DWORD replies[MAX_REPLY];

  char ftsc_date[20];  /* Obsolete date information.  If it weren't for the *
                        * fact that FTSC standards say that one cannot      *
                        * modify an in-transit message, I'd be VERY         *
                        * tempted to axe this field entirely, and recreate  *
                        * an FTSC-compatible date field using               *
                        * the information in 'date_written' upon            *
                        * export.  Nobody should use this field, except     *
                        * possibly for tossers and scanners.  All others    *
                        * should use one of the two binary datestamps,      *
                        * above.                                            */
  TFTNXMsgHeader& __fastcall operator =(const TMsgInfo &MsgInfo);
};

struct TMsgInfo        //Именно эту структуру рекомендуется использовать
{                      //при работе с TCustomFTNMsg и его наследниками
  TXMsgAttr Attr;
  char From[36];
  char To[36];
  char Subj[72];
  TNetAddr Orig;
  TNetAddr Dest;
  TTimeStamp DateWritten;   //
  TTimeStamp DateArrived;   //

  signed short  UTCOfs;
  DWORD ReplyTo;
  DWORD Replies[MAX_REPLY];

  char FTSCDate[20];
  TMsgInfo& __fastcall operator =(const TFTNXMsgHeader &XMsg);
};
//---------------------------------------------------------------------------
#pragma pack (pop)
//---------------------------------------------------------------------------
class PACKAGE TFTNMsgBody : public TStringList
{
protected:
	virtual AnsiString __fastcall GetTextStr(void);
public:
  __fastcall TFTNMsgBody(void);
  void __fastcall LoadFromStreamEx(TStream *Stream,int Size);
//  virtual void __fastcall LoadFromStream(TStream *Stream);
};
//---------------------------------------------------------------------------
class PACKAGE TCustomFTNMsg : public TComponent
{
private:
//  AnsiString FOrigin;
  TDateTime FOrigTime;
  TDateTime FDestTime;
  TFTNAddress FOrigAddr;
  TFTNAddress FDestAddr;
  TFTNMsgHeader *FHeader;
  TKludges *FKludges;
  TFTNMsgBody *FLines;
  AnsiString FTearlineText;
  AnsiString FOriginText;
  TKludges *FSeenBys;
  TKludges *FPath;
  TKludges *FVias;
  TMsgInfo *FMsgInfo;

  TStringList* __fastcall GetLines(void){return FLines;};
  TKludges* __fastcall GetKludges(void){return FKludges;};
  AnsiString __fastcall GetOrigin(void);
  void __fastcall SetOrigin(AnsiString Value);
  void __fastcall SetOrigAddr(TFTNAddress &Value);
  void __fastcall SetDestAddr(TFTNAddress &Value);
  void __fastcall SetOrigTime(TDateTime Value);
  void __fastcall SetFromName(AnsiString Value);
  void __fastcall SetToName(AnsiString Value);
  AnsiString __fastcall GetToName(void);
  void __fastcall SetSubject(AnsiString Value);
protected:
  __property TStringList *Lines={read=GetLines};
  __property TKludges *Kludges={read=GetKludges};
  __property TKludges *Vias={read=FVias};
  __property TFTNMsgHeader *Header={read=FHeader};
  __property TMsgInfo *Info={read=FMsgInfo};
  __property AnsiString Tearline={read=FTearlineText, write=FTearlineText};
  __property AnsiString Origin={read=FOriginText, write=FOriginText};
  __property TFTNAddress OrigAddr={read=FOrigAddr, write=SetOrigAddr};
  __property TFTNAddress DestAddr={read=FDestAddr, write=SetDestAddr};
  __property AnsiString FromName={write=SetFromName};
  __property AnsiString ToName={write=SetToName, read=GetToName};
  __property AnsiString Subject={write=SetSubject};
  __property TDateTime OrigDateTime={read=FOrigTime, write=SetOrigTime};
  //  virtual void __fastcall CreateNew(void);
public:
  __fastcall TCustomFTNMsg(TComponent* Owner);
  virtual __fastcall ~TCustomFTNMsg();
  virtual void __fastcall Clear(void);
  virtual void __fastcall SaveToStream(TStream *Stream);
  virtual void __fastcall SaveToStreamPacked(TStream *Stream);
  virtual void __fastcall LoadFromStream(TStream *Stream);
  virtual void __fastcall LoadFromStreamPacked(TStream *Stream);
  void __fastcall InvalidateOldTechInfo(void);
  void __fastcall SaveToFile(AnsiString FileName);
  void __fastcall LoadFromFile(AnsiString FileName);

__published:
};
//--- Сообщение описанное в FTS-1 -------------------------------------------
class PACKAGE TFTNMsg : public TCustomFTNMsg
{
private:
protected:
public:
  __fastcall TFTNMsg(TComponent* Owner);

  __property Header;
  __property FromName;
  __property ToName;
  __property Subject;
  __property OrigAddr;
  __property DestAddr;
  __property OrigDateTime;
//  __property DestDateTime;
  __property Kludges;
  __property Lines;
  __property Tearline;
  __property Origin;
  __property Vias;
__published:
};
//---------------------------------------------------------------------------
inline TTimeStamp __fastcall TimeDOS2VCL(const TStamp &stmp)
{
TTimeStamp Result={0,0};
  try
  {
  TraceS(__FUNC__);
    Result=DateTimeToTimeStamp(EncodeDate((Word)(stmp.date.yr+1980),
     (Word)stmp.date.mo,(Word)stmp.date.da)+EncodeTime((Word)stmp.time.hh,
     (Word)stmp.time.mm,(Word)(stmp.time.ss*2),0));;
     TraceS(__FUNC__);
  }
  catch(...)
  {
  TraceS(__FUNC__);
    Result.Date=0;
    Result.Time=0;
  }
//  __finally
//  {
    return Result;
//  }
}
//---------------------------------------------------------------------------
inline TStamp __fastcall TimeVCL2DOS(const TTimeStamp &TimeStamp)
{
struct TStamp stmp;
unsigned short da,mo,yr,ss,mm,hh,ms;
TraceS(__FUNC__);
TDateTime datetime=TimeStampToDateTime(TimeStamp);
TraceS(__FUNC__);
  datetime.DecodeDate(&yr,&mo,&da);
  datetime.DecodeTime(&hh,&mm,&ss,&ms);
  stmp.date.da=da;
  stmp.date.mo=mo;
  stmp.date.yr=yr-1980;
  stmp.time.ss=ss;
  stmp.time.mm=mm;
  stmp.time.hh=hh;
  TraceS(__FUNC__);
  return stmp;
}
//---------------------------------------------------------------------------
inline TTimeStamp __fastcall TimeUNIX2VCL(unsigned int UnixTime)
{
static const int DayBias=(DateDelta+70*365+70/4+2);
TTimeStamp Result;
TraceS(__FUNC__);
  Result.Date=UnixTime/SecsPerDay+DayBias;
  Result.Time=(UnixTime%SecsPerDay)*1000;//-Result.Date;//-Result.Date*SecsPerDay;
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
inline int __fastcall TimeVCL2UNIX(TDateTime ADateTime)
{
int Result=0;
TraceS(__FUNC__);
static const int DayBias=(DateDelta+70*365+70/4+2);
  TTimeStamp TimeStamp=DateTimeToTimeStamp(ADateTime);
  Result=(TimeStamp.Date-DayBias)*SecsPerDay+TimeStamp.Time/1000;
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
#endif
