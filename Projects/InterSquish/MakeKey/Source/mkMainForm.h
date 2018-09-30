//---------------------------------------------------------------------------
#ifndef mkMainFormH
#define mkMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel4;
  TDBGrid *RxDBGrid2;
  TSpeedButton *sbNewSNKeyGen;
  TSpeedButton *sbNewRegKeyGen;
  TSpeedButton *sbLock;
  TSpeedButton *sbGenSN;
  TSpeedButton *sbExportRC;
  TSpeedButton *sbGenRegKey;
  TSplitter *Splitter1;
  TDBMemo *DBMemo1;
  void __fastcall sbNewSNKeyGenClick(TObject *Sender);
  void __fastcall sbNewRegKeyGenClick(TObject *Sender);
  void __fastcall sbGenSNClick(TObject *Sender);
  void __fastcall sbExportRCClick(TObject *Sender);
  void __fastcall sbGenRegKeyClick(TObject *Sender);
private:	// User declarations
  void __fastcall GenerateKey(AnsiString Name);
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
