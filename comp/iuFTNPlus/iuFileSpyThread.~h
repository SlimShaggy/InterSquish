//---------------------------------------------------------------------------
#ifndef iuFileSpyThreadH
#define iuFileSpyThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TFileSpyThread : public TThread
{
private:
 HANDLE FHandle;
    AnsiString FFileName;
    AnsiString FPathName;
    STARTUPINFO StartUpInfo;
    PROCESS_INFORMATION ProcessInfo;
    void __fastcall SetFileName(AnsiString value);
protected:
  void __fastcall Execute();
public:
  //__fastcall TFileSpyThread(void);
  __fastcall TFileSpyThread(bool CreateSuspended);
  virtual __fastcall ~TFileSpyThread(void);
    __property AnsiString FileName  = { read = FFileName, write = SetFileName };
};
//---------------------------------------------------------------------------
#endif
