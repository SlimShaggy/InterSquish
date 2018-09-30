//---------------------------------------------------------------------------
#ifndef iuInterSquishServerH
#define iuInterSquishServerH
//---------------------------------------------------------------------------
#include "iuNNTPServer.h"
#include "iuNNTPServerThread.h"
#include "iuSMTPServer.h"
#include "iuSMTPServerThread.h"
#include "iuPOP3Server.h"
#include "iuPOP3ServerThread.h"
#include "FTNDataSet.h"
#include "Cfg.h"
#include "FTNPKT.h"
//#include "uMessages.h"
#include <ScktComp.hpp>
//#include "isInit.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TiuIssNNTPServer : public TiuCustomNNTPServer
{
private:
  AnsiString FSquishCfgName;
  AnsiString FUsersCfgName;
  TUserInfo FDefaultUserInfo;
  AnsiString FPostFlagFileName;
  AnsiString FPktOrigAddress;
  AnsiString FPktDir;
  AnsiString FTearLine;
  AnsiString FOrigin;
  bool FTryFoundTo;
  bool FDescriptionsInAnsi;
  bool FPlainFido;
  bool FNeedSeenBy;
  TAreasConfig FAreasConfigType;
  AnsiString FDefaultInternetGate;
  AnsiString FAreasMasquerade;
    //THashTable AreasMask;
  void __fastcall SetDefaultAddres(AnsiString Value);
  AnsiString __fastcall GetFtnAddress(void){return FDefaultUserInfo.Address.AsString;};
  void __fastcall SetDefaultInternetGate(AnsiString value);

protected:
  virtual  void __fastcall Accept(TObject *Sender,TCustomWinSocket *Socket);
  virtual  void __fastcall ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);

  virtual void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
  void __fastcall SetSquishCfgName(AnsiString Value);
  void __fastcall SetUsersCfgName(AnsiString Value);
  void __fastcall SetMaskAreasCfgName(AnsiString value);
  

public:
  bool FRegKeyExist;
  bool FSNDecrypted;
  char NameDelimiter;
  AnsiString JamReplyLink;

  __fastcall TiuIssNNTPServer(TComponent* Owner);
  virtual __fastcall ~TiuIssNNTPServer();
        AnsiString __fastcall GetUsersFileName();

__published:
__property AnsiString AreasMasquerade  = { read=FAreasMasquerade, write=FAreasMasquerade };
  __property TAreasConfig AreasConfigType={read=FAreasConfigType, write=FAreasConfigType};
  __property AnsiString SquishCfgName={read=FSquishCfgName, write=SetSquishCfgName};
  __property AnsiString UsersCfgName={read=FUsersCfgName, write=SetUsersCfgName};
  __property AnsiString DefaultGroups={read=FDefaultUserInfo.Groups, write=FDefaultUserInfo.Groups};
  __property AnsiString DefaultROGroups={read=FDefaultUserInfo.ROGroups, write=FDefaultUserInfo.ROGroups};
  __property AnsiString FTNAddress={read=GetFtnAddress
  /*FDefaultUserInfo.Address.AsString*/, write=SetDefaultAddres};
  __property AnsiString PostFlag={read=FPostFlagFileName, write=FPostFlagFileName};
  __property AnsiString PktDir={read=FPktDir, write=FPktDir};
  __property AnsiString PktOrigAddress={read=FPktOrigAddress, write=FPktOrigAddress};
  __property AnsiString TearLine={read=FTearLine, write=FTearLine};
  __property AnsiString Origin={read=FOrigin, write=FOrigin};
  __property bool TryFoundTo  = { read = FTryFoundTo, write = FTryFoundTo };
  __property bool NeedSeenBy  = { read = FNeedSeenBy, write = FNeedSeenBy };
  __property bool DescriptionsInAnsi  = { read = FDescriptionsInAnsi, write = FDescriptionsInAnsi };
  __property bool PlainFido  = { read = FPlainFido, write = FPlainFido };

  __property Active;
  __property Port;
  __property ThreadCacheSize;
//  __property ServerType;
  __property LogLevel;
  __property TimeOut;
  __property OnLogEvent;
  __property LogName;
    __property AnsiString DefaultInternetGate  = { read = FDefaultInternetGate, write = SetDefaultInternetGate };

};
//---------------------------------------------------------------------------
class PACKAGE TiuIssNNTPServerThread : public TiuCustomNNTPServerThread
{
  TFTNDataSet *FSquishBase;
  TCustomUsersCfg *FUsersCfg;
  TCustomAreasCfg *FSquishCfg;
//  TSquishBase *FSquishBase;
  TUserInfo FUserInfo;
  TFTNPKT *FOutPacket;
  bool AuthChecked;
  bool __fastcall FindArticle(DWORD ANumber);
  void __fastcall Transliterate(TObject* Sender,char* Src,char* Dest,bool ToOEM);
  TiuIssNNTPServer * __fastcall GetISS(void){ return (TiuIssNNTPServer *)Server;};
  AnsiString __fastcall TryFoundTo(AnsiString Area, AnsiString MsgID);
  int FTranslitMode;
protected:

