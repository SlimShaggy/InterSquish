//---------------------------------------------------------------------------
#ifndef isControlWindowH
#define isControlWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "isInit.h"
#include "Cfg.h"
#include "iuInterSquishServer.h"
#include "iuNNTPServer.h"
#include "iuServer.h"
#include "iuSMTPServer.h"
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include <Buttons.hpp>
#include "FTNDataSet.h"
#include <Db.hpp>
#include <Menus.hpp>
#include "iuInterSquishServer.h"
#include "iuPOP3Server.h"
#include "iuIPAddr.h"

#define MYWM_NOTIFY         (WM_APP+100)
#define IDC_MYICON                     1006
//extern HINSTANCE g_hinst;
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi);

//---------------------------------------------------------------------------
class TfDisplay : public TForm
{
__published:	// IDE-managed Components
  TPageControl *PageControl1;
  TTabSheet *tsNTTP;
  TTabSheet *tsSMTP;
  TTabSheet *tsPOP3;
  TSquishCfg *SquishCfg;
  TiuIssNNTPServer *IssNNTP;
  TTextCfg *TextCfg;
  TCustomUsersCfg *UsersCfg;
  TTimer *tmr;
  TTimer *Tim2;
  TiuIssSMTPServer *IssSMTP;
  TListBox *lbNNTP;
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel4;
  TLabel *lnntpActiveThreads;
  TPanel *Panel3;
  TLabel *lnntpIdleThreads;
  TPanel *Panel5;
  TLabel *lnntpThreadCacheSize;
  TPanel *Panel6;
  TLabel *lnntpActiveConnections;
  TBitBtn *bbtNNTPStart;
  TBitBtn *bbtNNTPStop;
  TTimer *tmrInfo;
  TPanel *Panel7;
  TPanel *Panel8;
  TPanel *Panel9;
  TLabel *lsmtpActiveThreads;
  TPanel *Panel10;
  TLabel *lsmtpIdleThreads;
  TPanel *Panel11;
  TLabel *lsmtpThreadCacheSize;
  TPanel *Panel12;
  TLabel *lsmtpActiveConnections;
  TBitBtn *bbtSMTPStart;
  TBitBtn *bbtSMTPStop;
  TListBox *lbSMTP;
  TPopupMenu *PopupMenu;
  TMenuItem *pmClose;
  TMenuItem *N2;
  TMenuItem *StopSMTP;
  TMenuItem *StartSMTP;
  TMenuItem *N3;
  TMenuItem *StopNNTP;
  TMenuItem *StartNNTP;
  TMenuItem *N1;
  TMenuItem *OpenWindow;
  TiuIssPOP3Server *IssPOP3;
  TPanel *Panel13;
  TLabel *lsmtpTotalSessions;
  TPanel *Panel14;
  TLabel *lnntpTotalSessions;
  TPanel *Panel15;
  TPanel *Panel16;
  TPanel *Panel17;
  TLabel *lpop3ActiveThreads;
  TPanel *Panel18;
  TLabel *lpop3IdleThreads;
  TPanel *Panel19;
  TLabel *lpop3ThreadCacheSize;
  TPanel *Panel20;
  TLabel *lpop3ActiveConnections;
  TPanel *Panel21;
  TLabel *lpop3TotalSessions;
  TBitBtn *bbtPOP3Start;
  TBitBtn *bbtPOP3Stop;
  TListBox *lbPOP3;
  TMenuItem *N4;
  TMenuItem *StartPOP3;
  TMenuItem *StopPOP3;
  TTwitIpCfg *TwitIpCfg;
  TFastechoCfg *FastechoCfg;
  TScriptCfg *ScriptCfg;
  void __fastcall IssNNTPServerEvent(TiuServer *Sender,
          TServerInfo &ServerInfo);
  void __fastcall tmrInfoTimer(TObject *Sender);
  void __fastcall bbtNNTPStopClick(TObject *Sender);
  void __fastcall bbtNNTPStartClick(TObject *Sender);
  void __fastcall bbtSMTPStartClick(TObject *Sender);
  void __fastcall bbtSMTPStopClick(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall pmCloseClick(TObject *Sender);
  void __fastcall OpenWindowClick(TObject *Sender);
  void __fastcall IssNNTPHostAccept(TiuServer *Sender,
          TCustomWinSocket *Socket);
  void __fastcall IssNNTPHostDisconnect(TiuServer *Sender,
          TCustomWinSocket *Socket);
  void __fastcall IssSMTPHostAccept(TiuServer *Sender,
          TCustomWinSocket *Socket);
  void __fastcall IssSMTPHostDisconnect(TiuServer *Sender,
          TCustomWinSocket *Socket);
  void __fastcall bbtPOP3StartClick(TObject *Sender);
  void __fastcall bbtPOP3StopClick(TObject *Sender);
  void __fastcall IssPOP3HostAccept(TiuServer *Sender,
          TCustomWinSocket *Socket);
  void __fastcall IssPOP3HostDisconnect(TiuServer *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
//TisMain  *FServer;
  TStringList *slNNTPConnections;
  bool bNNTPListChanged;
  TStringList *slSMTPConnections;
  bool bSMTPListChanged;
  TStringList *slPOP3Connections;
  bool bPOP3ListChanged;
  TCriticalSection *CriticalSection;
    void __fastcall DrawItem(TMessage& Msg);
    void __fastcall MyNotify(TMessage& Msg);
    void __fastcall QuerySession(TMessage& Msg);
    void __fastcall EndSession(TMessage& Msg);
    bool __fastcall TrayMessage(DWORD dwMessage);
    HICON __fastcall IconHandle(void);
    void __fastcall ToggleState(void);
    PSTR __fastcall TipText(void);
//    void __fastcall TrayPopUpMenu(TMessage & Msg);


public:		// User declarations
BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(WM_DRAWITEM,TMessage,DrawItem)
MESSAGE_HANDLER(MYWM_NOTIFY,TMessage,MyNotify)
MESSAGE_HANDLER(WM_QUERYENDSESSION,TMessage,QuerySession)
MESSAGE_HANDLER(WM_ENDSESSION,TMessage,EndSession)
//MESSAGE_HANDLER(WM_RBUTTONUP, TMessage, TrayPopUpMenu)
END_MESSAGE_MAP(TForm)

  __fastcall TfDisplay(TComponent* Owner);
    __fastcall ~TfDisplay();
};
//---------------------------------------------------------------------------
extern PACKAGE TfDisplay *fDisplay;
//---------------------------------------------------------------------------
#endif
 
 

