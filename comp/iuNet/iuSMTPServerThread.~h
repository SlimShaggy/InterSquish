//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuSMTPServerThreadH
#define iuSMTPServerThreadH
#include "iuSMTPServer.h"
#include "iuServerClientThread.h"
//---------------------------------------------------------------------------
enum TAuthStates {austNone,austLogin,austPassword};
//---------------------------------------------------------------------------
class PACKAGE TCustomSMTPServerThread : public TiuServerClientThread
{
private:
  TiuCustomSMTPServer* __fastcall GetSMTPServer(void){return (TiuCustomSMTPServer*) Server;};
  bool FAuthOk;
  TAuthStates FAuthState;
//	TStringList* FLocalRecipients;
//	TStringList* FRemoteRecipients;
//	TStringList* FFidoRecipients;
void __fastcall SendAnswer_(int ReplayCode, String Comment);

protected:

  virtual void __fastcall ProcessHELO(String Argument);
  virtual void __fastcall ProcessEHLO(String Argument);
  virtual void __fastcall ProcessAUTH(String Argument);
  virtual void __fastcall ProcessMAIL(String Argument);
  virtual void __fastcall ProcessRCPT(String Argument);
  virtual void __fastcall ProcessDATA(String Argument);
  virtual void __fastcall ProcessRSET(String Argument);
  virtual void __fastcall ProcessNOOP(String Argument);
  virtual void __fastcall ProcessQUIT(String Argument);

//  virtual void __fastcall ProcessPassword(AnsiString Argument);
  virtual bool _fastcall CheckLogin(AnsiString Name, AnsiString Password);
  virtual bool __fastcall SaveMsg(AnsiString sMsg)=0;
  virtual void __fastcall ClearRecipientsList(void)=0;
  virtual bool __fastcall AddRecipient(AnsiString Argument)=0;
  virtual void __fastcall Prepare(void){TiuServerClientThread::Prepare();};

  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);

public:
	__fastcall TCustomSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
  __property TiuCustomSMTPServer *SMTPServer={read=GetSMTPServer};

};
//---------------------------------------------------------------------------
/*
class PACKAGE TSMTPServerThread : public TCustomSMTPServerThread
{
private:
	TStringList* FLocalRecipients;
	TStringList* FRemoteRecipients;
	TStringList* FFidoRecipients;

  virtual void __fastcall ProcessHELO(String Argument);
  virtual void __fastcall ProcessMAIL(String Argument);
  virtual void __fastcall ProcessRCPT(String Argument);
  virtual void __fastcall ProcessDATA(String Argument);
  virtual void __fastcall ProcessRSET(String Argument);
  virtual void __fastcall ProcessNOOP(String Argument);
  virtual void __fastcall ProcessQUIT(String Argument);
//  virtual void __fastcall SaveMsg(AnsiString sMsg);

protected:
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);
  virtual bool __fastcall AddRecipient(AnsiString Argument){return false;};
  virtual void __fastcall ClearRecipientsList(void);
  virtual void __fastcall SaveMsg(AnsiString sMsg);

public:
	__fastcall TSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	__fastcall virtual ~TSMTPServerThread(void);
  __property TiuCustomSMTPServer *SMTPServer={read=GetSMTPServer};
};
//---------------------------------------------------------------------------
*/
#endif
