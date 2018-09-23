//---------------------------------------------------------------------------
#ifndef isPOP3H
#define isPOP3H
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include "Cfg.h"
#include "iuInterSquishServer.h"
#include "iuInterSquishServer.h"
#include "iuServer.h"
#include <ScktComp.hpp>
#include "iuPOP3Server.h"
#include "iuIPAddr.h"
//---------------------------------------------------------------------------
class TISsPOP3 : public TService
{
__published:    // IDE-managed Components
  void __fastcall ISsPOP3Start(TService *Sender, bool &Started);
  void __fastcall ISsPOP3Stop(TService *Sender, bool &Stopped);
private:        // User declarations
public:         // User declarations
  TTextCfg *TextCfg;
  TCustomUsersCfg *UsersCfg;
  TiuIssPOP3Server *IssPOP3Srv;
  TTwitIpCfg *TwitIpCfg;
  TScriptCfg *ScriptCfg;
	__fastcall TISsPOP3(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);
    __fastcall ~TISsPOP3();

	friend void __stdcall POP3ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TISsPOP3 *ISsPOP3;
//---------------------------------------------------------------------------
#endif

