//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef DynArrayH
#define DynArrayH
#include <stdlib.h>

//---------------------------------------------------------------------------
template <class Tx> class TDynArray
{
private:
  Tx* FMemory;
  int FCount;
  int FCapacity;
  int FElementSize;
  int FDelta;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void __fastcall SetCapacity(int Value)
  {
    FCapacity= Value>=0 ? Value :0;
    if(FCount>FCapacity)
      FCount=FCapacity;
    ReAllocMem();
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void __fastcall SetDelta(int Value)
  {
    FDelta=Value<=0 ? 8 : Value;
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void __fastcall ReAllocMem(void)
  {
    FMemory=(Tx*)realloc(FMemory,FCapacity*FElementSize);
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void __fastcall SetItem(int Index, Tx Value)
  {
    if(Index>=FCapacity)
    {
      FCapacity=Index+FDelta;
      ReAllocMem();
    }
    if(FCount<(Index+1))
      FCount=Index+1;
    FMemory[Index]=Value;
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Tx __fastcall GetItem(int Index)
  {
    if(Index>=FCapacity)
    {
      FCapacity=Index+FDelta;
      ReAllocMem();
    }
    if(FCount<(Index+1))
      FCount=Index+1;
    return FMemory[Index];
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  __fastcall TDynArray<Tx>(int Delta=8)
  {
    FElementSize=sizeof(Tx);
    SetDelta(Delta);
    FCapacity=FCount=0;
  };
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  __fastcall ~TDynArray<Tx>()
  {
    realloc(FMemory,0);
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  __property int Capacity={read=FCapacity,write=SetCapacity};
  __property int Count={read=FCount};
  __property int Delta={read=FDelta,write=SetDelta};
  __property Tx Items[int Index]={read=GetItem, write=SetItem};
  __property Tx *Memory={read=FMemory};//For direct faster access
};
//---------------------------------------------------------------------------
#endif
