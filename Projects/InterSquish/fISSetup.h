//---------------------------------------------------------------------------
#ifndef fISSetupH
#define fISSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include "RXSpin.hpp"
//---------------------------------------------------------------------------
class TisMainForm : public TForm
{
__published:	// IDE-managed Components
  
  TPanel *Panel1;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TButton *Button1;
  TFilenameEdit *feSquishCfg;
  TFilenameEdit *feLogFile;
  TPanel *Panel2;
  TButton *Button2;
  TButton *Button3;
  TRxSpinEdit *seLogLevel;
  TRxSpinEdit *sePort;
  TRxSpinEdit *seTimeout;
  TRxSpinEdit *seCacheSize;
  TLabel *Label6;
  void __fastcall Button1Click(TObject *Sender);
  
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TisMainForm(TComponent* Owner);
  virtual __fastcall ~TisMainForm(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TisMainForm *isMainForm;
//---------------------------------------------------------------------------
#endif
