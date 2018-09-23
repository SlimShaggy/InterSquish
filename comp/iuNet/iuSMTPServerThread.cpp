//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "iuEncoders.h"
#include "iuSMTPServerThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const String SMTP_HELO="HELO";
const String SMTP_EHLO="EHLO";
const String SMTP_AUTH="AUTH";
const String SMTP_MAIL="MAIL";
const String SMTP_RCPT="RCPT";
const String SMTP_DATA="DATA";
const String SMTP_RSET="RSET";
const String SMTP_NOOP="NOOP";
const String SMTP_QUIT="QUIT";

//---------------------------------------------------------------------------
__fastcall TCustomSMTPServerThread::TCustomSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
  : TiuServerClientThread(CreateSuspended,ASocket)
{
  FServiceName="SMTP";
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ClientExecute(void)
{
  if(ClientSocket->Connected)
  {
    //FAuthOk=true;

    if (!this->GetSMTPServer()->AuthRequired)
    {
        FAuthOk=true;
    }


    FAuthState=austNone;
    Prepare();
    SendAnswer(220,ServerSocket->LocalHost);
    TiuServerClientThread::ClientExecute();
    UnPrepare();
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TCustomSMTPServerThread::ProcessLogin(AnsiString Argument)
{
  FAuthState=austNone;
  if(CheckLogin(Argument,Argument))
  {
   SendAnswer(235,"Authentication successful");
  }
  else
  {
    SendAnswer(535,"Unknown user");
  }
}
*/
//---------------------------------------------------------------------------
/*
void __fastcall TCustomSMTPServerThread::ProcessPassword(AnsiString Argument)
{
  FAuthState=austNone;
  if(CheckUser(Argument))
  {
    FAuthOk=true;
    SendAnswer(235,"Authentication successful");
  }
  else
    SendAnswer(535,"Unknown user");
}
*/
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::HandleRecivedCommand(AnsiString Command)
{
//AnsiString Argument;
//  Argument=Command.TrimRight();
  TiuServerClientThread::HandleRecivedCommand(Command);
  if(!Terminated && ClientSocket->Connected)
  {
    if(!(Command.Trim()).Length())
      return;
//    if(FAuthState==austLogin)
//    {
//      ProcessLogin(Command);
//      return;
//    }

    AnsiString Argument=Command;
    Argument.Delete(1,Argument.Pos(" "));
    Argument=Argument.Trim();

    if(IsCommand(SMTP_HELO,Command))
		  ProcessHELO(Argument);
  	else
    if(IsCommand(SMTP_EHLO,Command))
		  ProcessEHLO(Argument);
  	else
	    if(IsCommand(SMTP_MAIL,Command))
  			ProcessMAIL(Argument);
	    else
  	  	if(IsCommand(SMTP_RCPT,Command))
  				ProcessRCPT(Argument);
	  	  else
  	    	if(IsCommand(SMTP_DATA,Command))
			  		ProcessDATA(Argument);
		  	  else
  	  	  	if(IsCommand(SMTP_RSET,Command))
	  					ProcessRSET(Argument);
      			else
   	    	  	if(IsCommand(SMTP_NOOP,Command))
				  			ProcessNOOP(Argument);
              else
             		if(IsCommand(SMTP_QUIT,Command))
                {
		  						ProcessQUIT(Argument);
                  ClientSocket->Close();
                }
                else
                  if(IsCommand(SMTP_AUTH,Command))
                    ProcessAUTH(Argument);
                else
                  SendAnswer(500,"Syntax error, command unrecognized");
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessHELO(String Argument)
{
  FAuthState=austNone;
  if(SMTPServer->AuthRequired)
  {
    SendAnswer(502,"Extended SMTP mode (EHLO) and AUTH command required");
    ClientSocket->Close();
  }
  else
  {
    FAuthOk=true;
    SendAnswer(250,ClientSocket->LocalHost);
  }
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::SendAnswer_(int ReplayCode, String Comment)
{
AnsiString tmp="";
  tmp.sprintf("%3.3d-%s",ReplayCode,Comment.c_str());
  WriteLn(tmp);
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessEHLO(String Argument)
{

  FAuthState=austNone;
  FAuthOk=!SMTPServer->AuthRequired;
  SendAnswer_(250,ClientSocket->LocalHost+" says hello");
  SendAnswer(250,"AUTH LOGIN");

}
//---------------------------------------------------------------------------
bool _fastcall TCustomSMTPServerThread::CheckLogin(AnsiString Name, AnsiString Password)
{
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessAUTH(String Argument)
{
    AnsiString asLoglogin;

  if(IsCommand("LOGIN", Argument))
  {
    SendAnswer(334,"VXNlcm5hbWU6");//"Username:";
    if(Terminated || !ClientSocket->Connected)
      return;
    AnsiString asUserName=ReadLn();
    asUserName=DecodeBase64(asUserName.TrimRight());
    asLoglogin="User: '"+asUserName+"' ";
    //SendAnswer(334,asUserName/*"VXNlcm5hbWU6"*/);//"Username:";
    if(FScriptArgsList)
      FScriptArgsList->ParamByName("ACC_NAME")=asUserName;

    if(Terminated || !ClientSocket->Connected)
      return;

    SendAnswer(334,"UGFzc3dvcmQ6");//"Password:";
    if(Terminated || !ClientSocket->Connected)
      return;

    AnsiString asUserPassword=ReadLn();
    asUserPassword=DecodeBase64(asUserPassword.TrimRight());

    asLoglogin+="Password: '"+asUserPassword+"'\n";

    Log(asLoglogin);
    //SendAnswer(334,asUserPassword);//"Password:";
    if(FScriptArgsList)
      FScriptArgsList->ParamByName("ACC_PASSWORD")=asUserPassword;

    if(Terminated || !ClientSocket->Connected)
      return;

    if(CheckLogin(asUserName,asUserPassword))
    {
      FAuthOk=true;
      SendAnswer(235,"Authentication successful");
    }
    else
      SendAnswer(535,"Unknown user");

//    FAuthState=austLogin;
  }
  else
    SendAnswer(504,"Unrecognized authentication type");
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessMAIL(String Argument)
{
  if(FAuthOk)
  {
  	ClearRecipientsList();
    SendAnswer(250,"OK");
  }
  else
    SendAnswer(530,"Authentication required");
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessRCPT(AnsiString Argument)
{
  if(FAuthOk)
  {
    if(AddRecipient(Argument))
    	SendAnswer(250,"OK");
    else
    	SendAnswer(550,"Invalid address");
  }
  else
    SendAnswer(530,"Authentication required");

}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessDATA(String Argument)
{
AnsiString sData;
  if(FAuthOk)
  {
  	SendAnswer(354,"Start mail input; end with <CRLF>.<CRLF>");

    sData=ReadMsg();
    
    if(Terminated || !ClientSocket->Connected)
    {
      SendAnswer(451,"SMTP Server internal error 01");
      return;
    }
  	if(SaveMsg(sData))
    {
      SendAnswer(250,"OK");
    }//Отказы обрабатываются в самой SaveMsg()...
  }
  else
    SendAnswer(530,"Authentication required");
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessRSET(String Argument)
{
  SendAnswer(250,"OK");
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessNOOP(String Argument)
{
  SendAnswer(220,"OK");
}
//---------------------------------------------------------------------------
void __fastcall TCustomSMTPServerThread::ProcessQUIT(String Argument)
{
 SendAnswer(221,ClientSocket->LocalHost+" Service closing transmission chanel");
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
__fastcall TSMTPServerThread::TSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket)
  : TCustomSMTPServerThread(CreateSuspended,ASocket)
{
  FLocalRecipients= new TStringList;
  FRemoteRecipients= new TStringList;
  FFidoRecipients= new TStringList;

  FLocalRecipients->Sorted=true;
  FRemoteRecipients->Sorted=true;
  FFidoRecipients->Sorted=true;

 	FLocalRecipients->Duplicates=dupIgnore;
 	FRemoteRecipients->Duplicates=dupIgnore;
 	FFidoRecipients->Duplicates=dupIgnore;
}
//---------------------------------------------------------------------------
__fastcall TSMTPServerThread::~TSMTPServerThread(void)
{
  FLocalRecipients->Free();
  FRemoteRecipients->Free();
  FFidoRecipients->Free();
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ClearRecipientsList(void)
{
  FLocalRecipients->Clear();
  FRemoteRecipients->Clear();
  FFidoRecipients->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ClientExecute(void)
{
  SendAnswer(220,ServerSocket->LocalHost);
  TiuServerClientThread::ClientExecute();
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::HandleRecivedCommand(AnsiString Command)
{
String Argument;
  Argument=Command.TrimRight();
  if(IsCommand(SMTP_HELO,Command) || IsCommand(SMTP_EHLO,Command))
		ProcessHELO(Argument);
	else
	  if(IsCommand(SMTP_MAIL,Command))
			ProcessMAIL(Argument);
	  else
  		if(IsCommand(SMTP_RCPT,Command))
				ProcessRCPT(Argument);
		  else
  	  	if(IsCommand(SMTP_DATA,Command))
					ProcessDATA(Argument);
		  	else
	  	  	if(IsCommand(SMTP_RSET,Command))
						ProcessRSET(Argument);
    			else
   	  	  	if(IsCommand(SMTP_NOOP,Command))
							ProcessNOOP(Argument);
            else
           		if(IsCommand(SMTP_QUIT,Command))
              {
								ProcessQUIT(Argument);
                Terminate();
              }
              else
                SendAnswer(500,"Syntax error, command unrecognized");
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessHELO(String Argument)
{
  SendAnswer(250,ClientSocket->LocalHost);
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessMAIL(String Argument)
{
	FLocalRecipients->Clear();
	FRemoteRecipients->Clear();
	FFidoRecipients->Clear();
  SendAnswer(250,"OK");

}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessRCPT(String Argument)
{
String sMailBox;
int iOffset;
TAddressType AddressType;

	iOffset=Argument.Pos("<")+1;//Вставить проверку!!!!!!!!!!!!!!!!!
	sMailBox=Argument.SubString(iOffset,Argument.Length()-iOffset);
	iOffset=sMailBox.Pos("@");
	if(iOffset)
		sMailBox=sMailBox.SubString(0,iOffset-1);
	AddressType=CheckAddressType(sMailBox);
  switch(AddressType)
  {
	case at_invalid:
    FLocalRecipients->Add("@Bad");
  	SendAnswer(550,"Unknown address");
    break;
  case at_local:
		FLocalRecipients->Add(sMailBox);
  	SendAnswer(250,"OK");
    break;
  case at_fido:
		FFidoRecipients->Add(sMailBox);
    SendAnswer(250,"OK");
    break;
  case at_internet:
		FRemoteRecipients->Add(sMailBox);
    SendAnswer(250,"OK");
    break;
  }

}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessDATA(String Argument)
{
AnsiString sData;
	SendAnswer(354,"Start mail input; end with <CRLF>.<CRLF>");

  sData=ReadMsg();
  if(Terminated)
  {
    SendAnswer(451,"Server internal error 01");
    return;
  }
	SaveMsg(sData);
  if(Terminated)
    SendAnswer(451,"Server internal error 02");
  else
    SendAnswer(250,"OK");
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessRSET(String Argument)
{
	FLocalRecipients->Clear();
	FRemoteRecipients->Clear();
	FFidoRecipients->Clear();
  SendAnswer(250,"OK");
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessNOOP(String Argument)
{
  SendAnswer(220,"OK");
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::ProcessQUIT(String Argument)
{
 SendAnswer(221,ClientSocket->LocalHost+" Service closing transmission chanel");
}
//---------------------------------------------------------------------------
void __fastcall TSMTPServerThread::SaveMsg(AnsiString sMsg)
{
HANDLE hMsg;
AnsiString sFullName;
DWORD dwBytesWritten;

	for(int i=0;i<FLocalRecipients->Count;i++)
  {
    sFullName=BoxesPath+"\\"+FLocalRecipients->Strings[i]+"\\"+GenMsgName();
    hMsg=CreateFile(sFullName.c_str(),GENERIC_WRITE,FILE_SHARE_WRITE,NULL,
      CREATE_NEW,FILE_ATTRIBUTE_NORMAL+FILE_FLAG_WRITE_THROUGH,NULL);
    if(hMsg!=INVALID_HANDLE_VALUE)
    {
      WriteFile(hMsg,sMsg.c_str(),sMsg.Length(),&dwBytesWritten,NULL);
      CloseHandle(hMsg);
    }
    else
      Terminate();
  }
}
//---------------------------------------------------------------------------
*/
