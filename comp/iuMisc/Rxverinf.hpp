// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RxVerInf.pas' rev: 4.00

#ifndef RxVerInfHPP
#define RxVerInfHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Rxverinf
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVersionLanguage { vlArabic, vlBulgarian, vlCatalan, vlTraditionalChinese, vlCzech, vlDanish, vlGerman, 
	vlGreek, vlUSEnglish, vlCastilianSpanish, vlFinnish, vlFrench, vlHebrew, vlHungarian, vlIcelandic, 
	vlItalian, vlJapanese, vlKorean, vlDutch, vlNorwegianBokmel, vlPolish, vlBrazilianPortuguese, vlRhaetoRomanic, 
	vlRomanian, vlRussian, vlCroatoSerbian, vlSlovak, vlAlbanian, vlSwedish, vlThai, vlTurkish, vlUrdu, 
	vlBahasa, vlSimplifiedChinese, vlSwissGerman, vlUKEnglish, vlMexicanSpanish, vlBelgianFrench, vlSwissItalian, 
	vlBelgianDutch, vlNorwegianNynorsk, vlPortuguese, vlSerboCroatian, vlCanadianFrench, vlSwissFrench, 
	vlUnknown };
#pragma option pop

#pragma option push -b-
enum TVersionCharSet { vcsASCII, vcsJapan, vcsKorea, vcsTaiwan, vcsUnicode, vcsEasternEuropean, vcsCyrillic, 
	vcsMultilingual, vcsGreek, vcsTurkish, vcsHebrew, vcsArabic, vcsUnknown };
#pragma option pop

#pragma pack(push, 4)
struct TLongVersion
{
	
	union
	{
		struct 
		{
			int MS;
			int LS;
			
		};
		struct 
		{
			Word All[4];
			
		};
		
	};
} ;
#pragma pack(pop)

class DELPHICLASS TVersionInfo;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TVersionInfo : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	char *FFileName;
	bool FValid;
	unsigned FSize;
	char *FBuffer;
	unsigned FHandle;
	void __fastcall ReadVersionInfo(void);
	AnsiString __fastcall GetFileName();
	void __fastcall SetFileName(const AnsiString Value);
	void * __fastcall GetTranslation(void);
	Windows::PVSFixedFileInfo __fastcall GetFixedFileInfo(void);
	TLongVersion __fastcall GetFileLongVersion();
	TLongVersion __fastcall GetProductLongVersion();
	AnsiString __fastcall GetTranslationString();
	AnsiString __fastcall GetComments();
	AnsiString __fastcall GetCompanyName();
	AnsiString __fastcall GetFileDescription();
	AnsiString __fastcall GetFileVersion();
	int __fastcall GetVersionNum(void);
	AnsiString __fastcall GetInternalName();
	AnsiString __fastcall GetLegalCopyright();
	AnsiString __fastcall GetLegalTrademarks();
	AnsiString __fastcall GetOriginalFilename();
	AnsiString __fastcall GetProductVersion();
	AnsiString __fastcall GetProductName();
	AnsiString __fastcall GetSpecialBuild();
	AnsiString __fastcall GetPrivateBuild();
	TVersionLanguage __fastcall GetVersionLanguage(void);
	TVersionCharSet __fastcall GetVersionCharSet(void);
	
public:
	__fastcall TVersionInfo(const AnsiString AFileName);
	__fastcall virtual ~TVersionInfo(void);
	AnsiString __fastcall GetVerValue(const AnsiString VerName);
	__property AnsiString FileName = {read=GetFileName, write=SetFileName};
	__property bool Valid = {read=FValid, nodefault};
	__property Windows::PVSFixedFileInfo FixedFileInfo = {read=GetFixedFileInfo};
	__property TLongVersion FileLongVersion = {read=GetFileLongVersion};
	__property TLongVersion ProductLongVersion = {read=GetProductLongVersion};
	__property void * Translation = {read=GetTranslation};
	__property TVersionLanguage VersionLanguage = {read=GetVersionLanguage, nodefault};
	__property TVersionCharSet VersionCharSet = {read=GetVersionCharSet, nodefault};
	__property int VersionNum = {read=GetVersionNum, nodefault};
	__property AnsiString Comments = {read=GetComments};
	__property AnsiString CompanyName = {read=GetCompanyName};
	__property AnsiString FileDescription = {read=GetFileDescription};
	__property AnsiString FileVersion = {read=GetFileVersion};
	__property AnsiString InternalName = {read=GetInternalName};
	__property AnsiString LegalCopyright = {read=GetLegalCopyright};
	__property AnsiString LegalTrademarks = {read=GetLegalTrademarks};
	__property AnsiString OriginalFilename = {read=GetOriginalFilename};
	__property AnsiString ProductVersion = {read=GetProductVersion};
	__property AnsiString ProductName = {read=GetProductName};
	__property AnsiString SpecialBuild = {read=GetSpecialBuild};
	__property AnsiString PrivateBuild = {read=GetPrivateBuild};
	__property AnsiString Values[AnsiString Name] = {read=GetVerValue};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString __fastcall LongVersionToString(const TLongVersion &Version);
extern PACKAGE TLongVersion __fastcall StringToLongVersion(const AnsiString Str);
extern PACKAGE bool __fastcall OkToWriteModule(AnsiString ModuleName, int NewVer);

}	/* namespace Rxverinf */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Rxverinf;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// RxVerInf
