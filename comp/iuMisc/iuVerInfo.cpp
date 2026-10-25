//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuVerInfo.h"

TiuExeVersionInfo VI_THIS_EXE;
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TiuExeVersionInfo::TiuExeVersionInfo(void)
{
  AnsiString FFileName=ParamStr(0);
  FTranslationString="\\StringFileInfo\\";
  FSize=GetFileVersionInfoSize(FFileName.c_str(), &FHandle);
  if(FSize)
  {
    FBuffer=new char[FSize];
    FValid = GetFileVersionInfo(FFileName.c_str(), FHandle, FSize, FBuffer);
    if(FValid)
    {
    unsigned int Len;
      DWORD *dwpTranslation=0;
      VerQueryValue(FBuffer, "\\VarFileInfo\\Translation", (void **)&dwpTranslation, &Len);
      if(dwpTranslation)
        FTranslationString+=IntToHex((int)(MAKELONG(HIWORD(*dwpTranslation), LOWORD(*dwpTranslation))), 8)+"\\";
      //--------ProductVersion
      // FileVersion IDE всегда формирует из номеров версии, суффикс (напр. -beta) можно задать только в ProductVersion
        FProductVersion= GetVerValue("ProductVersion");
        if(FProductVersion== "")
          FProductVersion= GetVerValue("FileVersion");
//        if(FProductVersion== "")
//          FProductVersion=LongVersionToString(FileLongVersion);
      //--------
        FInternalName=GetVerValue("InternalName");
    }
  }
}
//---------------------------------------------------------------------------
__fastcall TiuExeVersionInfo::~TiuExeVersionInfo(void)
{
  if(FBuffer)
    delete [] FBuffer;
}
//---------------------------------------------------------------------------
AnsiString __fastcall  TiuExeVersionInfo::GetVerValue(const AnsiString VerName)
{
char *Value;
unsigned int Len;
AnsiString FullName(FTranslationString + VerName);
AnsiString Result = "";
    if(VerQueryValue(FBuffer, FullName.c_str(), (void **)&Value, &Len))
      Result = AnsiString(Value);
  return Result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuExeVersionInfo::GetProductVersion(void)
{
  return FProductVersion;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuExeVersionInfo::GetInternalName(void)
{
  return FInternalName;
}
//---------------------------------------------------------------------------

