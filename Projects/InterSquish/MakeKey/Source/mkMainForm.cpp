//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "mkMainForm.h"
#include "rsaref.h"
#include "mkTables.h"
#include "mkRandomInput.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "RXDBCtrl"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GenerateKey(AnsiString Name)
{
 ZeroMemory(&dmTables->RandomStruct,sizeof(R_RANDOM_STRUCT));

  fRandomInput=new TfRandomInput(this,dmTables->RandomStruct.state,sizeof(dmTables->RandomStruct.state));
  fRandomInput->ShowModal();
  Screen->Cursor=crHourGlass;
  Application->ProcessMessages();
  try
  {
    dmTables->NewMkGen(Name);
  }
  __finally
  {
    Screen->Cursor=crDefault;
  }}
//---------------------------------------------------------------------------
void __fastcall TForm1::sbNewSNKeyGenClick(TObject *Sender)
{
  GenerateKey("SN_Key");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sbNewRegKeyGenClick(TObject *Sender)
{
  GenerateKey("RegKey");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sbGenSNClick(TObject *Sender)
{
  sbGenSN->Enabled=false;
  dmTables->GenSNs(256-dmTables->tRegData->RecordCount);
  sbGenSN->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sbExportRCClick(TObject *Sender)
{
  sbExportRC->Enabled=false;
  dmTables->ExportSNtoRC();
  sbExportRC->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sbGenRegKeyClick(TObject *Sender)
{
  sbGenRegKey->Enabled=false;
  dmTables->GenRegKey();
  sbGenRegKey->Enabled=true;
}
//---------------------------------------------------------------------------

