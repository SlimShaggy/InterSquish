//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuPOP3ServerH
#define iuPOP3ServerH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include "iuServer.h"
#include "iuPOP3ServerThread.h"

//---------------------------------------------------------------------------
class PACKAGE TiuCustomPOP3Server : public TiuServer
{
private:
  TStringList* FLockedMailDropList;
//  TOnCheckPassword FOnCheckPassword;
protected:
  virtual  void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
//  __property TOnCheckPassword OnCheckPassword={read=FOnCheckPassword,write=FOnCheckPassword};
public:
  __fastcall TiuCustomPOP3Server(TComponent* Owner);
  __fastcall ~TiuCustomPOP3Server();
  virtual bool __fastcall LockMailDrop(AnsiString Account);
  virtual void __fastcall UnLockMailDrop(AnsiString Account);
__published:
  __property HeadersTypeCode;

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TiuPOP3Server : public TiuCustomPOP3Server
{
private:
  TStringList* FLockedMailDropList;
  TOnCheckPassword FOnCheckPassword;
protected:
  virtual  void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
public:
  __fastcall TiuPOP3Server(TComponent* Owner);
  __fastcall ~TiuPOP3Server();
  virtual bool __fastcall AddLockMailDrop(AnsiString sMailBoxPath);
  virtual void __fastcall DelLockMailDrop(AnsiString sMailBoxPath);
__published:
  __property TOnCheckPassword OnCheckPassword={read=FOnCheckPassword,write=FOnCheckPassword}; 
  __property Active;
  __property Port;
  __property ThreadCacheSize;
//  __property ServerType;
  __property BoxesPath;
  __property LogLevel;
  __property TimeOut;
  __property OnLogEvent;
  __property LogName;
};
//---------------------------------------------------------------------------
#endif
