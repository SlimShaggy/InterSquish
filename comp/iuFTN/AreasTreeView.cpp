//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AreasTreeView.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TAreasTreeView::TAreasTreeView(TComponent* Owner)
  : TCustomTreeView(Owner)
{
  FItems=new TXTreeNodes<TAreaInfo>(this);
}
//---------------------------------------------------------------------------
__fastcall TAreasTreeView::~TAreasTreeView()
{
  FItems->Free();
  FItems=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TAreasTreeView::SetAreasCfg(TCustomAreasCfg *Value)
{
  if(FAreasCfg!=Value)
  {
    FAreasCfg=Value;
    Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TAreasTreeView::SetRootName(AnsiString Value)
{
  if(FRootName!=Value)
  {
    FRootName=Value;
    if(Items->Count)
      Items->Item[0]->Text=FRootName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAreasTreeView::AddBranch(TTreeNode *Parent, TListOfX<TAreaInfo> *AreaList)
{
  for(int i=0;i<AreaList->Count;i++)
    Items->AddChildObject(Parent,AreaList->Items[i]->Description,AreaList->Items[i]);
}
//---------------------------------------------------------------------------
void __fastcall TAreasTreeView::Refresh(void)
{
//TTreeNode *LocalAreas, *EchoAreas, *NetmailAreas;
  Items->Clear();
  Items->Add(NULL, FRootName);
  if(FAreasCfg)
  {
    AddBranch(Items->AddChild(Items->Item[0],"NetMail"),FAreasCfg->NetAreas);
    AddBranch(Items->AddChild(Items->Item[0],"Local Areas"),FAreasCfg->LocalAreas);
    AddBranch(Items->AddChild(Items->Item[0],"Echo Areas"),FAreasCfg->EchoAreas);
    if(!FAreasCfg->DupeArea->Tag.IsEmpty())
      Items->AddChild(Items->Item[0],FAreasCfg->DupeArea->Description);
    if(!FAreasCfg->BadArea->Tag.IsEmpty())
      Items->AddChild(Items->Item[0],FAreasCfg->BadArea->Description);
  }
  TCustomTreeView::Update();
}
//---------------------------------------------------------------------------
TAreaInfo * __fastcall TAreasTreeView::GetSelectedArea(void)
{
  return Selected ? (TAreaInfo*)(Selected->Data) : NULL;
}
//---------------------------------------------------------------------------
namespace Areastreeview
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TAreasTreeView)};
     RegisterComponents("FIDO Tech", classes, 0);
  }
}
//---------------------------------------------------------------------------
