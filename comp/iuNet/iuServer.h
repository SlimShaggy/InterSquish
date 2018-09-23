//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuServerH
#define iuServerH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "ScktComp.hpp"
#include "Xxxlist.h"
#include "iuIPAddr.h"
#include "iuServerClientThread.h"
//---------------------------------------------------------------------------
struct PACKAGE TServerInfo
{
  int ActiveConnections;
	int ActiveThreads;
	int IdleThreads;
	int ThreadCacheSize;
};
//---------------------------------------------------------------------------
class TiuServer;
typedef void __fastcall (__closure *TOnServerEvent)(TiuServer* Sender, TCustomWinSocket *Socket);
//typedef void __fastcall (__closure *TOnServerEvent)(TiuServer* Sender, TCustomWinSocket *Socket, AnsiString RemoteAddr,AnsiString RemoteHost);
//---------------------------------------------------------------------------
class PACKAGE TiuServer : public TCustomServerSocket
{
private:
  TOnLogEvent FOnLogEvent;
  TTwitIpCfg *FTwitIpCfg;
  TScriptCfg *FScriptCfg;
  int FWshTimeout;
//  TOnServerEvent FOnServerEvent;
  THeadersTypeCode FHeadersTypeCode;
  TOnServerEvent FOnAccept;
  TOnServerEvent FOnDisconnect;
  AnsiString FLogName;
  String FBoxesPath;
  int FLogLevel;
  int FTimeOut;
  int FSessionsCount;
  bool FAuthRequired;
  TCustomWinSocket *FtmpCurrentSocket;
  TServerInfo FServerInfo;
    int FNumSameConnections;
  TServerInfo * __fastcall GetServerInfo(void){return &FServerInfo;};
  bool __fastcall FindInTwitList(AnsiString IpAddress);
  bool FScriptingEnable;
//  void __fastcall DoOnAccept(void);
//  void __fastcall DoOnDisconnect(void);
protected:
  TCriticalSection *CriticalSection;
  virtual  void __fastcall Accept(TObject *Sender,TCustomWinSocket *Socket);
  virtual  void __fastcall ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);

  virtual void __fastcall ClientSocketEvent(TObject* Sender, TCustomWinSocket* Socket, TSocketEvent SocketEvent);
  virtual  void __fastcall ErrorEvent(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
  //  virtual  void __fastcall ClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
  virtual  void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
  virtual  void __fastcall Listen(TObject *Sender, TCustomWinSocket *Socket);
  virtual  void __fastcall ThreadEnd(TObject *Sender, TServerClientThread *Thread);
  virtual  void __fastcall ThreadStart(TObject *Sender, TServerClientThread *Thread);
//  virtual  void __fastcall ServerEvent(void);
  __property Active;
  __property Port;
  __property Service;
  __property ServerType;
  __property ThreadCacheSize;
  __property AnsiString BoxesPath={read=FBoxesPath,write=FBoxesPath};
  __property int LogLevel= {read=FLogLevel, write=FLogLevel};
  __property int TimeOut= {read=FTimeOut, write=FTimeOut};
  __property bool AuthRequired={read=FAuthRequired, write=FAuthRequired};
  __property TOnLogEvent OnLogEvent={read=FOnLogEvent, write=FOnLogEvent};

  __property AnsiString LogName={read=FLogName, write=FLogName};
  __property THeadersTypeCode HeadersTypeCode={read=FHeadersTypeCode, write=FHeadersTypeCode};
public:
  __fastcall TiuServer(TComponent* Owner);
  virtual __fastcall ~TiuServer();
  void __fastcall Log(AnsiString sEvent);
//  unsigned int __fastcall FileSize(AnsiString Name);
  void __fastcall UpdateServerInfo(void);
  __property TServerInfo * ServerInfo={read=GetServerInfo};
  __property int SessionsCount={read=FSessionsCount};
__published:

  __property TTwitIpCfg *TwitIpCfg = { read = FTwitIpCfg, write = FTwitIpCfg};
  __property TScriptCfg *ScriptCfg = { read = FScriptCfg, write = FScriptCfg};
  __property int NumSameConnections  = { read = FNumSameConnections, write = FNumSameConnections, default = 0 };
  __property bool ScriptingEnable  = { read = FScriptingEnable, write = FScriptingEnable };
  __property int WshTimeout  = { read = FWshTimeout, write = FWshTimeout };
  __property TOnServerEvent OnHostAccept={read=FOnAccept, write=FOnAccept};
  __property TOnServerEvent OnHostDisconnect={read=FOnDisconnect, write=FOnDisconnect};
};

//---------------------------------------------------------------------------
#endif
