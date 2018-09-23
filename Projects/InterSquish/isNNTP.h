//---------------------------------------------------------------------------
#ifndef isNNTPH
#define isNNTPH
//#define _WINSPOOL_
//---------------------------------------------------------------------------
#include <SvcMgr.hpp>
#include "Cfg.h"
#include "FTNDataSet.h"
#include "iuInterSquishServer.h"
#include "iuNNTPServer.h"
#include "iuServer.h"
#include <Db.hpp>
#include <ScktComp.hpp>
#include <Classes.hpp>
#include <ExtCtrls.hpp>
#include "iuIPAddr.h"
//---------------------------------------------------------------------------
class TISsNNTP : public TService
{
__published:    // IDE-managed Components
  TTimer *tmr;
  TTimer *Tim2;
  void __fastcall InterSquishStart(TService *Sender, bool &Started);
  void __fastcall InterSquishStop(TService *Sender, bool &Stopped);
  void __fastcall tmrTimer(TObject *Sender);
  void __fastcall Tim2Timer(TObject *Sender);
private:        // User declarations
public:         // User declarations
  TiuIssNNTPServer *IssNNTP;
  TTextCfg *TextCfg;
  TTwitIpCfg *TwitIpCfg;
  TScriptCfg *ScriptCfg;

	__fastcall TISsNNTP(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);
    __fastcall ~TISsNNTP();

	friend void __stdcall NNTPServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TISsNNTP *ISsNNTP;
//---------------------------------------------------------------------------
#endif

