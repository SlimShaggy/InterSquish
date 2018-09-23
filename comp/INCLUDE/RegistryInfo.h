//---------------------------------------------------------------------------
#ifndef RegistryInfoH
#define RegistryInfoH
//---------------------------------------------------------------------------
#pragma pack (push, 1)
struct TRegUserInfo
{
  unsigned char Sign[4];
  unsigned char Family[16];
  unsigned char Name[16];
  unsigned char Address[28];
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TKeyFileHeader
{
  unsigned char Signature[3];      //  'ISS'
  unsigned char KeyVersion;        //    '1'
};
struct TSerialNo
{
  unsigned char  ConstPart0;
  unsigned short No;
  unsigned char  ConstPart1;
  unsigned char  RegNo1[8];
  unsigned char  ConstPart2;
  unsigned char  RegNo2[4];
  unsigned char  ConstPart3;
  unsigned char  RegNo3[8];
  unsigned char  ConstPart4;
  unsigned short TableEntry;
  unsigned char  RegNo4[4];
  unsigned char  ConstPart5;
  unsigned char  RegNo5[8];
  unsigned char  ConstPart6;
  unsigned char  RegNo6[4];
  unsigned char  ConstPart7;
  unsigned char  RegNo7[16];
};
//---------------------------------------------------------------------------
struct TRegistryData
{
  TKeyFileHeader Header;
  unsigned char CryptedUserInfo[sizeof(TRegUserInfo)*2];
  unsigned char CryptedSerialNo[sizeof(TSerialNo)*2];
};
#pragma pack (pop)
//---------------------------------------------------------------------------
#endif
