//---------------------------------------------------------------------------

#include "isNNTP.h"
#include "isInit.h"

#ifdef SHAREWARE
#include "CRC32.h"
#endif

#include "log.h"
//#include <Registry.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Cfg"
#pragma link "iuInterSquishServer"
#pragma link "iuNNTPServer"
#pragma link "iuServer"
#pragma link "FTNDataSet"
#pragma link "iuIPAddr"
#pragma resource "*.dfm"

TISsNNTP *ISsNNTP;
//---------------------------------------------------------------------------
__fastcall TISsNNTP::TISsNNTP(TComponent* Owner)
    : TService(Owner)
{
  TraceS("create nntp service");
//#ifndef SHAREWARE
//  tmr->Enabled=false;
//  Tim2->Enabled=false;
//#endif
    this->IssNNTP=new TiuIssNNTPServer(Owner);
    this->TextCfg=new TTextCfg(Owner);
    this->TwitIpCfg=new TTwitIpCfg(Owner);
    this->ScriptCfg=new TScriptCfg(Owner);
}

__fastcall TISsNNTP::~TISsNNTP()
{
    /*if(this->IssNNTP->SessionsCount>0)
    {
        this->IssNNTP->Close();
    }
    delete this->IssNNTP;
    delete this->TextCfg;
    delete this->TwitIpCfg;
    delete this->ScriptCfg;
*/
}
//---------------------------------------------------------------------------
TServiceController __fastcall TISsNNTP::GetServiceController(void)
{
    //this->LogMessage("starting service",1,1,1);

    return (TServiceController) NNTPServiceController;
}

void __stdcall NNTPServiceController(unsigned CtrlCode)
{
    ISsNNTP->Controller(CtrlCode);
}
//---------------------------------------------------------------------------

void __fastcall TISsNNTP::InterSquishStart(TService *Sender,
      bool &Started)
{
  TraceS("enter start nntp service");
  TextCfg->Path=ParamStr(0).Delete(ParamStr(0).LastDelimiter("."),4)+".cfg";
  TwitIpCfg->Path=TextCfg->Path;
  ScriptCfg->Path=TextCfg->Path;
/*
  AnsiString asAreasCfg=TextCfg->ParamAsString("AreasCfg");
  if(asAreasCfg=="")
    asAreasCfg=TextCfg->ParamAsString("SquishCfg");
  if(asAreasCfg=="")
  {
    asAreasCfg=TextCfg->ParamAsString("FastechoCfg");
    FastechoCfg->Path=asAreasCfg;
//    IssNNTP->SquishCfgName=FastechoCfg;
  }
  else
  {
    SquishCfg->Path=asAreasCfg;
//    IssNNTP->SquishCfgName=SquishCfg;
  }
  AnsiString asUsersCfgName=TextCfg->ParamAsString("UsersCfg");
  if(asUsersCfgName!="")
    UsersCfg->Path=asUsersCfgName;
*/
  ReadNNTPServerConfiguration(IssNNTP, TextCfg);
  /*
  ISS->LogName=TextCfg->ParamAsString("LogFileName");
  ISS->LogLevel=TextCfg->ParamAsInt("LogLevel");
  ISS->Port=TextCfg->ParamAsInt("NNTPPort");
  ISS->TimeOut=TextCfg->ParamAsInt("ThreadTimeout")*1000;
  ISS->ThreadCacheSize=TextCfg->ParamAsInt("ThreadCacheSize");
*/
  IssNNTP->Open();


  Started=true;

}
//---------------------------------------------------------------------------

void __fastcall TISsNNTP::InterSquishStop(TService *Sender,
      bool &Stopped)
{
  TraceS("");
  IssNNTP->Close();
  Stopped=true;
  TraceS("");
}
//---------------------------------------------------------------------------
void __fastcall TISsNNTP::tmrTimer(TObject *Sender)
{
#ifdef SHAREWARE
static char Count=4;
  Count--;
  if(Count)
    return;

 int h=FileOpen(ParamStr(0),fmShareDenyNone);
  if(h>=0)
  {
    static struct
    {
      char cm1[4];
      long cc1;
    } sgn={{'s','u','v','i'},0};
    int iSize=GetFileSize((void*)h,0);
    unsigned char *mem=new unsigned char[iSize];
    try
    {
      long *Ptr=(long*)mem;
      FileRead(h,mem,iSize);
      long lSign=*((long*)sgn.cm1);
      for(int i=0;i<iSize/4;i++)
        if(*(Ptr++)==lSign)
          break;
      sgn.cc1=*Ptr;
      *Ptr=0;
      Tag=crnc32(mem,iSize)!=sgn.cc1;
/*
      if(Tag)
        FileClose(FileCreate("NOT_OK!.flg"));
      else
        FileClose(FileCreate("OK!.flg"));
*/
    }
    __finally
    {
      delete [] mem;
      FileClose(h);

    }
  }
#endif
  tmr->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TISsNNTP::Tim2Timer(TObject *Sender)
{
#ifdef SHAREWARE
  if(Tag)
    IssNNTP->Tag=IssNNTP->Tag+1;
#endif
}
//---------------------------------------------------------------------------
