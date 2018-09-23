//---------------------------------------------------------------------------
#ifndef FTNPKTH
#define FTNPKTH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "FTNMsg.h"
#include "..\..\comp\include\XxxList.h"
//---------------------------------------------------------------------------
/*
  Type-2 Packet Format (proposed, but currently in use)
  -----------------------------------------------------
    Field    Ofs Siz Type  Description                Expected value(s)
    -------  --- --- ----  -------------------------- -----------------
    OrgNode  0x0   2 Word  Origination node address   0-65535
    DstNode    2   2 Word  Destination node address   1-65535
    Year       4   2  Int  Year packet generated      19??-2???
    Month      6   2  Int  Month  "        "          0-11 (0=Jan)
    Day        8   2  Int  Day    "        "          1-31
    Hour       A   2  Int  Hour   "        "          0-23
    Min        C   2  Int  Minute "        "          0-59
    Sec        E   2  Int  Second "        "          0-59
    Baud      10   2  Int  Baud Rate (not in use)     ????
    PktVer    12   2  Int  Packet Version             Always 2
    OrgNet    14   2 Word  Origination net address    1-65535
    DstNet    16   2 Word  Destination net address    1-65535
    PrdCodL   18   1 Byte  FTSC Product Code     (lo) 1-255
  * PVMajor   19   1 Byte  FTSC Product Rev   (major) 1-255
    Password  1A   8 Char  Packet password            A-Z,0-9
  * QOrgZone  22   2  Int  Orig Zone (ZMailQ,QMail)   1-65535
  * QDstZone  24   2  Int  Dest Zone (ZMailQ,QMail)   1-65535
    Filler    26   2 Byte  Spare Change               ?
| * CapValid  28   2 Word  CW Byte-Swapped Valid Copy BitField
  * PrdCodH   2A   1 Byte  FTSC Product Code     (hi) 1-255
  * PVMinor   2B   1 Byte  FTSC Product Rev   (minor) 1-255
  * CapWord   2C   2 Word  Capability Word            BitField
  * OrigZone  2E   2  Int  Origination Zone           1-65535
  * DestZone  30   2  Int  Destination Zone           1-65535
  * OrigPoint 32   2  Int  Origination Point          1-65535
  * DestPoint 34   2  Int  Destination Point          1-65535
  * ProdData  36   4 Long  Product-specific data      Whatever
    PktTerm   3A   2 Word  Packet terminator          0000

  * - extensions to FTS-0001

  Ofs, Siz are in hex, other values are decimal.

*/
#pragma pack (push,1)
#define PKT_PASSWORD_LENGTH 8
struct TPacketHeader
{
  WORD OrigNode;    //(* of packet, not of messages in packet *)
  WORD DestNode;    //(* of packet, not of messages in packet *)
  WORD Year;        //(* of packet creation, e.g. 1986 *)
  WORD Month;       //(* of packet creation, 0-11 for Jan-Dec *)
  WORD Day;         //(* of packet creation, 1-31 *)
  WORD Hour;        //(* of packet creation, 0-23 *)
  WORD Minute;      //(* of packet creation, 0-59 *)
  WORD Second;      //(* of packet creation, 0-59 *)
  WORD Baud;        //(* max baud rate of orig and dest, 0=SEA *)
  WORD PacketType;  //=0x0002(* old type-1 packets now obsolete *)
  WORD OrigNet;     //(* of packet, not of messages in packet *)
  WORD DestNet;     //(* of packet, not of messages in packet *)
  BYTE ProdCode;    //(* 0 for Fido, write to FTSC for others *)
  BYTE SerialNo;    //(* binary serial number (otherwise null)*)
  char Password[PKT_PASSWORD_LENGTH]; //(* session password  (otherwise null)   *)
  WORD QOrgZone;    //2  Int  Orig Zone (ZMailQ,QMail)   1-65535
  WORD QDstZone;    //24   2  Int  Dest Zone (ZMailQ,QMail)   1-65535
  WORD SpareChange;   //26   2 Byte  Spare Change               ?

  WORD CapValid;    //28   2 Word  CW Byte-Swapped Valid Copy BitField
  BYTE PrdCodH;     //2A   1 Byte  FTSC Product Code     (hi) 1-255
  BYTE PVMinor;     //2B   1 Byte  FTSC Product Rev   (minor) 1-255
  WORD CapWord;     //2C   2 Word  Capability Word            BitField
  WORD OrigZone;    //2E   2  Int  Origination Zone           1-65535
  WORD DestZone;    //30   2  Int  Destination Zone           1-65535
  WORD OrigPoint;   //32   2  Int  Origination Point          1-65535
  WORD DestPoint;   //34   2  Int  Destination Point          1-65535
  DWORD ProdData;   //36   4 Long  Product-specific data      Whatever
//  WORD PktTerm;     //3A   2 Word  Packet terminator          0000

//  char Fill[20];
  TPacketHeader()
  {
    ZeroMemory(this,sizeof(TPacketHeader));
    PacketType=2;Baud=2400;CapValid=0x100;CapWord=1;
  };
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma pack (pop)
//---------------------------------------------------------------------------
class PACKAGE TFTNPKT : public TComponent
{
private:
  AnsiString FPath;
  TPacketHeader *FPacketHeader;
  TListOfX<TFTNMsg> *FMessages;
  TNotifyEvent FOnAfterPacketCreate;
  void __fastcall SetOrigAddr(TNetAddr &Value);
  void __fastcall SetDestAddr(TNetAddr &Value);
  TNetAddr __fastcall GetOrigAddr(void);
  TNetAddr __fastcall GetDestAddr(void);
  void __fastcall SetPassword(AnsiString Value);
  AnsiString __fastcall GetPassword(void);
  TFileStream * __fastcall CreatePKTFile(TDateTime dtCreate);
  void __fastcall SetPath(AnsiString Value);
protected:

public:
  __fastcall TFTNPKT(TComponent* Owner);
  virtual __fastcall ~TFTNPKT(void);
  void __fastcall ReadFromFile(AnsiString FileName);
  void __fastcall WriteToFile(void);
  void __fastcall Clear();

  __property TListOfX<TFTNMsg> *Messages={read=FMessages};
  __property TNetAddr OrigAddr={read=GetOrigAddr, write=SetOrigAddr};
  __property TNetAddr DestAddr={read=GetDestAddr, write=SetDestAddr};
  __property AnsiString Password={read=GetPassword, write=SetPassword};

__published:
  __property AnsiString Path={read=FPath, write=SetPath};
  __property TNotifyEvent OnAfterPacketCreate={read=FOnAfterPacketCreate, write=FOnAfterPacketCreate};

};
//---------------------------------------------------------------------------
#endif
