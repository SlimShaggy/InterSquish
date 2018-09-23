//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuPOP3ServerThreadH

#include "iuServerClientThread.h"
#include "Xxxlist.h"
//---------------------------------------------------------------------------
//typedef void __fastcall (__closure *TOnCheckPassword)(TObject *Sender,AnsiString sPsw, bool *Ok);

//---------------------------------------------------------------------------
struct TMailDropItem
{
  int MsgNo;
  int Size;
  AnsiString MsgId;
  bool Deleted;
  __fastcall TMailDropItem(void)
  {
    MsgNo=Size=0;
    MsgId="";
    Deleted=false;
  };
  __fastcall TMailDropItem(int AMsgNo, int ASize, AnsiString AMsgId)
  {
    MsgNo=AMsgNo;
    Size=ASize;
    MsgId=AMsgId;
    Deleted=false;
  }
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TiuCustomPOP3Server;
//---------------------------------------------------------------------------
class PACKAGE TiuCustomPOP3ServerThread : public TiuServerClientThread
{
private:
//  TOnCheckPassword FOnCheckPassword;
  bool FSuccessLocked;
  bool FPasswordValid;
  AnsiString FPassword;
  AnsiString FUser;

  TiuCustomPOP3Server *GetPOP3Server(void){return (TiuCustomPOP3Server *)Server;}
  void __fastcall DoLockMailDrop(void);
  void __fastcall DoUnLockMailDrop(void);

protected:
  TListOfX<TMailDropItem> *FMessages;

  void __fastcall SendOk(AnsiString Comment);
  void __fastcall SendErr(AnsiString Comment);

  virtual void _fastcall ProcessAUTH(AnsiString Argument);
  virtual void _fastcall ProcessUSER(AnsiString Argument);
	virtual void _fastcall ProcessPASS(AnsiString Argument);
	virtual void _fastcall ProcessSTAT(AnsiString Argument);
	virtual void _fastcall ProcessLIST(AnsiString Argument);
	virtual void _fastcall ProcessRETR(AnsiString Argument);
	virtual void _fastcall ProcessDELE(AnsiString Argument);
	virtual void _fastcall ProcessRSET(AnsiString Argument);
	virtual void _fastcall ProcessNOOP(AnsiString Argument);
	virtual void _fastcall ProcessQUIT(AnsiString Argument);
	virtual void _fastcall ProcessUIDL(AnsiString Argument);
	virtual void _fastcall ProcessTOP(AnsiString Argument);
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);

  virtual bool _fastcall CheckPassword(AnsiString Argument)=0;
  virtual bool _fastcall CheckUser(AnsiString Argument)=0;

  virtual bool __fastcall LockMailDrop(void);
  virtual void __fastcall UnLockMailDrop(void);
  virtual void __fastcall DeleteMsg(AnsiString MsgId)=0;
  virtual AnsiString __fastcall RetriveMsg(int MsgNo);
  virtual int __fastcall GetMsgSize(int Index)=0;
  virtual int __fastcall GetMsgCount()=0;
  virtual int __fastcall GetTotalMsgSize()=0;

  __property AnsiString User={read=FUser, write=FUser};
  __property bool PasswordValid={read=FPasswordValid};
  __property TiuCustomPOP3Server* POP3Server={read=GetPOP3Server};

  __property int TotalMsgSize  = { read = GetTotalMsgSize };
  __property TListOfX<TMailDropItem> * Messages  = { read = FMessages };

public:
	__fastcall TiuCustomPOP3ServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	__fastcall virtual ~TiuCustomPOP3ServerThread(void);

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
class PACKAGE TiuPOP3ServerThread : public TiuCustomPOP3ServerThread
{
private:
//  TOnCheckPassword FOnCheckPassword;
//  TiuPOP3Server *FServer;
  int  FTotalMsgSize;
  TStringList* FMessages;
  TStringList* FDeletedMsg;
  AnsiString FMailBoxPath;
  bool PasswordValid;


  void __fastcall ProcessAUTH(AnsiString &Argument);
  void __fastcall ProcessUSER(AnsiString &Argument);
	void __fastcall ProcessPASS(AnsiString &Argument);
	void __fastcall ProcessSTAT(AnsiString &Argument);
	void __fastcall ProcessLIST(AnsiString &Argument);
	void __fastcall ProcessRETR(AnsiString &Argument);
	void __fastcall ProcessDELE(AnsiString &Argument);
	void __fastcall ProcessRSET(AnsiString &Argument);
	void __fastcall ProcessNOOP(AnsiString &Argument);
	void __fastcall ProcessQUIT(AnsiString &Argument);
	void __fastcall ProcessUIDL(AnsiString &Argument);
  bool __fastcall CheckPassword(AnsiString &Argument);
  void __fastcall DoCheckPassword(void);
  void __fastcall LockMailDrop(void);
  void __fastcall DoAddMailDropLockList(void);
  void __fastcall DoDelLockMailDropList(void);
  AnsiString __fastcall GetMsgSize(int index);
  AnsiString __fastcall GetMsgFileName(int index);
  AnsiString __fastcall GetDeletingMsgName(int index);

protected:
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);
public:
	__fastcall TiuPOP3ServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	__fastcall virtual ~TiuPOP3ServerThread(void);
  __property String MsgFileName[int index] = {read=GetMsgFileName};
  __property String DeletingMsgName[int index] = {read=GetDeletingMsgName};
//  __property TOnCheckPassword OnCheckPassword={read=FOnCheckPassword,write=FOnCheckPassword};
  __property AnsiString MailBoxPath={read=FMailBoxPath,write=FMailBoxPath};
  __property AnsiString User={read=FUser, write=FUser};
  __property String MsgSize[int index] = {read=GetMsgSize};

};
*/
//---------------------------------------------------------------------------


#define iuPOP3ServerThreadH
//---------------------------------------------------------------------------
#endif
