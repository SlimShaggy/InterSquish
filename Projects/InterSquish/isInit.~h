//---------------------------------------------------------------------------
#ifndef isInitH
#define isInitH
#include "iuServer.h"
#include <Classes.hpp>
#include <ScktComp.hpp>
#include "iuInterSquishServer.h"
#include "Cfg.h"
#include "iuNNTPServer.h"
//---------------------------------------------------------------------------


class TisMain
{
private:	// User declarations
public:		// User declarations

  TSquishCfg *SquishCfg;
  TCustomUsersCfg *UsersCfg;
  TiuIssNNTPServer *IssNNTP;
  TiuIssSMTPServer *IssSMTP;
  TTextCfg *TextCfg;
  __fastcall TisMain(void);
  virtual __fastcall ~TisMain(void);
};
//---------------------------------------------------------------------------
void __fastcall ReadNNTPServerConfiguration(TiuIssNNTPServer *IssNNTP,TTextCfg *TextCfg);
void __fastcall ReadSMTPServerConfiguration(TiuIssSMTPServer *IssSMTP,TTextCfg *TextCfg);
void __fastcall ReadPOP3ServerConfiguration(TiuIssPOP3Server *IssPOP3,TTextCfg *TextCfg);
//---------------------------------------------------------------------------
#endif
