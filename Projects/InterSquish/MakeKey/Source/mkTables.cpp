//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>

#include "mkTables.h"
#include "rsaref.h"
#include "rsa.h"
#include "RegistryInfo.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmTables *dmTables;
//---------------------------------------------------------------------------
__fastcall TdmTables::TdmTables(TComponent* Owner)
  : TDataModule(Owner)
{
  tRegData->Open();
  ifKeys=new TIniFile(".\\MasterKeys.txt");
}
//---------------------------------------------------------------------------
__fastcall TdmTables::~TdmTables()
{
  delete ifKeys;
}
//---------------------------------------------------------------------------
void __fastcall TdmTables::XXAfterPost(TDataSet *DataSet)
{
  ((TTable *)DataSet)->FlushBuffers();
}
//---------------------------------------------------------------------------
AnsiString __fastcall DataToHex(unsigned char *Data, int len)
{
AnsiString asHex="{";
  for(int i=0;i<len;i++)
    asHex.sprintf("0x0%02.2x,",Data[i]);
  asHex[asHex.Length()]='}';
  return asHex;
}
//---------------------------------------------------------------------------
AnsiString __fastcall DataToRC(unsigned char *Data, int len)
{
AnsiString asHex="{";
  for(int i=0;i<len;i++)
    asHex.sprintf("'\\x%2.2x',",Data[i]);
  asHex[asHex.Length()]='}';
  return asHex;
}
//---------------------------------------------------------------------------
void __fastcall HexToData(AnsiString Hex, unsigned char *Data, int len)
{
AnsiString asHex=Hex;
AnsiString asNumber;
int iPos,Index=0;
  ZeroMemory(Data,len);
  asHex.Delete(1,1);
  asHex.Delete(asHex.Length(),1);
  while(asHex.Length())
  {
    iPos=asHex.Pos(",");
    if(iPos)
    {
      asNumber=asHex.SubString(1,iPos-1);
      asHex.Delete(1,iPos);
    }
    else
      asNumber=asHex;
    Data[Index++]=(unsigned char)asNumber.ToInt();
    if(Index==len)
      break;
  }
}

