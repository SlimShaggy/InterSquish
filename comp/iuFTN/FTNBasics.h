//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@geocities.com, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef FTNBasicsH
#define FTNBasicsH
#include <dstring.h>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma pack (push,1)
//---------------------------------------------------------------------------
struct PACKAGE TNetAddr
{
  WORD Zone;
  WORD Net;
  WORD Node;
  WORD Point;
};
//---------------------------------------------------------------------------
#pragma pack (pop)
//---------------------------------------------------------------------------
enum TFTNAddressType {atUnknown,atInternet,atFTN};
//---------------------------------------------------------------------------
class PACKAGE TCommonAddress
{
private:
    AnsiString FUserName;
    AnsiString FHost;
    AnsiString FAccount;
    AnsiString FFTNDomain;
    int FZone;
    int FNet;
    int FNode;
    int FPoint;
    AnsiString __fastcall GetAsRFCString();
    AnsiString __fastcall GetAs4dString();
    AnsiString __fastcall GetAs5dString();
    AnsiString __fastcall GetAsString();
    void __fastcall SetAsString(AnsiString value);
    void __fastcall SetNet(int value);
    void __fastcall SetNode(int value);
    void __fastcall SetPoint(int value);
    bool FIsFTN;
    void __fastcall SetAsFTSStruct(TNetAddr &Value);
    TNetAddr __fastcall GetAsFTSStruct();
//  AnsiString
protected:
public:
  __fastcall TCommonAddress();
  __fastcall TCommonAddress(AnsiString Address);
  __fastcall TCommonAddress(int AZone,int ANet,int ANode,int APoint=0,AnsiString AUserName="",AnsiString ADomain="");
  void __fastcall Clear(void);
  TCommonAddress& __fastcall operator=(const TCommonAddress& From);
    __property AnsiString AsRFCString  = { read = GetAsRFCString, write = SetAsString};
    __property AnsiString As4dString  = { read = GetAs4dString, write = SetAsString};
    __property AnsiString As5dString  = { read = GetAs5dString, write = SetAsString};
    __property AnsiString AsString  = { read = GetAsString, write = SetAsString};

    __property AnsiString UserName  = { read = FUserName, write = FUserName};
    __property AnsiString Host  = { read = FHost, write = FHost };
    __property AnsiString Account  = { read = FAccount, write = FAccount };
    __property int Zone  = { read = FZone };
    __property int Net  = { read = FNet, write = SetNet };
    __property int Node  = { read = FNode, write = SetNode };
    __property int Point  = { read = FPoint, write = SetPoint };
    __property bool IsFTN = {read=FIsFTN};
    __property AnsiString FTNDomain  = { read = FFTNDomain, write = FFTNDomain };
    __property TNetAddr AsFTSStruct  = { read = GetAsFTSStruct, write = SetAsFTSStruct };

};
inline TCommonAddress& __fastcall TCommonAddress::operator=(const TCommonAddress& From)
{
//  AsString=From.FFullString;
  FZone=From.Zone;
  FNet=From.Net;
  FNode=From.Node;
  FPoint=From.Point;
  FUserName=From.UserName;
  FHost=From.Host;
  FAccount=From.Account;
  FIsFTN=From.IsFTN;
  FFTNDomain=From.FTNDomain;
  return *this;
};
#define TFTNAddress  TCommonAddress
//---------------------------------------------------------------------------
/*
class PACKAGE TCustomAddress
{
private:
protected:
  TFTNAddressType FType;
  AnsiString FFullString;
  virtual void __fastcall SetAsString(AnsiString Value);
  virtual AnsiString __fastcall GetAsString(void);
//  __property AnsiString UserName={read=FUserName,write=FUserName};
  __property AnsiString AsString={read=GetAsString,write=SetAsString};
  __property TFTNAddressType Type={read=FType};
public:
  __fastcall TCustomAddress(void);
  __fastcall TCustomAddress(AnsiString AFullString);
};
//---------------------------------------------------------------------------
class PACKAGE TFTNAddress : public TCustomAddress
{
private:
  int FZone;
  int FNet;
  int FNode;
  int FPoint;
  AnsiString FDomain;
  AnsiString FAccount;
  AnsiString FName;
protected:
  virtual void __fastcall SetAsString(AnsiString Value);
  virtual AnsiString __fastcall GetAsString(void);
  void __fastcall SetInternetString(AnsiString Value);
  AnsiString __fastcall GetInternetString(void);
  AnsiString __fastcall GetAs4D(void);
  TNetAddr __fastcall GetFTSStruct(void);
  void __fastcall SetFTSStruct(TNetAddr Value);
public:
  __fastcall TFTNAddress(void);
  __fastcall TFTNAddress(AnsiString AFullString);
  __fastcall TFTNAddress(int AZone,int ANet,int ANode,int APoint=0,AnsiString ADomain="");
  TFTNAddress& __fastcall operator=(const TFTNAddress& From);

//  __property UserName;
  __property AsString;
  __property Type;
  __property AnsiString AsInternetString={read=GetInternetString,write=SetInternetString};
  __property AnsiString As4D={read=GetAs4D};
  __property TNetAddr AsFTSStruct={read=GetFTSStruct,write=SetFTSStruct};
  __property int Zone={read=FZone,write=FZone};
  __property int Net={read=FNet,write=FNet};
  __property int Node={read=FNode,write=FNode};
  __property int Point={read=FPoint,write=FPoint};
  __property AnsiString Domain={read=FDomain,write=FDomain};
  __property AnsiString Name={read=FName,write=FName};
};
inline TFTNAddress& __fastcall TFTNAddress::operator=(const TFTNAddress& From)
{
  AsString=From.FFullString;
//  FZone=From.FZone;
//  FNet=From.FNet;
//  FNode=From.FNode;
//  FPoint=From.FPoint;
//  FDomain=From.FDomain;
//  FAccount=From.FAccount;
  return *this;
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

