//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@tele-kom.ru, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef TransliteratesH
#define TransliteratesH
void __fastcall Transliterate(char *Source, char *Dest, char *Table);
void __fastcall OEM2KOI(char *Source, char *Dest);
void __fastcall KOI2OEM(char *Source, char *Dest);
void __fastcall N2H(char *Source, char *Dest);
void __fastcall Load_INET2FTN_Table(char * FileName);
void __fastcall Load_FTN2INET_Table(char * FileName);
//---------------------------------------------------------------------------
#endif
