//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "isControlWindow.h"
#include "iuVerInfo.h"
#include "isInit.h"
#include "log.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Cfg"
#pragma link "iuInterSquishServer"
#pragma link "iuNNTPServer"
#pragma link "iuServer"
#pragma link "iuSMTPServer"
#pragma link "FTNDataSet"
#pragma link "iuPOP3Server"
#pragma link "iuIPAddr"
#pragma resource "*.dfm"
TfDisplay *fDisplay;
//---------------------------------------------------------------------------
__fastcall TfDisplay::TfDisplay(TComponent* Owner)
  : TForm(Owner)
{

  CriticalSection= new TCriticalSection;

TraceS("enter create form");
  Application->ShowMainForm=false;
 	TrayMessage(NIM_ADD);
  TrayMessage(NIM_MODIFY);
  slNNTPConnections=new TStringList;
  bNNTPListChanged=true;
  slSMTPConnections=new TStringList;
  bSMTPListChanged=true;
  slPOP3Connections=new TStringList;
  bPOP3ListChanged=true;

  TextCfg->Path=ParamStr(0).Delete(ParamStr(0).LastDelimiter("."),4)+".cfg";
  TwitIpCfg->Path=TextCfg->Path;
  ScriptCfg->Path=TextCfg->Path;  
  AnsiString asAreasCfg=TextCfg->ParamAsString("AreasCfg");
  if(asAreasCfg=="")
    asAreasCfg=TextCfg->ParamAsString("SquishCfg");
  if(asAreasCfg=="")
  {
    asAreasCfg=TextCfg->ParamAsString("FastechoCfg");
    FastechoCfg->Path=asAreasCfg;
//    IssNNTP->SquishCfg=FastechoCfg;
  }
  else
  {
    SquishCfg->Path=asAreasCfg;
//    IssNNTP->SquishCfg=SquishCfg;
  }
  AnsiString asUsersCfgName=TextCfg->ParamAsString("UsersCfg");
  if(asUsersCfgName!="")
    UsersCfg->Path=asUsersCfgName;

//  UsersCfg->Path=TextCfg->ParamAsString("UsersCfg");

//  IssNNTP->UsersCfg=UsersCfg;
  ReadNNTPServerConfiguration(IssNNTP, TextCfg);
  ReadSMTPServerConfiguration(IssSMTP, TextCfg);
  ReadPOP3ServerConfiguration(IssPOP3, TextCfg);
  IssNNTP->Open();
  IssSMTP->Open();
  IssPOP3->Open();
  Caption="InterSquish "+VI_THIS_EXE.FileVersion;
TraceS("leave create form");
}
//---------------------------------------------------------------------------
__fastcall TfDisplay::~TfDisplay()
{
TraceS("enter destroy form");
  IssNNTP->Close();
  IssSMTP->Close();
  IssPOP3->Close();
  delete slNNTPConnections;
  delete slSMTPConnections;
  delete slPOP3Connections;
TraceS("leave destroy form");
delete CriticalSection;
}

