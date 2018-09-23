//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "iuRegistry.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
int __fastcall TRegistryEx::ReadIntegerDef(AnsiString Key, int DefVal)
  {
  int Result;
    try
    {
      Result=ReadInteger(Key);
    }
    catch(...)
    {
      Result=DefVal;
    }
    return Result;
  };
//---------------------------------------------------------------------------
AnsiString __fastcall TRegistryEx::ReadStringDef(AnsiString Key, AnsiString DefVal)
  {
  AnsiString Result;
    try
    {
      Result=ReadString(Key);
    }
    catch(...)
    {
      Result=DefVal;
    }
    return Result;
  };
//---------------------------------------------------------------------------
bool __fastcall TRegistryEx::ReadBoolDef(AnsiString Key, bool DefVal)
{
  bool Result;
    try
    {
      Result=ReadBool(Key);
    }
    catch(...)
    {
      Result=DefVal;
    }
    return Result;
};
//---------------------------------------------------------------------------
double __fastcall TRegistryEx::ReadFloatDef(AnsiString Key, double DefVal)
{
  double Result;
    try
    {
      Result=ReadFloat(Key);
    }
    catch(...)
    {
      Result=DefVal;
    }
    return Result;
};
//---------------------------------------------------------------------------
