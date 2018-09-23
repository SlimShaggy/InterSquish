//---------------------------------------------------------------------------
#ifndef isRreaderH
#define isRreaderH
#include "Cfg.h"

//---------------------------------------------------------------------------
class TDataCfg: public TCustomCfg
{
private:
  AnsiString FPath;
  void *FData;
protected:
  FILE *FCfg;
  virtual void __fastcall SetPath(AnsiString Value);
  virtual void __fastcall OpenFile(void);
  virtual void __fastcall CloseFile(void);
  virtual bool __fastcall TrimComments(char* &Line);
  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall Refresh(void);
  virtual void __fastcall Clear(void);
  virtual void __fastcall ImportCfgLine(char *Line);
  
  __property AnsiString Path={read=FPath, write=SetPath};
public:
  __fastcall TDataCfg(TComponent* Owner);
   virtual __fastcall ~TDataCfg();
   __property void *Data={read=GetData};
__published:
};

//---------------------------------------------------------------------------
#endif
