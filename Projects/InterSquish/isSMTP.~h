//---------------------------------------------------------------------------
#ifndef isSMTPH
#define isSMTPH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include "Cfg.h"
#include "iuInterSquishServer.h"
#include "iuServer.h"
#include "iuSMTPServer.h"
#include <ScktComp.hpp>
#include "iuIPAddr.h"
//---------------------------------------------------------------------------
class TISsSMTP : public TService
{
__published:    // IDE-managed Components
  void __fastcall ISsSMTPStart(TService *Sender, bool &Started);
  void __fastcall ISsSMTPStop(TService *Sender, bool &Stopped);
private:        // User declarations
public:         // User declarations
  TTextCfg *TextCfg;
  TiuIssSMTPServer *IssSMTP;
  TTwitIpCfg *TwitIpCfg;
  TCustomUsersCfg *UsersCfg;
  TScriptCfg *ScriptCfg;
	__fastcall TISsSMTP(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);
    __fastcall ~TISsSMTP();

	friend void __stdcall SMTPServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TISsSMTP *ISsSMTP;
//---------------------------------------------------------------------------
#endif
