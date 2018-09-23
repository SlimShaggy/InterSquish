// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'StrUtils.pas' rev: 4.00

#ifndef StrUtilsHPP
#define StrUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Strutils
{
//-- type declarations -------------------------------------------------------
typedef TSysCharSet TCharSet;
;

//-- var, const, procedure ---------------------------------------------------
#define DigitChars (System::Set<char, 0, 255> () << '\x30' << '\x31' << '\x32' << '\x33' << '\x34' << '\x35' \
	<< '\x36' << '\x37' << '\x38' << '\x39' )
#define Brackets (System::Set<char, 0, 255> () << '\x28' << '\x29' << '\x48' << '\x49' << '\x68' << '\x69' \
	)
#define StdWordDelims (System::Set<char, 0, 255> () << '\x0' << '\x1' << '\x2' << '\x3' << '\x4' << '\x5' \
	<< '\x6' << '\x7' << '\x8' << '\x9' << '\xa' << '\xb' << '\xc' << '\xd' << '\xe' << '\xf' << '\x10' \
	<< '\x11' << '\x12' << '\x13' << '\x14' << '\x15' << '\x16' << '\x17' << '\x18' << '\x19' << '\x1a' \
	<< '\x1b' << '\x1c' << '\x1d' << '\x1e' << '\x1f' << '\x20' << '\x21' << '\x22' << '\x23' << '\x24' \
	<< '\x25' << '\x26' << '\x27' << '\x28' << '\x29' << '\x2a' << '\x2b' << '\x2c' << '\x2d' << '\x2e' \
	<< '\x2f' << '\x30' << '\x31' << '\x32' << '\x33' << '\x34' << '\x35' << '\x36' << '\x37' << '\x38' \
	<< '\x39' << '\x3a' << '\x3b' << '\x3c' << '\x3d' << '\x3e' << '\x3f' << '\x40' << '\x41' << '\x42' \
	<< '\x43' << '\x44' << '\x45' << '\x46' << '\x47' << '\x48' << '\x49' << '\x4a' << '\x4b' << '\x4c' \
	<< '\x4d' << '\x4e' << '\x4f' << '\x50' << '\x51' << '\x52' << '\x53' << '\x54' << '\x55' << '\x56' \
	<< '\x57' << '\x58' << '\x59' << '\x5a' << '\x5b' << '\x5c' << '\x5d' << '\x5e' << '\x5f' << '\x60' \
	<< '\x61' << '\x62' << '\x63' << '\x64' << '\x65' << '\x66' << '\x67' << '\x68' << '\x69' << '\x6a' \
	<< '\x6b' << '\x6c' << '\x6d' << '\x6e' << '\x6f' << '\x70' << '\x71' << '\x72' << '\x73' << '\x74' \
	<< '\x75' << '\x76' << '\x77' << '\x78' << '\x79' << '\x7a' << '\x7b' << '\x7c' << '\x7d' << '\x7e' \
	<< '\x7f' << '\x80' << '\x81' << '\x82' << '\x83' << '\x84' << '\x85' << '\x86' << '\x87' << '\x88' \
	<< '\x89' << '\x8a' << '\x8b' << '\x8c' << '\x8d' << '\x8e' << '\x8f' << '\x90' << '\x91' << '\x92' \
	<< '\x93' << '\x94' << '\x95' << '\x96' << '\x97' << '\x98' << '\x99' << '\x9a' << '\x9b' << '\x9c' \
	<< '\x9d' << '\x9e' << '\x9f' << '\xa0' << '\xa1' << '\xa2' << '\xa3' << '\xa4' << '\xa5' << '\xa6' \
	<< '\xa7' << '\xa8' << '\xa9' << '\xaa' << '\xab' << '\xac' << '\xad' << '\xae' << '\xaf' << '\xb0' \
	<< '\xb1' << '\xb2' << '\xb3' << '\xb4' << '\xb5' << '\xb6' << '\xb7' << '\xb8' << '\xb9' << '\xba' \
	<< '\xbb' << '\xbc' << '\xbd' << '\xbe' << '\xbf' << '\xc0' << '\xc1' << '\xc2' << '\xc3' << '\xc4' \
	<< '\xc5' << '\xc6' << '\xc7' << '\xc8' << '\xc9' << '\xca' << '\xcb' << '\xcc' << '\xcd' << '\xce' \
	<< '\xcf' << '\xd0' << '\xd1' << '\xd2' << '\xd3' << '\xd4' << '\xd5' << '\xd6' << '\xd7' << '\xd8' \
	<< '\xd9' << '\xda' << '\xdb' << '\xdc' << '\xdd' << '\xde' << '\xdf' << '\xe0' << '\xe1' << '\xe2' \
	<< '\xe3' << '\xe4' << '\xe5' << '\xe6' << '\xe7' << '\xe8' << '\xe9' << '\xea' << '\xeb' << '\xec' \
	<< '\xed' << '\xee' << '\xef' << '\xf0' << '\xf1' << '\xf2' << '\xf3' << '\xf4' << '\xf5' << '\xf6' \
	<< '\xf7' << '\xf8' << '\xf9' << '\xfa' << '\xfb' << '\xfc' << '\xfd' << '\xfe' << '\xff' )
