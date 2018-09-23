//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuConsole.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
HWND TiuConsole::FWindowHandle;
void * TiuConsole::FOldWindowProc;

//---------------------------------------------------------------------------
__fastcall TiuConsole::TiuConsole(void)
{
  if(!AllocConsole())
    throw Exception("Console alredy allocated");
//HANDLE hc=CreateConsoleScreenBuffer(GENERIC_READ+GENERIC_WRITE,FILE_SHARE_READ+FILE_SHARE_WRITE,0,CONSOLE_TEXTMODE_BUFFER,0);
//COORD cc={40,25};
//SetConsoleScreenBufferSize(hc, cc);
//SetConsoleMode(hc,ENABLE_ECHO_INPUT+ENABLE_PROCESSED_OUTPUT);
//SetConsoleActiveScreenBuffer(hc);
  FhOut=CreateFile("CONOUT$",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0 );
  if(!SetStdHandle(STD_OUTPUT_HANDLE	, FhOut))
    throw Exception("Unable open CONOUT$");
  FWindowHandle=ConsoleHwnd();
  FOldWindowProc=(void*)SetWindowLong(FWindowHandle, GWL_WNDPROC,(LONG) &WindowProc);
int e=GetLastError();
  SetConsoleCtrlHandler((PHANDLER_ROUTINE) &ConHandler,true);
  TrayMessage(NIM_ADD);
  TrayMessage(NIM_MODIFY);
}
//---------------------------------------------------------------------------
__fastcall TiuConsole::~TiuConsole(void)
{
  TrayMessage(NIM_DELETE);
  SetConsoleCtrlHandler(&ConHandler,false);

  CloseHandle(FhOut);
  FreeConsole();
}
//---------------------------------------------------------------------------
LRESULT CALLBACK TiuConsole::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return CallWindowProc((int (__stdcall *)())FOldWindowProc, hwnd, uMsg, wParam, lParam);

//    WNDPROC lpPrevWndFunc,	// pointer to previous procedure
}
//---------------------------------------------------------------------------
BOOL __stdcall TiuConsole::ConHandler(DWORD dwCtrlType)
{
  switch(dwCtrlType)
  {
    case CTRL_C_EVENT:
      return true;
    case CTRL_BREAK_EVENT:
      return true;
    case CTRL_CLOSE_EVENT	:
//      ~TiuConsole();
      return false;
    case CTRL_LOGOFF_EVENT:
      return false;
      break;
    case CTRL_SHUTDOWN_EVENT:
      return false;
      break;
  }
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TiuConsole::SetCaption(AnsiString value)
{
  SetConsoleTitle(value.c_str());
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuConsole::GetCaption()
{
char Buffer[256];
  GetConsoleTitle(Buffer,256);
  return AnsiString(Buffer);
}
//---------------------------------------------------------------------------
void __fastcall TiuConsole::GotoXY(short x, short y)
{
COORD cXY={x,y};
  SetConsoleCursorPosition(FhOut,cXY);
};
//---------------------------------------------------------------------------
void __fastcall TiuConsole::Puts(AnsiString Line)
{
  WriteConsole(FhOut,Line.c_str(),Line.Length(),0,0);
};
//---------------------------------------------------------------------------
void __fastcall TiuConsole::PutsXY(short x, short y, AnsiString Line)
{
COORD cXY={x,y};
  SetConsoleCursorPosition(FhOut,cXY);
  WriteConsole(FhOut,Line.c_str(),Line.Length(),0,0);
}
//---------------------------------------------------------------------------
HWND __fastcall TiuConsole::ConsoleHwnd(void)
{
HWND hwndFound;
char pszNewWindowTitle[256];
char pszOldWindowTitle[256];
    GetConsoleTitle(pszOldWindowTitle, 256);
    wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
    SetConsoleTitle(pszNewWindowTitle);
    Sleep(40);
    hwndFound=FindWindow(NULL, pszNewWindowTitle);
    SetConsoleTitle(pszOldWindowTitle);
  return(hwndFound);
}
//---------------------------------------------------------------------------
bool __fastcall TiuConsole::ShowWindow(int Command)
{
  return (::ShowWindow(WindowHandle, Command));
}
//---------------------------------------------------------------------------
bool __fastcall TiuConsole::TrayMessage(DWORD dwMessage)
{
NOTIFYICONDATA tnd;
PSTR pszTip;
   pszTip ="InterSquish";

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = WindowHandle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage = MYWM_NOTIFY;

   if (dwMessage == NIM_MODIFY)
    {
        tnd.hIcon       = LoadIcon(0,IDI_APPLICATION);
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
int __fastcall TiuConsole::Run()
{
MSG   msg;
               while(true);
/*
      PeekMessage(&msg, 0, WM_USER, WM_USER, PM_NOREMOVE);
      while (GetMessage (&msg, 0,0,0))
      {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
      }
      */
}
//---------------------------------------------------------------------------
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
    HICON hIcon;

    hIcon = (HICON)LoadImage(0, MAKEINTRESOURCE(lpdi->CtlID), IMAGE_ICON,
        16, 16, 0);
    if (!hIcon)
        return(FALSE);

    DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
        16, 16, 0, NULL, DI_NORMAL);

    return(TRUE);
}

void __fastcall TiuConsole::DrawItem(TMessage& Msg)
{
     IconDrawItem((LPDRAWITEMSTRUCT)Msg.LParam);
//     TObject::Dispatch(&Msg);

}
//---------------------------------------------------------------------------