void __fastcall TfDisplay::IssNNTPServerEvent(TiuServer *Sender,
      TServerInfo &ServerInfo)
{
//
  lnntpActiveConnections->Caption=AnsiString(ServerInfo.ActiveConnections);
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::tmrInfoTimer(TObject *Sender)
{
  CriticalSection->Enter();
try
{
TraceS("enter infotimer");
  if(Visible)
  {
  IssNNTP->UpdateServerInfo();
  lnntpActiveConnections->Caption=AnsiString(IssNNTP->ServerInfo->ActiveConnections);
  lnntpActiveThreads->Caption=AnsiString(IssNNTP->ServerInfo->ActiveThreads);
  lnntpIdleThreads->Caption=AnsiString(IssNNTP->ServerInfo->IdleThreads);
  IssSMTP->UpdateServerInfo();
  TraceS("");
  if(bNNTPListChanged)
  {
    TraceS("nntplistchanged");
    lnntpThreadCacheSize->Caption=AnsiString(IssNNTP->ServerInfo->ThreadCacheSize);
    lbNNTP->Items->Assign(slNNTPConnections);
    bNNTPListChanged=false;
    lnntpTotalSessions->Caption=AnsiString(IssNNTP->SessionsCount);
  }
  TraceS("");
  lsmtpActiveConnections->Caption=AnsiString(IssSMTP->ServerInfo->ActiveConnections);
  lsmtpActiveThreads->Caption=AnsiString(IssSMTP->ServerInfo->ActiveThreads);
  lsmtpIdleThreads->Caption=AnsiString(IssSMTP->ServerInfo->IdleThreads);
  if(bSMTPListChanged)
  {
    TraceS("smtplistchanged");
    lsmtpThreadCacheSize->Caption=AnsiString(IssSMTP->ServerInfo->ThreadCacheSize);
    lbSMTP->Items->Assign(slSMTPConnections);
    bSMTPListChanged=false;
    lsmtpTotalSessions->Caption=AnsiString(IssSMTP->SessionsCount);
  }
  TraceS("");
  lpop3ActiveConnections->Caption=AnsiString(IssPOP3->ServerInfo->ActiveConnections);
  lpop3ActiveThreads->Caption=AnsiString(IssPOP3->ServerInfo->ActiveThreads);
  lpop3IdleThreads->Caption=AnsiString(IssPOP3->ServerInfo->IdleThreads);
  if(bPOP3ListChanged)
  {
    TraceS("pop3listchanged");
    lpop3ThreadCacheSize->Caption=AnsiString(IssPOP3->ServerInfo->ThreadCacheSize);
    lbPOP3->Items->Assign(slPOP3Connections);
    bPOP3ListChanged=false;
    lpop3TotalSessions->Caption=AnsiString(IssPOP3->SessionsCount);
  }

  }
}
__finally
{
  TraceS("leave infotimer");
  CriticalSection->Leave();
}
}
//---------------------------------------------------------------------------
void __fastcall OpenServer(TiuServer *Server, TBitBtn *bbtStart, TBitBtn *bbtStop)
{
  TraceS("");
  Screen->Cursor=crHourGlass;
  try
  {
  TraceS("");
    Server->Open();
  TraceS("");
    bbtStart->Enabled=false;
    bbtStop->Enabled=true;
  }
  __finally
  {
    Screen->Cursor=crDefault;
  }
}
//---------------------------------------------------------------------------
void __fastcall CloseServer(TiuServer *Server, TBitBtn *bbtStart, TBitBtn *bbtStop)
{
  TraceS("");
  Screen->Cursor=crHourGlass;
  try
  {
  TraceS("");
    Server->Close();
  TraceS("");
    bbtStart->Enabled=true;
    bbtStop->Enabled=false;
  }
  __finally
  {
    Screen->Cursor=crDefault;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::bbtNNTPStopClick(TObject *Sender)
{
  CloseServer(IssNNTP,bbtNNTPStart,bbtNNTPStop);

  StartNNTP->Enabled=true;
  StopNNTP->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TfDisplay::bbtNNTPStartClick(TObject *Sender)
{
  TextCfg->Refresh();
  ReadNNTPServerConfiguration(IssNNTP, TextCfg);

  OpenServer(IssNNTP,bbtNNTPStart,bbtNNTPStop);
  StartNNTP->Enabled=false;
  StopNNTP->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::bbtSMTPStartClick(TObject *Sender)
{
  TextCfg->Refresh();
  ReadSMTPServerConfiguration(IssSMTP, TextCfg);
  OpenServer(IssSMTP,bbtSMTPStart,bbtSMTPStop);
  StartSMTP->Enabled=false;
  StopSMTP->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfDisplay::bbtSMTPStopClick(TObject *Sender)
{

  CloseServer(IssSMTP,bbtSMTPStart,bbtSMTPStop);
  StartSMTP->Enabled=true;
  StopSMTP->Enabled=false;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TfDisplay::DrawItem(TMessage& Msg)
{
     IconDrawItem((LPDRAWITEMSTRUCT)Msg.LParam);
     TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::MyNotify(TMessage& Msg)
{
    POINT MousePos;
  TraceS("enter notify");
    switch(Msg.LParam)
    {
        case WM_RBUTTONUP:
            if (GetCursorPos(&MousePos))
            {
                PopupMenu->PopupComponent = fDisplay;
                SetForegroundWindow(Handle);
                PopupMenu->Popup(MousePos.x, MousePos.y);
            }
            else
                Show();
            break;
        case WM_LBUTTONDBLCLK:
            Show();
            Application->Restore();
      //      Application->ProcessMessages();
            break;
        default:

            break;
    }
//    Dispatch(&Msg);
    TForm::Dispatch(&Msg);
  TraceS("leave notify");
}
//---------------------------------------------------------------------------
bool __fastcall TfDisplay::TrayMessage(DWORD dwMessage)
{
   NOTIFYICONDATA tnd;
   PSTR pszTip;

   pszTip = TipText();

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = Handle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage	= MYWM_NOTIFY;

   if (dwMessage == NIM_MODIFY)
    {
        tnd.hIcon		= (HICON)IconHandle();
        if (pszTip)
           lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	    else
        tnd.szTip[0] = '\0';
    }
   else
    {
        tnd.hIcon = NULL;
        tnd.szTip[0] = '\0';
    }

   return (Shell_NotifyIcon(dwMessage, &tnd));
}
//---------------------------------------------------------------------------
HICON __fastcall TfDisplay::IconHandle(void)
{
  return LoadIcon(HInstance,"MAINICON");
//    if (RadioButton1->Checked)
//        return (Image1->Picture->Icon->Handle);
//    else
//        return (Image2->Picture->Icon->Handle);
}
//---------------------------------------------------------------------------
PSTR __fastcall TfDisplay::TipText(void)
{
static char buf[48];
  AnsiString tmp="InterSquish "+VI_THIS_EXE.FileVersion;
  strncpy(buf,tmp.c_str(),40);
  return buf;
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::FormDestroy(TObject *Sender)
{
	TrayMessage(NIM_DELETE);
}
//---------------------------------------------------------------------------
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
	HICON hIcon;
  hIcon = LoadIcon(0,"MAINICON");
	if (!hIcon)
		return(FALSE);

	DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
		16, 16, 0, NULL, DI_NORMAL);

	return(TRUE);
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::QuerySession(TMessage& Msg)
{
  Msg.Result=true;
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::EndSession(TMessage& Msg)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose=false;
  Hide();
 	TrayMessage(NIM_ADD);
  TrayMessage(NIM_MODIFY);
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::pmCloseClick(TObject *Sender)
{
  Application->Terminate();
  Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfDisplay::OpenWindowClick(TObject *Sender)
{
  Show();
//  BringToFront();
//  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall AddHost(TStringList *Strings,AnsiString HostAddr)
{
  Strings->Add(HostAddr/*+" "+HostName*/);

}
//---------------------------------------------------------------------------
void __fastcall DelHost(TStringList *Strings,AnsiString HostAddr)
{
  TraceS("");
  AnsiString DeletedItem=HostAddr;//+" "+HostName;
  int i=Strings->IndexOf(DeletedItem);
  if(i>=0)
    Strings->Delete(i);
  TraceS("");
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssNNTPHostAccept(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  TraceS("");
  AddHost(slNNTPConnections, Socket->RemoteAddress);
  bNNTPListChanged=true;
  TraceS("");
//    Application->ProcessMessages();
//  lbNNTP->Items->Add("xxx");
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssNNTPHostDisconnect(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  TraceS("");
  DelHost(slNNTPConnections, Socket->RemoteAddress);
  bNNTPListChanged=true;
    TraceS("");
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssSMTPHostAccept(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  AddHost(slSMTPConnections, Socket->RemoteAddress);
  bSMTPListChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssSMTPHostDisconnect(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  DelHost(slSMTPConnections, Socket->RemoteAddress);
  bSMTPListChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::bbtPOP3StartClick(TObject *Sender)
{
  TextCfg->Refresh();
  ReadPOP3ServerConfiguration(IssPOP3, TextCfg);

  OpenServer(IssPOP3,bbtPOP3Start,bbtPOP3Stop);
  StartPOP3->Enabled=false;
  StopPOP3->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::bbtPOP3StopClick(TObject *Sender)
{
  CloseServer(IssPOP3,bbtPOP3Start,bbtPOP3Stop);
  StartPOP3->Enabled=true;
  StopPOP3->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssPOP3HostAccept(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  AddHost(slPOP3Connections, Socket->RemoteAddress);
  bPOP3ListChanged=true;

}
//---------------------------------------------------------------------------
void __fastcall TfDisplay::IssPOP3HostDisconnect(TiuServer *Sender,
      TCustomWinSocket *Socket)
{
  DelHost(slPOP3Connections, Socket->RemoteAddress);
  bPOP3ListChanged=true;

}
//---------------------------------------------------------------------------



