//---------------------------------------------------------------------------
#ifndef iuEncodersH
#define iuEncodersH
//#include <stdio.h>
//---------------------------------------------------------------------------
AnsiString __fastcall EncodeBase64(AnsiString Value);
AnsiString __fastcall DecodeBase64(AnsiString Value);
//AnsiString __fastcall UUEncodeFile(FILE *in);
void PACKAGE __fastcall IncludeAttachAsUUE(AnsiString &Msg, AnsiString FileName);
//---------------------------------------------------------------------------
#endif
