//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>

#include "iuPOP3ServerThread.h"
#include "iuPOP3Server.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const AnsiString POP3_AUTH="AUTH";
const AnsiString POP3_USER="USER";
const AnsiString POP3_PASS="PASS";
const AnsiString POP3_STAT="STAT";
const AnsiString POP3_LIST="LIST";
const AnsiString POP3_RETR="RETR";
const AnsiString POP3_DELE="DELE";
const AnsiString POP3_NOOP="NOOP";
const AnsiString POP3_RSET="RSET";
const AnsiString POP3_QUIT="QUIT";
const AnsiString POP3_UIDL="UIDL";
const AnsiString POP3_TOP="TOP";
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuCustomPOP3ServerThread::TiuCustomPOP3ServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
  : TiuServerClientThread(CreateSuspended,ASocket)
{
  FMessages=new TListOfX<TMailDropItem>;
  FServiceName="POP3";
//  FDeletedMsg=new TMsgIndex;
}
//---------------------------------------------------------------------------
__fastcall TiuCustomPOP3ServerThread::~TiuCustomPOP3ServerThread(void)
{
  if(FMessages)
    delete FMessages;
//  if(FDeletedMsg)
//    delete FDeletedMsg;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::ClientExecute(void)
{
  if(ClientSocket->Connected)
  {
    Prepare();
    FSuccessLocked=false;

    try
    {
      SendOk("POP3 Server ready");
      TiuServerClientThread::ClientExecute();
    }
    catch(...)
    {
      Terminate();
    }
    UnPrepare();
    if(FSuccessLocked)
      UnLockMailDrop();
  }
}



//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::HandleRecivedCommand(AnsiString Command)
{
  TiuServerClientThread::HandleRecivedCommand(Command);
  if(!Terminated && ClientSocket->Connected)
  {
    if(!(Command.Trim()).Length())
      return;
    AnsiString Argument=Command;
    if(Argument.Pos(" "))
    {
      Argument.Delete(1,Argument.Pos(" "));
      Argument=Argument.Trim();
    }
    else
      Argument="";

    if(IsCommand(POP3_AUTH,Command))
	  	ProcessAUTH(Argument);
  	else if(IsCommand(POP3_USER,Command))
      ProcessUSER(Argument);
    else if(IsCommand(POP3_PASS,Command))
      ProcessPASS(Argument);
    else if(IsCommand(POP3_STAT,Command))
	  	ProcessSTAT(Argument);
    else if(IsCommand(POP3_LIST,Command))
      ProcessLIST(Argument);
    else if(IsCommand(POP3_RETR,Command))
      ProcessRETR(Argument);
    else if(IsCommand(POP3_DELE,Command))
      ProcessDELE(Argument);
    else if(IsCommand(POP3_RSET,Command))
      ProcessRSET(Argument);
    else if(IsCommand(POP3_NOOP,Command))
      ProcessNOOP(Argument);
    else if(IsCommand(POP3_UIDL,Command))
      ProcessUIDL(Argument);
    else if(IsCommand(POP3_TOP,Command))
      ProcessTOP(Argument);
    else if(IsCommand(POP3_QUIT,Command))
    {
 	    ProcessQUIT(Argument);
      ClientSocket->Close();
    }
    else
    SendErr("Unknown command");
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::SendOk(AnsiString Comment)
{
  WriteLn("+OK "+Comment);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::SendErr(AnsiString Comment)
{
  WriteLn("-ERR "+Comment);
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessAUTH(AnsiString Argument)
{
 	SendOk("");
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessUSER(AnsiString Argument)
{
  if(FScriptArgsList)
    FScriptArgsList->ParamByName("ACC_NAME")=Argument;
	if (CheckUser(Argument))
  {
    FUser=Argument;
  	SendOk("Mailbox " +UpperCase(Argument)+ " was founded");
  }
  else
  	SendErr("Sorry, no mailbox for "+UpperCase(Argument)+" here");
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessPASS(AnsiString Argument)
{
  FMessages->Clear();
//  FDeletedMsg->Clear();
  if(FScriptArgsList)
    FScriptArgsList->ParamByName("ACC_PASSWORD")=Argument;

	if (CheckPassword(Argument))
  {
		if(LockMailDrop())
      SendOk("Maildrop locked and ready");
    else
    SendErr("Unable to lock maildrop");
  }
  else
  	SendErr("Invalid password");
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessSTAT(AnsiString Argument)
{
  SendOk(AnsiString(FMessages->Count)+" "+AnsiString(TotalMsgSize));
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessLIST(AnsiString Argument)
{
	if(Argument!="")
  {
		int iMsgNo=StrToIntDef(Argument,0);
    if((iMsgNo>0) && (iMsgNo<=FMessages->Count))
			SendOk(Argument+" "+AnsiString(FMessages->Items[iMsgNo-1]->Size));
    else
      SendErr("No such message: "+AnsiString(iMsgNo)+" Only "+AnsiString(FMessages->Count)+" messages in maildrop");
  }
  else
  {
		SendOk(AnsiString(FMessages->Count)+" messages ("+AnsiString(TotalMsgSize)+" octets)");
    for(int i=0;i<FMessages->Count;i++)
    	WriteLn(AnsiString(i+1)+" "+FMessages->Items[i]->Size);
		WriteLn(".");
  }
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessRETR(AnsiString Argument)
{
int i;
AnsiString asMsg;
		i=StrToIntDef(Argument,0);
    if(LogLevel>2)
      Server->Log("Retr "+AnsiString(i)+"-"+AnsiString(FMessages->Count)+"\r\n");
    if(!i || (i>FMessages->Count+1))
    	SendErr("No such message");
    else
		{
      asMsg=RetriveMsg(FMessages->Items[i-1]->MsgNo);
      if(asMsg!="")
      {
        SendOk(AnsiString(asMsg.Length())+" octets");
        WriteLn(asMsg);
      }
	    else
  	  	SendErr("No such message");
    }
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessTOP(AnsiString Argument)
{
int iMsgNo=0, iLinesCount=0;
AnsiString asMsg;
    sscanf(Argument.c_str(),"%d %d",&iMsgNo,&iLinesCount);
//		i=StrToIntDef(Argument,0);
    if(LogLevel>2)
      Server->Log("Retr "+AnsiString(iMsgNo)+"-"+AnsiString(FMessages->Count)+"\r\n");
    if(!iMsgNo || (iMsgNo>FMessages->Count+1))
    	SendErr("No such message");
    else
		{
      asMsg=RetriveMsg(FMessages->Items[iMsgNo-1]->MsgNo);
      if(asMsg!="")
      {
      char *pcMsg=asMsg.c_str();
        SendOk("");
        while(iLinesCount)
        {
          pcMsg=strchr(pcMsg,'\n');
          if(!pcMsg)
            break;
          else
            pcMsg++;
          iLinesCount--;
        }
        if(pcMsg)
        {
          if(pcMsg!=asMsg.c_str())
          {
            asMsg.Delete(pcMsg-asMsg.c_str(),asMsg.Length());
            WriteLn(asMsg);
          }
     		  WriteLn(".");
        }
        else
          WriteLn(asMsg);//¬ыводим все сообщение ( в том числе и точечку)
      }
	    else
  	  	SendErr("No such message");
    }

}
//---------------------------------------------------------------------------
/*
void __fastcall TiuCustomPOP3ServerThread::AddItem(int *Items, int Item)
{
  int i=0;
  while(Items[i]>0)
    i++;
  Items[i]=Item;
};
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::ClearItems(int *Items)
{
  for(int i=0;i<FMessages->Count;i++)
    Items[i]=0;
}
*/
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::ProcessDELE(AnsiString Argument)
{
int i;
	i=StrToIntDef(Argument,0);
  if((!i) || (i>FMessages->Count))
  	SendErr("No such message");
  else
	{
//    FDeletedMsg->AddNew(FMessages->Items[i-1]);
    FMessages->Items[i-1]->Deleted=true;
  	SendOk("Message "+Argument+" deleted");
	}
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessRSET(AnsiString Argument)
{
//	FMessages->AddItems(FDeletedMsg);
//  FDeletedMsg->Clear();
  for(int i=0;i<FMessages->Count;i++)
    FMessages->Items[i]->Deleted=false;
//  SendOk(Format("Maildrop has %d messages",ARRAYOFCONST((FMessages->Count))));


  SendOk("Maildrop has "+AnsiString(FMessages->Count)+ " messages");
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessNOOP(AnsiString Argument)
{
	SendOk("");
}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessQUIT(AnsiString Argument)
{

	for(int i=0;i<FMessages->Count;i++)
    if(FMessages->Items[i]->Deleted)
    	DeleteMsg(FMessages->Items[i]->MsgId);
	SendOk("Dewey POP3 Server signing off");
  UnLockMailDrop();
  //this->Terminate();

}
//---------------------------------------------------------------------------
void _fastcall TiuCustomPOP3ServerThread::ProcessUIDL(AnsiString Argument)
{
	if(Argument!="")
  {
		int iMsgNo=StrToIntDef(Argument,0);
    if((iMsgNo>0) && (iMsgNo<=FMessages->Count))
			SendOk(Argument+" "+FMessages->Items[iMsgNo-1]->MsgId);
    else
      SendErr("No such message: "+AnsiString(iMsgNo)+" Only "+AnsiString(FMessages->Count)+" messages in maildrop");
    //    	SendErr(Format("No such message: %d. Only %d messages in maildrop",
//        ARRAYOFCONST((iMsgNo,FMessages->Count))));
  }
  else
  {
		SendOk("");
    for (int i=1;i<=FMessages->Count;i++)
    	WriteLn(AnsiString(i)+" "+FMessages->Items[i-1]->MsgId);
		WriteLn(".");
  }
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomPOP3ServerThread::LockMailDrop(void)
{
//  FTotalMsgSize=0;
  FMessages->Clear();
  Synchronize(DoLockMailDrop);
  return FSuccessLocked;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::DoLockMailDrop(void)
{
  FSuccessLocked=POP3Server->LockMailDrop(FUser);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::UnLockMailDrop(void)
{
  FMessages->Clear();
  Synchronize(DoUnLockMailDrop);
  FSuccessLocked=false;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3ServerThread::DoUnLockMailDrop(void)
{
  POP3Server->UnLockMailDrop(FUser);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuCustomPOP3ServerThread::RetriveMsg(int MsgNo)
{
  return "";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

