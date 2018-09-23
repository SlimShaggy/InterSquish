//---------------------------------------------------------------------------
#ifndef iuRegistryH
#define iuRegistryH

#include <registry.hpp>
//---------------------------------------------------------------------------
class TRegistryEx : public TRegistry
{
public:
  int __fastcall ReadIntegerDef(AnsiString Key, int DefVal);
  AnsiString __fastcall ReadStringDef(AnsiString Key, AnsiString DefVal);
  bool __fastcall ReadBoolDef(AnsiString Key, bool DefVal);
  double __fastcall ReadFloatDef(AnsiString Key, double DefVal);
};

//---------------------------------------------------------------------------
#endif
