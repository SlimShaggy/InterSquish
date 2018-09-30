//---------------------------------------------------------------------------
#ifndef mkRandomInputH
#define mkRandomInputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfRandomInput : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  int FIndex;
  int FBufSize;
  int FLastTickCount;
  unsigned char *FRandBuf;

public:		// User declarations
  __fastcall TfRandomInput(TComponent* Owner,unsigned char *RandBuf,int BufSize);
};
//---------------------------------------------------------------------------
extern PACKAGE TfRandomInput *fRandomInput;
//---------------------------------------------------------------------------
#endif
