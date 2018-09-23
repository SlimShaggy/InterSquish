//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuSMTPServerH
#define iuSMTPServerH
//---------------------------------------------------------------------------
#include "iuServer.h"
//#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class PACKAGE TiuCustomSMTPServer : public TiuServer
{
protected:
  virtual  void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);

public:
  __fastcall TiuCustomSMTPServer(TComponent* Owner);
  virtual __fastcall ~TiuCustomSMTPServer(void);
__published:
  __property AuthRequired;

};
//---------------------------------------------------------------------------
/*
class PACKAGE TiuSMTPServer : public TiuCustomSMTPServer
{
private:
protected:
  virtual  void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);

public:
  __fastcall TiuSMTPServer(TComponent* Owner);
__published:
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
*/
#endif
