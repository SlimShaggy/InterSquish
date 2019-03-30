//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <time.h>
#include <values.h>
#include "Cfg.h"
#include "Transliterates.h"
#include "iuInterSquishServer.h"

#ifdef SHAREWARE
#include "RegistryInfo.h"
#include "Rsa.h"
#endif

#include "iuVerInfo.h"
#include "iuConsole.h"
#include "iuEncoders.h"
//#include "crc32.h"
#include "log.h"

#include "scriptUtils.h"
//TVersionInfo *viISS=0;
//TiuConsole *ISConsole;

#pragma package(smart_init)

#ifdef SHAREWARE
TRegistryData *RD=0;
int fh[3]={0,0,0};
struct TSerialNo *SN=0;
AnsiString Fcs="";
AnsiString asTableEntry;
static R_RSA_PUBLIC_KEY RegPublicKey;
static HANDLE H1, H2;
static R_RSA_PUBLIC_KEY SNPublicKey;
int Fics;
unsigned int uiOutLen=0;
unsigned int uiOutLen2=0;
//unsigned char CryptedSNr_[sizeof(TSerialNo)*2]=".pkt\x0. * Origin: \x0Service error\x0.tmp\x0Unable create flag file %s\r\n\x0Invalid Message: %s";
//unsigned char CryptedSNc_[sizeof(TSerialNo)*2]="1234567890123456789012345678901234567890123456789012345678901234567890\x0$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
unsigned char *CryptedSNr=0;
unsigned char *CryptedSNc=0;
#endif
//-------------------------------------------------------------
//;SERVICENAME    - им€ сервиса ("NNTP","SMTP" или "POP3")
//;REMOTE_IP      - ip-адрес пользовател€
//;THREAD_ID      - id вызывающего потока
//;COMMAND        - отрабатываема€ в данный момент RFC-команда
//;ACC_NAME       - им€ аккаунта пользовател€
//;ACC_PASSWORD   - пароль

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssNNTPServer::TiuIssNNTPServer(TComponent* Owner)
  : TiuCustomNNTPServer(Owner)
{
  FAreasConfigType=acUnknown;
  TraceS("");
#ifdef SHAREWARE
  FRegKeyExist=FSNDecrypted=false;
  CryptedSNc=new char[(sizeof(TSerialNo)*4+8)];
  CryptedSNr=CryptedSNc+(sizeof(TSerialNo)*2+4);
  RD=new TRegistryData;
  setmem(CryptedSNc,(sizeof(TSerialNo)*2+4), '@');
  SN=new TSerialNo;
  setmem(CryptedSNr,(sizeof(TSerialNo)*2+4), '*');
#endif
  UpdateServerInfo();
  TraceS("");
#ifdef SHAREWARE
/*
  void *vPtr;

  H1= FindResource(HInstance, "iuRK", RT_RCDATA);
  if(H1)
    H2= LoadResource(HInstance, H1);
  if(H2)
  {
    vPtr = LockResource(H2);
    if(vPtr)
      memcpy(&RegPublicKey,vPtr,sizeof(R_RSA_PUBLIC_KEY));
  }

    AnsiString asfn=ParamStr(0);
    asfn[asfn.Length()-2]='k';
    asfn[asfn.Length()-1]='e';
    asfn[asfn.Length()]='y';

    fh[2]=FileOpen(asfn,fmOpenRead);
    if(fh[2])
    {
      int RealReaded=FileRead(fh[2],RD,sizeof(TRegistryData));
      Fics=crnc32((unsigned char *)RD,RealReaded);
      FRegKeyExist=(AnsiString((char *)RD->Header.Signature,3)=="ISS");
      FileClose(fh[2]);
      RegPublicKey.bits=1024;
      ZeroMemory(SN,sizeof(TSerialNo));

      H1=H2=0;
      FSNDecrypted=!RSAPublicDecrypt((unsigned char*)SN,&uiOutLen,(unsigned char*)RD->CryptedSerialNo,sizeof(RD->CryptedSerialNo),&RegPublicKey);
      if(FSNDecrypted)
      {
      void *vPtr;
        H1= FindResource(HInstance, "iuPK", RT_RCDATA);
        if(H1)
          H2= LoadResource(HInstance, H1);
        if(H2)
        {
          vPtr = LockResource(H2);
          if(vPtr)
          {
            memcpy(&SNPublicKey,vPtr,sizeof(R_RSA_PUBLIC_KEY));
            SNPublicKey.bits=1024;
          }
        }
        if(SNPublicKey.bits==1024)
        {
        R_RANDOM_STRUCT randomStruct;
          asTableEntry=AnsiString(SN->TableEntry);
          AnsiString asResId="iuRS"+asTableEntry;
          H1= FindResource(HInstance, asResId.c_str(), RT_RCDATA);
          if(H1)
            H2= LoadResource(HInstance, H1);
          if(H2)
          {
            vPtr = LockResource(H2);
            if(vPtr)
            {
              memcpy(&randomStruct,vPtr,sizeof(R_RANDOM_STRUCT));
              asResId="iuSE"+AnsiString(SN->TableEntry);
              H1= FindResource(HInstance, asResId.c_str(), RT_RCDATA);
              if(H1)
                H2= LoadResource(HInstance, H1);
              if(H2)
              {
                vPtr = LockResource(H2);
                if(vPtr)
                 memcpy(CryptedSNr,vPtr,sizeof(TSerialNo)*2);
              }
            }
          }
          if(H1 && H2)
            RSAPublicEncrypt(CryptedSNc,&uiOutLen2,(unsigned char*)SN,sizeof(TSerialNo),&SNPublicKey,&randomStruct);
//        Fcs.sprintf(" %s/%08.8X",asTableEntry.c_str(),Fics);
//        PostingAllowed=(CryptedSNr[9]==CryptedSNc[9])&&(CryptedSNr[17]==CryptedSNc[17]);
      }
    }
  }
*/
#endif
}
//---------------------------------------------------------------------------
__fastcall TiuIssNNTPServer::~TiuIssNNTPServer()
{
  TraceS("");
#ifdef SHAREWARE
  delete RD;
  if(SN)
    delete SN;
  if(CryptedSNc)
    delete [] CryptedSNc;
  TraceS("");
#endif
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  TraceS(__FUNC__);
  SocketThread= new TiuIssNNTPServerThread(true,ClientSocket);
//!!!  SocketThread->Priority=tpIdle;
  TiuCustomNNTPServer::GetThread(Sender, ClientSocket, SocketThread);
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::Accept(TObject *Sender, TCustomWinSocket *Socket)
{
  TraceS(__FUNC__);
//  CriticalSection->Enter();
//try
//{
  TiuCustomNNTPServer::Accept(Sender, Socket);
/*
  if(FSquishCfg)
  {
  TraceS(__FUNC__);
    FSquishCfg->Refresh();
  TraceS(__FUNC__);
    if(FSquishCfgFileAge!=FSquishCfg->LastWriteTime)
    {
  TraceS(__FUNC__);
      FSquishCfgFileAge=FSquishCfg->LastWriteTime;
      NewsList->Clear();
  TraceS(__FUNC__);
      if(FSquishCfg->EchoAreas)
        for(int i=0;i<FSquishCfg->EchoAreas->Count;i++)
          if(!FSquishCfg->EchoAreas->Items[i]->IsPassthru)
            NewsList->AddObject(FSquishCfg->EchoAreas->Items[i]->Tag, FSquishCfg->EchoAreas->Items[i]);
    }
  }
  TraceS(__FUNC__);
*/
  UpdateServerInfo();
//}
//__finally
//{
//  CriticalSection->Leave();
//}
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
  TraceS(__FUNC__);
  TiuCustomNNTPServer::ClientDisconnect(Sender, Socket);
  UpdateServerInfo();
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::SetUsersCfgName(AnsiString Value)
{
  TraceS(__FUNC__);
  if(FUsersCfgName!=Value)
  {
    FUsersCfgName=Value;
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------

void __fastcall TiuIssNNTPServer::SetSquishCfgName(AnsiString Value)
{

  TraceS(__FUNC__);

  if(FSquishCfgName!=Value)
  {
    FSquishCfgName=Value;

//    BuildNewsGroupList();
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::SetDefaultAddres(AnsiString Value)
{
  FDefaultUserInfo.Address.AsString=Value;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServer::SetDefaultInternetGate(AnsiString value)
{
    FDefaultInternetGate = value;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssNNTPServerThread::TiuIssNNTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket):
  TiuCustomNNTPServerThread(CreateSuspended, ASocket)
{
  FUsersCfg=new TCustomUsersCfg(NULL);
  TraceS(__FUNC__);
  /*
#ifdef SHAREWARE
  PostingAllowed=false;
    if(H1 && H2)
//      if(!RSAPublicEncrypt(CryptedSNc,&uiOutLen2,(unsigned char*)SN,sizeof(TSerialNo),&SNPublicKey,&randomStruct))
      {
        Fcs.sprintf(" %s/%08.8X",asTableEntry.c_str(),Fics);
        PostingAllowed=(CryptedSNr[9]==CryptedSNc[9])&&(CryptedSNr[17]==CryptedSNc[17]);
      }
//  }
  TraceS(__FUNC__);
#else*/
  PostingAllowed=true;
  //#endif
}
//---------------------------------------------------------------------------
__fastcall TiuIssNNTPServerThread::~TiuIssNNTPServerThread(void)
{
  if(FUsersCfg)
    delete FUsersCfg;
  if(FSquishCfg)
    delete FSquishCfg;
  TraceS(__FUNC__);
  if(FSquishBase)
    delete FSquishBase;

  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::BuildNewsGroupList(void)
{
//CriticalSection->Enter();
try
{
    AnsiString outAreaName;
    //TStringList *areaSection=new TStringList();

  TraceS(__FUNC__);
    NewsList->Clear();

    TraceS(__FUNC__);
    if(FSquishCfg)
    {
  TraceS(__FUNC__);
      FSquishCfg->Refresh();
//      FSquishCfgFileAge=FSquishCfg->LastWriteTime;
      if(FSquishCfg->EchoAreas)
        for(int i=0;i<FSquishCfg->EchoAreas->Count;i++)
        {
          if(!FSquishCfg->EchoAreas->Items[i]->IsPassthru)
          {
            outAreaName=FSquishCfg->EchoAreas->Items[i]->Tag;
            outAreaName=SelectedGroup->getExternalName(outAreaName,FSquishCfg->EchoAreas->Items[i]->Group);


            NewsList->AddObject(outAreaName,FSquishCfg->EchoAreas->Items[i]);
          }
    }   }
  TraceS(__FUNC__);
/*
  FSNDecrypted=!RSAPublicDecrypt((unsigned char*)SN,&uiOutLen,(unsigned char*)RD->CryptedSerialNo,sizeof(RD->CryptedSerialNo),&RegPublicKey);
  if(FSNDecrypted)
  {
  HANDLE H1, H2;
  void *vPtr;
    H1= FindResource(HInstance, "iuPK", RT_RCDATA);
    if(H1)
      H2= LoadResource(HInstance, H1);
    if(H2)
    {
      vPtr = LockResource(H2);
      if(vPtr)
      {
        memcpy(&SNPublicKey,vPtr,sizeof(R_RSA_PUBLIC_KEY));
        SNPublicKey.bits=1024;

      }

    }
  }
*/
}
__finally
{
//CriticalSection->Leave();
}
  TraceS(__FUNC__);
  return FSquishCfg;
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::ValidateUser(TUserInfo &UserInfo)
{
bool Result=false;
int i;
  TraceS(__FUNC__);
//CriticalSection->Enter();
try
{
  FUsersCfg->Refresh();
  for(i=0;i<FUsersCfg->Users->Count;i++)
    if(FUsersCfg->Users->Items[i]->NAME==UserInfo.NAME)
    {
  TraceS(__FUNC__);
      if(FUsersCfg->Users->Items[i]->Password==UserInfo.Password)
      {
  TraceS(__FUNC__);
//        UserInfo.Address=FUsersCfg->Users->Items[i]->Address;
        UserInfo.Groups=FUsersCfg->Users->Items[i]->Groups;
        UserInfo.ROGroups=FUsersCfg->Users->Items[i]->ROGroups;
        UserInfo.Address=FUsersCfg->Users->Items[i]->Address;
#ifdef SHAREWARE
        if(CryptedSNr[5]!=CryptedSNc[5])
          UserInfo.ROGroups=UserInfo.Groups;
#endif
        if(!AnsiCompareText(FUsersCfg->Users->Items[i]->CharsetName,"OEM"))
          FTranslitMode=2;
        else if(!AnsiCompareText(FUsersCfg->Users->Items[i]->CharsetName,"ANSI"))
          FTranslitMode=1;
        else
          FTranslitMode=0;
        Result=true;
      }
      break;
    }
}
__finally
{
//  CriticalSection->Leave();
}
  TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
TAreaInfo * __fastcall TiuIssNNTPServerThread::GetAreaInfo(int Index)
{
  TraceS(__FUNC__);
  if(NewsList->Count<=Index)
    return NULL;
  else
    return (TAreaInfo *)NewsList->Objects[Index];
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::Transliterate(TObject* Sender,char* Src,char* Dest,bool ToOEM)
{
  switch(FTranslitMode)
  {
    case 0://KOI8
        OEM2KOI(Src,Dest);
        break;
    case 1://ANSI
        OemToChar(Src,Dest);
        break;
    default://OEM
      strcpy(Dest,Src);
  }
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::FindArticle(DWORD ANumber)
{
bool Founded;
  TraceS(__FUNC__);
  try
  {
    Founded=FSquishBase->FindByMsgNom(ANumber);
  }
  catch(...)
  {
     Founded=false;
     this->SendAnswer(430,"no such article found");
  }
  TraceS(__FUNC__);
  return Founded;
}
//---------------------------------------------------------------------------
/*
AnsiString __fastcall Plain2QuotedPrintable(AnsiString PlainText)
{
AnsiString Result="";
  unsigned char *Ptr=(unsigned char *)PlainText.c_str();
  while(*Ptr)
  {
    if(*Ptr>128)
      Result.sprintf("=%02.2X",*Ptr);
    else
      Result.sprintf("%c",*Ptr);
    Ptr++;
  }
  return Result;
}
*/
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::PrepareHeader(TArticleHeader &AHeader)
{
  TraceS(__FUNC__);
  AnsiString Allmsg;
  bool Result=FindArticle(AHeader.iNumber);
  if(!Result)
    return Result;
  AnsiString KludgesLine=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Kludges);
  TKludges Kludges(KludgesLine);
  AHeader.asSubj=RecodeLine(FSquishBase->FieldByName("Subj")->AsString);
  AHeader.asFrom="\"" + RecodeLine(FSquishBase->FieldByName("From")->AsString)+"\" <";
  //if(Kludges.RELPYADDR!="")
  if (Kludges.REPLYADDR!="")
  {
     if (Kludges.REPLYADDR.Pos("<") == 0 || Kludges.REPLYADDR.Pos(">") == 0)
     {
        AHeader.asFrom+=Kludges.REPLYADDR+">";
     } else
     {
        char *Ptr = Kludges.REPLYADDR.c_str();
        while (*Ptr != '<') Ptr++;
        Ptr++;
        while (*Ptr != '>')
        {
            AHeader.asFrom += *Ptr;
            Ptr++;
        }
      }
  }else
  {
    AnsiString asFromAcc=FSquishBase->FieldByName("From")->AsString.Trim();
    if(Kludges.KludgeByName("RFC-From:")->AsString !="") //есть постинг через гейт
    {
        asFromAcc=Kludges.KludgeByName("RFC-From:")->AsString.Trim();
        AHeader.asFrom=asFromAcc;
    }else
    {
        for(char *Ptr=asFromAcc.c_str();*Ptr;Ptr++)
            if(((*Ptr>='A') &&(*Ptr<='Z'))|| ((*Ptr>='a') &&(*Ptr<='z'))||((*Ptr>='0') &&(*Ptr<='9')))
                continue;
            else
                *Ptr=this->ISS->NameDelimiter;  //*Ptr='_';

            AHeader.asFrom+=asFromAcc+"@"+ExtractFTNAddr(Kludges.MSGID);
            AHeader.asFrom+=">";
    }
  }
  TraceS(__FUNC__);
  AHeader.asFrom+="\r\n";
  TraceS(__FUNC__);
  AHeader.asDate=FSquishBase->FieldByName("FTSC_date")->AsString+AnsiString();
  if(AHeader.asDate=="")
  {
    TDateTime DateTime;
    DateTime=FSquishBase->FieldByName("DateWritten")->AsDateTime+
    FSquishBase->FieldByName("TimeWritten")->AsDateTime;
    AHeader.asDate=FormatDateTime("dd mmm yy  hh:nn:ss",DateTime);
  }
  TraceS(__FUNC__);
  if(Kludges.MSGID=="") //пустой msgid - вырезать из origin
  {
        AnsiString origin;
        AnsiString realorigin;
        Allmsg=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Text);
        int pos=Allmsg.Pos("* Origin"); //выловить слово оригин
        origin=Allmsg.SubString(pos,80); //выловили строку с оригином
        pos=origin.Pos("\r"); //нашли конец оригина
        origin=origin.SubString(1,pos); //
        int posend;
        int posstart;
        for(int i=origin.Length();i>1;i--)
        {
            if(origin[i]==')') posend=i;
            if(origin[i]=='(')
            {
                posstart=i;
                break;
            }
        }
        realorigin=origin.SubString(posstart+1,posend-1-posstart);
        Kludges.KludgeByName("MSGID")->AsString=realorigin+" "+AnsiString("").sprintf(" %08.8x",time(NULL));
  }

//  проверка валидности msgid
    if(Kludges.MSGID!="")
    {
        int pos;
        pos=Kludges.MSGID.Pos(" ");
        if(pos==0) //нет timestamp
        {
            Kludges.KludgeByName("MSGID")->AsString=Kludges.MSGID+" "+AnsiString("").sprintf(" %08.8x",time(NULL));
        }
    }

  AHeader.asMessage_ID=MSGID2MessageId(Kludges.MSGID);
  AHeader.asReference=Kludges.REPLY;
  if(AHeader.asReference!="")
  {
    int pos;
    pos=AHeader.asReference.Pos(" ");
    if(pos!=0)
        AHeader.asReference=MSGID2MessageId(AHeader.asReference);
  }
  char *Ptr=((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Text;
  for(AHeader.iLines=0;*Ptr;Ptr++)
    if(*Ptr=='\r')
      AHeader.iLines++;
  AHeader.iSize=strlen(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Text);
  TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::SendNewsListDesc(void)
{
AnsiString asOutString;
//CriticalSection->Enter();
//try
//{
  for(int i=0;i<NewsList->Count;i++)
  {
    asOutString=((TAreaInfo*)NewsList->Objects[i])->Description;
    asOutString.Unique();
    if(ISS->DescriptionsInAnsi)
      OemToChar(asOutString.c_str(),asOutString.c_str());
    else
      OEM2KOI(asOutString.c_str(),asOutString.c_str());

//    asOutString=RecodeLine(asOutString);
//asOutString=RecodeLine("Description");

    asOutString=NewsList->Strings[i]+" "+asOutString;

    WriteLn(asOutString);
  }
// }
// __finally
// {
//  CriticalSection->Leave();
// }
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::SendNewNewsList(TStringList *slRequestedGroups,TDateTime RequestedTime)
{
//TDateTime DateTime;
  TraceS(__FUNC__);
TKludges Kludges;
  TraceS(__FUNC__);
  for(int i=0;i<slRequestedGroups->Count;i++)
  {
    if(SetActiveGroup(slRequestedGroups->Strings[i]))
    {
      if(FSquishBase->RecordCount>0)
      {
        FSquishBase->Last();
        while(!FSquishBase->Bof)
        {
          if((FSquishBase->FieldByName("DateArrived")->AsDateTime+FSquishBase->FieldByName("TimeArrived")->AsDateTime)>=RequestedTime)
          {
            Kludges.Body=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Kludges);
            WriteLn(MSGID2MessageId(Kludges.MSGID));
          }
          else
            break;
          FSquishBase->Prior();
          Sleep(0);
        }
      }
    }
    Sleep(3);
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall IsGroupByNumber(char *pcGroupsLine, char cGroup)
{
bool result=false;
char Buf[4];
  TraceS(__FUNC__);
  while(bool(pcGroupsLine=strchr(pcGroupsLine,'#')))
  {
    *((int *) Buf)=0;
    for(int i=0;i<3;i++)
    {
      if(isdigit(*(++pcGroupsLine)))
        Buf[i]=*pcGroupsLine;
      else
        break;
    }
  TraceS(__FUNC__);
    if(cGroup==atoi(Buf))
      return true;
  }
  TraceS(__FUNC__);
  return result;
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::SetActiveGroup(AnsiString NewsGroup)
{
int Index;
  TraceS(__FUNC__);
        if(FSquishBase)
        {
          delete FSquishBase;
          FSquishBase=NULL;
        }
//  CriticalSection->Enter();
  try
  {
    if(NewsList->Find(NewsGroup,Index))
    {
      TraceS(__FUNC__);
      char *pcGroupsLine=UserInfo.Groups.c_str();
      char cGroup=Areas[Index]->Group;
      if((cGroup && strchr(pcGroupsLine,cGroup)) || strchr(pcGroupsLine,'*') || IsGroupByNumber(pcGroupsLine,cGroup))
      {
        TraceS(__FUNC__);
        PostingAllowed=!strchr(UserInfo.ROGroups.c_str(),cGroup) || !strchr(UserInfo.ROGroups.c_str(),'*');
        if(Areas[Index]->Format==afSquish)
          FSquishBase=new TSquishBase(NULL);
        else
          if(Areas[Index]->Format==afJAM)
            FSquishBase=new TJAMBase(NULL);
          else
          {
//            ISS->Log("!!! Area '"+ISS->Areas[Index]->Tag+"' has unknown type. Assign a squish type\n");
            FSquishBase=new TSquishBase(NULL);
          }
        FSquishBase->OnTransliterate=Transliterate;
        FSquishBase->BasePath=((TAreaInfo*) (NewsList->Objects[Index]))->Path;
        FSquishBase->Open();
        TraceS(__FUNC__);
      }
      TraceS(__FUNC__);
    }

  }
    __finally
    {
//      CriticalSection->Leave();
    }

    TraceS(__FUNC__);
    if(FSquishBase)
      return FSquishBase->Active;
    else
      return false;
//  }
}
//---------------------------------------------------------------------------
int __fastcall TiuIssNNTPServerThread::GetArticleNom(int Index)
{
//  return Index>=0 ? FSquishBase->Indexes[Index].umsgid : 0;
  TraceS(__FUNC__);
  return Index>=0 ? FSquishBase->MsgNo[Index] : 0;
}
//---------------------------------------------------------------------------
int __fastcall TiuIssNNTPServerThread::GetArticlesCount(void)
{
  TraceS(__FUNC__);
  return FSquishBase->RecordCount;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::ProcessQUIT(AnsiString Argument)
{
  TraceS(__FUNC__);
  TiuCustomNNTPServerThread::ProcessQUIT(Argument);
  if(FSquishBase)
    FSquishBase->Close();
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::ProcessAUTHINFO_USER(AnsiString Argument)
{
  TraceS(__FUNC__);
  if(Argument!="")
  {
    FUserInfo.Name=Argument;
    SendAnswer(381,"More authentication information required");
  }
  else
    SendAnswer(281,"No username. Default permission granted");
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::ProcessAUTHINFO_PASS(AnsiString Argument)
{
AnsiString AuthString="";
  TraceS(__FUNC__);
  FUserInfo.Password=Argument;
  if(Server->ScriptingEnable)
  {
    AuthString=ExecInstruction(Server->ScriptCfg->InstructionByName("IsUserValid"),FScriptControl, FScriptArgsList,"");
  }
  if(AuthString=="")
//    DoValidateUser();
    UserValid=ValidateUser(FUserInfo);
  else
  {
    UserValid=true;
    FUserInfo.ImportLine(AuthString);
  }
  if(UserValid)
  {
    SendAnswer(281,"Authentication accepted");
    AuthChecked=true;
  }
  else
    SendAnswer(502,"No permission");
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
//void __fastcall TiuIssNNTPServerThread::DoValidateUser(void)
//{
//  TraceS(__FUNC__);
//  UserValid=ValidateUser(FUserInfo);
//  TraceS(__FUNC__);
//}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::RetriveArticle(AnsiString MessageID, AnsiString &Article)
{
  TraceS(__FUNC__);
TKludges Kludges;
  TraceS(__FUNC__);
  if(FSquishBase)
  {
    TraceS(__FUNC__);

    if(FSquishBase->RecordCount>0)
    {
      TraceS(__FUNC__);
        FSquishBase->Last();
        while(!FSquishBase->Bof)
        {
          Kludges.Body=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Kludges);
          if(MSGID2MessageId(Kludges.MSGID)==MessageID)
          {
            Article=RetriveCurrentArticle();
            return true;
          }
          FSquishBase->Prior();
        }

    }
      TraceS(__FUNC__);
    return TiuCustomNNTPServerThread::RetriveArticle(MessageID, Article);
  }
  else
  {
    TraceS(__FUNC__);
    SendAnswer(412,"no newsgroup has been selected");
      TraceS(__FUNC__);
    return false;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::RetriveArticle(int ArticleNumber, AnsiString &Article)
{
  TraceS(__FUNC__);
  if(FSquishBase)
  {
    if(FindArticle(ArticleNumber))
    {
      Article=RetriveCurrentArticle();
TraceS(__FUNC__);
      return true;
    }
    else
    {
    TraceS(__FUNC__);
      return TiuCustomNNTPServerThread::RetriveArticle(ArticleNumber, Article);
    }
  }
  {
  TraceS(__FUNC__);
    SendAnswer(412,"no newsgroup has been selected");
    return false;
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuIssNNTPServerThread::RetriveCurrentArticle(void)
{
    int lastslKluges;

  TraceS(__FUNC__);
//AnsiString Article("");
  FCurrentArticle="";
TStringList *slPath=new TStringList();
TStringList *slKluges=new TStringList();
TStringList *slRFCKluges=new TStringList();
TStringList *slText=new TStringList();
  TraceS(__FUNC__);
  try
  {
//    AnsiString asKludges=FSquishBase->FieldByName("Kludges")->AsString;
      AnsiString asKludges=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Kludges);
//FiCurrentArticle=FSquishBase->FieldByName("MsgID")->AsInteger;
      TraceS(__FUNC__);
      TKludges Kludges(asKludges);
      slKluges->Text=asKludges;
  TraceS(__FUNC__);
        TKludges *FtnKludges=new TKludges(asKludges);
        AnsiString KludgeName;
        AnsiString asTemp;
        for(int i=0;i<FtnKludges->KludgeList->Count;i++)
        {
          KludgeName=FtnKludges->KludgeList->Items[i]->Name;
          if(KludgeName!="" && KludgeName.Pos("RFC-")!=0
              && AnsiCompareText(KludgeName,"RFC-Newsgroups:")
              && AnsiCompareText(KludgeName,"RFC-Date:")
              && AnsiCompareText(KludgeName,"RFC-Lines:")
              && AnsiCompareText(KludgeName,"RFC-To:")
              && AnsiCompareText(KludgeName,"RFC-Message-ID:")
              && AnsiCompareText(KludgeName,"RFC-References:")
              && AnsiCompareText(KludgeName,"RFC-From:"))
            {
                asTemp=FtnKludges->KludgeList->Items[i]->AsString;
                if(KludgeName[KludgeName.Length()]==':')
                    KludgeName=KludgeName.SubString(0,KludgeName.Length()-1);
                if(KludgeName.Pos("RFC-")!=0)
                        KludgeName=KludgeName.SubString(5,KludgeName.Length());
              //asTemp.Delete(1,5);
                slRFCKluges->Add(KludgeName+": "+asTemp);
                /*
                asTemp=FtnKludges->KludgeList->Items[i]->AsKludgeString;
                asTemp.Delete(1,5);
              slRFCKluges->Add(asTemp);*/

            }else
            if(KludgeName!="")
            {
                asTemp=FtnKludges->KludgeList->Items[i]->AsString;
                if(KludgeName[KludgeName.Length()]==':')
                    KludgeName=KludgeName.SubString(0,KludgeName.Length()-1);
                slRFCKluges->Add("X-FTN-"+KludgeName+": "+asTemp);
            }
        }
        delete FtnKludges;

//      for(int i=0;i<slKluges->Count;i++)
//      {
//        slKluges->Strings[i]="Comment "+slKluges->Strings[i];
//      }

      slText->Text=AnsiString(((TFTNBaseRecord*)(FSquishBase->ActiveRecordBuf))->Text);
      for (int i = slText->Count-1; i > 0; i--) {
         if (slText->Strings[i].Pos("SEEN-BY:")==1) {
            slPath->Insert(0,"X-FTN-SEEN-BY:"+slText->Strings[i].SubString(9,slText->Strings[i].Length()-8));
            slText->Delete(i);
            continue;
         }
         if (slText->Strings[i].Pos("\x1PATH")==1) {
            slPath->Insert(0,"X-FTN-PATH:"+slText->Strings[i].SubString(7,slText->Strings[i].Length()-6));
            slText->Delete(i);
            continue;
         }
         if (slText->Strings[i].Pos(" * Origin:")==1) {
            break;
         }
      }
/*
      Article+="From: "+FSquishBase->FieldByName("From")->AsString+" ("
        +FSquishBase->FieldByName("OrigZone")->AsString+":"
        +FSquishBase->FieldByName("OrigNet")->AsString+"/"
        +FSquishBase->FieldByName("OrigNode")->AsString+"."
        +FSquishBase->FieldByName("OrigPoint")->AsString+")\r\n";
*/
      if (Kludges.KludgeByName("RFC-Path")->AsString!="")
      {
        FCurrentArticle+="Path: "+ClientSocket->LocalHost+"!"+Kludges.KludgeByName("RFC-Path")->AsString+"\r\n";
      }else  FCurrentArticle+="Path: "+ClientSocket->LocalHost+"!not-for-mail\r\n";

      FCurrentArticle+="Distribution: fido7"+AnsiString("\r\n");
      FCurrentArticle+="From: \""+RecodeLine(FSquishBase->FieldByName("From")->AsString)+"\" <";
      //if(Kludges.REPLYADDR!="")
      if (Kludges.REPLYADDR!="")
      {
         if (Kludges.REPLYADDR.Pos("<") == 0 || Kludges.REPLYADDR.Pos(">") == 0) {
            FCurrentArticle+=Kludges.REPLYADDR+">";
         } else {
            char *Ptr = Kludges.REPLYADDR.c_str();
            while (*Ptr != '<') Ptr++;
            Ptr++;
            while (*Ptr != '>') {
               FCurrentArticle += *Ptr;
               Ptr++;
            }
         }
      } else {
        AnsiString asFromAcc=FSquishBase->FieldByName("From")->AsString.Trim();

        if(Kludges.KludgeByName("RFC-From:")->AsString !="") //есть постинг через гейт
        {
            asFromAcc=Kludges.KludgeByName("RFC-From:")->AsString.Trim();
            FCurrentArticle="From: "+asFromAcc;
        }else
        {
            for(char *Ptr=asFromAcc.c_str();*Ptr;Ptr++)
            if(((*Ptr>='A') &&(*Ptr<='Z'))|| ((*Ptr>='a') &&(*Ptr<='z'))||((*Ptr>='0') &&(*Ptr<='9')))
                continue;
            else
                *Ptr=this->ISS->NameDelimiter;
            FCurrentArticle+=asFromAcc+"@"+ExtractFTNAddr(Kludges.MSGID);
            FCurrentArticle+=">";
        }
      }
        TraceS(__FUNC__);
        FCurrentArticle+="\r\n";
      FCurrentArticle+="X-Comment-To: "+RecodeLine(FSquishBase->FieldByName("To")->AsString)+"\r\n";
      FCurrentArticle+="Newsgroups: "+SelectedGroup->Tag+"\r\n";
      FCurrentArticle+="Subject: "+RecodeLine(FSquishBase->FieldByName("Subj")->AsString)+"\r\n";
FCurrentArticleMessageId=MSGID2MessageId(Kludges.MSGID);
      FCurrentArticle+="Message-ID: "+FCurrentArticleMessageId+"\r\n";
      FCurrentArticle+="Date: "+FSquishBase->FieldByName("FTSC_date")->AsString+"\r\n";

      AnsiString asReference=Kludges.REPLY;
      if(asReference!="")
        FCurrentArticle+="References: "+MSGID2MessageId(asReference)+"\r\n";

      FCurrentArticle+="Lines: "+AnsiString(slText->Count)+"\r\n";
      FCurrentArticle+="Xref: "+ClientSocket->LocalHost+" "+SelectedGroup->Tag+":"+FSquishBase->FieldByName("MsgNo")->AsString+"\r\n";
      FCurrentArticle+="Content-Type: text/plain; charset=koi8-r\r\n";
      //FCurrentArticle+="X-FTN-MSGID: "+Kludges.MSGID+"\r\n";
      FCurrentArticle+=slPath->Text;
      /*
      удалить из остальных клуджей клудж path
      */
      //lastslKluges=slRFCKluges->IndexOf("Path");
      //if (lastslKluges!=0)
      if (slRFCKluges->Count>0)
      {
        if(slRFCKluges->Strings[0].LowerCase().Pos("path")>0) slRFCKluges->Delete(0); //удалить path: он-по-идее идет первым в списке
      }
      FCurrentArticle+=slRFCKluges->Text;
    FCurrentArticleHeader=FCurrentArticle+"\r\n.";
    FCurrentArticleBody=slText->Text+"\r\n.";
      FCurrentArticle+="\r\n"+FCurrentArticleBody;
  TraceS(__FUNC__);
  }
  __finally
  {
  TraceS(__FUNC__);
    delete slText;
    delete slRFCKluges;
    delete slKluges;
    delete slPath;
  TraceS(__FUNC__);
  }
  return FCurrentArticle;
}
//---------------------------------------------------------------------------
int  __fastcall TiuIssNNTPServerThread::BeginSaveArticles(TStringList *NewsGroups)
{
int Index;
AnsiString OutGroup;

  TraceS(__FUNC__);

  for(int i=0;i<NewsGroups->Count;i++)
    if(NewsList->Find(NewsGroups->Strings[i],Index))
    {
      char cGroup=Areas[Index]->Group;
      if((cGroup && strchr(UserInfo.Groups.c_str(),cGroup)) || strchr(UserInfo.Groups.c_str(),'*'))
      {
        if(strchr(UserInfo.ROGroups.c_str(),cGroup) || strchr(UserInfo.ROGroups.c_str(),'*'))
          return 1;

        OutGroup=SelectedGroup->getInternalName(Areas[Index]->Tag,"",UserInfo);
        if(!UserInfo.Posting) return 10; //постинг не разрешен в mask.ini


      }
      else
        return 2;
    }
    else
      return 3;
#ifdef SHAREWARE
  if(CryptedSNr[33]!=CryptedSNc[33])
    return 4;
#endif
  if(!FOutPacket)
  {
#ifdef SHAREWARE
    if(ISS->Tag<32)
#endif
      FOutPacket=new TFTNPKT(NULL);
#ifdef SHAREWARE
    else
      return 5;
#endif
    FOutPacket->Path=ISS->PktDir;

    FOutPacket->OrigAddr=TFTNAddress(ISS->PktOrigAddress).AsFTSStruct;
    FOutPacket->DestAddr=TFTNAddress(ISS->FTNAddress).AsFTSStruct;
    //инициализаци€ пакета
  }
  TraceS(__FUNC__);
  return 0;
}
//---------------------------------------------------------------------------
AnsiString __fastcall ExtactREPLY(AnsiString References)
{
//AnsiString Result;
  TraceS(__FUNC__);
  AnsiString LastRef=AnsiString(References.c_str()+References.LastDelimiter("<"));
  LastRef.Delete(LastRef.Pos(">"),LastRef.Length());
  AnsiString Stamp=LastRef.SubString(1,LastRef.Pos("@")-1);
  LastRef.Delete(1,LastRef.Pos("@"));
  TFTNAddress Addr;
  Addr.AsRFCString=LastRef;
/*
  if(Addr.Point)
    Result.sprintf("%d:%d/%d.%d %s",Addr.Zone,Addr.Net,Addr.Node,Addr.Point,Stamp.c_str());
  else
    Result.sprintf("%d:%d/%d %s",Addr.Zone,Addr.Net,Addr.Node,Stamp.c_str());
*/
  TraceS(__FUNC__);
  return Addr.AsString+" "+Stamp;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuIssNNTPServerThread::TryFoundTo(AnsiString Area,AnsiString MsgID)
{
  TraceS(__FUNC__);
  AnsiString Result="";
int index;
TKludges *Kludges;
AnsiString AsTmp;
TFTNDataSet *SqBase=NULL;
  SqBase=new TSquishBase(NULL);
  try
  {
    if(NewsList->Find(Area,index))
    {
      TAreaFormat AreaFormat=((TAreaInfo*) (NewsList->Objects[index]))->Format;
      if(AreaFormat==afSquish)
        SqBase=new TSquishBase(NULL);
      else
        if(AreaFormat==afJAM)
          SqBase=new TJAMBase(NULL);
        else
          return "";
      SqBase->BasePath=((TAreaInfo*) (NewsList->Objects[index]))->Path;
      SqBase->Open();
      SqBase->Last();
      AnsiString asID=MsgID;
      TFTNAddress fAddr(MsgID);
      asID.Delete(1,asID.Pos(" "));
      asID=Trim(asID);
      while(!SqBase->Bof )
      {
//        index=SqBase->FieldByName("OrigNet")->AsInteger;
        if(AnsiString(((TFTNBaseRecord*)(SqBase->ActiveRecordBuf))->Kludges).Pos(asID))
        {
          Kludges=new TKludges(AnsiString(((TFTNBaseRecord*)(SqBase->ActiveRecordBuf))->Kludges));
          try
          {
            AsTmp=Kludges->KludgeByName("MSGID:")->AsString;
            TFTNAddress FromAddr(AsTmp);
            if((fAddr.Zone==FromAddr.Zone) &&
            (fAddr.Net==FromAddr.Net) &&
            (fAddr.Node==FromAddr.Node) &&
            (fAddr.Point==FromAddr.Point) &&
            AsTmp.Pos(asID)
            )
            {
              Result=SqBase->FieldByName("From")->AsString;
              CharToOem(Result.c_str(),Result.c_str());
            }
//        SqBase->FieldByName("Kludges")->AsString;
          }
          __finally
          {
            delete Kludges;
          }
          if(Result!="")
            break;
        }
        Sleep(1);
        SqBase->Prior();
      }
    }
  }
  __finally
  {
    if(SqBase)
      delete SqBase;
  }
  TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
inline __fastcall bool IsField(AnsiString Line,AnsiString Field)
{
  return !StrLIComp(Line.c_str(), Field.c_str(),Field.Length());
}//ѕопробовать заменить на #define и sizeof
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall ConvertRFCHeader(TFTNMsg *Msg, TStringList *slRFCHeader, AnsiString GateAddr,TUserInfo *UserInfo=NULL, bool PlainFido = false)
{
AnsiString asFieldLine;
AnsiString asFieldName;
AnsiString asFieldContent;
int iBeginFieldContent;
  TraceS(__FUNC__);

    for(int i=0;i<slRFCHeader->Count;i++)
    {
      asFieldLine=slRFCHeader->Strings[i];
      iBeginFieldContent=asFieldLine.Pos(":");
      if(!iBeginFieldContent)
        throw Exception("Invalid Message header!");
      asFieldName=asFieldLine.SubString(1,iBeginFieldContent);
      iBeginFieldContent++;
      asFieldContent=Trim(asFieldLine.SubString(iBeginFieldContent,asFieldLine.Length()));

      if(IsField(asFieldLine,"MIME-Version:") || IsField(asFieldLine,"Content-Type:"))
      {
        Msg->Kludges->KludgeByName("RFC-"+asFieldName)->AsString=asFieldContent;
        continue;
      }

      if(IsField(asFieldLine,"References:"))
      {
        Msg->Kludges->KludgeByName("REPLY:")->AsString=ExtactREPLY(asFieldContent);
        if (!PlainFido) {
           Msg->Kludges->KludgeByName("RFC-References:")->AsString=asFieldContent;
        }
      }
      else if(IsField(asFieldLine,"From:"))
      {
        TFTNAddress tmp(asFieldContent);
        Msg->FromName=tmp.UserName!="" ? tmp.UserName : tmp.Account;
//        Msg->Kludges->KludgeByName("RFC-From:")->AsString=asFromName;
        if(UserInfo)
        {
          Msg->OrigAddr=UserInfo->Address.As5dString;
          if (UserInfo->ReplyAddr!="") Msg->Kludges->KludgeByName("REPLYADDR:")->AsString=UserInfo->ReplyAddr;
          if (UserInfo->ReplyTo!="") Msg->Kludges->KludgeByName("REPLYTO:")->AsString=UserInfo->ReplyTo;
        }
        else
        {
          if(tmp.Net && tmp.Zone)
            Msg->OrigAddr=tmp.As5dString;
          else
          {
            Msg->Kludges->KludgeByName("REPLYTO:")->AsString=GateAddr+" UUCP";
            Msg->Kludges->KludgeByName("REPLYADDR:")->AsString=tmp.AsRFCString;
          }
        }
      }
      else if(IsField(asFieldLine,"To:"))
      {
        TFTNAddress tmp(asFieldContent);
        Msg->ToName=tmp.UserName!="" ? tmp.UserName : tmp.Account;
      }
      else if(((Msg->ToName=="") || (Msg->ToName=="All")) && IsField(asFieldLine,"X-Comment-To:"))
      {
        Msg->ToName=asFieldContent;
      }
      else if(IsField(asFieldLine,"X-FTN-Origin:"))
      {
        Msg->Origin=asFieldContent;
      }
      else if(IsField(asFieldLine,"Subject:"))
      {

        asFieldContent = DecodeMimeHeader(asFieldContent);

        if (asFieldContent.Length()>72)
        {
            Msg->Lines->Insert(0,"Subject: "+asFieldContent);
            Msg->Lines->Insert(1,"");
            Msg->Subject=asFieldContent.SubString(0,71);
        }else
        {
            Msg->Subject=asFieldContent;
        }

      }

      if(!AnsiCompareText(asFieldName,"X-Newsreader:") || !AnsiCompareText(asFieldName,"X-Mailer:"))
      {
        Msg->Tearline=asFieldContent;
        continue;
      }


      if(AnsiCompareText(asFieldName,"Newsgroups:") && AnsiCompareText(asFieldName,"Date:") && AnsiCompareText(asFieldName,"Lines:")&& AnsiCompareText(asFieldName,"Subject:"))
      {
        if (!PlainFido)
        {
            //if (asFieldName.LowerCase()!="subject")
            //{
                Msg->Kludges->KludgeByName("RFC-"+asFieldName)->AsString=asFieldContent;
            //}
        }
      }
    }



    TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssNNTPServerThread::DoSaveArticle(AnsiString NewsGroup, AnsiString Body)
{
  TraceS(__FUNC__);
TDateTime PostDateTime=Now();
DWORD TimeStamp=time(NULL);

static DWORD lastTimeStamp;
static short int beginend;
AnsiString asUueFilename;

        if(beginend!=1 && beginend!=2) beginend=0;

AnsiString asTemp;
AnsiString asMsgBody;
//int iLinesPos;
  TraceS(__FUNC__);
  Body.Unique();
  if(lastTimeStamp==TimeStamp)
  {
        Sleep(1100);
        TimeStamp=time(NULL);
  }
  //Sleep(1100);//dupes prevent;
  lastTimeStamp=TimeStamp;

#ifdef SHAREWARE
  if(ISS->Tag<18)
  {
#endif
//    KOI2OEM(Body.c_str(),Body.c_str());
  switch(FTranslitMode)
  {
    case 0://KOI8
        KOI2OEM(Body.c_str(),Body.c_str());
        break;
    case 1://ANSI
        CharToOem(Body.c_str(),Body.c_str());
        break;
    default://OEM
        break;
  }
#ifdef SHAREWARE
  }
#endif
  N2H(Body.c_str(),Body.c_str());
  TFTNMsg *Msg=new TFTNMsg(NULL);
  TStringList *slRFCHeaderLines=new TStringList;


  Msg->Kludges->KludgeByName("AREA:")->AsString=this->SelectedGroup->getInternalName(NewsGroup.UpperCase(),NULL,UserInfo);
  /*if(!UserInfo.Posting) //постинг запрещен!
  {
    this->SendAnswer(440,"Posting not allowed");
    delete slRFCHeaderLines;
    delete Msg;
    return false;
  }*/
  //Msg->Kludges->KludgeByName("AREA:")->AsString=SelectedGroup->Tag.UpperCase();
  Msg->Kludges->KludgeByName("MSGID:")->AsString=
   UserInfo.Address.AsString+AnsiString("").sprintf(" %08.8x",TimeStamp);
  Msg->OrigAddr=UserInfo.Address.AsString;
  Msg->DestAddr=ISS->FTNAddress;//  Msg->DestAddr=ISS->FTNAddress;
  TraceS(__FUNC__);

  Msg->OrigDateTime=PostDateTime;
//#ifdef SHAREWARE
//  Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion+Fcs;
//#else
  Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion+"Free";
//#endif
  Msg->Kludges->KludgeByName("NNTP-Posting-Host:")->AsString=ClientSocket->LocalHost;
  Msg->ToName="All";
  Msg->Header->wAttr=0;

  asMsgBody=SplitRfcMessage(Body, slRFCHeaderLines);
  asMsgBody.Unique();
  asMsgBody.Delete(asMsgBody.Length()-4,5);

  Msg->Lines->Text=asMsgBody;
  /*
  TStringList tsl;
  tsl.

  if(beginend==2)
  {
    Msg->Lines->Insert(1,"begin 666 "+asUueFilename);
  }
  for(int i=1;i<Msg->Lines->Count;i++)
  {
        AnsiString asTst;
        asTst=Msg->Lines->Text[i];
        if(asTst.Pos("begin 666")>0) //найдено начало begin
        {
            beginend=1; //найдено начало uue
            asUueFilename=asTst.SubString(11,50);
            asUueFilename.Trim();
        }
        if(asTst.SubString(1,3)=="---" && beginend==1) //не найден конец ююка, а пришел тирлайн
        {
            Msg->Lines->Insert(i,"`");
            Msg->Lines->Insert(i+1,"end");
            beginend=2; //multipart
        }
        if(asTst.SubString(1,3)=="---" && beginend==2) //не найден конец ююка, а пришел тирлайн (multipart)
        {
            Msg->Lines->Insert(i,"`");
            Msg->Lines->Insert(i+1,"end");
        }

        if(asTst.SubString(1,3)=="end") //найден конец ююка, (multipart)
            beginend=0;
        break;

  }
  */
  if(AuthChecked)
    ConvertRFCHeader(Msg,slRFCHeaderLines,ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate,&UserInfo,ISS->PlainFido);
  else
    ConvertRFCHeader(Msg,slRFCHeaderLines,ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate,0,ISS->PlainFido);


  if(((Msg->ToName=="")||(Msg->ToName=="All"))&&(Msg->Kludges->KludgeByName("REPLY:")->AsString!="")&& (ISS->TryFoundTo))
  {
    AnsiString asFoundTo=TryFoundTo(Msg->Kludges->KludgeByName("AREA:")->AsString,Msg->Kludges->KludgeByName("REPLY:")->AsString);
    if(asFoundTo!="")
      Msg->ToName=asFoundTo;
  }

  TraceS(__FUNC__);
  Msg->InvalidateOldTechInfo();

    if (ISS->TearLine!="")
    {
        Msg->Tearline=ISS->TearLine;
    }
  if (Msg->Origin == "") {
     if(ISS->Origin!="")
       Msg->Origin=ISS->Origin;
     else
       Msg->Origin="Default InterSquish Origin";
  }
  TraceS(__FUNC__);
  Msg->Kludges->KludgeByName("FMPT")->AsString="";
  Msg->Kludges->KludgeByName("TOPT")->AsString="";
  if(ISS->NeedSeenBy) //надо вставл€ть seen-by
  {
    AnsiString ftnAddr;
    ftnAddr=this->ISS->FTNAddress;
    ftnAddr=ftnAddr.SubString(3,ftnAddr.Pos(".")-3);
    Msg->Vias->KludgeByName("SEEN-BY:")->AsString=ftnAddr;
  }
  FOutPacket->Messages->Add(Msg);
  TraceS(__FUNC__);
  delete slRFCHeaderLines;
  return true;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::EndSaveArticles(void)
{

  FOutPacket->WriteToFile();
  delete FOutPacket;
  FOutPacket=NULL;
#ifdef SHAREWARE
  if(ISS->Tag<8)
#endif
    FileClose(FileCreate(ISS->PostFlag));
}
//---------------------------------------------------------------------------
void __fastcall TiuIssNNTPServerThread::Prepare(void)
{
  TiuCustomNNTPServerThread::Prepare();

  //this->MaskAreas=new TIniFile(this->ISS->AreasMasquerade);
  this->SelectedGroup->MaskFileName=this->ISS->AreasMasquerade;

  if(!FSquishCfg)
  {
//    if(ISS->SquishCfgName)
    if(ISS->AreasConfigType==acSquish)
      FSquishCfg=new TSquishCfg(NULL);
    else
      FSquishCfg=new TFastechoCfg(NULL);
  }
  CriticalSection->Enter();
  try
  {
    FUsersCfg->Path=ISS->UsersCfgName;
    FSquishCfg->Path=ISS->SquishCfgName;
  }
  __finally
  {
    CriticalSection->Leave();
  }
  BuildNewsGroupList();
  FTranslitMode=0;
  UserValid=false;
  AuthChecked=false;
  UserInfo.Address.AsString=ISS->FTNAddress;
  UserInfo.Groups=ISS->DefaultGroups;
  UserInfo.ROGroups=ISS->DefaultROGroups;
#ifdef SHAREWARE
  if(CryptedSNr[22]!=CryptedSNc[22])
    UserInfo.ROGroups=ISS->DefaultGroups;
#endif
  UserInfo.Name="";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssSMTPServer::TiuIssSMTPServer(TComponent* Owner)
  : TiuCustomSMTPServer(Owner)
{
  FMaxMsgSize=MAXINT;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  SocketThread= new TiuIssSMTPServerThread(true,ClientSocket);
//!!!  SocketThread->Priority=tpIdle;
  TiuIssSMTPServerThread *isst=(TiuIssSMTPServerThread *)SocketThread;
  isst->UserInfo.Address=FDefaultUserInfo.Address;
  TiuCustomSMTPServer::GetThread(Sender, ClientSocket, SocketThread);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServer::SetDefaultInternetGate(AnsiString value)
{
    FDefaultInternetGate = value;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServer::SetDefaultAddres(AnsiString Value)
{
  FDefaultUserInfo.Address.AsString=Value;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServer::SetUsersCfg(TCustomUsersCfg *Value)
{
  if(FUsersCfg!=Value)
  {
    FUsersCfg=Value;
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssSMTPServerThread::TiuIssSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
:TCustomSMTPServerThread(CreateSuspended, ASocket)
{
  FReciptAddreses=new TListOfX<TFTNAddress>;
}
//---------------------------------------------------------------------------
__fastcall TiuIssSMTPServerThread::~TiuIssSMTPServerThread(void)
{
  delete FReciptAddreses;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServerThread::Prepare(void)
{
  FTranslitMode=0;
  FUserInfo.Name="";
  FUserInfo.Password="";
  FUserInfo.Address=ISS->FTNAddress;
//  FUserFTNAddress.AsString=ISS->FTNAddress;
  FUserInfo.ReplyAddr="";
  FUserInfo.ReplyTo="";
  TCustomSMTPServerThread::Prepare();

  CriticalSection->Enter();
  try
  {
    //FUsersCfg->Path=ISS->UsersCfgName;
    //FSquishCfg->Path=ISS->SquishCfgName;
  }
  __finally
  {
    CriticalSection->Leave();
  }

//  PasswordValid=false;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServerThread::FillAdrList(TListOfX<TFTNAddress> *adrList,TStringList *RfcMsg,char * FieldName)
{
Cardinal FieldNameLen=strlen(FieldName);
AnsiString AssembledStr="";
  for(int i=0;i<RfcMsg->Count;i++)
  {
//    RfcMsg->Strings[i];
    if(!StrLIComp(RfcMsg->Strings[i].c_str(), FieldName, FieldNameLen))
    {
      AssembledStr=AnsiString(RfcMsg->Strings[i].c_str()+FieldNameLen);
/*
      for(int j=i+1;j<RfcMsg->Count;j++)
      {
        char cFirstSym=*(RfcMsg->Strings[j].c_str());
        if((cFirstSym==9)||(cFirstSym==32))
          AssembledStr=AssembledStr+RfcMsg->Strings[j];
        else
          break;
      }
*/
      AnsiString Item;
      int iLastComma;
      do
      {
        iLastComma=AssembledStr.LastDelimiter(",");

        Item=AssembledStr.SubString(iLastComma+1,1024);
        adrList->Add(new TFTNAddress(Item));
        AssembledStr.Delete(iLastComma,1024);
      } while(iLastComma);
//        for(int index=0;index<slRecpts->Count;index++)
//        {
//
//        }
      break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServerThread::InitMsg(TFTNMsg *Msg, AnsiString MsgBody, TStringList *HeaderLines, TFTNAddress *ReciptAddress)
{
TDateTime PostDateTime=Now();
DWORD TimeStamp=time(NULL);
static DWORD lastTimeStamp;
      Msg->Kludges->KludgeByName("MSGID:")->AsString=
       FUserInfo.Address.AsString+AnsiString("").sprintf(" %08.8x",TimeStamp);

      Msg->OrigAddr=FUserInfo.Address.AsString;

      Msg->DestAddr=*ReciptAddress;
      Msg->OrigDateTime=PostDateTime;
#ifdef SHAREWARE
      Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion+Fcs;
#else
      Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion+"Free";
#endif
      //Msg->ToName="Sysop";
      Msg->Header->wAttr=0;
    Msg->Header->Attr.Local=true;
    Msg->Header->Attr.Private=true;
//      iLinesPos=sMsg.Pos("\r\n\r\n")-1;
//      asTemp=AnsiString(sMsg.c_str()+iLinesPos+4);
//      asTemp.Delete(asTemp.Length()-4,5);
      MsgBody.Unique();
      MsgBody.Delete(MsgBody.Length()-4,5);
      Msg->Lines->Text=MsgBody;
//      sMsg.SetLength(iLinesPos);

      AnsiString param;
      AnsiString value;
      AnsiString line;
      AnsiString flags;
      for(int i=0;i<HeaderLines->Count;i++)
      {

        int ValuePos;
        line=HeaderLines->Strings[i];
        ValuePos=line.Pos(":");
        if(ValuePos)
        {
            param=line.SubString(1,ValuePos-1);
            value=Trim(line.SubString(ValuePos+1,line.Length()));
            if(param==this->ISS->RemoteRequest) //это запрос на подтверждение о прочтении
            {

                flags=Msg->Kludges->FLAGS;
                if(flags!="")
                {
                    flags+=" "+this->ISS->RemoteReadRequestFlags;
                }else
                    flags+=this->ISS->RemoteReadRequestFlags;

                Msg->Kludges->FLAGS=flags;
            }
        }

       }

      ConvertRFCHeader(Msg,HeaderLines,ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate,&FUserInfo,ISS->PlainFido);
      if(ReciptAddress->UserName!="")
        Msg->ToName=ReciptAddress->UserName;
      Msg->InvalidateOldTechInfo();
      if(!Msg->DestAddr.IsFTN)
      {
        Msg->DestAddr=ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate;
        Msg->Lines->Insert(0,"To: "+ReciptAddress->AsRFCString+"\r\n\r\n");
        Msg->ToName="UUCP";
      }
      if(ISS->ForceINTL)
      {
        AnsiString asIntl="";
        asIntl.sprintf("%d:%d/%d %d:%d/%d",Msg->DestAddr.Zone,Msg->DestAddr.Net,
         Msg->DestAddr.Node, Msg->OrigAddr.Zone,Msg->OrigAddr.Net,Msg->OrigAddr.Node);
        Msg->Kludges->KludgeByName("INTL")->AsString=asIntl;
      }
      if(ISS->TearLine!="")
          Msg->Tearline=ISS->TearLine;

      if(ISS->Origin!="")
        Msg->Origin=ISS->Origin;
      {
       AnsiString asViaLine="";
       WORD year,mon,day,hour,min,sec,msec;
       DecodeDate(PostDateTime,year,mon,day);
       DecodeTime(PostDateTime,hour,min,sec,msec);
        asViaLine.sprintf("%s @%04.4u%02.2u%02.2u.%02.2u%02.2u%02.2u.UTC%+d %s %s",
         ISS->PktOrigAddress.c_str(),year,mon,day,hour,min,sec,-FUTC,
         VI_THIS_EXE.InternalName.c_str(),VI_THIS_EXE.FileVersion.c_str());
        Msg->Vias->Add(new TKludge("Via",asViaLine));
      }
      if(lastTimeStamp==TimeStamp)
      {
        Sleep(1100);
        TimeStamp=time(NULL);
      }
  //Sleep(1100);//dupes prevent;
  lastTimeStamp=TimeStamp;}
//---------------------------------------------------------------------------
bool __fastcall TiuIssSMTPServerThread::SaveMsg(AnsiString RfcMsg)
{
TFTNMsg *Msg;
AnsiString asMsgBody;


  if(RfcMsg.Length()>ISS->MaxMsgSize)
  {
    SendAnswer(552,AnsiString("message exceeds fixed maximum message size - ")+AnsiString(ISS->MaxMsgSize)+" bytes");
    return false;
  }

  TFTNPKT  *OutPacket=new TFTNPKT(NULL);
  TListOfX<TFTNAddress> *adrList=new TListOfX<TFTNAddress>;
  TListOfX<TFTNAddress> *adrListtemp=new TListOfX<TFTNAddress>;
  TStringList *slRFCHeaderLines=new TStringList;

  try
  {
    OutPacket->Path=ISS->PktDir;
    OutPacket->OrigAddr=TFTNAddress(ISS->PktOrigAddress).AsFTSStruct;
    OutPacket->DestAddr=TFTNAddress(ISS->FTNAddress).AsFTSStruct;

    RfcMsg.Unique();
//    KOI2OEM(RfcMsg.c_str(),RfcMsg.c_str());
  switch(FTranslitMode)
  {
    case 0://KOI8
        KOI2OEM(RfcMsg.c_str(),RfcMsg.c_str());
        break;
    case 1://ANSI
        CharToOem(RfcMsg.c_str(),RfcMsg.c_str());
        break;
    default://OEM
        break;
  }
    N2H(RfcMsg.c_str(),RfcMsg.c_str());

    asMsgBody=SplitRfcMessage(RfcMsg, slRFCHeaderLines);

    FillAdrList(adrListtemp,slRFCHeaderLines,"TO:");
    if(adrListtemp->Count>1)
    {
        for(int i=0;i<adrListtemp->Count;i++)
        {
                asMsgBody.Insert("To: "+adrListtemp->Items[i]->UserName+" "+adrListtemp->Items[i]->As5dString+"\n",0);
        }
    }

    adrListtemp->Clear();

    FillAdrList(adrListtemp,slRFCHeaderLines,"CC:");
    if(adrListtemp->Count>1)
    {
        for(int i=0;i<adrListtemp->Count;i++)
        {
                asMsgBody.Insert("To: "+adrListtemp->Items[i]->UserName+"\n",0);
        }
    }


    FillAdrList(adrList,slRFCHeaderLines,"TO:");
    FillAdrList(adrList,slRFCHeaderLines,"CC:");
    FillAdrList(adrList,slRFCHeaderLines,"BCC:");
    for(int i=0; i<adrList->Count;i++)
    {
      Msg=new TFTNMsg(NULL);
      InitMsg(Msg,asMsgBody,slRFCHeaderLines,adrList->Items[i]);
      OutPacket->Messages->Add(Msg);
      for(int j=0;j<FReciptAddreses->Count;j++)
      {
//        TFTNAddress *ReciptAddress=FReciptAddreses->Items[j];
//        TFTNAddress *Sent=adrList->Items[i];
        if(FReciptAddreses->Items[j]
         && (adrList->Items[i]->Host==FReciptAddreses->Items[j]->Host)
         && (adrList->Items[i]->Account==FReciptAddreses->Items[j]->Account))
        {
          FReciptAddreses->Delete(j);
        }
      }
    }
    FReciptAddreses->Pack();
    for(int i=0; i<FReciptAddreses->Count;i++)
    {
      Msg=new TFTNMsg(NULL);
      InitMsg(Msg,asMsgBody,slRFCHeaderLines,FReciptAddreses->Items[i]);
      OutPacket->Messages->Add(Msg);
    }

    //OutPacket->Messages->Clear();
/*
    for(int i=0;i<FReciptAddreses->Count;i++)
    {
      sMsg=RfcMsg;
      Msg=new TFTNMsg(NULL);
      Msg->Kludges->KludgeByName("MSGID:")->AsString=
       FUserInfo.Address.AsString+AnsiString("").sprintf(" %08.8x",TimeStamp);

      Msg->OrigAddr=FUserInfo.Address.AsString;

      Msg->DestAddr=*FReciptAddreses->Items[i];
      Msg->OrigDateTime=PostDateTime;
      Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion;
      Msg->ToName="Sysop";
      Msg->Header->wAttr=0;
    Msg->Header->Attr.Local=true;
    Msg->Header->Attr.Private=true;
      iLinesPos=sMsg.Pos("\r\n\r\n")-1;
      asTemp=AnsiString(sMsg.c_str()+iLinesPos+4);
      asTemp.Delete(asTemp.Length()-4,5);
      Msg->Lines->Text=asTemp;
      sMsg.SetLength(iLinesPos);
      ConvertRFCHeader(Msg,sMsg,ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate,&FUserInfo,ISS->PlainFido);
      Msg->InvalidateOldTechInfo();
      if(!Msg->DestAddr.IsFTN)
      {
        Msg->DestAddr=ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate;
        Msg->Lines->Insert(0,"To: "+FReciptAddreses->Items[i]->AsRFCString+"\r\n\r\n");
        Msg->ToName="UUCP";
      }
      if(ISS->ForceINTL)
      {
        AnsiString asIntl="";
        asIntl.sprintf("%d:%d/%d %d:%d/%d",Msg->DestAddr.Zone,Msg->DestAddr.Net,
         Msg->DestAddr.Node, Msg->OrigAddr.Zone,Msg->OrigAddr.Net,Msg->OrigAddr.Node);
        Msg->Kludges->KludgeByName("INTL")->AsString=asIntl;
      }
      if(ISS->TearLine!="")
        Msg->Tearline=ISS->TearLine;
      else
        Msg->Tearline="InterSquish NNTP Server/FTN Gate v."+VI_THIS_EXE.FileVersion;
      if(ISS->Origin!="")
        Msg->Origin=ISS->Origin;
      {
       asTemp="";
       WORD year,mon,day,hour,min,sec,msec;
       DecodeDate(PostDateTime,year,mon,day);
       DecodeTime(PostDateTime,hour,min,sec,msec);
        asTemp.sprintf("%s @%04.4u%02.2u%02.2u.%02.2u%02.2u%02.2u.UTC%+d %s %s",
         ISS->PktOrigAddress.c_str(),year,mon,day,hour,min,sec,-FUTC,
         VI_THIS_EXE.InternalName.c_str(),VI_THIS_EXE.FileVersion.c_str());
        Msg->Vias->Add(new TKludge("Via",asTemp));
      }
      OutPacket->Messages->Add(Msg);
    }
*/
    OutPacket->WriteToFile();

    FileClose(FileCreate(ISS->PostFlag));

  }
  __finally
  {
    delete adrList;
    delete OutPacket;
    delete slRFCHeaderLines;
  }
  return true;
}
//---------------------------------------------------------------------------
/*
void __fastcall TiuIssSMTPServerThread::SaveMsg(AnsiString RfcMsg)
{
TDateTime PostDateTime=Now();
DWORD TimeStamp=time(NULL);
AnsiString sMsg, asTemp;
int iLinesPos;
TFTNMsg *Msg;
  TFTNPKT  *OutPacket=new TFTNPKT(NULL);
  try
  {
    OutPacket->Path=ISS->PktDir;
    OutPacket->OrigAddr=TFTNAddress(ISS->PktOrigAddress).AsFTSStruct;
    OutPacket->DestAddr=TFTNAddress(ISS->FTNAddress).AsFTSStruct;

    RfcMsg.Unique();
    KOI2OEM(RfcMsg.c_str(),RfcMsg.c_str());
    N2H(RfcMsg.c_str(),RfcMsg.c_str());
    //OutPacket->Messages->Clear();
    for(int i=0;i<FReciptAddreses->Count;i++)
    {
      sMsg=RfcMsg;
      Msg=new TFTNMsg(NULL);
      Msg->Kludges->KludgeByName("MSGID:")->AsString=
       FUserInfo.Address.AsString+AnsiString("").sprintf(" %08.8x",TimeStamp);

      Msg->OrigAddr=FUserInfo.Address.AsString;

      Msg->DestAddr=*FReciptAddreses->Items[i];
      Msg->OrigDateTime=PostDateTime;
      Msg->Kludges->KludgeByName("PID:")->AsString=VI_THIS_EXE.InternalName+" "+VI_THIS_EXE.FileVersion;
      Msg->ToName="Sysop";
      Msg->Header->wAttr=0;
    Msg->Header->Attr.Local=true;
    Msg->Header->Attr.Private=true;
      iLinesPos=sMsg.Pos("\r\n\r\n")-1;
      asTemp=AnsiString(sMsg.c_str()+iLinesPos+4);
      asTemp.Delete(asTemp.Length()-4,5);
      Msg->Lines->Text=asTemp;
      sMsg.SetLength(iLinesPos);
      ConvertRFCHeader(Msg,sMsg,ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate,&FUserInfo,ISS->PlainFido);
      Msg->InvalidateOldTechInfo();
      if(!Msg->DestAddr.IsFTN)
      {
        Msg->DestAddr=ISS->DefaultInternetGate=="" ? ISS->FTNAddress:ISS->DefaultInternetGate;
        Msg->Lines->Insert(0,"To: "+FReciptAddreses->Items[i]->AsRFCString+"\r\n\r\n");
        Msg->ToName="UUCP";
      }
      if(ISS->ForceINTL)
      {
        AnsiString asIntl="";
        asIntl.sprintf("%d:%d/%d %d:%d/%d",Msg->DestAddr.Zone,Msg->DestAddr.Net,
         Msg->DestAddr.Node, Msg->OrigAddr.Zone,Msg->OrigAddr.Net,Msg->OrigAddr.Node);
        Msg->Kludges->KludgeByName("INTL")->AsString=asIntl;
      }
      if(ISS->TearLine!="")
        Msg->Tearline=ISS->TearLine;
      else
        Msg->Tearline="InterSquish NNTP Server/FTN Gate v."+VI_THIS_EXE.FileVersion;
      if(ISS->Origin!="")
        Msg->Origin=ISS->Origin;
      {
       asTemp="";
       WORD year,mon,day,hour,min,sec,msec;
       DecodeDate(PostDateTime,year,mon,day);
       DecodeTime(PostDateTime,hour,min,sec,msec);
        asTemp.sprintf("%s @%04.4u%02.2u%02.2u.%02.2u%02.2u%02.2u.UTC%+d %s %s",
         ISS->PktOrigAddress.c_str(),year,mon,day,hour,min,sec,-FUTC,
         VI_THIS_EXE.InternalName.c_str(),VI_THIS_EXE.FileVersion.c_str());
        Msg->Vias->Add(new TKludge("Via",asTemp));
      }
      OutPacket->Messages->Add(Msg);
    }
    OutPacket->WriteToFile();
    FileClose(FileCreate(ISS->PostFlag));
  }
  __finally
  {
    delete OutPacket;
  }
}
*/
//---------------------------------------------------------------------------
void __fastcall TiuIssSMTPServerThread::ClearRecipientsList()
{
  FReciptAddreses->Clear();
}

inline TiuIssSMTPServer * __fastcall TiuIssSMTPServerThread::GetISS(void)
{
    return (TiuIssSMTPServer *)Server;
};

//---------------------------------------------------------------------------
bool _fastcall TiuIssSMTPServerThread::CheckLogin(AnsiString Name, AnsiString Password)
{
bool Result;
  AnsiString NAME=Name.UpperCase();

  if(this->ISS->UsersCfg==NULL)
  {
    this->ISS->UsersCfg=new TCustomUsersCfg(NULL);
    this->ISS->UsersCfg->Path=this->ISS->UsersCfgName;
  }

  if(Server->ScriptingEnable)
  {
    AnsiString AuthString=ExecInstruction(Server->ScriptCfg->InstructionByName("IsUserValid"),FScriptControl, FScriptArgsList,"");
    if(AuthString!="")
    {
      FUserInfo.ImportLine(AuthString);
      if(FUserInfo.Address.AsString=="")//!!! Ёто не верно!
        FUserInfo.Address=ISS->FTNAddress;

      return true;
    }
  }
  CriticalSection->Enter();
  try
  {
    TCustomUsersCfg *UsersCfg=this->ISS->UsersCfg;     //ISS->UsersCfg;
    //TCustomUsersCfg *UsersCfg=new TCustomUsersCfg(
    UsersCfg->Refresh();

  for(int i=0;i<UsersCfg->Users->Count;i++)
    if(UsersCfg->Users->Items[i]->NAME==NAME)
    {
      FUserInfo.Address=UsersCfg->Users->Items[i]->Address.AsString;
      if(FUserInfo.Address.AsString=="")//!!! Ёто не верно!
        FUserInfo.Address=ISS->FTNAddress;
//      FUserFTNAddress.AsString=FUserAddress;
/*
      FDedicatedPoint=(FUserFTNAddress.Zone!=ISS->Address->Zone) ||
                    (FUserFTNAddress.Net!=ISS->Address->Net) ||
                    (FUserFTNAddress.Node!=ISS->Address->Node) ||
                    (FUserFTNAddress.Point!=ISS->Address->Point);
*/
      FUserInfo.Password=UsersCfg->Users->Items[i]->Password;
      Result=FUserInfo.Password==Password;

      if(!AnsiCompareText(UsersCfg->Users->Items[i]->CharsetName,"OEM"))
          FTranslitMode=2;
      else if(!AnsiCompareText(UsersCfg->Users->Items[i]->CharsetName,"ANSI"))
          FTranslitMode=1;
      else
          FTranslitMode=0;
      break;
    }
  }
  __finally
  {
    CriticalSection->Leave();
  }
  return Result;
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssSMTPServerThread::AddRecipient(AnsiString Argument)
{
AnsiString Addr=AnsiString(Argument.c_str()+Argument.LastDelimiter("<"));
  Addr.Delete(Addr.Pos(">"),Addr.Length());


  FReciptAddreses->Add(new TFTNAddress(Addr));
  return true;
}
//---------------------------------------------------------------------------

namespace Iuintersquishserver
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[3] = {__classid(TiuIssNNTPServer),__classid(TiuIssSMTPServer),__classid(TiuIssPOP3Server)};
     RegisterComponents("FIDO Tech", classes, 2);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssPOP3Server::TiuIssPOP3Server(TComponent* Owner)
:TiuCustomPOP3Server(Owner)
{
   FAddress=new TFTNAddress;
}
//---------------------------------------------------------------------------
__fastcall TiuIssPOP3Server::~TiuIssPOP3Server(void)
{
  delete FAddress;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3Server::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  SocketThread= new TiuIssPOP3ServerThread(true,ClientSocket);
  TiuCustomPOP3Server::GetThread(Sender, ClientSocket, SocketThread);
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3Server::SetAddress(AnsiString Value)
{
  FAddress->AsString=Value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuIssPOP3Server::GetAddress(void)
{
  return FAddress->AsString;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3Server::SetUsersCfg(TCustomUsersCfg *Value)
{
  if(FUsersCfg!=Value)
  {
    FUsersCfg=Value;
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuIssPOP3ServerThread::TiuIssPOP3ServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
:TiuCustomPOP3ServerThread(CreateSuspended,  ASocket)
{
  FMsgBase=new TMsgBase(NULL);
  FMsgBase->OnFilterRecord=FilterRecord;
  FMsgBase->Filtered=true;
  FMsgBase->OnTransliterate=Transliterate;
//  FMsgBase->DeletedPath=ISS->TrashPath;
}
//---------------------------------------------------------------------------
__fastcall TiuIssPOP3ServerThread::~TiuIssPOP3ServerThread(void)
{
  delete FMsgBase;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::Prepare(void)
{
  FMsgBase->DeletedPath=ISS->TrashPath;
  FUserInfo.Name="";
  FUserInfo.Password="";
  FUserInfo.Address.Clear();
  FMsgBase->Close();
  FTranslitMode=0;
  TiuCustomPOP3ServerThread::Prepare();
//  PasswordValid=false;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::UnPrepare(void)
{
  FMsgBase->Close();
  TiuCustomPOP3ServerThread::UnPrepare();
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::FilterRecord(TDataSet *DataSet, bool &Accept)
{
 /* DONE :
—делать фильтрацию по атрибутам, например, письма,
с атрибутом Sent - не посылать. ¬ идеале должно настраиватьс€. */
WORD wAttr=(WORD)DataSet->FieldByName("Attr")->AsInteger;
  CriticalSection->Enter();
  try
  {
    Accept=!(ISS->HoldFlagsMask & wAttr);
  }
  __finally
  {
    CriticalSection->Leave();
  }
  if(!Accept)
    return;

  if(FDedicatedPoint || !ISS->BBSMode)
  {
  TKludges Kludges(DataSet->FieldByName("Kludges")->AsString);
  int Zone=ISS->Address->Zone;
    int Point=Kludges.KludgeByName("TOPT")->AsString.ToIntDef(0);
    int Node=DataSet->FieldByName("DestNode")->AsInteger;
    int Net=DataSet->FieldByName("DestNet") ->AsInteger;
    AnsiString AsIntl=Kludges.KludgeByName("INTL")->AsString;
    if(AsIntl!="")
    {
      AsIntl.Delete(AsIntl.Pos(" "),AsIntl.Length());
    }
    Accept=(FUserInfo.Address.Zone==Zone) && (FUserInfo.Address.Net==Net) &&
     (FUserInfo.Address.Node==Node) && (FUserInfo.Address.Point==Point);

  }
  else
    Accept=FUserInfo.Name==DataSet->FieldByName("To")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::FindUser(void)
{
  AnsiString NAME=FUserInfo.Name.UpperCase();

  CriticalSection->Enter();
  try
  {
    if(this->ISS->UsersCfg==NULL)
    {
        this->ISS->UsersCfg=new TCustomUsersCfg(NULL);
        this->ISS->UsersCfg->Path=this->ISS->UsersCfgName;
    }
    TCustomUsersCfg *UsersCfg=ISS->UsersCfg;
    UsersCfg->Refresh();
    for(int i=0;i<UsersCfg->Users->Count;i++)
      if(UsersCfg->Users->Items[i]->NAME==NAME)
      {
        FUserInfo.Address=UsersCfg->Users->Items[i]->Address.AsString;
//        FUserInfo.Address.AsString=FUserAddress;
        if(FUserInfo.Address.AsString=="")//!!! Ёто не верно!
          FUserInfo.Address=ISS->FTNAddress;
        FDedicatedPoint=(FUserInfo.Address.Zone!=ISS->Address->Zone) ||
                      (FUserInfo.Address.Net!=ISS->Address->Net) ||
                      (FUserInfo.Address.Node!=ISS->Address->Node) ||
                      (FUserInfo.Address.Point!=ISS->Address->Point);
        FUserInfo.Password=UsersCfg->Users->Items[i]->Password;

      if(!AnsiCompareText(UsersCfg->Users->Items[i]->CharsetName,"OEM"))
          FTranslitMode=2;
      else if(!AnsiCompareText(UsersCfg->Users->Items[i]->CharsetName,"ANSI"))
          FTranslitMode=1;
      else
          FTranslitMode=0;

        break;
      }
  }
  __finally
  {
    CriticalSection->Leave();
  }
}
//---------------------------------------------------------------------------
bool _fastcall TiuIssPOP3ServerThread::CheckUser(AnsiString Argument)
{
  FUserInfo.Name=Argument;
  FUserInfo.Address.Clear();
  return true;
}
//---------------------------------------------------------------------------
bool _fastcall TiuIssPOP3ServerThread::CheckPassword(AnsiString Argument)
{
  if(Server->ScriptingEnable)
  {
    AnsiString AuthString=ExecInstruction(Server->ScriptCfg->InstructionByName("IsUserValid"),FScriptControl, FScriptArgsList,"");
    if(AuthString!="")
    {
      FUserInfo.ImportLine(AuthString);
      return true;
    }
  }
  Synchronize(FindUser);

  return (FUserInfo.Address.AsString!="") && (Argument==FUserInfo.Password);
}
//---------------------------------------------------------------------------
bool __fastcall TiuIssPOP3ServerThread::LockMailDrop(void)
{
  if(!TiuCustomPOP3ServerThread::LockMailDrop())
    return false;
  try
  {
    FMsgBase->BasePath=ISS->BoxesPath;
    FMsgBase->Open();
    FMsgBase->Filtered=true;
    FMsgBase->First();
    int i=1;
    while(!FMsgBase->Eof)
    {
      Messages->Add(new TMailDropItem(i++,
       FMsgBase->FieldByName("MsgSize")->AsInteger,
       FMsgBase->FieldByName("FileName")->AsString));
      FMsgBase->Next();
    }
  }
  catch(Exception &exception)
  {
    Server->Log(exception.Message);
  }
  return FMsgBase->Active;

}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::DeleteMsg(AnsiString MsgId)
{
  FMsgBase->First();
  while(!FMsgBase->Eof)
  {
    if(FMsgBase->FieldByName("FileName")->AsString==MsgId)
    {
      FMsgBase->Delete();
      break;
    }
    FMsgBase->Next();
  }
//  FMsgBase->MoveTo(MsgNo);
//  FMsgBase->Delete();
}
//---------------------------------------------------------------------------
void __fastcall TiuIssPOP3ServerThread::Transliterate(TObject* Sender,char* Src,char* Dest,bool ToOEM)
{
  switch(FTranslitMode)
  {
    case 0://KOI8
        OEM2KOI(Src,Dest);
        break;
    case 1://ANSI
        OemToChar(Src,Dest);
        break;
    default://OEM
      strcpy(Dest,Src);
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuIssPOP3ServerThread::RetriveMsg(int MsgNo)
{
AnsiString RMsg="";
bool IsAttach;
    TStringList *slPath=new TStringList();
    TStringList *slKluges=new TStringList();
    TStringList *slRFCKluges=new TStringList();
    TStringList *slText=new TStringList();
    try
    {
      FMsgBase->MoveTo(MsgNo);
      {
        IsAttach=FMsgBase->FieldByName("Attr")->AsInteger & 16;
        AnsiString asKludges=AnsiString(((TMsgRecord*)(FMsgBase->ActiveRecordBuf))->Kludges);
        TKludges Kludges(asKludges);
        slKluges->Text=asKludges;
  /*
        for(int i=0;i<slKluges->Count;i++)
        {
          slKluges->Strings[i]="Comment "+slKluges->Strings[i];
        }
  */
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        TraceS(__FUNC__);
          AnsiString KludgeName;
          AnsiString asTemp;
          TKludges *FtnKludges=new TKludges(asKludges);
        try
        {
          for(int i=0;i<FtnKludges->KludgeList->Count;i++)
          {
            KludgeName=FtnKludges->KludgeList->Items[i]->Name;
            if(KludgeName!="" && KludgeName.Pos("RFC-")!=0
              && AnsiCompareText(KludgeName,"RFC-Newsgroups:")
              && AnsiCompareText(KludgeName,"RFC-Date:")
              && AnsiCompareText(KludgeName,"RFC-Lines:")
              && AnsiCompareText(KludgeName,"RFC-To:")
              && AnsiCompareText(KludgeName,"RFC-Message-ID:")
              && AnsiCompareText(KludgeName,"RFC-References:")
              && AnsiCompareText(KludgeName,"RFC-From:"))
            {
                asTemp=FtnKludges->KludgeList->Items[i]->AsString;
                if(KludgeName[KludgeName.Length()]==':')
                    KludgeName=KludgeName.SubString(0,KludgeName.Length()-1);
                if(KludgeName.Pos("RFC-")!=0)
                        KludgeName=KludgeName.SubString(5,KludgeName.Length());
              //asTemp.Delete(1,5);
                slRFCKluges->Add(KludgeName+": "+asTemp);
                /*
                asTemp=FtnKludges->KludgeList->Items[i]->AsKludgeString;
                asTemp.Delete(1,5);
              slRFCKluges->Add(asTemp);*/

            }else
            if(KludgeName!="")
            {
                asTemp=FtnKludges->KludgeList->Items[i]->AsString;
                if(KludgeName[KludgeName.Length()]==':')
                    KludgeName=KludgeName.SubString(0,KludgeName.Length()-1);
                slRFCKluges->Add("X-FTN-"+KludgeName+": "+asTemp);
            }
          }
        }
        __finally
        {
          delete FtnKludges;
        }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        slText->Text=AnsiString(((TMsgRecord*)(FMsgBase->ActiveRecordBuf))->Text);
        if(slText->Count)
        {
          while(slText->Strings[slText->Count-1].Pos("\x1")==1)
          {
            slPath->Insert(0,"X-Comment-Path "+slText->Strings[slText->Count-1]);
            slText->Delete(slText->Count-1);
          }
        }
        RMsg+="From: \""+RecodeLine(FMsgBase->FieldByName("From")->AsString)+"\" <";
        if(Kludges.REPLYADDR!="")
          RMsg+=Kludges.REPLYADDR;
        else
        {
        AnsiString asFromAcc=FMsgBase->FieldByName("From")->AsString.Trim();

          for(char *Ptr=asFromAcc.c_str();*Ptr;Ptr++)
            if(((*Ptr>='A') &&(*Ptr<='Z'))|| ((*Ptr>='a') &&(*Ptr<='z'))||((*Ptr>='0') &&(*Ptr<='9')))
              continue;
            else
                *Ptr=this->ISS->NameDelimiter;
              //*Ptr='_';
          RMsg+=asFromAcc+"@"+ExtractFTNAddr(Kludges.MSGID);
        }
        RMsg+=">\r\n";
        RMsg+="To: "+RecodeLine(FMsgBase->FieldByName("To")->AsString.Trim())+"\r\n";
        if(IsAttach)
        {
          RMsg+="Subject: "+RecodeLine(ExtractFileName(FMsgBase->FieldByName("Subj")->AsString))+"\r\n";
        }
        else
        {
          RMsg+="Subject: "+RecodeLine(FMsgBase->FieldByName("Subj")->AsString)+"\r\n";
        }
        RMsg+="Message-ID: "+MSGID2MessageId(Kludges.MSGID)+"\r\n";
        RMsg+="Date: "+FMsgBase->FieldByName("FTSC_date")->AsString+"\r\n";

        AnsiString asReference=Kludges.REPLY;
        if(asReference!="")
          RMsg+="References: "+MSGID2MessageId(asReference)+"\r\n";

        RMsg+="Lines: "+AnsiString(slText->Count)+"\r\n";
        RMsg+=slRFCKluges->Text;
        RMsg+=slPath->Text;
  //      RMsg+=slKluges->Text;

        RMsg+="\r\n"+slText->Text;
        if(IsAttach)
        {
          IncludeAttachAsUUE(RMsg,FMsgBase->FieldByName("Subj")->AsString);
        }
        RMsg+="\r\n.";
      }
    }
    __finally
    {
      delete slRFCKluges;
      delete slText;
      delete slKluges;
      delete slPath;
    }

  return RMsg;
}
//---------------------------------------------------------------------------
int __fastcall TiuIssPOP3ServerThread::GetMsgSize(int Index)
{
  FMsgBase->MoveTo(Index);
  return FMsgBase->FieldByName("MsgSize")->AsInteger;
}
//---------------------------------------------------------------------------
int __fastcall TiuIssPOP3ServerThread::GetMsgCount()
{
  return FMsgBase->RecordCount;
}
//---------------------------------------------------------------------------
int __fastcall TiuIssPOP3ServerThread::GetTotalMsgSize()
{
int Result=0;
  FMsgBase->First();
  while(!FMsgBase->Eof)
  {
    Result+=FMsgBase->FieldByName("MsgSize")->AsInteger;
    FMsgBase->Next();
  }
  return Result;
}
//---------------------------------------------------------------------------
