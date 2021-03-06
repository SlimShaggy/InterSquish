//---------------------------------------------------------------------------
#ifndef iuIPAddrH
#define iuIPAddrH
//#include <winsock.h>
#include <system.hpp>
#include "Cfg.h"
//#include "XxxList.h"
//---------------------------------------------------------------------------
/*
class TiuIPAddress
{
private:
SOCKADDR_IN FSockAddr;
int FOctets[4];
AnsiString FString;
    bool FIsMasked;
    unsigned int FAddressMask;
    bool __fastcall GetIsMasked();
    void __fastcall SetAsString(AnsiString value);
    AnsiString __fastcall GetAsString();
    void __fastcall SetAddresMask(unsigned int value);
    void __fastcall SetSockAddr(const SOCKADDR_IN &ASockAddr);
    SOCKADDR_IN & __fastcall GetSockAddr();
    void __fastcall ScanCharLine(char *CharLine);
protected:
public:
    __fastcall TiuIPAddress(char *ASocketAddress);
    __fastcall TiuIPAddress(AnsiString ASocketAddress);
    __fastcall TiuIPAddress(const SOCKADDR_IN & ASockAddr);
    bool __fastcall operator ==(const TiuIPAddress &IPAddress);
    __property bool IsMasked  = { read = GetIsMasked };
    __property AnsiString AsString  = { read = GetAsString, write = SetAsString };
    __property unsigned int AddresMask  = { read = FAddressMask, write = SetAddresMask };
    __property SOCKADDR_IN SockAddr  = { read = GetSockAddr, write = SetSockAddr };
};
//---------------------------------------------------------------------------
inline bool __fastcall TiuIPAddress::operator ==(const TiuIPAddress &IPAddress)
{
//bool //Result;
//  Result=(FOctets[0]==IPAddress.FOctets[0]) && (FOctets[1]==IPAddress.FOctets[1])
//   && (FOctets[2]==IPAddress.FOctets[2]) && (FOctets[3]==IPAddress.FOctets[3]);
//  if(!Result)
//  {
    for(int i=0;i<4;i++)
    {
      if((FOctets[i]==1111)||(IPAddress.FOctets[i]==1111))
        continue;
      else
        if(FOctets[i]!=IPAddress.FOctets[i])
          return false;
    }
//  }
  return true;
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TTwitIpCfg : public TCustomCfg
{
private:
  TStringList *FNNTPList;
  TStringList *FSMTPList;
  TStringList *FPOP3List;
  TStringList *FList;
protected:
  virtual void __fastcall Clear();
//  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall ImportCfgLine(char *Line);

public:
  __fastcall TTwitIpCfg(TComponent* Owner);
   virtual __fastcall~TTwitIpCfg();

  __property TStringList *NNTPList={read=FNNTPList};
  __property TStringList *SMTPList={read=FSMTPList};
  __property TStringList *POP3List={read=FPOP3List};
  __property TStringList *List={read=FList};
__published:
  __property Path;
  __property OnRefresh;
};
/*
class PACKAGE TTwitIpCfg : public TCustomCfg
{
private:
  TListOfX<TiuIPAddress> *FNNTPList;
  TListOfX<TiuIPAddress> *FSMTPList;
  TListOfX<TiuIPAddress> *FPOP3List;
  TListOfX<TiuIPAddress> *FList;
protected:
  virtual void __fastcall Clear();
//  virtual void __fastcall Scan(FILE * stream);
  virtual void __fastcall ImportCfgLine(char *Line);

public:
  __fastcall TTwitIpCfg(TComponent* Owner);
   virtual __fastcall~TTwitIpCfg();

  __property TListOfX<TiuIPAddress> *NNTPList={read=FNNTPList};
  __property TListOfX<TiuIPAddress> *SMTPList={read=FSMTPList};
  __property TListOfX<TiuIPAddress> *POP3List={read=FPOP3List};
  __property TListOfX<TiuIPAddress> *List={read=FList};
__published:
  __property Path;
  __property OnRefresh;
};
*/

//---------------------------------------------------------------------------
#endif
