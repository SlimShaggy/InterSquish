//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FTNPKT.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TFTNPKT *)
{
  new TFTNPKT(NULL);
}
//---------------------------------------------------------------------------
__fastcall TFTNPKT::TFTNPKT(TComponent* Owner)
  : TComponent(Owner)
{
  FPacketHeader=new TPacketHeader;
  FMessages= new TListOfX<TFTNMsg>;
  Clear();
}
//---------------------------------------------------------------------------
__fastcall TFTNPKT::~TFTNPKT(void)
{
  delete FMessages;
  delete FPacketHeader;
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::ReadFromFile(AnsiString FileName)
{
}
//---------------------------------------------------------------------------
TFileStream * __fastcall TFTNPKT::CreatePKTFile(TDateTime dtCreate)
{
AnsiString asFileName;
TFileStream *fsPKT;
WORD year,mon,day,hour,min,sec,msec;
DWORD idname;

  while(true)
  {
    asFileName="";
    DecodeDate(dtCreate,year,mon,day);
    DecodeTime(dtCreate,hour,min,sec,msec);
    idname=(DWORD)(((DWORD)day<<27) | ((__int64)hour<<22) | ((__int64)min<<16)|((__int64)sec<<10)|(msec/10));
    asFileName.sprintf("%s\\%08.8x.pkt",FPath.c_str(),idname);
    if(FileExists(asFileName))
    {
      Sleep(50);
      continue;
    }
    else break;
  };
    fsPKT= new TFileStream(asFileName,fmCreate);
  return fsPKT;
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::WriteToFile(void)
{
TDateTime dtCreation=Now();
  TFileStream *fsPKT=CreatePKTFile(dtCreation);
  try
  {
  WORD Dummy;
    DecodeDate(dtCreation,FPacketHeader->Year,FPacketHeader->Month,FPacketHeader->Day);
    DecodeTime(dtCreation,FPacketHeader->Hour,FPacketHeader->Minute,FPacketHeader->Second,Dummy);
    FPacketHeader->Month-=(WORD)1;
    FPacketHeader->Baud=2400;    
    if(fsPKT->Write(FPacketHeader,sizeof(TPacketHeader))!=sizeof(TPacketHeader))
      throw Exception("Unable create .PKT file");
    for(int i=0;i<FMessages->Count;i++)
      FMessages->Items[i]->SaveToStreamPacked(fsPKT);
    fsPKT->Write("\x0",2);
    if(FOnAfterPacketCreate)
      FOnAfterPacketCreate(this);
  }
  __finally
  {
    delete fsPKT;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::SetOrigAddr(TNetAddr &Value)
{
  FPacketHeader->OrigNode=Value.Node;
  FPacketHeader->OrigNet=Value.Net;
  FPacketHeader->QOrgZone=Value.Zone;
  FPacketHeader->OrigZone=Value.Zone;
  FPacketHeader->OrigPoint=Value.Point;
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::SetDestAddr(TNetAddr &Value)
{
  FPacketHeader->DestNode=Value.Node;
  FPacketHeader->DestNet=Value.Net;
  FPacketHeader->QDstZone=Value.Zone;
  FPacketHeader->DestZone=Value.Zone;
  FPacketHeader->DestPoint=Value.Point;
}
//---------------------------------------------------------------------------
TNetAddr __fastcall TFTNPKT::GetOrigAddr(void)
{
TNetAddr NetAddr={0,0,0,0};
  NetAddr.Node=FPacketHeader->OrigNode;
  NetAddr.Net=FPacketHeader->OrigNet;
  NetAddr.Zone=FPacketHeader->QOrgZone;
  NetAddr.Point=FPacketHeader->OrigPoint;
  return NetAddr;
}
//---------------------------------------------------------------------------
TNetAddr __fastcall TFTNPKT::GetDestAddr(void)
{
TNetAddr NetAddr={0,0,0,0};
  NetAddr.Node=FPacketHeader->DestNode;
  NetAddr.Net=FPacketHeader->DestNet;
  NetAddr.Zone=FPacketHeader->QDstZone;
  NetAddr.Point=FPacketHeader->DestPoint;
  return NetAddr;
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::SetPassword(AnsiString Value)
{
  char *ps=Value.c_str();
  char *pd=FPacketHeader->Password;
  ZeroMemory(pd,PKT_PASSWORD_LENGTH);
  for(int i=0;(i<8) && ps[i];i++)
    pd[i]=ps[i];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFTNPKT::GetPassword(void)
{
char cPassword[9];
//  cPassword[8]=0;
  strncpy(cPassword,FPacketHeader->Password,8);
  return AnsiString(cPassword);
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::Clear()
{
  FMessages->Clear();
  ZeroMemory(FPacketHeader,sizeof(TPacketHeader));
  FPacketHeader->PacketType=2;
  FPacketHeader->CapValid=0x100;
  FPacketHeader->CapWord=1;
}
//---------------------------------------------------------------------------
void __fastcall TFTNPKT::SetPath(AnsiString Value)
{
  FPath=Value;
  while(FPath.LastDelimiter("\\.")==FPath.Length())
    FPath.SetLength(FPath.Length()-1);
}
//---------------------------------------------------------------------------
namespace Ftnpkt
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TFTNPKT)};
     RegisterComponents("FIDO Tech", classes, 0);
  }
}
//---------------------------------------------------------------------------
 