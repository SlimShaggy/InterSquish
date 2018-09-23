//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuPOP3Server.h"
#pragma link "iuServer"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TiuCustomPOP3Server::TiuCustomPOP3Server(TComponent* Owner)
  : TiuServer(Owner)
{
  Port=110;
  FLockedMailDropList=new TStringList;
  FLockedMailDropList->Sorted=true;
	FLockedMailDropList->Duplicates=dupIgnore;
}
//---------------------------------------------------------------------------
__fastcall TiuCustomPOP3Server::~TiuCustomPOP3Server()
{
  delete FLockedMailDropList;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3Server::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  TiuServer::GetThread(Sender, ClientSocket, SocketThread);
  ((TiuServerClientThread*) SocketThread)->HeadersTypeCode=HeadersTypeCode;

}
//---------------------------------------------------------------------------
void __fastcall TiuCustomPOP3Server::UnLockMailDrop(AnsiString Account)
{
int	Index;
  if(FLockedMailDropList->Find(Account,Index))
    FLockedMailDropList->Delete(Index);
}
//---------------------------------------------------------------------------
bool __fastcall TiuCustomPOP3Server::LockMailDrop(AnsiString Account)
{
int Index;
bool Result;
  Result=false;
  if(FLockedMailDropList && !FLockedMailDropList->Find(Account,Index))
  {
		FLockedMailDropList->Add(Account);
    Result=true;
  }
  return Result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
__fastcall TiuPOP3Server::TiuPOP3Server(TComponent* Owner)
  : TiuCustomPOP3Server(Owner)
{
//  Port=110;
//  FLockedMailDropList=new TStringList;
//  FLockedMailDropList->Sorted=true;
//	FLockedMailDropList->Duplicates=dupIgnore;

}
//---------------------------------------------------------------------------
__fastcall TiuPOP3Server::~TiuPOP3Server()
{
//  FLockedMailDropList->Free();
}
//---------------------------------------------------------------------------
void __fastcall TiuPOP3Server::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
//  TiuServer::GetThread(Sender, ClientSocket, SocketThread);
  SocketThread= new TiuPOP3ServerThread(true,ClientSocket);
//  ((TiuServerClientThread *)SocketThread)->TimeOut=TimeOut;
//  ((TiuServerClientThread *)SocketThread)->BoxesPath=BoxesPath;
//  ((TiuServerClientThread *)SocketThread)->LogLevel=LogLevel;
//  ((TiuServerClientThread *)SocketThread)->OnLogEvent=OnLogEvent;

//  ((TiuPOP3ServerThread *)SocketThread)->Server=this;
  ((TiuPOP3ServerThread *)SocketThread)->OnCheckPassword=OnCheckPassword;
  TiuCustomPOP3Server::GetThread(Sender, ClientSocket, SocketThread);
//  SocketThread->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TiuPOP3Server::DelLockMailDrop(AnsiString sMailBoxPath)
{
int	Index;
  if(FLockedMailDropList->Find(sMailBoxPath,Index))
    FLockedMailDropList->Delete(Index);
}
//---------------------------------------------------------------------------
bool __fastcall TiuPOP3Server::AddLockMailDrop(AnsiString sMailBoxPath)
{
int Index;
bool Result;
  Result=false;
  if(FLockedMailDropList && !FLockedMailDropList->Find(sMailBoxPath,Index))
  {
		FLockedMailDropList->Add(sMailBoxPath);
    Result=true;
  }
  return Result;
}
//---------------------------------------------------------------------------
namespace Iupop3server
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TiuPOP3Server)};
     RegisterComponents("Internet", classes, 0);
  }
}
//---------------------------------------------------------------------------
*/
