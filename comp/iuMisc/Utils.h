//---------------------------------------------------------------------------
#ifndef UtilsH
#define UtilsH
#include <vcl.h>

//---------------------------------------------------------------------------
AnsiString __fastcall GetPrivatePath(AnsiString FileName);
void __fastcall ExpandWildCards(AnsiString Mask, TStringList *SourceList, TStringList *DestList);
void __fastcall ExcludeWildCards(TStringList *List, AnsiString Mask);

//---------------------------------------------------------------------------
#endif
