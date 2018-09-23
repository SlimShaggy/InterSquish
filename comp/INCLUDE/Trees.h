#ifndef TreesH
#define TreesH
//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------

#include <vcl/comctrls.hpp>
//---------------------------------------------------------------------------
template <class TXx> class TXTreeNodes:public TTreeNodes
{
protected:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  TXx* __fastcall AllocObject(TXx *Ptr)
  {
    TXx *tmp=new TXx;
    *tmp=*Ptr;
    return tmp;
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  __fastcall TXTreeNodes<TXx>(TCustomTreeView* AOwner):TTreeNodes(AOwner){};

  __fastcall virtual ~TXTreeNodes<TXx>(void)
  {
    Clear();
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void __fastcall Clear(void)
  {
    for(int i=0;i<Count;i++)
      if(Item[i]->Data)
      {
        delete Item[i]->Data;
        Item[i]->Data=NULL;
      }
    TTreeNodes::Clear();
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TTreeNode* __fastcall AddChildObject(TTreeNode* Node, const AnsiString S, void * Ptr)
  {
    return TTreeNodes::AddChildObject(Node,S,AllocObject((TXx *)Ptr));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TTreeNode* __fastcall AddObjectFirst(TTreeNode* Node, const AnsiString S, void * Ptr)
  {
    return TTreeNodes::AddObjectFirst(Node,S,AllocObject((TXx *)Ptr));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TTreeNode* __fastcall AddObject(TTreeNode* Node, const AnsiString S, void * Ptr)
  {
    return TTreeNodes::AddObject(Node,S,AllocObject((TXx*)Ptr));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void __fastcall Delete(TTreeNode* Node)
  {
    if(Node->Data)
    {
      delete Node->Data;
      Node->Data=NULL;
    }
    TTreeNodes::Delete();
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TTreeNode* __fastcall InsertObject(TTreeNode* Node, const AnsiString S, void * Ptr)
  {
    return TTreeNodes::InsertObject(Node,S,AllocObject((TXx*)Ptr));
  }

//        __property TXx * Items[int Index] = {read=Get, write=Put};
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

