//---------------------------------------------------------------------------
#ifndef iuConsoleH
#define iuConsoleH
//---------------------------------------------------------------------------
//#include <SysUtils.hpp>
//#include <Classes.hpp>

#include <windows.h>
#define MYWM_NOTIFY         (WM_APP+100)
#define IDC_MYICON           1006

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TiuConsole//:public TObject
{
private:
    void __fastcall SetCaption(AnsiString value);
    AnsiString __fastcall GetCaption();
    HANDLE FhOut;
    static HWND FWindowHandle;
    static void* FOldWindowProc;
//  HANDLE FhConsoleOutput
    HWND __fastcall ConsoleHwnd(void);
    bool __fastcall TrayMessage(DWORD dwMessage);
    void __fastcall DrawItem(TMessage& Msg);
    static BOOL __stdcall ConHandler(DWORD dwCtrlType);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  public:
    __fastcall TiuConsole(void);
    virtual __fastcall ~TiuConsole(void);
    void __fastcall GotoXY(short x, short y);
    void __fastcall Puts(AnsiString Line);
    void __fastcall PutsXY(short x, short y, AnsiString Line);
    bool __fastcall ShowWindow(int Command);
    virtual int __fastcall Run();
    __property AnsiString Caption  = { read = GetCaption, write = SetCaption};
    __property HWND WindowHandle  = { read = FWindowHandle };
protected:
//    BEGIN_MESSAGE_MAP
//        VCL_MESSAGE_HANDLER(WM_DRAWITEM, TMessage, DrawItem)
//    END_MESSAGE_MAP(TObject)
};
//---------------------------------------------------------------------------
#endif
