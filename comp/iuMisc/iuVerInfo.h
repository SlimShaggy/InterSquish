//---------------------------------------------------------------------------
#ifndef iuVerInfoH
#define iuVerInfoH




//-- type declarations -------------------------------------------------------
/*
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
*/
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

class PACKAGE TiuExeVersionInfo
{
private:
	bool FValid;
	unsigned FSize;
	char *FBuffer;
	unsigned long FHandle;
//----------------------------------------
  AnsiString FTranslationString;
  AnsiString FFileVersion;
  AnsiString FInternalName;

//----------------------------------------
//	void * __fastcall GetTranslation(void);
//	Windows::PVSFixedFileInfo __fastcall GetFixedFileInfo(void);
	TLongVersion __fastcall GetFileLongVersion(void);
	TLongVersion __fastcall GetProductLongVersion(void);
	AnsiString __fastcall GetTranslationString(void);
	AnsiString __fastcall GetComments(void);
	AnsiString __fastcall GetCompanyName(void);
	AnsiString __fastcall GetFileDescription(void);
	AnsiString __fastcall GetFileVersion(void);
	int __fastcall GetVersionNum(void);
	AnsiString __fastcall GetInternalName(void);
	AnsiString __fastcall GetLegalCopyright(void);
	AnsiString __fastcall GetLegalTrademarks(void);
	AnsiString __fastcall GetOriginalFilename(void);
	AnsiString __fastcall GetProductVersion(void);
	AnsiString __fastcall GetProductName(void);
	AnsiString __fastcall GetSpecialBuild(void);
	AnsiString __fastcall GetPrivateBuild(void);
//	TVersionLanguage __fastcall GetVersionLanguage(void);
//	TVersionCharSet __fastcall GetVersionCharSet(void);

public:

  __fastcall TiuExeVersionInfo(void);
  __fastcall ~TiuExeVersionInfo(void);


	AnsiString __fastcall GetVerValue(const AnsiString VerName);
//	__property AnsiString FileName = {read=GetFileName, write=SetFileName};
//	__property bool Valid = {read=FValid, nodefault};
//	__property Windows::PVSFixedFileInfo FixedFileInfo = {read=GetFixedFileInfo};
//	__property TLongVersion FileLongVersion = {read=GetFileLongVersion};
//	__property TLongVersion ProductLongVersion = {read=GetProductLongVersion};
//	__property void * Translation = {read=GetTranslation};
//	__property TVersionLanguage VersionLanguage = {read=GetVersionLanguage, nodefault};
//	__property TVersionCharSet VersionCharSet = {read=GetVersionCharSet, nodefault};
//	__property int VersionNum = {read=GetVersionNum, nodefault};
//	__property AnsiString Comments = {read=GetComments};
//	__property AnsiString CompanyName = {read=GetCompanyName};
//	__property AnsiString FileDescription = {read=GetFileDescription};
	__property AnsiString FileVersion = {read=GetFileVersion};
	__property AnsiString InternalName = {read=GetInternalName};
//	__property AnsiString LegalCopyright = {read=GetLegalCopyright};
//	__property AnsiString LegalTrademarks = {read=GetLegalTrademarks};
//	__property AnsiString OriginalFilename = {read=GetOriginalFilename};
//	__property AnsiString ProductVersion = {read=GetProductVersion};
//	__property AnsiString ProductName = {read=GetProductName};
//	__property AnsiString SpecialBuild = {read=GetSpecialBuild};
//	__property AnsiString PrivateBuild = {read=GetPrivateBuild};
//	__property AnsiString Values[AnsiString Name] = {read=GetVerValue};

};
extern TiuExeVersionInfo VI_THIS_EXE;
//---------------------------------------------------------------------------
#endif

