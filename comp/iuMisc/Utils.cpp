//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Masks.hpp"
#include "Utils.h"

//---------------------------------------------------------------------------
AnsiString __fastcall GetPrivatePath(AnsiString FileName)
{
AnsiString Result=ParamStr(0);
  Result.Delete(Result.LastDelimiter(":\\")+1,256);
  return Result+FileName;
}
//---------------------------------------------------------------------------
void __fastcall ExpandWildCards(AnsiString Mask, TStringList *SourceList, TStringList *DestList)
{
  if(!Mask.Pos("*"))
  {
  int Index;
    if(SourceList->Find(Mask,Index))
      DestList->Add(SourceList->Strings[Index]);
  }
  else
  {
    AnsiString asItem;
    TMask *WildMask=new TMask(Mask);
    try
    {
      for(int i=0;i<SourceList->Count;i++)
      {
        asItem=SourceList->Strings[i];
        if(WildMask->Matches(asItem))
          DestList->Add(asItem);
      }
    }
    __finally
    {
      delete WildMask;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall ExcludeWildCards(TStringList *List, AnsiString Mask)
{
  if(!Mask.Pos("*"))
  {
  int Index;
    if(List->Find(Mask,Index))
      List->Delete(Index);
  }
  else
  {
    TMask *WildMask=new TMask(Mask);
    try
    {
      for(int i=List->Count-1;i>=0;i--)
      {
        if(WildMask->Matches(List->Strings[i]))
          List->Delete(i);
      }
    }
    __finally
    {
      delete WildMask;
    }
  }

}
//---------------------------------------------------------------------------

#pragma package(smart_init)
