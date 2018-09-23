//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuSMTPServer.h"
#include "iuSMTPServerThread.h"

#pragma link "iuServer"
#pragma link "iuSMTPServerThread"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TiuCustomSMTPServer::TiuCustomSMTPServer(TComponent* Owner)
  : TiuServer(Owner)
{
  Port=25;
}
//---------------------------------------------------------------------------
__fastcall TiuCustomSMTPServer::~TiuCustomSMTPServer(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomSMTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  TiuServer::GetThread(Sender, ClientSocket, SocketThread);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
__fastcall TiuSMTPServer::TiuSMTPServer(TComponent* Owner)
  : TiuCustomSMTPServer(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuSMTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  SocketThread= new TSMTPServerThread(true,ClientSocket);
  TiuCustomSMTPServer::GetThread(Sender, ClientSocket, SocketThread);
}
//---------------------------------------------------------------------------
namespace Iusmtpserver
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TiuSMTPServer)};
     RegisterComponents("Internet", classes, 0);
  }
}
//---------------------------------------------------------------------------
*/
