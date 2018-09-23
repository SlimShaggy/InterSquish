//---------------------------------------------------------------------------
#ifndef fConfigH
#define fConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfSetup : public TForm
{
__published:	// IDE-managed Components
  TButton *Button1;
  TButton *Button2;
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfSetup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfSetup *fSetup;
//---------------------------------------------------------------------------
#endif
