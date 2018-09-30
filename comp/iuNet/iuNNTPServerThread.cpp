//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <time.h>
#include "iuNNTPServerThread.h"
#include "Utils.h"
#include "log.h"
#include "Kludges.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
  const String NNTP_ARTICLE="ARTICLE";              // частично -------------
  const String NNTP_BODY="BODY";
  const String NNTP_DATE="DATE";                    // ОК -------------------
  const String NNTP_GROUP="GROUP";                  // ОК -------------------
  const String NNTP_HEAD="HEAD";
  const String NNTP_HELP="HELP";
  const String NNTP_IHAVE="IHAVE";
  const String NNTP_LAST="LAST";
  const String NNTP_LIST_NEWSGROUPS="LIST NEWSGROUPS";
  const String NNTP_LIST_OVERVIEW_FMT="LIST OVERVIEW.FMT";
  const String NNTP_LIST="LIST";
  const String NNTP_NEWGROUPS="NEWGROUPS";
  const String NNTP_NEWNEWS="NEWNEWS";
  const String NNTP_NEXT="NEXT";
  const String NNTP_POST="POST";                    // ОК -------------------
  const String NNTP_QUIT="QUIT";                    // ОК -------------------
  const String NNTP_SLAVE="SLAVE";
  const String NNTP_STAT="STAT";
  const String NNTP_AUTHINFO_USER="AUTHINFO USER";
  const String NNTP_AUTHINFO_PASS="AUTHINFO PASS";
  const String NNTP_MODE_READER="MODE READER";      // ОК -------------------
  const String NNTP_XOVER="XOVER";                  //
  const String NNTP_XMOTD="XMOTD";

