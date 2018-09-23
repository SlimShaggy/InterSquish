//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuServerClientThreadH
#define iuServerClientThreadH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include "iuScriptControl.h"

//---------------------------------------------------------------------------
#define I_BUF_SIZE 1025
//---------------------------------------------------------------------------
//enum TAddressType {at_invalid,at_local,at_fido,at_internet};
enum TLogLevel {llTCPLayer=1,llRFCLayer,llRFCLayer2,llDebugLevel};
enum THeadersTypeCode {htcPlain=0,htcQuotedPrintable};

//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOnCheckPassword)(TObject *Sender,AnsiString sPsw, bool *Ok);
typedef void __fastcall (__closure *TOnLogEvent)(TObject* Sender,AnsiString sEvent);

//---------------------------------------------------------------------------
class PACKAGE TiuServer;
//---------------------------------------------------------------------------
class PACKAGE TiuServerClientThread : public TServerClientThread
{
private:
  TiuServer *FServer;
  TOnLogEvent FOnLogEvent;
  TOnCheckPassword FOnCheckPassword;

  String FReceivedLine;
  String FSendingLine;
  AnsiString FBoxesPath;
  int FLogLevel;
  char FInternalBuffer[I_BUF_SIZE];
  int FIntBufPos;
  void __fastcall SetBoxesPath(AnsiString Value);
  int FTimeOut;
  THeadersTypeCode FHeadersTypeCode;
  void __fastcall ScriptError(TObject *Sender);
  void __fastcall ScriptTimeout(TObject *Sender);
  void __fastcall LogEventHandler(TObject *Sender,AnsiString Message);
protected:
  TCriticalSection *CriticalSection;
  TWinSocketStream* FSocketStream;
  TiuScriptControl* FScriptControl;
  TiuScriptArgsList *FScriptArgsList;
  AnsiString FServiceName;
  
  TIME_ZONE_INFORMATION FtzInfo;
  int FUTC;
  int __fastcall GetUTC(void);

  bool __fastcall IsCommand(AnsiString Command, AnsiString CommandLine);
  bool __fastcall IsCommand(AnsiString Command, AnsiString CommandLine, AnsiString &Argument);
  String __fastcall GenMsgName(void);
//  TAddressType __fastcall CheckAddressType(String sMailBox);
  virtual void __fastcall Prepare(void);
  virtual void __fastcall UnPrepare(void);
	virtual void __fastcall ClientExecute(void);
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  void __fastcall SendAnswer(int ReplayCode, String Comment);
  void __fastcall Write(AnsiString sData);
  void __fastcall WriteLn(AnsiString sData);
  AnsiString __fastcall ReadLn(void);
  AnsiString __fastcall ReadMsg(void);

  void __fastcall DoInboundLogging(void);
  void __fastcall DoOutboundLogging(void);
  void __fastcall Log(AnsiString LogLine);
  AnsiString __fastcall RecodeLine(AnsiString PlainText);
  AnsiString __fastcall SplitRfcMessage(AnsiString RfcMessage, TStringList *HeaderLines);
public:
	__fastcall TiuServerClientThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	__fastcall virtual ~TiuServerClientThread(void);

  __property AnsiString BoxesPath={read=FBoxesPath,write=SetBoxesPath};
  __property int LogLevel= {read=FLogLevel, write=FLogLevel};
  __property int TimeOut= {read=FTimeOut, write=FTimeOut};
  __property TiuServer *Server= {read=FServer, write=FServer};
  __property TOnLogEvent OnLogEvent={read=FOnLogEvent, write=FOnLogEvent};
  __property TOnCheckPassword OnCheckPassword={read=FOnCheckPassword,write=FOnCheckPassword};
  __property THeadersTypeCode HeadersTypeCode={read=FHeadersTypeCode, write=FHeadersTypeCode};
};
//---------------------------------------------------------------------------
#endif
