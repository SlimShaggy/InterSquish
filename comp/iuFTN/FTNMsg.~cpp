//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <log.h>
#include "FTNMsg.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
inline TTimeStamp __fastcall TimeDOS2VCL(const TStamp &stmp)
{
TTimeStamp Result={0,0};
  try
  {
    Result=DateTimeToTimeStamp(EncodeDate((Word)(stmp.date.yr+1980),
     (Word)stmp.date.mo,(Word)stmp.date.da)+EncodeTime((Word)stmp.time.hh,
     (Word)stmp.time.mm,(Word)(stmp.time.ss*2),0));;
  }
  catch(...)
  {
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
TDateTime datetime=TimeStampToDateTime(TimeStamp);
  datetime.DecodeDate(&yr,&mo,&da);
  datetime.DecodeTime(&hh,&mm,&ss,&ms);
  stmp.date.da=da;
  stmp.date.mo=mo;
  stmp.date.yr=yr-1980;
  stmp.time.ss=ss;
  stmp.time.mm=mm;
  stmp.time.hh=hh;
  return stmp;
}
*/
//---------------------------------------------------------------------------
__fastcall TFTNMsgBody::TFTNMsgBody(void):TStringList()
{
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFTNMsgBody::GetTextStr(void)
{
TraceS(__FUNC__);
int i,iItemLen,iSize=0;
char *pcP;
AnsiString asResult,asItem;
  for(i=0;i<Count;i++)
    iSize+=Strings[i].Length()+2;
  asResult=AnsiString::StringOfChar(' ',iSize);
  pcP=asResult.c_str();

  for(i=0;i<Count;i++)
  {
    asItem = Get(i);
    if((bool)(iItemLen=asItem.Length()))
    {
      memmove(pcP,asItem.c_str(),iItemLen);
      pcP+=iItemLen;
    }
    if(*pcP=='\n')
      *pcP='\r';
    else
      *(pcP++)='\r';
  }
  asResult.SetLength(pcP-asResult.c_str());
  return asResult;
}
//---------------------------------------------------------------------------
void __fastcall TFTNMsgBody::LoadFromStreamEx(TStream *Stream, int Size)
{
TraceS(__FUNC__);
  BeginUpdate();
  try
  {
    char *cBuf=new char[Size];
    try
    {
      Stream->Read(cBuf, Size);
//      for(int i=0;i<Size;i++)
//        if(!cBuf[i])
//          cBuf[i]='\r';
      SetTextStr(AnsiString(cBuf));
    }
    __finally
    {
      delete [] cBuf;
    }
  }
  __finally
  {
    EndUpdate();
 }
}
//---------------------------------------------------------------------------
TFTNMsgHeader& __fastcall TFTNMsgHeader::operator =(const TMsgInfo &MsgInfo)
{
  strncpy(FromUser,MsgInfo.From,sizeof(FromUser));
  strncpy(ToUser,MsgInfo.To,sizeof(ToUser));
  strncpy(Subject,MsgInfo.Subj,sizeof(Subject));
  strncpy(DateTime,MsgInfo.FTSCDate,sizeof(DateTime));
  TimesRead=Cost=0;
  DestNode=MsgInfo.Dest.Node;
  OrigNode=MsgInfo.Orig.Node;
  OrigNet=MsgInfo.Orig.Net;
  DestNet=MsgInfo.Dest.Net;
  DestZone=MsgInfo.Dest.Zone;
  OrigZone=MsgInfo.Dest.Zone;
  DestPoint=MsgInfo.Dest.Point;
  OrigPoint=MsgInfo.Orig.Point;
  ReplyTo=*((Word*)&MsgInfo.ReplyTo);         //Не уверен, что это правильно...
  *((Word *)&Attr)=*((Word*)(&MsgInfo.Attr));
  ReplyNext=*((Word*)MsgInfo.Replies);        //Не уверен, что это правильно...
  return *this;
}
//---------------------------------------------------------------------------
TMsgInfo& __fastcall TMsgInfo::operator =(const TFTNXMsgHeader &XMsg)
{
  *((DWORD *)&Attr)=*((DWORD *)(&XMsg.attr));
  strncpy(From,XMsg.from,sizeof(From));
  strncpy(To,XMsg.to,sizeof(To));
  strncpy(Subj,XMsg.subj,sizeof(Subj));
  strncpy(FTSCDate,XMsg.ftsc_date,sizeof(FTSCDate));
  Orig=XMsg.orig;
  Dest=XMsg.dest;

  DateWritten=TimeDOS2VCL(XMsg.date_written);
  DateArrived=TimeDOS2VCL(XMsg.date_arrived);

  UTCOfs=XMsg.utc_ofs;
  ReplyTo=XMsg.replyto;
  memmove(Replies,XMsg.replies,sizeof(Replies));
  return *this;
}
//---------------------------------------------------------------------------
TFTNXMsgHeader& __fastcall TFTNXMsgHeader::operator =(const TMsgInfo &MsgInfo)
{
  *((DWORD *)&attr)=*((DWORD *)(&MsgInfo.Attr));
  strncpy(from,MsgInfo.From,sizeof(from));
  strncpy(to,MsgInfo.To,sizeof(to));
  strncpy(subj,MsgInfo.Subj,sizeof(subj));
  strncpy(ftsc_date,MsgInfo.FTSCDate,sizeof(ftsc_date));
  orig=MsgInfo.Orig;
  dest=MsgInfo.Dest;

  date_written=TimeVCL2DOS(MsgInfo.DateWritten);
  date_arrived=TimeVCL2DOS(MsgInfo.DateArrived);

  utc_ofs=MsgInfo.UTCOfs;
  replyto=MsgInfo.ReplyTo;
  memmove(replies,MsgInfo.Replies,sizeof(replies));
  return *this;
}
//---------------------------------------------------------------------------
/*
void __fastcall TFTNMsgBody::LoadFromStream(TStream *Stream)
{
  Size: Integer;
  S: string;

  BeginUpdate();
  try
  {
    Size := Stream.Size - Stream.Position;
    SetString(S, nil, Size);
    Stream.Read(Pointer(S)^, Size);
    SetTextStr(S);
  }
  __finally
  {
    EndUpdate();
  }
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCustomFTNMsg::TCustomFTNMsg(TComponent* Owner)
  : TComponent(Owner)
{
  FMsgInfo=new TMsgInfo;
  FHeader=new TFTNMsgHeader;
  FLines=new TFTNMsgBody;
  FKludges=new TKludges;
  FVias=new TKludges;
  FSeenBys=new TKludges;
}
//---------------------------------------------------------------------------
__fastcall TCustomFTNMsg::~TCustomFTNMsg()
{
  delete FHeader;
  FHeader=NULL;
  delete FMsgInfo;
  FMsgInfo=NULL;
  FLines->Free();
  FLines=NULL;
  delete FKludges;
  FKludges=NULL;
  delete FVias;
  FVias=NULL;
  delete FSeenBys;
  FSeenBys=NULL;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCustomFTNMsg::GetOrigin(void)
{
AnsiString Result="";
int iPos;
  for(int i=FLines->Count-1;i>=0;i--)
  {
    iPos=FLines->Strings[i].Pos(" * Origin:");
    if(iPos)
    {
      Result=FLines->Strings[i].Delete(1,iPos+10);
      for(int j=Result.Length()-1;j>=0;j--)
        if(Result[j]=='(')
        {
          Result.Delete(j-1,32);
          break;
        }
      break;
    }
  }
  return Result.Trim();
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetOrigin(AnsiString Value)
{
AnsiString asNewOrigin;
int FoundLine=-1;
  asNewOrigin.sprintf(" * Origin: %s (%s)",Value.c_str(),FOrigAddr.AsString.c_str());
  for(int i=FLines->Count-1;i>=0;i--)
    if(FLines->Strings[i].Pos(" * Origin:"))
    {
      FoundLine=i;//По хорошему сюда необходимо добавить инвалидацию "посторонних" оригинов
      break;
    }
  if(FoundLine>=0)
  {
    FLines->Delete(FoundLine);
    FLines->Insert(FoundLine,asNewOrigin);
  }
  FLines->Add(asNewOrigin);
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetOrigAddr(TFTNAddress &Value)
{
  FOrigAddr=Value;
  FHeader->OrigNode=(WORD)FOrigAddr.Node;
  FHeader->OrigNet=(WORD)FOrigAddr.Net;
  if(FOrigAddr.Point)
  {
    FKludges->KludgeByName("FMPT")->AsString=AnsiString(FOrigAddr.Point);
  }

}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetDestAddr(TFTNAddress &Value)
{
  FDestAddr=Value;
  FHeader->DestNode=(WORD)FDestAddr.Node;
  FHeader->DestNet=(WORD)FDestAddr.Net;
  if(FDestAddr.Point)
  {
    FKludges->KludgeByName("TOPT")->AsString=AnsiString(FDestAddr.Point);
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetOrigTime(TDateTime Value)
{
  FOrigTime=Value;
  AnsiString DateStr=FormatDateTime("dd mmm yy  hh:nn:ss",Value);
  strncpy(FHeader->DateTime,DateStr.c_str(),19);
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetFromName(AnsiString Value)
{
  strncpy(FHeader->FromUser,Value.c_str(),35);
  FHeader->FromUser[35]=0;
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetToName(AnsiString Value)
{
  strncpy(FHeader->ToUser,Value.c_str(),35);
  FHeader->ToUser[35]=0;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCustomFTNMsg::GetToName(void)
{
  return AnsiString(FHeader->ToUser);
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SetSubject(AnsiString Value)
{
  strncpy(FHeader->Subject,Value.c_str(),71);
  FHeader->Subject[71]=0;
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::Clear(void)
{
  memset(FHeader,0,sizeof(TFTNMsgHeader));
  FLines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::InvalidateOldTechInfo(void)
{
int iPos;
AnsiString asTemp;
  for(int i=0;i<FLines->Count;i++)
  {
    asTemp=FLines->Strings[i];
    iPos=asTemp.Pos("* Origin:");
    if(iPos)
    {
      asTemp[iPos]='+';
      FLines->Strings[i]=asTemp;
    }
    else
    {
      iPos=asTemp.Pos("--- ");
      if(iPos)
      {
        asTemp[iPos+1]='+';
        FLines->Strings[i]=asTemp;
      }
      else
      {
        iPos=asTemp.Pos("SEEN-BY");
        if(iPos)
        {
          asTemp[iPos+4]='+';
          FLines->Strings[i]=asTemp;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SaveToStream(TStream *Stream)
{
  Stream->WriteBuffer(FHeader,sizeof(TFTNMsgHeader));
  FLines->SaveToStream(Stream);
  Stream->WriteBuffer("",1);//Дописываем нолик в конец
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SaveToStreamPacked(TStream *Stream)
{
TPackedMsgHeader PackedMsgHeader;
AnsiString asTemp;
//  ZeroMemory(&PackedMsgHeader, sizeof(TPackedMsgHeader));
  PackedMsgHeader.OrigNode=FHeader->OrigNode;
  PackedMsgHeader.DestNode=FHeader->DestNode;
  PackedMsgHeader.OrigNet=FHeader->OrigNet;
  PackedMsgHeader.DestNet=FHeader->DestNet;
  PackedMsgHeader.Attr=FHeader->Attr;
  PackedMsgHeader.Cost=FHeader->Cost;
  strncpy(PackedMsgHeader.DateTime,FHeader->DateTime,19);
Stream->WriteBuffer(&PackedMsgHeader,sizeof(TPackedMsgHeader));
  Stream->WriteBuffer(FHeader->ToUser,strlen(FHeader->ToUser)+1);
  Stream->WriteBuffer(FHeader->FromUser,strlen(FHeader->FromUser)+1);
  Stream->WriteBuffer(FHeader->Subject,strlen(FHeader->Subject)+1);
  FKludges->SaveToStream(Stream);
  
  FLines->SaveToStream(Stream);
  asTemp="--- "+FTearlineText+"\r";
  Stream->WriteBuffer(asTemp.c_str(),asTemp.Length());
  asTemp="";
  asTemp.sprintf(" * Origin: %s (%s)\r",FOriginText.c_str(),FOrigAddr.As4dString.c_str());
  Stream->WriteBuffer(asTemp.c_str(),asTemp.Length());
  FVias->SaveToStream(Stream);
  
  FSeenBys->SaveToStream(Stream);
  Stream->WriteBuffer("",1);//Дописываем нолик в конец
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::LoadFromStream(TStream *Stream)
{
  Stream->ReadBuffer(FHeader,sizeof(TFTNMsgHeader));
  FLines->LoadFromStream(Stream);
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::LoadFromStreamPacked(TStream *Stream)
{
  throw Exception("function LoadFromStreamPacked is not designed");
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::SaveToFile(AnsiString FileName)
{
  TFileStream* FileStream=new TFileStream(FileName,fmCreate);
  try
  {
    SaveToStream(FileStream);
  }
  __finally
  {
    FileStream->Free();
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomFTNMsg::LoadFromFile(AnsiString FileName)
{
  Clear();
  TFileStream* FileStream=new TFileStream(FileName,fmOpenRead+fmShareDenyWrite);
  try
  {
    LoadFromStream(FileStream);
  }
  __finally
  {
    FileStream->Free();
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFTNMsg::TFTNMsg(TComponent* Owner):TCustomFTNMsg(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
namespace Ftnmsg
{
  void __fastcall PACKAGE Register()
  {
//     TComponentClass classes[2] = {__classid(TFTNMsg),__classid(TFTNXMsg)};
//     RegisterComponents("FIDO Tech", classes,1 );
  }
}
//---------------------------------------------------------------------------