//---------------------------------------------------------------------------
__fastcall TiuCustomNNTPServerThread::TiuCustomNNTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
  : TiuServerClientThread(CreateSuspended,ASocket)
{
  FServiceName="NNTP";
  FNewsGroupsList= new TStringList;
  FNewsGroupsList->Sorted=true;
  FNewsGroupsList->Duplicates=dupIgnore;
  FSelectedGroup=new TAreaInfo();

}
//---------------------------------------------------------------------------
__fastcall TiuCustomNNTPServerThread::~TiuCustomNNTPServerThread(void)
{
  delete FNewsGroupsList;
  delete FSelectedGroup;

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ClientExecute(void)
{
TraceS(__FUNC__);
  if(ClientSocket->Connected)
  {
    Prepare();
    FSelectedGroup->Tag="";
    try
    {
      if(ClientSocket->Connected)
      {
        if(FPostingAllowed)
          SendAnswer(200,ClientSocket->LocalHost+" news server ready - posting ok");
        else
          SendAnswer(201,ClientSocket->LocalHost+" news server ready - no posting allowed");
        TiuServerClientThread::ClientExecute();
      }
    }
    catch(...)
    {
    TraceS(__FUNC__);
      Terminate();
    }
    UnPrepare();
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::HandleRecivedCommand(AnsiString Command)
{
TraceS(__FUNC__);
TraceS(Command.c_str());
  TiuServerClientThread::HandleRecivedCommand(Command);
  if(!Terminated && ClientSocket->Connected)
  {
  AnsiString Argument="";
    Command=Command.Trim();
    if(!Command.Length())
      return;
    TraceS(__FUNC__);
    if(Command.LastDelimiter("\t "))
    {//Есть пробелы - есть и аргументы...
      Argument=Command;
      Argument.Delete(1,Argument.Pos(" "));
      Argument=Argument.Trim();
    }

    this->Log("Command:"+Command+" Argument:"+Argument+"\n");

  if(IsCommand(NNTP_ARTICLE,Command))
    ProcessARTICLE(Argument);
  else if(IsCommand(NNTP_BODY,Command))
    ProcessBODY(Argument);
  else if(IsCommand(NNTP_GROUP,Command))
    ProcessGROUP(Argument);
  else if(IsCommand(NNTP_HEAD,Command))
    ProcessHEAD(Argument);
  else if(IsCommand(NNTP_HELP,Command))
    ProcessHELP(Argument);
  else if(IsCommand(NNTP_IHAVE,Command))
    ProcessIHAVE(Argument);
  else if(IsCommand(NNTP_LAST,Command))
    ProcessLAST(Argument);
//  else if(IsCommand(NNTP_LIST_NEWSGROUPS,Command))
//    ProcessLIST_NEWSGROUPS(Argument);
  else if(IsCommand(NNTP_LIST_OVERVIEW_FMT,Command))
    ProcessLIST_OVERVIEW_FMT(Argument);
  else if(IsCommand(NNTP_LIST,Command))
    ProcessLIST(Argument);
  else if(IsCommand(NNTP_NEWGROUPS,Command))
    ProcessNEWGROUPS(Argument);
  else if(IsCommand(NNTP_NEWNEWS,Command))
    ProcessNEWNEWS(Argument);
  else if(IsCommand(NNTP_NEXT,Command))
    ProcessNEXT(Argument);
  else if(IsCommand(NNTP_POST,Command))
    ProcessPOST(Argument);
  else if(IsCommand(NNTP_QUIT,Command))
  {
    ProcessQUIT(Argument);
    ClientSocket->Close();
  }
  else if(IsCommand(NNTP_SLAVE,Command))
    ProcessSLAVE(Argument);
  else if(IsCommand(NNTP_STAT,Command))
    ProcessSTAT(Argument);
  else if(IsCommand(NNTP_AUTHINFO_USER,Command,Argument))
  {
    if(FScriptArgsList)
      FScriptArgsList->ParamByName("ACC_NAME")=Argument;
    ProcessAUTHINFO_USER(Argument);
  }
  else if(IsCommand(NNTP_AUTHINFO_PASS,Command,Argument))
  {
    if(FScriptArgsList)
      FScriptArgsList->ParamByName("ACC_PASSWORD")=Argument;
    ProcessAUTHINFO_PASS(Argument);
  }
  else if(IsCommand(NNTP_MODE_READER,Command))
  {
    if(FPostingAllowed)
      SendAnswer(200,"Hello, you can post");
    else
      SendAnswer(201,"Hello, you can't post");
  }
  else if(IsCommand(NNTP_XOVER,Command))
    ProcessXOVER(Argument);
  else if(IsCommand(NNTP_DATE,Command))
    ProcessDATE(Argument);
  else
    SendAnswer(503,"Function not performed");
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomNNTPServerThread::PrepareHeader(TArticleHeader &AHeader)
{
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessDATE(AnsiString Argument)
{
AnsiString DateString="";
SYSTEMTIME st;
TraceS(__FUNC__);
  GetSystemTime(&st);
  DateString.sprintf("%4d%02d%02d%02d%02d%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
  SendAnswer(111,DateString);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
static void __fastcall ReplaceBadSymbols(AnsiString Line)
{
unsigned char *Ptr=(unsigned char *)Line.c_str();
  while(*Ptr)
  {
    if(((*Ptr)<32) && (*Ptr))
      *Ptr=32;
    Ptr++;
  }
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::SendArticleHeader(int ArticleNumber)
{
TraceS(__FUNC__);
TArticleHeader AHeader;
char cAnswer[1024];
  AHeader.iNumber=ArticleNumber;
  if(!PrepareHeader(AHeader))
    return; //нет такой статьи.
  try
  {
TraceS(__FUNC__);
    ReplaceBadSymbols(AHeader.asSubj);
    ReplaceBadSymbols(AHeader.asFrom);
    ReplaceBadSymbols(AHeader.asDate);
TraceS(__FUNC__);
    ReplaceBadSymbols(AHeader.asMessage_ID);
    ReplaceBadSymbols(AHeader.asReference);

TraceS(__FUNC__);
    sprintf(cAnswer,"%d\t%s\t%s\t%s\t%s\t%s\t%d\t%d",
    AHeader.iNumber,AHeader.asSubj.c_str(),AHeader.asFrom.c_str(),AHeader.asDate.c_str(),
    AHeader.asMessage_ID.c_str(),AHeader.asReference.c_str(),AHeader.iSize,AHeader.iLines);
TraceS(__FUNC__);
    WriteLn(AnsiString(cAnswer));
//    WriteLn(Format("%d\t%s\t%s\t%s\t%s\t%s\t%d\t%d",
//    ARRAYOFCONST((AHeader.iNumber,AHeader.asSubj,AHeader.asFrom,AHeader.asDate,
//    AHeader.asMessage_ID,AHeader.asReference,AHeader.iSize,AHeader.iLines))));
TraceS(__FUNC__);
  }
  catch(Exception &exception)
  {
    Server->Log(exception.Message);
    ClientSocket->Close();
    Terminate();
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessXOVER(AnsiString Argument)
{
TraceS(__FUNC__);
  if(FSelectedGroup->Tag.Length())
  {
    if(Argument.Length())
    {
    int iFirst=0,iLast=0;
TraceS(__FUNC__);
      SendAnswer(224,"data follows");
      sscanf(Argument.c_str(),"%d-%d",&iFirst,&iLast);
      TraceS(__FUNC__);
      if(!iLast)
        iLast=iFirst;
      for(int i=iFirst;i<=iLast;i++)
      {
//CriticalSection->Enter();
//try
//{
        SendArticleHeader(i);
//}
//__finally
//{
//CriticalSection->Leave();
//}
        Sleep(5);
        if(Terminated || !ClientSocket->Connected)
          return;
      }
      WriteLn(".");
    }
    else
      if (FiCurrentArticle)
      {
        SendAnswer(224,"data follows");
        //.........................
      }
      else
        SendAnswer(420,"No article selected");

    //  WriteLn(".");
  }
  else
    SendAnswer(412,"No group selected");
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomNNTPServerThread::RetriveArticle(AnsiString MessageID, AnsiString &Article)
{
  SendAnswer(430,"no such article found");
  return false;
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomNNTPServerThread::RetriveArticle(int ArticleNumber, AnsiString &Article)
{
  SendAnswer(423,"no such article number in this group");
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessARTICLE(AnsiString Argument)
{
//AnsiString ArticleBody;
TraceS(__FUNC__);
  if(FSelectedGroup->Tag=="")
  {
    SendAnswer(412,"no newsgroup has been selected");
    return;
  }
  if(Argument.c_str()[0]=='<')
  {//By Message-ID
    if(RetriveArticle(Argument,FCurrentArticle))
    {
      SendAnswer(220, Argument+" Article retrieved, text follows");
      WriteLn(FCurrentArticle);
    }
  }
  else
  {
    int ArticleNumber=Argument.ToIntDef(0);
    if(!ArticleNumber || (ArticleNumber>ArticleNom[ArticlesCount-1]))
    {
      SendAnswer(423,"no such article number in this group");
      return;
    }
    if(RetriveArticle(ArticleNumber,FCurrentArticle))
    {
      SendAnswer(220, AnsiString(ArticleNumber)+" Article retrieved, text follows");
      WriteLn(FCurrentArticle);
    }
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessSTAT(AnsiString Argument)
{
TraceS(__FUNC__);
  if(FSelectedGroup->Tag=="")
  {
    SendAnswer(412,"no newsgroup has been selected");
    return;
  }
  if(Argument.c_str()[0]=='<')
  {//By Message-ID

    if(RetriveArticle(Argument,FCurrentArticle))
    {
      SendAnswer(223, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - statistics only");
//      WriteLn(FCur);
    }
  }
  else
  {
    int ArticleNumber=Argument.ToIntDef(0);
    if(!ArticleNumber || (ArticleNumber>ArticleNom[ArticlesCount-1]))
    {
      SendAnswer(423,"no such article number in this group");
      return;
    }
    if(RetriveArticle(ArticleNumber,FCurrentArticle))
    {
      SendAnswer(223, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - statistics only");
//      WriteLn(FCurrentArticle);
    }
  }
TraceS(__FUNC__);

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessHEAD(AnsiString Argument)
{
TraceS(__FUNC__);
  if(FSelectedGroup->Tag=="")
  {
    SendAnswer(412,"no newsgroup has been selected");
    return;
  }
  if(Argument=="")
  {
    if(FCurrentArticle!="")
    {
      SendAnswer(221, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - head follows");
      WriteLn(FCurrentArticleHeader);
    }
    else
      SendAnswer(420,"No current article has been selected");
  }
  else if(Argument.c_str()[0]=='<')
  {//By Message-ID

    if(RetriveArticle(Argument,FCurrentArticle))
    {
      SendAnswer(221, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - head follows");
      WriteLn(FCurrentArticleHeader);
    }
  }
  else
  {
    int ArticleNumber=Argument.ToIntDef(0);
    if(!ArticleNumber || (ArticleNumber>ArticleNom[ArticlesCount-1]))
    {
      SendAnswer(423,"no such article number in this group");
      return;
    }
    if(RetriveArticle(ArticleNumber,FCurrentArticle))
    {
      SendAnswer(221, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - head follows");
      WriteLn(FCurrentArticleHeader);
    }
  }
TraceS(__FUNC__);

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessBODY(AnsiString Argument)
{
TraceS(__FUNC__);
  if(FSelectedGroup->Tag=="")
  {
    SendAnswer(412,"no newsgroup has been selected");
    return;
  }
  if(Argument=="")
  {
    if(FCurrentArticle!="")
    {
      SendAnswer(222, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - head follows");
      WriteLn(FCurrentArticleBody);
    }
    else
      SendAnswer(420,"No current article has been selected");;
  }
  else if(Argument.c_str()[0]=='<')
  {//By Message-ID

    if(RetriveArticle(Argument,FCurrentArticle))
    {
      SendAnswer(222, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - body follows");
      WriteLn(FCurrentArticleBody);
    }
  }
  else
  {
    int ArticleNumber=Argument.ToIntDef(0);
    if(!ArticleNumber || (ArticleNumber>ArticleNom[ArticlesCount-1]))
    {
      SendAnswer(423,"no such article number in this group");
      return;
    }
    if(RetriveArticle(ArticleNumber,FCurrentArticle))
    {
      SendAnswer(222, AnsiString(FiCurrentArticle)+" "+FCurrentArticleMessageId+" Article retrieved - body follows");
      WriteLn(FCurrentArticleBody);
    }
  }
TraceS(__FUNC__);

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessGROUP(AnsiString Argument)
{
int iPos;
TraceS(__FUNC__);
  FiCurrentArticle=0;
  FCurrentArticle="";
  FCurrentArticleMessageId="";
  FCurrentArticleHeader="";
  FCurrentArticleBody="";

  if(FNewsGroupsList->Find(Argument,iPos))
  {
    FSelectedGroup->Tag=Argument;
    FSelectedGroup->InternalTag=Argument;
    if(SetActiveGroup(FSelectedGroup->Tag))
    {
    AnsiString tmp="";
      tmp.sprintf("%d %d %d %s group selected",ArticlesCount,ArticleNom[0],ArticleNom[ArticlesCount-1],FSelectedGroup->Tag.c_str());
      SendAnswer(211,tmp);
      //      SendAnswer(211,Format("%d %d %d %s group selected",
//        ARRAYOFCONST((ArticlesCount,ArticleNom[0],ArticleNom[ArticlesCount-1],FSelectedGroup))));
      if(ArticlesCount)
        FiCurrentArticle=ArticleNom[0];
    }
    else
      SendAnswer(411,"No such news group");
    //      SendAnswer(451,"Unable open group. Server internal error 03");
  }
  else
    SendAnswer(411,"No such news group");
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessHELP(AnsiString Argument)
{
  SendAnswer(100,"Help text follows");

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessIHAVE(AnsiString Argument)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessLAST(AnsiString Argument)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessXMOTD(AnsiString Argument)
{

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessLIST(AnsiString Argument)
{
  SendAnswer(215, "information follows");
  if(Argument=="NEWSGROUPS")
    SendNewsListDesc();
//    SendNewsListDesc;
  else
    SendNewsGroupsList();
  WriteLn(".");
//    SendNewsGroupsList();
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessLIST_OVERVIEW_FMT(AnsiString Argument)
{
  SendAnswer(215, "Information follows");

  WriteLn("Subject:\r\nFrom:\r\nDate:\r\nMessage-ID:\r\nReferences:\r\nBytes:\r\nLines:");
  WriteLn(".");
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::SendNewsListDesc(void)
{
/*
  for(int i=0;i<NNTPServer->NewsList->Count;i++)
  {
  AnsiString sNewsGroup;
//    sNewsGroup=NNTPServer->NewsList->Strings[i];
//    if(SetActiveGroup(sNewsGroup))
    {

//      WriteLn("\""+sNewsGroup+"\" \"cccccccccc\"");

    }
  }
*/
//  WriteLn(".");

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessNEWGROUPS(AnsiString Argument)
{
//SendAnswer(215, "List of newsgroups follows");
  SendAnswer(500, "Not implemented");
  WriteLn(".");
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::SendNewNewsList(TStringList *slRequestedGroups,TDateTime RequestedTime)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessNEWNEWS(AnsiString Argument)
{
TraceS(__FUNC__);
char Group_s[256];
char cYear[4], cMonth[4], cDay[4], cHour[4], cMin[4], cSec[4], cGMT[4];
TStringList *slRequestedGLine;
TStringList *slRejectedGLine;
TStringList *slRequestedGroups;
TDateTime dtRequestedTime;
TraceS(__FUNC__);
  sscanf(Argument.c_str(),"%255s %2s%2s%2s %2s%2s%2s %3s",
   Group_s, cYear, cMonth, cDay, cHour, cMin, cSec, cGMT);
TraceS(__FUNC__);
  dtRequestedTime=EncodeDate(atoi(cYear)+2000,atoi(cMonth),atoi(cDay))+
   EncodeTime(atoi(cHour),atoi(cMin),atoi(cSec),0);
TraceS(__FUNC__);
  if(!AnsiCompareText(AnsiString(cGMT),AnsiString("GMT")))
  {
    int iTotalBias=FtzInfo.Bias+FtzInfo.DaylightBias;
    int iHourBias=iTotalBias/60;
    int iMinBias=iTotalBias%60;
    TraceS(__FUNC__);
    if(iTotalBias>0)
      dtRequestedTime-=EncodeTime(iHourBias,iMinBias,0,0);
    else
      dtRequestedTime+=EncodeTime(-iHourBias,-iMinBias,0,0);
      TraceS(__FUNC__);
  }
  if(LogLevel>=llDebugLevel)
  {
    Server->Log("DateTime decoded: "+DateTimeToStr(dtRequestedTime)+"\n");
  }
TraceS(__FUNC__);
  slRequestedGroups=new TStringList;
  slRequestedGroups->Sorted=true;
  slRequestedGroups->Duplicates=dupIgnore;
  slRequestedGLine=new TStringList;
  slRejectedGLine=new TStringList;
  TraceS(__FUNC__);
  try
  {
    slRequestedGLine->CommaText=Group_s;
    for(int i=slRequestedGLine->Count-1;i>=0;i--)
    {
      if(slRequestedGLine->Strings[i].c_str()[0]=='!')
      {
        slRejectedGLine->Add(AnsiString(slRequestedGLine->Strings[i].c_str()+1));
        slRequestedGLine->Delete(i);
      }
      else
        ExpandWildCards(slRequestedGLine->Strings[i], FNewsGroupsList, slRequestedGroups);
    }
    for(int i=0;i<slRejectedGLine->Count;i++)
      ExcludeWildCards(slRequestedGroups,slRejectedGLine->Strings[i]);

    if(LogLevel>=llDebugLevel)
    {
      Server->Log("GroupsList: "+slRequestedGroups->CommaText+"\n");
    }

    SendAnswer(230, "New news follows");
TraceS(__FUNC__);
    SendNewNewsList(slRequestedGroups, dtRequestedTime);
    TraceS(__FUNC__);
    WriteLn(".");
    TraceS(__FUNC__);
  }
  __finally
  {
    delete slRejectedGLine;
    delete slRequestedGLine;
    delete slRequestedGroups;
  }
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessNEXT(AnsiString Argument)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::CheckValidFields(void)
{
TraceS(__FUNC__);
    if(FiCurrentData.Length())
    {
      int iMsgHeaderLength=FiCurrentData.Pos("\r\n\r\n")+2;
      AnsiString asMsgHeader=(FiCurrentData.SubString(1,iMsgHeaderLength)).LowerCase();
      if(!asMsgHeader.Pos("lines:"))
      {
        int iLines=0;
        TraceS(__FUNC__);
        for(int i=iMsgHeaderLength+2;i<FiCurrentData.Length();i++)
          if(FiCurrentData[i]=='\r')
          {
            iLines++;
            i++;
          }
          AnsiString tmp="";
          tmp.sprintf("Lines: %d\r\n",iLines);
          FiCurrentData.Insert(tmp,iMsgHeaderLength);
         //        FiCurrentData.Insert(Format("Lines: %d\r\n",ARRAYOFCONST((iLines))),iMsgHeaderLength);

      }
      TraceS(__FUNC__);
      if(!asMsgHeader.Pos("date:"))
      {
       // int tz=_timezone;
        AnsiString asDate="Date: ";
        asDate+=FormatDateTime("ddd, dd mmm yyy hh:nn:ss",Now());
        asDate+="\r\n";
        FiCurrentData.Insert(asDate,iMsgHeaderLength);
      }
    }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessPOST(AnsiString Argument)
{
//*!!13/06/99
TraceS(__FUNC__);
  if(!FPostingAllowed)
  {
    SendAnswer(440,"Posting not allowed");
    return;
  }
  else
    SendAnswer(340,"Continue posting");
//*/
//    SendAnswer(340,"Continue posting");
    FiCurrentData=ReadMsg();
    if(Terminated || !ClientSocket->Connected)
      SendAnswer(441,"Posting Failed. Server internal error 01");
    else
    {
      //****** Если майлер не поддерживает некоторые поля, то их надо добавить
      CheckValidFields();
      //***********************************************************************
      SaveArticle();//Записываем FiCurrentData на диск
//      if(Terminated)
//        SendAnswer(451,"Posting Failed. Server internal error 02");
//      else
//        SendAnswer(240,"Article posted successfully");
    }
//  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessQUIT(AnsiString Argument)
{
  SendAnswer(205,"Closing connection - goodbye!");
  FUserValid=false;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessSLAVE(AnsiString Argument)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessAUTHINFO_USER(AnsiString Argument)
{
  FUserValid=true;
  SendAnswer(281,"Ok");
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::ProcessAUTHINFO_PASS(AnsiString Argument)
{
  SendAnswer(281,"Ok");
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::SaveArticle(void)
{
TraceS(__FUNC__);
AnsiString asNewsGroups;
TStringList *slNewsGroups;
int iPos;
bool posting;
  slNewsGroups=new TStringList;
  try
  {
    //выкусываем служебную информацию
    asNewsGroups=(FiCurrentData.SubString(1,FiCurrentData.Pos("\r\n\r\n"))).LowerCase();
    iPos=asNewsGroups.Pos("newsgroups:");
    if(iPos)
    {
      asNewsGroups.Delete(1,iPos+10);
      asNewsGroups.Delete(asNewsGroups.Pos("\n"),asNewsGroups.Length());
      asNewsGroups=asNewsGroups.Trim();
      //определние, в какую из групп попало сообщение

      //asNewsGroups=this->SelectedGroup->InternalTag;
    }
    else
      asNewsGroups="";

    slNewsGroups->CommaText=asNewsGroups;
//    slNewsGroups->CommaText=this->SelectedGroup->Tag;
    int iSaveResults=BeginSaveArticles(slNewsGroups);
 TraceS(__FUNC__);
    if(LogLevel>=llDebugLevel)
      Server->Log("First save phase exit code: "+AnsiString(iSaveResults)+"\r\n");
    if(!iSaveResults)
    {
      for(int i=0;i<slNewsGroups->Count;i++)
      {

        if(!DoSaveArticle(slNewsGroups->Strings[i],FiCurrentData))
        {
          ClientSocket->Close();
        }
          /*if(slNewsGroups->Count>i && i>0)
            Sleep(1100);*/
      }
      EndSaveArticles();
      SendAnswer(240,"Article posted successfully");
    }
    else
      SendAnswer(440,"Posting not allowed");
//        Terminate();
      //обработку ошибок - переделать!
     // else
TraceS(__FUNC__);
  }
  __finally
  {
    slNewsGroups->Free();
  }
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomNNTPServerThread::DoSaveArticle(AnsiString NewsGroup, AnsiString Body)
{
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServerThread::SendNewsGroupsList(void)
{
AnsiString tmp;
AnsiString sNewsGroup;
TraceS(__FUNC__);
  for(int i=0;i<FNewsGroupsList->Count;i++)
  {
    if(!ClientSocket->Connected)
      break;
    sNewsGroup=FNewsGroupsList->Strings[i];
    if(SetActiveGroup(sNewsGroup))
    {
      tmp="";
      tmp.sprintf("%s %d %d %c",sNewsGroup.c_str(),ArticleNom[0],ArticleNom[ArticlesCount-1],FPostingAllowed ? 'y' :'n');
      WriteLn(tmp);
      //      WriteLn(sNewsGroup+" "+Format("%d %d",ARRAYOFCONST((ArticleNom[0],ArticleNom[ArticlesCount-1])))+
//      (FPostingAllowed ? " y" :" n"));

    }
  }
//  WriteLn(".");
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
inline  TiuCustomNNTPServer* __fastcall TiuCustomNNTPServerThread::GetNNTPServer(void)
{
  return (TiuCustomNNTPServer*)Server;
}
