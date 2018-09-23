//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@usa.net, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//#include <inifiles.hpp>
#include <masks.hpp>
#include <stdio.h>
#include <log.h>
#include "iuServer.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TiuServer::TiuServer(TComponent* Owner)
  : TCustomServerSocket(Owner)
{
TraceS(__FUNC__);
  CriticalSection=new TCriticalSection;
  FTimeOut=30000;
  FWshTimeout=20;
  FServerSocket = new TServerWinSocket(INVALID_SOCKET);
    FServerSocket->ThreadCacheSize=7;
    InitSocket(FServerSocket);
    OnAccept=Accept;
//    OnClientError=ClientError;
//    OnClientConnect=ClientConnect;
    OnClientDisconnect=ClientDisconnect;

    OnGetThread=GetThread;
    OnListen=Listen;
    OnThreadEnd=ThreadEnd;
    OnThreadStart=ThreadStart;
    ServerType=stThreadBlocking;
  FHeadersTypeCode=htcQuotedPrintable;
TraceS(__FUNC__);

}
//---------------------------------------------------------------------------
__fastcall TiuServer::~TiuServer()
{
TraceS(__FUNC__);
  for(int i=FServerSocket->ActiveConnections;i;i--)
  {
    TraceS(__FUNC__);
    FServerSocket->Connections[i]->Close();
  }
  delete CriticalSection;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::Log(AnsiString sEvent)
{
TraceS(__FUNC__);
  if(FLogLevel)
  {//                      FormatDatetime
    sEvent=Now().FormatString("dd.mm.yyyy hh:nn:ss:zzz ")+sEvent;
    if(FOnLogEvent)
      FOnLogEvent(this,sEvent);
    if(FLogName!="")
    {
    FILE *out;
      CriticalSection->Enter();
      try
      {
        out=fopen(FLogName.c_str(),"a");
        if(out)
        {
          fputs(sEvent.c_str(),out);
          fclose(out);
        }
      }
      __finally
      {
        CriticalSection->Leave();
      }
    }
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TiuServer::FindInTwitList(AnsiString IpAddress)
{
/*
  TiuIPAddress IpAddr(IpAddress);
  if(TwitIpCfg)
  {
    FTwitIpCfg->Refresh();
    for(int i=0;i<FTwitIpCfg->List->Count;i++)
    {
      if(*(FTwitIpCfg->List->Items[i])==IpAddr)
        return true;
    }
  }
*/
TraceS(__FUNC__);
  bool Result=false;

    if(TwitIpCfg)
    {
      CriticalSection->Enter();
      try
      {
        FTwitIpCfg->Refresh();
        for(int i=0;i<FTwitIpCfg->List->Count;i++)
        {
          Result=MatchesMask(IpAddress, FTwitIpCfg->List->Strings[i].Trim());
          if(Result)
            break;
        }
      }
      __finally
      {
        CriticalSection->Leave();
      }
    }
TraceS(__FUNC__);
    return Result;

}
//---------------------------------------------------------------------------
void __fastcall TiuServer::Accept(TObject *Sender,TCustomWinSocket *Socket)
{
AnsiString asLogLine="";
TraceS(__FUNC__);
//AnsiString asRemoteHost=
  asLogLine.sprintf("TCP/IP: Accept port=%d socket handle=%d New connection created. Remote host: [%s]\n",
    Port,Socket->SocketHandle,/*Socket->RemoteHost.c_str(),*/ Socket->RemoteAddress.c_str());
  FSessionsCount++;
  Log(asLogLine);

  if(FindInTwitList(Socket->RemoteAddress))
  {
    asLogLine="";
    asLogLine.sprintf("TCP/IP: Connection refused by twit condition. Socket handle=%d Remote host: [%s]\n",Socket->SocketHandle, Socket->RemoteAddress.c_str());
    Socket->Close();
    Log(asLogLine);
  }
  else if(FNumSameConnections)
  {
  unsigned long ulRemoteAddr=Socket->RemoteAddr.sin_addr.S_un.S_addr;
  int SameConnections=0;
    for(int i=0;i<FServerSocket->ActiveConnections;i++)
    {
      if(ulRemoteAddr==FServerSocket->Connections[i]->RemoteAddr.sin_addr.S_un.S_addr)
      {
        SameConnections++;
        if(SameConnections>FNumSameConnections)
        {
          asLogLine="";
          asLogLine.sprintf("TCP/IP: Connection refused - limit was exhausted. Socket handle=%d Remote host: [%s]\n",Socket->SocketHandle, Socket->RemoteAddress.c_str());
          Socket->Close();
          Log(asLogLine);

        //          FServerSocket->Disconnect((int)Socket->Handle);
          break;
        }
      }
    }
  }
  if(FOnAccept)
    FOnAccept(this,Socket);
TraceS(__FUNC__);
//    FOnAccept(this,Socket->RemoteAddress,Socket->RemoteHost);
}
//---------------------------------------------------------------------------

//void __fastcall TiuServer::ClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
//{
//  Log(Format("Client error. Error code %d\r\n",ARRAYOFCONST((ErrorCode))));
//}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TiuServer::GetThread(TObject *Sender, TServerClientWinSocket *ClientSocket, TServerClientThread *&SocketThread)
{
TraceS(__FUNC__);
    ((TiuServerClientThread *)SocketThread)->TimeOut=TimeOut;
    ((TiuServerClientThread *)SocketThread)->BoxesPath=BoxesPath;
    ((TiuServerClientThread *)SocketThread)->LogLevel=LogLevel;
    ((TiuServerClientThread *)SocketThread)->Server=this;
    ((TiuServerClientThread *)SocketThread)->OnLogEvent=OnLogEvent;
//  if(ClientSocket->Connected)
    SocketThread->Resume();
TraceS(__FUNC__);
//  else
//    SocketThread->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::ClientSocketEvent(TObject* Sender, TCustomWinSocket* Socket, TSocketEvent SocketEvent)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::ErrorEvent(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::Listen(TObject *Sender, TCustomWinSocket *Socket)
{
  Log("TCP/IP: Listen socket "+AnsiString(Socket->SocketHandle)+"\n");
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
AnsiString asLogLine="";
  asLogLine.sprintf("TCP/IP: Connection dropped. Remote host: [%s]\n",
  /*Socket->RemoteHost.c_str(),*/Socket->RemoteAddress.c_str());
//  FtmpCurrentSocket=Socket;
  if(FOnDisconnect)
    FOnDisconnect(this,Socket);
//    FOnDisconnect(this,Socket->RemoteAddress,Socket->RemoteHost);
  Log(asLogLine);
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::ThreadEnd(TObject *Sender, TServerClientThread *Thread)
{
  Log("Server thread [ID="+AnsiString((int)Thread->ThreadID)+"] stoped\n");
//  Log(Format("Server thread [ID=%d] stoped\r\n",ARRAYOFCONST(((int)(Thread->ThreadID)))));
}
//---------------------------------------------------------------------------
void __fastcall TiuServer::ThreadStart(TObject *Sender, TServerClientThread *Thread)
{
  Log("Server thread [ID="+AnsiString((int)Thread->ThreadID)+"] starting\n");

//  Log(Format("Server thread [ID=%d] starting\r\n",ARRAYOFCONST(((int)(Thread->ThreadID)))));

}
//---------------------------------------------------------------------------
/*
unsigned int __fastcall TiuServer::FileSize(AnsiString Name)
{
int hFile;
OFSTRUCT  ofstruct;
unsigned int dwSize=0;
  hFile=OpenFile(Name.c_str(),&ofstruct,OF_READ);
	if (hFile!=HFILE_ERROR)
  {
    dwSize=GetFileSize((HANDLE)hFile,NULL);
   	FileClose(hFile);
  }
  return dwSize;
}
*/
//---------------------------------------------------------------------------
void __fastcall TiuServer::UpdateServerInfo(void)
{
TraceS(__FUNC__);
CriticalSection->Enter();

  FServerInfo.ActiveConnections=FServerSocket->ActiveConnections;
  FServerInfo.ActiveThreads=FServerSocket->ActiveThreads;
	FServerInfo.IdleThreads=FServerSocket->IdleThreads;
	FServerInfo.ThreadCacheSize=FServerSocket->ThreadCacheSize;
CriticalSection->Leave();  
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------

