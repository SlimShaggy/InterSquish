//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <ctype.h>
#include "iuServer.h"
#include "iuServerClientThread.h"
#include "log.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TiuServerClientThread::TiuServerClientThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
  : TServerClientThread(CreateSuspended,ASocket)
{
TraceS(__FUNC__);
  FIntBufPos=0;
  CriticalSection= new TCriticalSection;
//  SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_IDLE);
}
//---------------------------------------------------------------------------
__fastcall TiuServerClientThread::~TiuServerClientThread(void)
{
  if(FScriptControl)
    delete FScriptControl;
  if(FScriptArgsList)
    delete FScriptArgsList;
  if(FSocketStream)
    delete FSocketStream;
  delete CriticalSection;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::ScriptError(TObject *Sender)
{
TraceS(__FUNC__);
AnsiString asLogLine="";//"WSH error:";
  asLogLine+=AnsiString(FScriptControl->Error->Source)+". ";
  asLogLine+=AnsiString(FScriptControl->Error->Description)+" (";
  asLogLine+="file: "+AnsiString(FScriptControl->CurrentFilename)+" ";
  asLogLine+="line: "+AnsiString(FScriptControl->Error->Line)+" ";
  asLogLine+="column: "+AnsiString(FScriptControl->Error->Column)+") ";

  asLogLine+=AnsiString(FScriptControl->Error->Text)+" ";
  Log(asLogLine+"\n");

  FScriptControl->Error->Clear();
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::ScriptTimeout(TObject *Sender)
{
TraceS(__FUNC__);
  Log("Script timeout. file:"+AnsiString(FScriptControl->CurrentFilename)+"\n");
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::Write(AnsiString sData)
{
TraceS(__FUNC__);
//  FSendingLine=sData+"\n";
  FSendingLine=sData;//+"\n";
//  sData+="\r\n";
  try
  {
    if(!FSocketStream->Write(sData.c_str(),sData.Length()))
      ClientSocket->Close();
//      Terminate();
    else
      if(LogLevel>=llRFCLayer)
        Synchronize(DoOutboundLogging);
    Sleep(3);
  }
  catch(...)
  {
    TraceS(__FUNC__);
    ClientSocket->Close();
//    Terminate();
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::WriteLn(AnsiString sData)
{
TraceS(__FUNC__);
  FSendingLine=sData;//+"\n";
  sData+="\r\n";
  try
  {
    if(!FSocketStream->Write(sData.c_str(),sData.Length()))
      ClientSocket->Close();
//      Terminate();
    else
      if(LogLevel>=llRFCLayer)
        Synchronize(DoOutboundLogging);
    Sleep(3);
  }
  catch(...)
  {
    TraceS(__FUNC__);
    ClientSocket->Close();
    Terminate();
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuServerClientThread::ReadLn(void)
{
TraceS(__FUNC__);
  Sleep(1);
  FReceivedLine="";
  try
  {
    while(true)
    {
      if(FInternalBuffer[FIntBufPos])
      {
        int iPrevLength=FReceivedLine.Length();
        FReceivedLine+=AnsiString(&FInternalBuffer[FIntBufPos]);

        char* index=strchr(FReceivedLine.c_str(),'\n');
        if(index)
        {
          FIntBufPos+=index-FReceivedLine.c_str()+1-iPrevLength;
          FReceivedLine.Delete(index-FReceivedLine.c_str()+2,I_BUF_SIZE);
          break;
        }
      }
      FIntBufPos=0;
TraceS(__FUNC__);
      while(!FSocketStream->WaitForData(200))
      {
        Sleep(10);
        if(Terminated || !ClientSocket->Connected)
          return FReceivedLine;
      }
  if(Terminated || !ClientSocket->Connected)
    return FReceivedLine;
      FInternalBuffer[FSocketStream->Read(FInternalBuffer,(I_BUF_SIZE-1))]=0;
      if(!FInternalBuffer[0])
      {
        ClientSocket->Close();
//        Terminate();
        break;
      }
    }
    if(LogLevel>=llRFCLayer)
      Synchronize(DoInboundLogging);
    Sleep(3);
TraceS(__FUNC__);
  }
  catch(...)
  {
TraceS(__FUNC__);
    FReceivedLine="";
    ClientSocket->Close();
    Terminate();
  }
TraceS(__FUNC__);
  return FReceivedLine;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TiuServerClientThread::ReadMsg(void)
{
AnsiString sMsg;
char Buf[I_BUF_SIZE];
int iPos;
TraceS(__FUNC__);
  sMsg="";
  if(FInternalBuffer[FIntBufPos])//провер€ем, есть ли остатки в общем буфере...
    sMsg+=AnsiString(&FInternalBuffer[FIntBufPos]);
  FInternalBuffer[FIntBufPos=0]=0;
  try
  {
  TraceS(__FUNC__);
    while(!sMsg.Pos("\r\n.\r\n"))
    {
      iPos=FSocketStream->Read(Buf,(I_BUF_SIZE-1));
      if(!iPos)
      {
        ClientSocket->Close();
//        Terminate();
        break;
      }
      Buf[iPos]=0;
      sMsg+=AnsiString(Buf);
    }
    TraceS(__FUNC__);
    char *tail=StrPos(Buf,"\r\n.\r\n");
    if(tail)
      strcpy(FInternalBuffer,tail+5);

    if(LogLevel>=llRFCLayer)
    {
      FReceivedLine=sMsg;
      Synchronize(DoInboundLogging);
      Sleep(3);
    }
  }
  catch(...)
  {
  TraceS(__FUNC__);
    sMsg="";
    ClientSocket->Close();
//    Terminate();
  }
  return sMsg;
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::ClientExecute(void)
{
TraceS(__FUNC__);
  try
  {
    while(!Terminated && ClientSocket->Connected)
      HandleRecivedCommand(ReadLn());
  }
  catch(Exception &exception)
  {
  char Buffer[1024];
    ExceptionErrorMessage(&exception, ExceptAddr(), Buffer, sizeof(Buffer));
    Log(AnsiString(Buffer)+"\n");
    Terminate();
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::LogEventHandler(TObject *Sender,AnsiString Message)
{
  Log(Message+"\n");
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::Prepare(void)
{
  FIntBufPos=0;
TraceS(__FUNC__);
  ZeroMemory(FInternalBuffer,I_BUF_SIZE);
  if(!FSocketStream)
    FSocketStream=new TWinSocketStream(ClientSocket,60000);
  FSocketStream->TimeOut=FTimeOut;
  FUTC=GetUTC();
  if(FServer->ScriptingEnable)
  {
    TraceS(__FUNC__);
    if(!FScriptControl)
    {
      TraceS(__FUNC__);
//      ::CoInitializeEx(0, COINIT_MULTITHREADED);
      ::CoInitialize(NULL);
      FScriptControl=new TiuScriptControl((TComponent *)FServer);
      FScriptArgsList=new TiuScriptArgsList;
      FScriptControl->Timeout=FServer->WshTimeout*1000;

      FScriptControl->OnError=ScriptError;
      FScriptControl->OnTimeout=ScriptTimeout;
      FScriptControl->OnLogEvent=LogEventHandler;
    }

    FScriptArgsList->ParamByName("SERVICENAME")=FServiceName;
    FScriptArgsList->ParamByName("REMOTE_IP")=ClientSocket->RemoteAddress;
    FScriptArgsList->ParamByName("THREAD_ID")=ThreadID;
    FScriptArgsList->ParamByName("COMMAND")="";
    FScriptArgsList->ParamByName("ACC_NAME")="";
    FScriptArgsList->ParamByName("ACC_PASSWORD")="";
    if(!(bool)ExecInstruction(Server->ScriptCfg->InstructionByName("IsIpValid"),FScriptControl, FScriptArgsList))
      ClientSocket->Close();
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::UnPrepare(void)
{
TraceS(__FUNC__);
  delete FSocketStream;
  FSocketStream=NULL;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuServerClientThread::RecodeLine(AnsiString PlainText)
{
TraceS(__FUNC__);
  if((FHeadersTypeCode==htcPlain)||(PlainText==""))
    return PlainText;
unsigned char *Ptr=(unsigned char *)PlainText.c_str();
  while(true)//ѕроверка на то, стоит ли вообще затеватьс€ с перекодировкой...
  {
    if(*Ptr>127)
      break;
    Ptr++;
    if(!(*Ptr))//дошли до конца строки но так и не встретили не-ascii символ...
      return PlainText;
  }
  Ptr=(unsigned char *)PlainText.c_str();//ќп€ть становимс€ в начало строки
  AnsiString Result("=?koi8-r?Q?");


  while(*Ptr)
  {
#if (__BORLANDC__ ==0x0530) || (__BORLANDC__ ==0x0540)
    if (*Ptr > 127 || *Ptr == 0x9 || *Ptr == 0x20 || *Ptr == 0x3D || *Ptr == 0x3F
        || *Ptr == 0x5F)
      Result.sprintf("=%02.2X",*Ptr);
    else
      Result.sprintf("%c",*Ptr);
#elif (__BORLANDC__ >=0x0550)
    if (*Ptr > 127 || *Ptr == 0x9 || *Ptr == 0x20 || *Ptr == 0x3D || *Ptr == 0x3F
        || *Ptr == 0x5F)
      //Result.cat_sprintf("=%02.2X",*Ptr);
      Result+="="+IntToHex(*Ptr, 2);
    else
      Result+=AnsiString((char *)Ptr,1);
//      Result.cat_sprintf("%c",*Ptr);
#else
#error UnknownVersion CBuilder!
#endif
    Ptr++;
  }
TraceS(__FUNC__);
  return Result+"?=";
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::HandleRecivedCommand(AnsiString Command)
{
TraceS(__FUNC__);
TraceS(Command.c_str());
  if(FScriptArgsList)
    FScriptArgsList->ParamByName("COMMAND")=Command;
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::SendAnswer(int ReplayCode, String Comment)
{
AnsiString tmp="";
TraceS(__FUNC__);
  tmp.sprintf("%3.3d %s",ReplayCode,Comment.c_str());
  TraceS(tmp.c_str());
  WriteLn(tmp);
  TraceS(__FUNC__);
  //  WriteLn(Format("%3.3d %s",ARRAYOFCONST((ReplayCode,Comment))));
}
//---------------------------------------------------------------------------
bool __fastcall TiuServerClientThread::IsCommand(AnsiString Command, AnsiString CommandLine)
{
TraceS(__FUNC__);
  CommandLine=CommandLine.UpperCase();
  Command=Command.UpperCase();
  return CommandLine.Pos(Command)==1;
}
//---------------------------------------------------------------------------
bool __fastcall TiuServerClientThread::IsCommand(AnsiString Command, AnsiString CommandLine, AnsiString &Argument)
{
TraceS(__FUNC__);
  if(IsCommand(Command, CommandLine))
  {
    Argument=CommandLine;
    Argument.Delete(1,Command.Length());
    Argument=Argument.Trim();
TraceS(__FUNC__);
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------
String __fastcall TiuServerClientThread::GenMsgName(void)
{
SYSTEMTIME STm;
AnsiString Result="";
	GetSystemTime(&STm);
  Result.sprintf("%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d-%3.3d.m",
  STm.wYear,STm.wMonth,STm.wDay,STm.wHour,STm.wMinute,STm.wSecond,STm.wMilliseconds);
//  return Format("%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d-%3.3d.m",
//    ARRAYOFCONST((STm.wYear,STm.wMonth,STm.wDay,STm.wHour,STm.wMinute,
//    STm.wSecond,STm.wMilliseconds)));
  return Result;
}
//---------------------------------------------------------------------------
int __fastcall TiuServerClientThread::GetUTC(void)
{
TraceS(__FUNC__);
  GetTimeZoneInformation(&FtzInfo);
  return (FtzInfo.Bias+FtzInfo.DaylightBias)/60;
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::SetBoxesPath(AnsiString Value)
{
TraceS(__FUNC__);
TraceS(Value.c_str());
  if(Value.c_str()[Value.Length()-1]=='\\')
    Value.Delete(Value.Length(),1);
  FBoxesPath=Value;
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::DoInboundLogging(void)
{
//  if(FOnLogEvent)
//    FOnLogEvent(this,"In: "+FReceivedLine);
TraceS(__FUNC__);
  if(FReceivedLine!="")
  {
  AnsiString asTemp=FReceivedLine;
    asTemp.Unique();
    if(LogLevel<llDebugLevel)
    {
      int iOldLen=asTemp.Length();
      asTemp.Delete(asTemp.Pos("\r"),asTemp.Length());
      if((asTemp.Length()+2)<iOldLen)
        asTemp+=" <...>";
    }
    Server->Log("["+AnsiString(ThreadID)+"] In: "+asTemp+"\n");
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::DoOutboundLogging(void)
{
//  if(FOnLogEvent)
//    FOnLogEvent(this,"Out: "+FSendingLine);
TraceS(__FUNC__);
  if(FSendingLine!="")
  {
    if(LogLevel<llDebugLevel)
    {
      int iOldLen=FSendingLine.Length();
      FSendingLine.Delete(FSendingLine.Pos("\r"),iOldLen);
      if((FSendingLine.Length()+2)<iOldLen)
        FSendingLine+=" <...>";
    }
    Server->Log("["+AnsiString(ThreadID)+"] Out: "+FSendingLine+"\n");
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServerClientThread::Log(AnsiString LogLine)
{
  Server->Log("["+AnsiString(ThreadID)+"] "+LogLine);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuServerClientThread::SplitRfcMessage(AnsiString RfcMessage, TStringList *HeaderLines)
{//„асто очень удобно работать заголовком сообщени€ в виде списка строк. ƒелаем такой список.
char cFirstChar;
AnsiString MessageBody="";
//  Result->Clear();
  int iEndOfHeaderPos=RfcMessage.Pos("\r\n\r\n");
  if(iEndOfHeaderPos)
  {
    HeaderLines->Text=AnsiString(RfcMessage.c_str(), iEndOfHeaderPos-1);
    MessageBody=AnsiString(RfcMessage.c_str()+iEndOfHeaderPos+3);
  }
  else
  {
    HeaderLines->Text=RfcMessage;
  }
  for(int i=HeaderLines->Count-1;i>0;i--)
  {
    cFirstChar=*(HeaderLines->Strings[i].c_str());
    if((cFirstChar==9)||(cFirstChar==32))
    {
      HeaderLines->Strings[i-1]=HeaderLines->Strings[i-1]+HeaderLines->Strings[i];
      HeaderLines->Delete(i);
    }
  }
  return MessageBody;
}
//---------------------------------------------------------------------------


