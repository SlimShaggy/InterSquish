//---------------------------------------------------------------------------
//#include <vcl.h>
//#pragma hdrstop

#include "iuIPAddr.h"
#include <stdio.h>
#include <string.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
namespace Iuipaddr
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[] = {__classid(TTwitIpCfg)
                                  };
     RegisterComponents("FIDO Tech", classes, 0);
  }
}
/*
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIPAddress::TiuIPAddress(AnsiString ASocketAddress)
{
  SetAsString(ASocketAddress);
}
//---------------------------------------------------------------------------
__fastcall TiuIPAddress::TiuIPAddress(char *ASocketAddress)
{
  ScanCharLine(ASocketAddress);
}
//---------------------------------------------------------------------------
__fastcall TiuIPAddress::TiuIPAddress(const SOCKADDR_IN & ASockAddr)
{
    //TODO: Add your source code here
}
//---------------------------------------------------------------------------
bool __fastcall TiuIPAddress::GetIsMasked()
{
    return FIsMasked;
}
//---------------------------------------------------------------------------
void __fastcall TiuIPAddress::ScanCharLine(char *CharLine)
{
char cOctets[4][4];
char *Ptr=CharLine;
  while(*Ptr)
  {
    if(*Ptr=='.')
      *Ptr=0x20;
    Ptr++;
  }
  ZeroMemory(cOctets,16);
//  FOctets[0]=FOctets[1]=FOctets[2]=FOctets[3]=1111;
  sscanf(CharLine,"%s %s %s %s",cOctets[0], cOctets[1], cOctets[2], cOctets[3]);
  for(int i=0;i<4;i++)
  {
    FOctets[i]=1111;
    if(cOctets[i][0] && isdigit(cOctets[i][0]))
      sscanf(cOctets[i],"%d",&FOctets[i]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TiuIPAddress::SetAsString(AnsiString value)
{
  FString = value;
  ScanCharLine(FString.c_str());
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuIPAddress::GetAsString()
{
    return FString;
}
//---------------------------------------------------------------------------
void __fastcall TiuIPAddress::SetAddresMask(unsigned int value)
{
    FAddressMask = value;
}
//---------------------------------------------------------------------------
void __fastcall TiuIPAddress::SetSockAddr(const SOCKADDR_IN &ASockAddr)
{
//    FSockAddr = ASockAddr;
}
//---------------------------------------------------------------------------
SOCKADDR_IN & __fastcall TiuIPAddress::GetSockAddr()
{
    return FSockAddr;
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
__fastcall TTwitIpCfg::TTwitIpCfg(TComponent* Owner):TCustomCfg(Owner)
{
  FNNTPList=new TListOfX<TiuIPAddress>;
  FSMTPList=new TListOfX<TiuIPAddress>;
  FPOP3List=new TListOfX<TiuIPAddress>;
  FList=new TListOfX<TiuIPAddress>;
}
//---------------------------------------------------------------------------
__fastcall TTwitIpCfg::~TTwitIpCfg()
{
  delete FNNTPList;
  delete FSMTPList;
  delete FPOP3List;
  delete FList;
}
//---------------------------------------------------------------------------
void __fastcall TTwitIpCfg::Clear()
{
  FNNTPList->Clear();
  FSMTPList->Clear();
  FPOP3List->Clear();
  FList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TTwitIpCfg::ImportCfgLine(char *Line)
{
//char cBuf[MAX_LINE_SIZE+1];
static const char cTagBuf_NNTP[]="NNTPTWITIP";
static const char cTagBuf_SMTP[]="SMTPTWITIP";
static const char cTagBuf_POP3[]="POP3TWITIP";
static const char cTagBuf_All[] ="TWITIPADDR";
//char cTestBuf[32];
TListOfX<TiuIPAddress> *List;
int i;
  CharUpperBuff(Line,10);
  if(strstr(Line,cTagBuf_All)==Line)
    List=FList;
  else if(strstr(Line,cTagBuf_NNTP)==Line)
    List=FNNTPList;
  else if(strstr(Line,cTagBuf_SMTP)==Line)
    List=FSMTPList;
  else if(strstr(Line,cTagBuf_POP3)==Line)
    List=FPOP3List;
  else
    return;
//попробовать sizeof...
  for(i=sizeof(cTagBuf_NNTP);(Line[i]==32)||(Line[i]==9);i++);

  TiuIPAddress *TwitAddress=new TiuIPAddress(Line+i);

    List->Add(TwitAddress);
}
*/

__fastcall TTwitIpCfg::TTwitIpCfg(TComponent* Owner):TCustomCfg(Owner)
{
  FNNTPList=new TStringList;
  FSMTPList=new TStringList;
  FPOP3List=new TStringList;
  FList=new TStringList;
}
//---------------------------------------------------------------------------
__fastcall TTwitIpCfg::~TTwitIpCfg()
{
  delete FNNTPList;
  delete FSMTPList;
  delete FPOP3List;
  delete FList;
}
//---------------------------------------------------------------------------
void __fastcall TTwitIpCfg::Clear()
{
  FNNTPList->Clear();
  FSMTPList->Clear();
  FPOP3List->Clear();
  FList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TTwitIpCfg::ImportCfgLine(char *Line)
{
//char cBuf[MAX_LINE_SIZE+1];
static const char cTagBuf_NNTP[]="NNTPTWITIP";
static const char cTagBuf_SMTP[]="SMTPTWITIP";
static const char cTagBuf_POP3[]="POP3TWITIP";
static const char cTagBuf_All[] ="TWITIPADDR";
//char cTestBuf[32];
TStringList *List;
int i;
  CharUpperBuff(Line,10);
  if(strstr(Line,cTagBuf_All)==Line)
    List=FList;
  else if(strstr(Line,cTagBuf_NNTP)==Line)
    List=FNNTPList;
  else if(strstr(Line,cTagBuf_SMTP)==Line)
    List=FSMTPList;
  else if(strstr(Line,cTagBuf_POP3)==Line)
    List=FPOP3List;
  else
    return;
//попробовать sizeof...
  for(i=sizeof(cTagBuf_NNTP);(Line[i]==32)||(Line[i]==9);i++)
    ;//Ничего не делаем, только пропускаем пробелы
//  TiuIPAddress *TwitAddress=new TiuIPAddress(Line+i);
  List->Add(/*Trim*/(Line+i));
}

//---------------------------------------------------------------------------

