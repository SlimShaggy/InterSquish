//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuNNTPServer.h"
#include "iuNNTPServerThread.h"
#include "log.h"
#pragma link "iuServer"

#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TiuCustomNNTPServer::TiuCustomNNTPServer(TComponent* Owner)
  : TiuServer(Owner)
{
TraceS(__FUNC__);
  Port=119;
//  FNewsGroupsList= new TStringList;
//  FNewsGroupsList->Sorted=true;
//  FNewsGroupsList->Duplicates=dupIgnore;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TiuCustomNNTPServer::~TiuCustomNNTPServer()
{
//  delete FNewsGroupsList;
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServer::Listen(TObject *Sender, TCustomWinSocket *Socket)
{
TraceS(__FUNC__);
  TiuServer::Listen(Sender,Socket);
//  BuildNewsGroupList();
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuCustomNNTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  TiuServer::GetThread(Sender, ClientSocket, SocketThread);
  ((TiuServerClientThread*) SocketThread)->HeadersTypeCode=HeadersTypeCode;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
__fastcall TiuNNTPServer::TiuNNTPServer(TComponent* Owner)
  : TiuCustomNNTPServer(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TiuNNTPServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
  SocketThread= new TiuNNTPServerThread(true,ClientSocket);
  TiuCustomNNTPServer::GetThread(Sender, ClientSocket, SocketThread);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuNNTPServer::PathToNewsGroupName(AnsiString sNewsPath)
{

  AnsiString asGroupName=sNewsPath;
  asGroupName.Unique();
  asGroupName.Delete(1,BoxesPath.Length()+1);
  char *cpGroupName=asGroupName.c_str();
  for(int i=1;0<asGroupName.Length();i++)
    if(cpGroupName[i]=='\\')
      cpGroupName[i]='.';
  return asGroupName;
  
}
//---------------------------------------------------------------------------
AnsiString __fastcall TiuNNTPServer::NewsGroupNameToPath(AnsiString sNewsName)
{

  AnsiString asGroupPath=sNewsName;
  asGroupPath.Unique();
  char *cpGroupPath=asGroupPath.c_str();
  for(int i=1;i<asGroupPath.Length();i++)
    if(cpGroupPath[i]=='.')
      cpGroupPath[i]='\\';
  return BoxesPath+"\\"+asGroupPath;
  
}
//---------------------------------------------------------------------------
bool __fastcall TiuNNTPServer::BuildNewsGroupList()
{
  NewsList->Clear();
  return MakeNewsGroupList(BoxesPath);
}

//---------------------------------------------------------------------------

bool __fastcall TiuNNTPServer::MakeNewsGroupList(AnsiString sNewsPath)
{

HANDLE	hFindFile;
WIN32_FIND_DATA	FindFileData;
String sNewsName=sNewsPath+"\\*";
bool Result=true;

  hFindFile=FindFirstFile(sNewsName.c_str(),&FindFileData);
	if(hFindFile!=INVALID_HANDLE_VALUE)
  {
    do
    {
      if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&
      (FindFileData.cFileName[0]!='.'))
      {
        Result=false;
        AnsiString sFullPath=sNewsPath+"\\"+FindFileData.cFileName;
//        if(MakeNewsGroupList(sFullPath))
          NewsList->Add(PathToNewsGroupName(sFullPath));
          MakeNewsGroupList(sFullPath);
      }
    } while (FindNextFile(hFindFile,&FindFileData));
		FindClose(hFindFile);
  }
  return Result;
  
}

//---------------------------------------------------------------------------
namespace Iunntpserver
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TiuNNTPServer)};
     RegisterComponents("Internet", classes, 0);
  }
}
//---------------------------------------------------------------------------
*/



__fastcall THashTable::THashTable()
{
    keys=new TStringList();
    values=new TStringList();
}

__fastcall THashTable::~THashTable()
{
    delete keys;
    delete values;
}


bool __fastcall THashTable::add(AnsiString key, AnsiString value)
{
    int pos;

    if (key.IsEmpty())
        return false;

    pos=this->seekKey(key);
    if (pos>0)
    {
        this->values->Strings[pos]=value;
    }else
    {
        this->keys->Add(key);
        this->values->Add(value);
    }

    return true;
}

bool __fastcall THashTable::containKey(AnsiString key)
{
    if (this->seekKey(key))
        return true;

    return false;
}

bool __fastcall THashTable::containValue(AnsiString value)
{
    if (this->seekValue(value))
        return true;

    return false;
}

int THashTable::seekValue(AnsiString value)
{
    int i;

    if (this->values->Count==0)
        return 0;

    for (i=0;i<values->Count;i++)
    {
        if (values->Strings[i]==value)
            return i;
    }
    return 0;
}


int THashTable::seekKey(AnsiString key)
{
    int i;

    if (this->keys->Count==0)
        return 0;

    for (i=0;i<keys->Count;i++)
    {
        if (keys->Strings[i]==key)
            return i;
    }
    return 0;
}

AnsiString __fastcall THashTable::get(AnsiString key)
{
    int pos;

    pos=this->seekKey(key);
    if (pos==0)
        return NULL;

    return this->values->Strings[pos];        
}

AnsiString __fastcall THashTable::getKey(AnsiString value)
{
    int pos;

    pos=this->seekValue(value);
    if (pos==0)
        return NULL;

    return this->keys->Strings[pos];
}

__fastcall THashTable::deleteKey(AnsiString key)
{
    int pos;

    pos=this->seekKey(key);
    if(pos>0)
    {
        this->keys->Delete(pos);
        this->values->Delete(pos);
    }
}

__fastcall THashTable::deleteValue(AnsiString value)
{
    int pos;

    pos=this->seekValue(value);
    if(pos>0)
    {
        this->keys->Delete(pos);
        this->values->Delete(pos);
    }
}