//---------------------------------------------------------------------------
void __fastcall TdmTables::NewMkGen(AnsiString SectionName)
{
R_RSA_PROTO_KEY    protoKey;
R_RSA_PUBLIC_KEY   PUBLIC_KEY;
R_RSA_PRIVATE_KEY  PRIVATE_KEY;
  protoKey.bits = 1024;
  protoKey.useFermat4 = 1;
  ZeroMemory(&PUBLIC_KEY,sizeof(R_RSA_PUBLIC_KEY));
  ZeroMemory(&PRIVATE_KEY,sizeof(R_RSA_PRIVATE_KEY));
  Screen->Cursor=crHourGlass;
  if(R_GeneratePEMKeys(&PUBLIC_KEY, &PRIVATE_KEY, &protoKey, &RandomStruct))
    throw Exception("Error generation keys");
  ifKeys->WriteString(SectionName, "PublicExponent", DataToHex(PUBLIC_KEY.exponent,sizeof(PUBLIC_KEY.exponent)));
  ifKeys->WriteString(SectionName, "Modulus", DataToHex(PUBLIC_KEY.modulus,sizeof(PUBLIC_KEY.modulus)));
  ifKeys->WriteString(SectionName, "PrivateExponent", DataToHex(PRIVATE_KEY.exponent,sizeof(PRIVATE_KEY.exponent)));
  ifKeys->WriteString(SectionName, "PrivatePrime0", DataToHex(PRIVATE_KEY.prime[0],sizeof(PRIVATE_KEY.prime[0])));
  ifKeys->WriteString(SectionName, "PrivatePrime1", DataToHex(PRIVATE_KEY.prime[1],sizeof(PRIVATE_KEY.prime[1])));
  ifKeys->WriteString(SectionName, "PrivatePrimeExponent0", DataToHex(PRIVATE_KEY.primeExponent[0],sizeof(PRIVATE_KEY.primeExponent[0])));
  ifKeys->WriteString(SectionName, "PrivatePrimeExponent1", DataToHex(PRIVATE_KEY.primeExponent[1],sizeof(PRIVATE_KEY.primeExponent[1])));
  ifKeys->WriteString(SectionName, "PrivateCoefficient", DataToHex(PRIVATE_KEY.coefficient,sizeof(PRIVATE_KEY.coefficient)));

}
//---------------------------------------------------------------------------
void __fastcall TdmTables::GenSNs(int NomCount)
{
TSerialNo SerialNo;

  randomize();
  unsigned char *Ptr=(unsigned char *)(&SerialNo);
  for(int i=0;i<NomCount;i++)
  {
    ZeroMemory(&SerialNo,sizeof(TSerialNo));
    for(int k=0;k<sizeof(TSerialNo);k++)
    {
      for(int j=0;j<(random(1000));j++)
      {
        Application->MainForm->Invalidate();

        Application->ProcessMessages();
      }
      Ptr[k]=(unsigned char)GetTickCount();
    }
    SerialNo.TableEntry=(short)i;
    SerialNo.ConstPart0=0x23;
    SerialNo.ConstPart1=0xa3;
    SerialNo.ConstPart2=0x9a;
    SerialNo.ConstPart3=0xad;
    SerialNo.ConstPart4=0x49;
    SerialNo.ConstPart5=0x2f;
    SerialNo.ConstPart6=0x18;
    SerialNo.ConstPart7=0xc2;
    tRegData->Append();
    tRegDataSerialNo->AsString=DataToHex((unsigned char *)&SerialNo,sizeof(TSerialNo));
    tRegData->Post();
  }
}
//---------------------------------------------------------------------------
void __fastcall TdmTables::ExportSNtoRC(void)
{
R_RSA_PUBLIC_KEY PK_PUBLIC_KEY;
R_RSA_PUBLIC_KEY RK_PUBLIC_KEY;
R_RANDOM_STRUCT randomStruct;
TSerialNo SerialNo;
AnsiString asRCLine;
#define CRYPTED_SN_SIZE (sizeof(TSerialNo)*2)
unsigned char CryptedSN[CRYPTED_SN_SIZE];
unsigned int BytesCrypted;
int Index;
  ZeroMemory(&PK_PUBLIC_KEY,sizeof(R_RSA_PUBLIC_KEY));
  ZeroMemory(&randomStruct,sizeof(R_RANDOM_STRUCT));
  HexToData(ifKeys->ReadString("SN_Key","Modulus",""),PK_PUBLIC_KEY.modulus,sizeof(PK_PUBLIC_KEY.modulus));
  HexToData(ifKeys->ReadString("SN_Key","PublicExponent",""),PK_PUBLIC_KEY.exponent,sizeof(PK_PUBLIC_KEY.exponent));
  HexToData(ifKeys->ReadString("RegKey","Modulus",""),RK_PUBLIC_KEY.modulus,sizeof(RK_PUBLIC_KEY.modulus));
  HexToData(ifKeys->ReadString("RegKey","PublicExponent",""),RK_PUBLIC_KEY.exponent,sizeof(RK_PUBLIC_KEY.exponent));
  randomize();

  for(int i=0;i<sizeof(randomStruct.output);i++)
  {
    randomStruct.output[i]=(unsigned char)random(256);
    randomStruct.state[i]=(unsigned char)random(256);
  }

  tRegData->First();
  int hf=FileCreate(".\\SNs.rc");
  asRCLine="iuPK RCDATA "+DataToRC((unsigned char*)&PK_PUBLIC_KEY,sizeof(R_RSA_PUBLIC_KEY))+"\r\n";
  FileWrite(hf,asRCLine.c_str(),asRCLine.Length());
  asRCLine="iuRK RCDATA "+DataToRC((unsigned char*)&RK_PUBLIC_KEY,sizeof(R_RSA_PUBLIC_KEY))+"\r\n";
  FileWrite(hf,asRCLine.c_str(),asRCLine.Length());
  PK_PUBLIC_KEY.bits=1024;
  if(hf)
  {
    Index=0;
    while(!tRegData->Eof)
    {
      HexToData(tRegDataSerialNo->AsString,(unsigned char*)&SerialNo,sizeof(TSerialNo));
      ZeroMemory(CryptedSN, CRYPTED_SN_SIZE);
      asRCLine="iuRS"+AnsiString(Index)+" RCDATA "+DataToRC((unsigned char*)&randomStruct,sizeof(R_RANDOM_STRUCT))+"\r\n";
      FileWrite(hf,asRCLine.c_str(),asRCLine.Length());
      if(RSAPublicEncrypt(CryptedSN, &BytesCrypted,(unsigned char*)&SerialNo,sizeof(TSerialNo),&PK_PUBLIC_KEY,&randomStruct))
        throw Exception("S/N Encryption error");
      asRCLine="iuSE"+AnsiString(Index)+" RCDATA "+DataToRC(CryptedSN,BytesCrypted)+"\r\n";
      FileWrite(hf,asRCLine.c_str(),asRCLine.Length());

      tRegData->Next();
      Index++;
    }
    FileClose(hf);
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall GenDirForName(AnsiString Name, AnsiString Family)
{
AnsiString Result=".\\Keys";
  CreateDirectory(Result.c_str(),NULL);
  Result+="\\"+Name+" "+Family;
  CreateDirectory(Result.c_str(),NULL);
  Result+="\\is.key";
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TdmTables::GenRegKey(void)
{
TSerialNo SerialNo;
TRegUserInfo UserInfo;
TRegistryData RegKey;
R_RSA_PRIVATE_KEY PRIVATE_KEY;
unsigned int BytesCrypted;

  ZeroMemory(&SerialNo,sizeof(TSerialNo));
  ZeroMemory(&UserInfo,sizeof(TRegUserInfo));
  ZeroMemory(&RegKey,sizeof(TRegistryData));
  ZeroMemory(&PRIVATE_KEY,sizeof(R_RSA_PRIVATE_KEY));
  PRIVATE_KEY.bits=1024;
  HexToData(ifKeys->ReadString("RegKey","Modulus",""),PRIVATE_KEY.modulus,sizeof(PRIVATE_KEY.modulus));
  HexToData(ifKeys->ReadString("RegKey","PublicExponent",""),PRIVATE_KEY.publicExponent,sizeof(PRIVATE_KEY.publicExponent));
  HexToData(ifKeys->ReadString("RegKey","PrivateExponent",""),PRIVATE_KEY.exponent,sizeof(PRIVATE_KEY.exponent));
  HexToData(ifKeys->ReadString("RegKey","PrivatePrime0",""),PRIVATE_KEY.prime[0],sizeof(PRIVATE_KEY.prime[0]));
  HexToData(ifKeys->ReadString("RegKey","PrivatePrime1",""),PRIVATE_KEY.prime[1],sizeof(PRIVATE_KEY.prime[1]));
  HexToData(ifKeys->ReadString("RegKey","PrivatePrimeExponent0",""),PRIVATE_KEY.primeExponent[0],sizeof(PRIVATE_KEY.primeExponent[0]));
  HexToData(ifKeys->ReadString("RegKey","PrivatePrimeExponent1",""),PRIVATE_KEY.primeExponent[1],sizeof(PRIVATE_KEY.primeExponent[1]));
  HexToData(ifKeys->ReadString("RegKey","PrivateCoefficient",""),PRIVATE_KEY.coefficient,sizeof(PRIVATE_KEY.coefficient));
  HexToData(tRegDataSerialNo->AsString,(unsigned char *)&SerialNo,sizeof(TSerialNo));
  strncpy((char *)UserInfo.Name,tRegDataName->AsString.c_str(),sizeof(UserInfo.Name)-1);
  strncpy((char *)UserInfo.Family,tRegDataFamily->AsString.c_str(),sizeof(UserInfo.Family)-1);
  strncpy((char *)UserInfo.Address,tRegDataAddresses->AsString.c_str(),sizeof(UserInfo.Address)-1);
  memcpy(UserInfo.Sign,"IvUs Software",sizeof(UserInfo.Sign));
  RegKey.Header.Signature[0]='I';
  RegKey.Header.Signature[1]='S';
  RegKey.Header.Signature[2]='S';
  RegKey.Header.KeyVersion='0';

  if(RSAPrivateEncrypt(RegKey.CryptedUserInfo,&BytesCrypted,(unsigned char *)&UserInfo,sizeof(TRegUserInfo),&PRIVATE_KEY))
    throw Exception("UserInfo Encryption error");
  if(RSAPrivateEncrypt(RegKey.CryptedSerialNo,&BytesCrypted,(unsigned char *)&SerialNo,sizeof(TSerialNo),&PRIVATE_KEY))
    throw Exception("S/N Encryption error");

//  int fh=FileCreate(".\\"+tRegDataName->AsString+"_"+tRegDataFamily->AsString+"_is.key");
  int fh=FileCreate(GenDirForName(tRegDataName->AsString,tRegDataFamily->AsString));

  if(fh)
  {
    FileWrite(fh,&RegKey, sizeof(TRegistryData));
    FileClose(fh);
    Application->MessageBox("Okey","Okey",0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TdmTables::tRegDataCalcFields(TDataSet *DataSet)
{
  DataSet->FieldByName("SecRecNo")->AsInteger=DataSet->RecNo;  
}
//---------------------------------------------------------------------------

