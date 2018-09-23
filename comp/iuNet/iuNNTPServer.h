//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuNNTPServerH
#define iuNNTPServerH
//---------------------------------------------------------------------------
#include "iuServer.h"
//---------------------------------------------------------------------------
class THashTable
{

public:
    __fastcall THashTable();
    __fastcall ~THashTable();
    bool __fastcall add(AnsiString key, AnsiString value);
    bool __fastcall containKey(AnsiString key);
    bool __fastcall containValue(AnsiString value);
    AnsiString __fastcall get(AnsiString key);
    AnsiString __fastcall getKey(AnsiString value);
    __fastcall deleteKey(AnsiString key);
    __fastcall deleteValue(AnsiString value);

private:
    TStringList *keys;
    TStringList *values;
    int seekKey(AnsiString key);
    int seekValue(AnsiString value);
};

class PACKAGE TiuCustomNNTPServer : public TiuServer
{
private:
//  TStringList *FNewsGroupsList;
protected:
//  virtual bool __fastcall BuildNewsGroupList(void)=0;
  virtual  void __fastcall Listen(TObject *Sender, TCustomWinSocket *Socket);
  virtual void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
public:
  __fastcall TiuCustomNNTPServer(TComponent* Owner);
  virtual __fastcall ~TiuCustomNNTPServer();
//  __property TStringList *NewsList={read=FNewsGroupsList};
__published:
  __property HeadersTypeCode;

};
//---------------------------------------------------------------------------
/*
class PACKAGE TiuNNTPServer : public TiuCustomNNTPServer
{
private:
  bool __fastcall MakeNewsGroupList(AnsiString sNewsPath);
protected:
  virtual bool __fastcall BuildNewsGroupList();
  virtual void __fastcall GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread);
public:
  __fastcall TiuNNTPServer(TComponent* Owner);
  AnsiString __fastcall PathToNewsGroupName(AnsiString sNewsPath);
  AnsiString __fastcall NewsGroupNameToPath(AnsiString sNewsName);
__published:
  __property Active;
  __property Port;
  __property ThreadCacheSize;
  __property BoxesPath;
  __property LogLevel;
  __property TimeOut;
  __property OnLogEvent;
  __property LogName;

};
*/
//---------------------------------------------------------------------------
#endif
