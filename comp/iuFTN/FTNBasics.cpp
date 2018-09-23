//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FTNBasics.h"
#include <stdio.h>
#include <log.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TCommonAddress::TCommonAddress(AnsiString Address)
{
TraceS(__FUNC__);
  SetAsString(Address);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TCommonAddress::TCommonAddress()
{
TraceS(__FUNC__);
  FIsFTN=false;
  FZone=0;
  FNet=0;
  FNode=0;
  FPoint=0;
  FUserName=0;
  FFTNDomain="";
  FHost="";
  FAccount="";
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TCommonAddress::TCommonAddress(int AZone,int ANet,int ANode,int APoint,AnsiString AUserName, AnsiString ADomain)
{
TraceS(__FUNC__);
  FIsFTN=true;
  FZone=AZone;
  FNet=ANet;
  FNode=ANode;
  FPoint=APoint;
  FUserName=AUserName;
  FFTNDomain=ADomain;
  FHost="";
  FAccount="";
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCommonAddress::GetAsRFCString()
{
AnsiString Result="";
TraceS(__FUNC__);
  FIsFTN=FZone && FNet;
  if(FIsFTN)
  {
    if(FUserName!="")
    {

    AnsiString FTNAccount=FUserName;
      FTNAccount.Unique();
      unsigned char *Ptr=(unsigned char *)FTNAccount.c_str();
      for(;*Ptr;Ptr++)
        if(!IsCharAlphaNumeric(*Ptr)|| (*Ptr>127))
          *Ptr='_';
      Result+=FTNAccount+"@";
    }
    Result.sprintf("p%u.f%u.n%u.z%u",FPoint,FNode,FNet,FZone);
    if(FFTNDomain!="")
      Result+="."+FFTNDomain;
  }
  else
  {
    if(FAccount!="")
    {
      Result=FAccount;
      if(FHost!="")
        Result+="@";
    }
    Result+=FHost;
  }
  if(FUserName!="")
    Result+=" ("+FUserName+")";
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCommonAddress::GetAs4dString()
{
TraceS(__FUNC__);
AnsiString Result="";
  if(FPoint)
    Result.sprintf("%d:%d/%d.%d",FZone,FNet,FNode,FPoint);
  else
    Result.sprintf("%d:%d/%d",FZone,FNet,FNode);
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCommonAddress::GetAs5dString()
{
TraceS(__FUNC__);
AnsiString Result=GetAs4dString();
  if(FFTNDomain!="" && FFTNDomain != "ftn")
    Result+="@"+FFTNDomain;
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TCommonAddress::SetAsString(AnsiString value)
{
int iPos;
TraceS(__FUNC__);
  Clear();
  if(value=="")
    return;
  value.Unique();
  iPos=value.Pos("<");// "Vasia Pupkin" <vp@usa.net>
  if(iPos)
  {
  TraceS(__FUNC__);
    FUserName=value;
    FUserName.Delete(iPos,FUserName.Length());
    value.Delete(1,iPos);
    iPos=value.Pos(">");
    if(iPos)
      value.Delete(iPos,value.Length());
  }
  iPos=value.Pos(" (");//  vp@usa.net (Vasia Pupkin)
  TraceS(__FUNC__);
  if(iPos)
  {
    FUserName=value;
    FUserName.Delete(1,iPos+1);
    value.Delete(iPos,value.Length());
    iPos=FUserName.Pos(")");
    if(iPos)
      FUserName.Delete(iPos,FUserName.Length());
  }
  FIsFTN=strchr(value.c_str(),':');
  iPos=value.Pos("@");
TraceS(__FUNC__);
  if(FIsFTN)
  {
    sscanf(value.c_str(),"%u:%u/%u.%u",&FZone,&FNet,&FNode,&FPoint);
    if(iPos)
        FFTNDomain=value.c_str()+iPos;
  }
  else
  {
  TraceS(__FUNC__);
  char buf[256];
    buf[0]=0;
    if(iPos)
    {
      FAccount=value;
      FAccount.Delete(iPos,FAccount.Length());
      value.Delete(1,iPos);
    }
    char *pcAcc=value.c_str();
    if((value.Length()>2) && (pcAcc[0]=='p') && isdigit(pcAcc[1]))
      sscanf(pcAcc,"p%u.f%u.n%u.z%u.%255s",&FPoint,&FNode,&FNet,&FZone,buf);
    if(FZone && FNet)
    {
      FIsFTN=true;
//      if(value!="")
//        FFTNDomain=value;
//      else
        FFTNDomain=AnsiString(buf);
      FHost=FFTNDomain;
    }
    else
    {
      FHost=value;
//    if(iPos)
//      FDomain.Delete(1,iPos);
    }
  }
TraceS(__FUNC__);
  FUserName=FUserName.Trim();
  if(FUserName.c_str()[0]=='"')
  {
    FUserName=AnsiString(FUserName.c_str()+1,FUserName.Length()-2);
  }
  FHost=FHost.Trim();
  FAccount=FAccount.Trim();
  FFTNDomain=FFTNDomain.Trim();
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TCommonAddress::Clear(void)
{
TraceS(__FUNC__);
  FZone=FNet=FNode=FPoint=0;
  FUserName=FHost=FAccount=FFTNDomain="";
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCommonAddress::GetAsString()
{
  FIsFTN=FZone && FNet;
  return FIsFTN ? GetAs5dString() : GetAsRFCString();
}
//---------------------------------------------------------------------------
void __fastcall TCommonAddress::SetAsFTSStruct(TNetAddr &Value)
{
TraceS(__FUNC__);
  FZone=Value.Zone;
  FNet=Value.Net;
  FNode=Value.Node;
  FPoint=Value.Point;
  FHost="";
  FAccount="";
  FIsFTN=true;
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
TNetAddr __fastcall TCommonAddress::GetAsFTSStruct()
{
TraceS(__FUNC__);
TNetAddr Result;
  Result.Zone=(WORD)FZone;
  Result.Net=(WORD)FNet;
  Result.Node=(WORD)FNode;
  Result.Point=(WORD)FPoint;
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------

