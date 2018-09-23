//---------------------------------------------------------------------------
#ifndef AreasTreeViewH
#define AreasTreeViewH
//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "cfg.h"
#include "..\..\comp\include\Trees.h"

//---------------------------------------------------------------------------
class PACKAGE TAreasTreeView : public TCustomTreeView
{
private:
  TXTreeNodes<TAreaInfo> *FItems;
  AnsiString FRootName;
  TCustomAreasCfg *FAreasCfg;
  void __fastcall AddBranch(TTreeNode *Parent, TListOfX<TAreaInfo> *AreaList);
  void __fastcall SetRootName(AnsiString Value);
  TAreaInfo * __fastcall GetSelectedArea(void);
protected:
  void __fastcall SetAreasCfg(TCustomAreasCfg *Value);
public:
  __fastcall TAreasTreeView(TComponent* Owner);
  virtual __fastcall ~TAreasTreeView();
  void __fastcall Refresh(void);
  __property TAreaInfo *SelectedArea={read=GetSelectedArea};
	__property TXTreeNodes<TAreaInfo> *Items={read=FItems, write=FItems};

__published:
  __property AnsiString RootName={read=FRootName, write=SetRootName};
  __property TCustomAreasCfg *AreasCfg={read=FAreasCfg, write=SetAreasCfg};
	__property ShowButtons ;
	__property BorderStyle ;
	__property DragCursor ;
	__property ShowLines ;
	__property ShowRoot ;
	__property ReadOnly ;
	__property RightClickSelect ;
	__property DragMode ;
	__property HideSelection ;
	__property Indent ;

	__property OnEditing ;
	__property OnEdited ;
	__property OnExpanding ;
	__property OnExpanded ;
	__property OnCollapsing ;
	__property OnCompare ;
	__property OnCollapsed ;
	__property OnChanging ;
	__property OnChange ;
	__property OnDeletion ;
	__property OnGetImageIndex ;
	__property OnGetSelectedIndex ;
	__property Align ;
	__property Enabled ;
	__property Font ;
	__property Color ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property Ctl3D ;
	__property SortType ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnStartDrag ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnDblClick ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property PopupMenu ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property Images ;
	__property StateImages ;

};
//---------------------------------------------------------------------------
#endif