extern PACKAGE AnsiString __fastcall StrToOem(const AnsiString AnsiStr);
extern PACKAGE AnsiString __fastcall OemToAnsiStr(const AnsiString OemStr);
extern PACKAGE bool __fastcall IsEmptyStr(const AnsiString S, const Sysutils::TSysCharSet &EmptyChars
	);
extern PACKAGE AnsiString __fastcall ReplaceStr(const AnsiString S, const AnsiString Srch, const AnsiString 
	Replace);
extern PACKAGE AnsiString __fastcall DelSpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelChars(const AnsiString S, char Chr);
extern PACKAGE AnsiString __fastcall DelBSpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelESpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelRSpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelSpace1(const AnsiString S);
extern PACKAGE AnsiString __fastcall Tab2Space(const AnsiString S, Byte Numb);
extern PACKAGE AnsiString __fastcall MakeStr(char C, int N);
extern PACKAGE AnsiString __fastcall MS(char C, int N);
extern PACKAGE int __fastcall NPos(const AnsiString C, AnsiString S, int N);
extern PACKAGE AnsiString __fastcall AddChar(char C, const AnsiString S, int N);
extern PACKAGE AnsiString __fastcall AddCharR(char C, const AnsiString S, int N);
extern PACKAGE AnsiString __fastcall LeftStr(const AnsiString S, int N);
extern PACKAGE AnsiString __fastcall RightStr(const AnsiString S, int N);
extern PACKAGE int __fastcall CompStr(const AnsiString S1, const AnsiString S2);
extern PACKAGE int __fastcall CompText(const AnsiString S1, const AnsiString S2);
extern PACKAGE AnsiString __fastcall Copy2Symb(const AnsiString S, char Symb);
extern PACKAGE AnsiString __fastcall Copy2SymbDel(AnsiString &S, char Symb);
extern PACKAGE AnsiString __fastcall Copy2Space(const AnsiString S);
extern PACKAGE AnsiString __fastcall Copy2SpaceDel(AnsiString &S);
extern PACKAGE AnsiString __fastcall AnsiProperCase(const AnsiString S, const Sysutils::TSysCharSet 
	&WordDelims);
extern PACKAGE int __fastcall WordCount(const AnsiString S, const Sysutils::TSysCharSet &WordDelims)
	;
extern PACKAGE int __fastcall WordPosition(const int N, const AnsiString S, const Sysutils::TSysCharSet 
	&WordDelims);
extern PACKAGE AnsiString __fastcall ExtractWord(int N, const AnsiString S, const Sysutils::TSysCharSet 
	&WordDelims);
extern PACKAGE AnsiString __fastcall ExtractWordPos(int N, const AnsiString S, const Sysutils::TSysCharSet 
	&WordDelims, int &Pos);
extern PACKAGE AnsiString __fastcall ExtractDelimited(int N, const AnsiString S, const Sysutils::TSysCharSet 
	&Delims);
extern PACKAGE AnsiString __fastcall ExtractSubstr(const AnsiString S, int &Pos, const Sysutils::TSysCharSet 
	&Delims);
extern PACKAGE bool __fastcall IsWordPresent(const AnsiString W, const AnsiString S, const Sysutils::TSysCharSet 
	&WordDelims);
extern PACKAGE AnsiString __fastcall QuotedString(const AnsiString S, char Quote);
extern PACKAGE AnsiString __fastcall ExtractQuotedString(const AnsiString S, char Quote);
extern PACKAGE AnsiString __fastcall Numb2USA(const AnsiString S);
extern PACKAGE AnsiString __fastcall CenterStr(const AnsiString S, int Len);
extern PACKAGE AnsiString __fastcall Dec2Hex(int N, Byte A);
extern PACKAGE AnsiString __fastcall D2H(int N, Byte A);
extern PACKAGE int __fastcall Hex2Dec(const AnsiString S);
extern PACKAGE int __fastcall H2D(const AnsiString S);
extern PACKAGE AnsiString __fastcall Dec2Numb(int N, Byte A, Byte B);
extern PACKAGE int __fastcall Numb2Dec(AnsiString S, Byte B);
extern PACKAGE int __fastcall RomanToInt(const AnsiString S);
extern PACKAGE AnsiString __fastcall IntToRoman(int Value);
extern PACKAGE AnsiString __fastcall IntToBin(int Value, int Digits, int Spaces);
extern PACKAGE int __fastcall FindPart(const AnsiString HelpWilds, const AnsiString InputStr);
extern PACKAGE bool __fastcall IsWild(AnsiString InputStr, AnsiString Wilds, bool IgnoreCase);
//extern PACKAGE bool __fastcall FindCmdLineSwitch(const AnsiString Switch, const Sysutils::TSysCharSet &SwitchChars, bool IgnoreCase);
//extern PACKAGE AnsiString __fastcall GetCmdLineArg(const AnsiString Switch, const Sysutils::TSysCharSet	&SwitchChars);

}	/* namespace Strutils */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Strutils;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// StrUtils
