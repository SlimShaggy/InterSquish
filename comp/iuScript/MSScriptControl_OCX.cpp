// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.134.1.39  $
// File generated on 24.06.2000 17:52:23 from Type Library described below.

// ************************************************************************ //
// Type Lib: C:\WINNT\System32\msscript.ocx (1)
// IID\LCID: {0E59F1D2-1FBE-11D0-8FF2-00A0D10038BC}\0
// Helpfile: C:\WINNT\System32\MSSCRIPT.HLP
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINNT\System32\stdole2.tlb)
//   (2) v4.0 StdVCL, (C:\WINNT\System32\STDVCL40.DLL)
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "MSScriptControl_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Msscriptcontrol_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TScriptControl which
// allows "Control to host scripting engines that understand the ActiveX Scripting interface" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TScriptControl::EventDispIDs[2] = {
    0x00000BB8, 0x00000BB9};

TControlData TScriptControl::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x0E59F1D5, 0x1FBE, 0x11D0,{ 0x8F, 0xF2, 0x00, 0xA0, 0xD1, 0x00, 0x38, 0xBC} }, // CoClass
  {0x8B167D60, 0x8605, 0x11D0,{ 0xAB, 0xCB, 0x00, 0xA0, 0xC9, 0x0F, 0xFF, 0xC0} }, // Events

  // Count of Events and array of their DISPIDs
  2, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x00000000)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, NULL,

  // Count of Pict Prop and array of their DISPIDs
  0, NULL,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TScriptControl::DEF_CTL_INTF = {0x0E59F1D3, 0x1FBE, 0x11D0,{ 0x8F, 0xF2, 0x00, 0xA0, 0xD1, 0x00, 0x38, 0xBC} };
TNoParam TScriptControl::OptParam;

static inline void ValidCtrCheck(TScriptControl *)
{
   delete new TScriptControl((TComponent*)(0));
};

void __fastcall TScriptControl::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TScriptControl::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMIScriptControl __fastcall TScriptControl::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TScriptControl::_AboutBox(void)
{
  GetDefaultInterface()->_AboutBox();
}

void __fastcall TScriptControl::AddObject(BSTR Name/*[in]*/, LPDISPATCH Object/*[in]*/, 
                                          TOLEBOOL AddMembers/*[in,def,opt]*/)
{
  GetDefaultInterface()->AddObject(Name/*[in]*/, Object/*[in]*/, AddMembers/*[in,def,opt]*/);
}

void __fastcall TScriptControl::Reset(void)
{
  GetDefaultInterface()->Reset();
}

void __fastcall TScriptControl::AddCode(BSTR Code/*[in]*/)
{
  GetDefaultInterface()->AddCode(Code/*[in]*/);
}

TVariant __fastcall TScriptControl::Eval(BSTR Expression/*[in]*/)
{
  return GetDefaultInterface()->Eval(Expression/*[in]*/);
}

void __fastcall TScriptControl::ExecuteStatement(BSTR Statement/*[in]*/)
{
  GetDefaultInterface()->ExecuteStatement(Statement/*[in]*/);
}

TVariant __fastcall TScriptControl::Run(BSTR ProcedureName/*[in]*/, LPSAFEARRAY* Parameters/*[in]*/)
{
  return GetDefaultInterface()->Run(ProcedureName/*[in]*/, Parameters/*[in]*/);
}

Msscriptcontrol_tlb::IScriptModuleCollectionPtr __fastcall TScriptControl::Get_Modules(void)
{
  return GetDefaultInterface()->get_Modules();
}

Msscriptcontrol_tlb::IScriptErrorPtr __fastcall TScriptControl::Get_Error(void)
{
  return GetDefaultInterface()->get_Error();
}

LPDISPATCH __fastcall TScriptControl::Get_CodeObject(void)
{
  return GetDefaultInterface()->get_CodeObject();
}

Msscriptcontrol_tlb::IScriptProcedureCollectionPtr __fastcall TScriptControl::Get_Procedures(void)
{
  return GetDefaultInterface()->get_Procedures();
}


};     // namespace Msscriptcontrol_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Msscriptcontrol_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Msscriptcontrol_tlb::TScriptControl)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Msscriptcontrol_ocx
