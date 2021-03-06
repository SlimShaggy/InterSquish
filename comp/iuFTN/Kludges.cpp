//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <inifiles.hpp>
#include "Kludges.h"
#include "FTNBasics.h"
#include "log.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/*
AnsiString __fastcall TAreaInfo::getInternalName(AnsiString postingName)
{
    return postingName;
}

__fastcall TAreaInfo::TAreaInfo()
{
    Format=afUnknown;
    Group=IsPassthru=MaxCount=MaxAge=0;
}

AnsiString __fastcall TAreaInfo::getExternalName(AnsiString tagName)
{
    AnsiString OutName;

    if (this->MaskFileName=="")
        return tagName;
    TIniFile *maskfile=new TIniFile(this->MaskFileName);

    TStringList *slSection=new TStringList();
    maskfile->ReadSection(tagName,slSection);
    if (slSection->Count>0) //���� �������� ������������
    {
        OutName=maskfile->ReadString(tagName,"distrib","")+"."+tagName;
    }

    delete maskfile;
    delete slSection;

    return OutName;
}


*/

//---------------------------------------------------------------------------
AnsiString __fastcall MSGID2MessageId(AnsiString MSGID)
{
char cPart1[1024];
char cStamp[1024];
AnsiString asResult;
  TraceS(__FUNC__);
  sscanf(MSGID.c_str(),"%s %s",cPart1,cStamp);
TFTNAddress Address(cPart1);
    asResult.sprintf("<%s@%s",cStamp,Address.AsRFCString.c_str());
    if(Address.IsFTN && (Address.FTNDomain==""))
      asResult+=".ftn";
    asResult+=">";
  TraceS(__FUNC__);
  return asResult;
}
//---------------------------------------------------------------------------
AnsiString __fastcall ExtractFTNAddr(AnsiString MSGID)
{
  TraceS(__FUNC__);
int zone,net,node,point;
AnsiString asResult;
  zone=net=node=point=0;
  if(isdigit(MSGID.c_str()[0]))
  {
    sscanf(MSGID.c_str(),"%u:%u/%u.%u",&zone,&net,&node,&point);
  }
  if(zone && net/* && node*/) //������ ����� ���� � ������ �����
  {
    asResult.sprintf("p%u.f%u.n%u.z%u.fidonet.org",point,node,net,zone);
  }
  TraceS(__FUNC__);
  return asResult;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TKludge::TKludge(AnsiString KludgeLine)
{
  TraceS(__FUNC__);
  char *Ptr=strchr(KludgeLine.c_str(),'\x20');
  if(Ptr)
  {
    FName=AnsiString(KludgeLine.c_str(),Ptr-KludgeLine.c_str()).Trim();
    FValue=AnsiString(Ptr).Trim();
  }
  else
    FName=KludgeLine;
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TKludge::TKludge(AnsiString Name, AnsiString Value)
{
  TraceS(__FUNC__);
  FName=Name.Trim();
  FValue=Value.Trim();
}
//---------------------------------------------------------------------------
void __fastcall TKludge::SetName(AnsiString Value)
{
  FName=Value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludge::GetName(void)
{
  return FName;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludge::GetKludgeString(void)
{
  TraceS(__FUNC__);
  if (!AnsiCompareText(FName,"SEEN-BY:"))
  {
    return FName+" "+FValue;
  }
  if(!AnsiCompareText(FName,"AREA:"))
  {
    return FName+FValue;
  }
  return "\x1"+FName+" "+FValue;
}
//---------------------------------------------------------------------------
TKludge& __fastcall TKludge::operator = (const AnsiString &KludgeData)
{

  return *this;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCustomKludges::TCustomKludges(void)
//  : TPersistent()
{
  FKludgeList=new TListOfX<TKludge>;
}
//---------------------------------------------------------------------------
__fastcall TCustomKludges::TCustomKludges(AnsiString ABody)
//  : TPersistent()
{
  FKludgeList=new TListOfX<TKludge>;
  Body=ABody;
}
//---------------------------------------------------------------------------
__fastcall TCustomKludges::~TCustomKludges(void)
{

  delete FKludgeList;
}
//---------------------------------------------------------------------------
void __fastcall TCustomKludges::Import(AnsiString ABody)
{
  TraceS(__FUNC__);
  AnsiString asTemp=ABody.Trim();

  for(char *cPtr=asTemp.c_str();*cPtr;cPtr++)
    if(*cPtr=='\x1')
      *cPtr='\r';
  FKludgeList->Clear();
  TStringList *slKludges=new TStringList;
    TraceS(__FUNC__);
  try
  {
    slKludges->Text=asTemp;
    for(int i=0;i<slKludges->Count;i++)
      FKludgeList->Add(new TKludge(slKludges->Strings[i]));
  }
  __finally
  {
    delete slKludges;
  }
/*
char *cPtr=asTemp.c_str();
char *cNext;

  while(true)
  {
    cNext=strchr(cPtr,'\x1');
    if(!cNext)
      cNext=strchr(cPtr,'\r');
    if(!cNext)
    {
      cNext=strchr(cPtr,'\r');
//      if(cNext)
        FKludgeList->Add(new TKludge(AnsiString(cPtr,cNext-cPtr)));
      break;
    }
    else
    {
      FKludgeList->Add(new TKludge(AnsiString(cPtr,cNext-cPtr)));
    }
    cPtr=cNext+1;
  }
*/
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCustomKludges::Export(void)
{
AnsiString Result;
TKludge *Kludge;
  TraceS(__FUNC__);
  for(int i=0;i<FKludgeList->Count;i++)
  {
    Kludge=FKludgeList->Items[i];
    if(Kludge->AsString!="")
      Result+=Kludge->AsKludgeString+"\r";
//      Result+=Kludge->Name+" "+Kludge->AsString+"\r";
  }
    TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
TKludge * __fastcall TCustomKludges::KludgeByName(AnsiString Name)
{

    AnsiString in;
    AnsiString out;

    if (Name.SubString(Name.Length(),1)==":")
    {
        in=Name.SubString(0,Name.Length()-1);
    }else
    {
        in=Name;
    }

    //TKludge *tk;
  //TraceS(__FUNC__);
  for(int i=0;i<FKludgeList->Count;i++)
  {
    //tk=FKludgeList->Items[i];
    out=FKludgeList->Items[i]->Name;

    if (out.SubString(out.Length(),1)==":")
    {
        out=out.SubString(0,out.Length()-1);
    }

    if(AnsiCompareText(in,out)==0)
    {
        //tk=FKludgeList->Items[i];
        return FKludgeList->Items[i];
    }
  }
  TKludge *NewKludge=new TKludge(Name,"");
  FKludgeList->Add(NewKludge);
  return NewKludge;
/*
AnsiString Result="";
AnsiString asUpperBody=FBody.UpperCase();
int iPos=asUpperBody.Pos("\0x1"+Name.UpperCase());
  if(iPos)
  {
    Result=(FBody.SubString(iPos+Name.Length()+1,128)).TrimLeft();
    iPos=Result.Pos("\x01");
    if(iPos)
      Result.SetLength(iPos-1);
  }
  return Result;
*/
}
//---------------------------------------------------------------------------
void __fastcall TCustomKludges::Add(TKludge *Kludge)
{
  FKludgeList->Add(Kludge);
}
//---------------------------------------------------------------------------
void __fastcall TCustomKludges::Delete(AnsiString Name)
{
  for(int i=0;i<FKludgeList->Count;i++)
    if(!AnsiCompareText(Name,FKludgeList->Items[i]->Name))
      FKludgeList->Delete(i);
}
//---------------------------------------------------------------------------
void __fastcall TCustomKludges::SaveToStream(TStream *Stream)
{
TKludge *Kludge;
AnsiString asTemp;
  TraceS(__FUNC__);
  for(int i=0;i<FKludgeList->Count;i++)
  {
    Kludge=FKludgeList->Items[i];
    if(Kludge->AsString!="")
    {
      asTemp=Kludge->AsKludgeString+"\r";
      Stream->Write(asTemp.c_str(),asTemp.Length());
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomKludges::Clear(void)
{
  FKludgeList->Clear();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TKludges::TKludges(void)
  : TCustomKludges()
{
}
//---------------------------------------------------------------------------
__fastcall TKludges::TKludges(AnsiString ABody)
  : TCustomKludges(ABody)
{
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetMsgId(void)
{
  return KludgeByName("MSGID:")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetReply(void)
{
  return KludgeByName("REPLY:")->AsString;
}
//-------------------------------------------
AnsiString __fastcall TKludges::getFlags(void)
{
    return KludgeByName("FLAGS")->AsString;
}

void __fastcall TKludges::setFlags(AnsiString fl)
{
    KludgeByName("FLAGS")->AsString=fl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetPID(void)
{
  return KludgeByName("PID:")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetTID(void)
{
  return KludgeByName("TID:")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetRFC_Message_ID(void)
{
  return KludgeByName("RFC-Message-ID:")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetRFC_References(void)
{
  return KludgeByName("RFC-References:")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TKludges::GetReplyAddr(void)
{
    AnsiString result;

    result=KludgeByName("REPLYADDR:")->AsString;

return result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
namespace Kludges
{
  void __fastcall PACKAGE Register()
  {
//     TComponentClass classes[1] = {__classid(TKludges)};
//     RegisterComponents("FIDO Tech", classes, 0);
  }
}
*/
//---------------------------------------------------------------------------