  TAreaInfo * __fastcall GetAreaInfo(int Index);
  virtual void __fastcall Prepare(void);

  virtual bool __fastcall PrepareHeader(TArticleHeader &AHeader);
  virtual bool __fastcall SetActiveGroup(AnsiString NewsGroup);
  virtual int __fastcall GetArticleNom(int Index);
  virtual int __fastcall GetArticlesCount(void);
  virtual void __fastcall ProcessQUIT(AnsiString Argument);
  virtual void __fastcall ProcessAUTHINFO_USER(AnsiString Argument);
  virtual void __fastcall ProcessAUTHINFO_PASS(AnsiString Argument);
  AnsiString __fastcall RetriveCurrentArticle(void);
  virtual bool __fastcall RetriveArticle(int ArticleNumber, AnsiString &Article);
  virtual bool __fastcall RetriveArticle(AnsiString MessageID, AnsiString &Article);
  virtual bool __fastcall BuildNewsGroupList(void);
  bool __fastcall ValidateUser(TUserInfo &UserInfo);

  virtual int __fastcall BeginSaveArticles(TStringList *NewsGroups);
  virtual bool __fastcall DoSaveArticle(AnsiString NewsGroup, AnsiString Body);
  virtual void __fastcall EndSaveArticles(void);
  virtual void __fastcall SendNewNewsList(TStringList *slRequestedGroups,TDateTime RequestedTime);
  virtual void __fastcall SendNewsListDesc(void);  
public:
	__fastcall TiuIssNNTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	virtual __fastcall ~TiuIssNNTPServerThread(void);
  __property TUserInfo UserInfo={read=FUserInfo,write=FUserInfo};
  __property TiuIssNNTPServer *ISS={read=GetISS};
  __property TAreaInfo *Areas[int Index]={read=GetAreaInfo};

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TiuIssSMTPServer : public TiuCustomSMTPServer
{
private:
  
  TUserInfo FDefaultUserInfo;
  AnsiString FPostFlagFileName;
  AnsiString FPktOrigAddress;
  AnsiString FPktDir;
  AnsiString FTearLine;
  AnsiString FOrigin;
  AnsiString FDefaultInternetGate;
  AnsiString FRemoteReadRequestFlags;
  AnsiString FRemoteRequest;
  bool FForceINTL;
  bool FPlainFido;
  TCustomUsersCfg *FUsersCfg;
  void __fastcall SetUsersCfg(TCustomUsersCfg *Value);

  void __fastcall SetDefaultAddres(AnsiString Value);
  AnsiString __fastcall GetFtnAddress(void){return FDefaultUserInfo.Address.AsString;};
    void __fastcall SetDefaultInternetGate(AnsiString value);
  int FMaxMsgSize;
    AnsiString FUsersCfgName;
protected:
  virtual void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
public:
  __fastcall TiuIssSMTPServer(TComponent* Owner);

__published:
  __property TCustomUsersCfg *UsersCfg={read=FUsersCfg, write=SetUsersCfg};
  __property AnsiString FTNAddress={read=GetFtnAddress
  /*FDefaultUserInfo.Address.AsString*/, write=SetDefaultAddres};
  __property AnsiString PostFlag={read=FPostFlagFileName, write=FPostFlagFileName};
  __property AnsiString PktDir={read=FPktDir, write=FPktDir};
  __property AnsiString PktOrigAddress={read=FPktOrigAddress, write=FPktOrigAddress};
  __property AnsiString TearLine={read=FTearLine, write=FTearLine};
  __property AnsiString Origin={read=FOrigin, write=FOrigin};
  __property bool ForceINTL  = { read = FForceINTL, write = FForceINTL };
  __property int  MaxMsgSize = { read = FMaxMsgSize, write = FMaxMsgSize};
  __property bool PlainFido  = { read = FPlainFido, write = FPlainFido };
  __property AnsiString UsersCfgName={read=FUsersCfgName,write=FUsersCfgName};
  __property AnsiString RemoteReadRequestFlags={read=FRemoteReadRequestFlags,write=FRemoteReadRequestFlags};
  __property AnsiString RemoteRequest={read=FRemoteRequest,write=FRemoteRequest};
  __property Active;
  __property Port;
  __property ThreadCacheSize;
  __property LogLevel;
  __property TimeOut;
  __property OnLogEvent;
  __property LogName;
    __property AnsiString DefaultInternetGate  = { read = FDefaultInternetGate, write = SetDefaultInternetGate };

};
//---------------------------------------------------------------------------
class PACKAGE TiuIssSMTPServerThread : public TCustomSMTPServerThread
{
private:
  int FTranslitMode;
  TUserInfo FUserInfo;
  bool FDedicatedPoint;
  TListOfX<TFTNAddress> *FReciptAddreses;
  TUserInfo loginUser;

