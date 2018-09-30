#ifndef TXxxListH
#include <vcl/classes.hpp>
//---------------------------------------------------------------------------
// Шаблон для всякого рода TListOfSructure,TListOfObjects, 
// в общем - TListOfX
// Отличия от TList:
//       - Автоматический контроль типов добавляемых объектов
//       - Автоматическое удаление объектов, на которые указывает список
//         при удалении самого списка
//
//  Пример использования:
//       #include "TXxxList.h"
//       TListOfX<double> *FloatList;
//       main()
//       {
//       double *Value;
//         FloatList=new TListOfX<double>;
//         ...
//         Value=new double;
//         FloatList->Add(Value);
//         ...
//         Value=FloatList->Items[0]*2.0;       //Hикаких приведений типов!
//         ...
//         delete FloatList;                    //Объекты тоже удалились
//       }
//                                   (©) Усков Иван, 1997-1999
//
//---------------------------------------------------------------------------
template <class TXx> class TListOfX:public TList
{
protected:
  TXx * __fastcall Get(int Index);
  void __fastcall Put(int Index, TXx * Item);
public:
  virtual __fastcall ~TListOfX<TXx>(){Clear();};
  void __fastcall Clear(void)
  {
    for(int i=0;i<Count;i++)
     if (Items[i])
     {
      delete Items[i];
      Items[i]=NULL;
     }
    TList::Clear();
  };
  int __fastcall Add(TXx * Item);
  int __fastcall AddNew(TXx * Item);
  void __fastcall AddItems(TListOfX<TXx> *List);
  void __fastcall AddItemsNew(TListOfX<TXx> *List);
  TXx * __fastcall First(void);
  int __fastcall IndexOf(TXx * Item);
  void __fastcall Insert(int Index, TXx * Item);
  TXx * __fastcall Last(void);
  int __fastcall Remove(TXx * Item);
  void __fastcall Delete(int Index);
  __property TXx * Items[int Index] = {read=Get, write=Put};
};
//
template <class TXx>
inline  TXx * __fastcall  TListOfX<TXx>::Get(int Index)
{
        return (TXx *)TList::Get(Index);
}
//
template <class TXx>
inline  void __fastcall TListOfX<TXx>::Put(int Index, TXx * Item)
{
  TList::Put(Index,Item);
}
//
template <class TXx>
inline int __fastcall TListOfX<TXx>::Add(TXx * Item)
{
  return TList::Add(Item);
};
//
template <class TXx>
inline int __fastcall TListOfX<TXx>::AddNew(TXx * Item)
{
TXx *Ptr=new TXx;
  memcpy(Ptr,Item,sizeof(TXx));
  return TList::Add(Ptr);
};
//
template <class TXx>
inline void __fastcall TListOfX<TXx>::AddItems(TListOfX<TXx> *List)
{
  for(int i=0;i<List->Count;i++)
    Add(List->Items[i]);
}
//
template <class TXx>
inline void __fastcall TListOfX<TXx>::AddItemsNew(TListOfX<TXx> *List)
{
  for(int i=0;i<List->Count;i++)
    AddNew(List->Items[i]);
}
//
template <class TXx>
inline TXx * __fastcall TListOfX<TXx>::First(void)
{
  return (TXx *) TList::First();
}
//
template <class TXx>
inline int __fastcall TListOfX<TXx>::IndexOf(TXx * Item)
{
  return TList::IndexOf(Item);
}
//
template <class TXx>
inline void __fastcall TListOfX<TXx>::Insert(int Index, TXx * Item)
{
  TList::Insert(Index,Item);
}
//
template <class TXx>
inline TXx * __fastcall TListOfX<TXx>::Last(void)
{
  return (TXx *) TList::Last();
}
//
template <class TXx>
inline int __fastcall TListOfX<TXx>::Remove(TXx * Item)
{
TXx *tmp=Item;
  int PrevIndex=TList::Remove(Item);
  delete tmp;
  return PrevIndex;
}
//
template <class TXx>
inline  void __fastcall TListOfX<TXx>::Delete(int Index)
{
  delete Items[Index];
  Items[Index]=NULL;
  TList::Delete(Index);
}

//---------------------------------------------------------------------------
#define TXxxListH
//---------------------------------------------------------------------------
#endif




