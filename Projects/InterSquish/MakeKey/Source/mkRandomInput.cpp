//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "mkRandomInput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfRandomInput *fRandomInput;
//---------------------------------------------------------------------------
__fastcall TfRandomInput::TfRandomInput(TComponent* Owner,unsigned char *RandBuf,int BufSize)
  : TForm(Owner)
{
  FRandBuf=RandBuf;
  FLastTickCount=GetTickCount();
  FIndex=0;
  FBufSize=BufSize;
  Panel->Caption=AnsiString(FBufSize-FIndex);

}
//---------------------------------------------------------------------------
void __fastcall TfRandomInput::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  FRandBuf[FIndex]=(unsigned char)(GetTickCount()-FLastTickCount);
  if(++FIndex==FBufSize)
    Close();
  Panel->Caption=AnsiString(FBufSize-FIndex);
}
//---------------------------------------------------------------------------
void __fastcall TfRandomInput::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action=caFree;
}
//---------------------------------------------------------------------------