  inline TiuIssSMTPServer * __fastcall GetISS(void);
  /*{
    return (TiuIssSMTPServer *)Server;
  };*/

  void __fastcall FillAdrList(TListOfX<TFTNAddress> *adrList,TStringList *RfcMsg,char * FieldName);
  void __fastcall InitMsg(TFTNMsg *Msg, AnsiString MsgBody, TStringList *HeaderLines, TFTNAddress *ReciptAddress);
protected:

  virtual bool __fastcall SaveMsg(AnsiString RfcMsg);
  virtual void __fastcall ClearRecipientsList();
  virtual bool __fastcall AddRecipient(AnsiString Argument);
  virtual bool _fastcall CheckLogin(AnsiString Name, AnsiString Password);
  virtual void __fastcall Prepare(void);

public:
	__fastcall TiuIssSMTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	virtual __fastcall ~TiuIssSMTPServerThread(void);
  //__property TFTNAddress Address={read=FUserFTNAddress, write=FUserFTNAddress};
  __property TiuIssSMTPServer *ISS={read=GetISS};
  __property TUserInfo UserInfo={read=FUserInfo,write=FUserInfo};

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TiuIssPOP3Server : public TiuCustomPOP3Server
{
  TFTNAddress *FAddress;
  TCustomUsersCfg *FUsersCfg;
  AnsiString FTrashPath;
  WORD FHoldFlagsMask;
  bool FBBSMode;
  void __fastcall SetUsersCfg(TCustomUsersCfg *Value);
  void __fastcall SetAddress(AnsiString Value);
  AnsiString __fastcall GetAddress(void);
  int FTranslitMode;
  AnsiString FUsersCfgName;
protected:
  virtual void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);

public:
    char NameDelimiter;
    __fastcall TiuIssPOP3Server(TComponent* Owner);
   virtual  __fastcall ~TiuIssPOP3Server(void);
  __property TFTNAddress *Address={read=FAddress};
__published:
  __property TCustomUsersCfg *UsersCfg={read=FUsersCfg, write=SetUsersCfg};
  __property AnsiString FTNAddress={read=GetAddress, write=SetAddress};
  __property AnsiString TrashPath  = { read = FTrashPath, write = FTrashPath };
  __property bool BBSMode = {read = FBBSMode, write = FBBSMode};
  __property WORD HoldFlagsMask={read = FHoldFlagsMask, write = FHoldFlagsMask};
  __property AnsiString UsersCfgName={read=FUsersCfgName,write=FUsersCfgName};
  __property Active;
  __property Port;
  __property ThreadCacheSize;
//  __property ServerType;
  __property LogLevel;
  __property TimeOut;
  __property OnLogEvent;
  __property LogName;
  __property BoxesPath;

};
//---------------------------------------------------------------------------
class PACKAGE TiuIssPOP3ServerThread : public TiuCustomPOP3ServerThread
{
private:
  int FTranslitMode;
  TMsgBase *FMsgBase;
  TiuIssPOP3Server * __fastcall GetISS(void){ return (TiuIssPOP3Server *)Server;};
  TUserInfo FUserInfo;
//  AnsiString FUserName;
//  AnsiString FUserPassword;
//  AnsiString FUserAddress;
//  TFTNAddress FUserFTNAddress;
  bool FDedicatedPoint;
  void __fastcall FindUser(void);
  void __fastcall FilterRecord(TDataSet *DataSet, bool &Accept);
  void __fastcall Transliterate(TObject* Sender,char* Src,char* Dest,bool ToOEM);

protected:
  virtual void __fastcall Prepare(void);
  virtual void __fastcall UnPrepare(void);

  virtual bool _fastcall CheckPassword(AnsiString Argument);
  virtual bool _fastcall CheckUser(AnsiString Argument);
  virtual bool __fastcall LockMailDrop(void);
  virtual void __fastcall DeleteMsg(AnsiString MsgId);
  virtual AnsiString __fastcall RetriveMsg(int MsgNo);
  virtual int __fastcall GetMsgSize(int Index);
  virtual int __fastcall GetMsgCount();
  virtual int __fastcall GetTotalMsgSize();

public:
	__fastcall TiuIssPOP3ServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
	virtual __fastcall ~TiuIssPOP3ServerThread(void);
  __property TiuIssPOP3Server *ISS={read=GetISS};
__published:
};
//---------------------------------------------------------------------------
#endif

