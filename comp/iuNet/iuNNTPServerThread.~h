//---------------------------------------------------------------------------
//
//
//
//    Copyright (c) 1999 Ivan Uskov (ivus@geocities.com, 2:5055/101.3@fidonet)
//---------------------------------------------------------------------------
#ifndef iuNNTPServerThreadH
#define iuNNTPServerThreadH
#include <stdio.h>
#include <inifiles.hpp>
#include "iuNNTPServer.h"
#include "iuServerClientThread.h"
#include "Kludges.h"


//---------------------------------------------------------------------------
struct TArticleHeader
{
  int iNumber;
  AnsiString asSubj;
  AnsiString asFrom;
  AnsiString asDate;
  AnsiString asMessage_ID;
  AnsiString asReference;
  int iSize;
  int iLines;
};
//---------------------------------------------------------------------------

class PACKAGE TiuCustomNNTPServerThread : public TiuServerClientThread
{
private:
  AnsiString FiCurrentData;
  bool FPostingAllowed;
  bool FUserValid;
  TStringList *FNewsGroupsList;

protected:
  //TIniFile * maskAreas;
  //AnsiString FSelectedGroup;//текущая группа
  TAreaInfo *FSelectedGroup;

  int FiCurrentArticle;
  AnsiString FCurrentArticle;
  AnsiString FCurrentArticleMessageId;
  AnsiString FCurrentArticleHeader;
  AnsiString FCurrentArticleBody;

  TiuCustomNNTPServer* __fastcall GetNNTPServer(void);
  virtual bool __fastcall SetActiveGroup(AnsiString NewsGroup)=0;
  virtual bool __fastcall PrepareHeader(TArticleHeader &AHeader);
  virtual int __fastcall GetArticleNom(int Index)=0;
  virtual int __fastcall GetArticlesCount(void)=0;
  virtual bool __fastcall RetriveArticle(int ArticleNumber, AnsiString &Article);
  virtual bool __fastcall RetriveArticle(AnsiString MessageID, AnsiString &Article);
  virtual int __fastcall BeginSaveArticles(TStringList *NewsGroups)=0;
  virtual bool __fastcall DoSaveArticle(AnsiString NewsGroup, AnsiString Body);   //!
  virtual void __fastcall EndSaveArticles(void)=0;

  virtual void __fastcall ProcessARTICLE(AnsiString Argument);
  virtual void __fastcall ProcessBODY(AnsiString Argument);
  virtual void __fastcall ProcessGROUP(AnsiString Argument);
  virtual void __fastcall ProcessHEAD(AnsiString Argument);
  virtual void __fastcall ProcessHELP(AnsiString Argument);
  virtual void __fastcall ProcessIHAVE(AnsiString Argument);
  virtual void __fastcall ProcessLAST(AnsiString Argument);
  virtual void __fastcall ProcessLIST(AnsiString Argument);
  virtual void __fastcall ProcessXMOTD(AnsiString Argument);
  virtual void __fastcall ProcessLIST_OVERVIEW_FMT(AnsiString Argument);
  virtual void __fastcall ProcessNEWGROUPS(AnsiString Argument);
  virtual void __fastcall ProcessNEWNEWS(AnsiString Argument);
  virtual void __fastcall ProcessNEXT(AnsiString Argument);
  virtual void __fastcall ProcessPOST(AnsiString Argument);
  virtual void __fastcall ProcessQUIT(AnsiString Argument);
  virtual void __fastcall ProcessSLAVE(AnsiString Argument);
  virtual void __fastcall ProcessSTAT(AnsiString Argument);
  virtual void __fastcall ProcessAUTHINFO_USER(AnsiString Argument);
  virtual void __fastcall ProcessAUTHINFO_PASS(AnsiString Argument);
  virtual void __fastcall ProcessXOVER(AnsiString Argument);
  virtual void __fastcall ProcessDATE(AnsiString Argument);
  virtual void __fastcall SendArticleHeader(int ArticleNumber);

  virtual void __fastcall SendNewsGroupsList(void);
  virtual void __fastcall SendNewsListDesc(void);
  virtual void __fastcall SaveArticle(void);
  virtual void __fastcall CheckValidFields(void);
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);
  virtual void __fastcall SendNewNewsList(TStringList *slRequestedGroups,TDateTime RequestedTime);
  __property int ArticleNom[int Index]={read=GetArticleNom};
  __property int ArticlesCount={read=GetArticlesCount};
  __property TAreaInfo * SelectedGroup={read=FSelectedGroup,write=FSelectedGroup};
  __property bool PostingAllowed={read=FPostingAllowed,write=FPostingAllowed,nodefault};
  __property bool UserValid={read=FUserValid,write=FUserValid,nodefault};
  __property TStringList *NewsList={read=FNewsGroupsList};
public:
    __fastcall TiuCustomNNTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
    __fastcall virtual ~TiuCustomNNTPServerThread(void);
  __property TiuCustomNNTPServer *NNTPServer={read=GetNNTPServer};
  //__property TIniFile* MaskAreas={read=maskAreas, write=maskAreas};
};

//---- В будущем планируется породить этот класс от TiuCustomNNTPServerThread
//---------------------------------------------------------------------------
/*
class PACKAGE TiuNNTPServerThread : public TiuServerClientThread
{
private:
  TStringList *FArticles;
  AnsiString FSelectedGroup;//текущая группа
  int FiCurrentArticle;
//  int FiCurrentArticleNomber;
  AnsiString FiCurrentData;
  void __fastcall ProcessARTICLE(AnsiString Argument);
  void __fastcall ProcessBODY(AnsiString Argument);
  void __fastcall ProcessGROUP(AnsiString Argument);
  void __fastcall ProcessHEAD(AnsiString Argument);
  void __fastcall ProcessHELP(AnsiString Argument);
  void __fastcall ProcessIHAVE(AnsiString Argument);
  void __fastcall ProcessLAST(AnsiString Argument);
  void __fastcall ProcessLIST(void);
  void __fastcall ProcessNEWGROUPS(AnsiString Argument);
  void __fastcall ProcessNEWNEWS(AnsiString Argument);
  void __fastcall ProcessNEXT(AnsiString Argument);
  void __fastcall ProcessPOST(AnsiString Argument);
  void __fastcall ProcessQUIT(AnsiString Argument);
  void __fastcall ProcessSLAVE(AnsiString Argument);
  void __fastcall ProcessSTAT(AnsiString Argument);
  void __fastcall ProcessAUTHINFO_USER(AnsiString Argument);
  void __fastcall ProcessXOVER(AnsiString Argument);
  void __fastcall SendArticleHeader(int ArticleNumber);

  TiuNNTPServer* __fastcall GetNNTPServer(void);
  void __fastcall SendNewsGroupsList(void);
  void __fastcall SaveArticle(void);
  void __fastcall CheckValidFields(void);
  AnsiString __fastcall LastAndFirst(AnsiString NewsGroup);
  AnsiString __fastcall GetNewArticleName(AnsiString Article);
  AnsiString __fastcall GetArticleFileName(int ArticleNumber);
  int __fastcall ArticleNom(int Index);
protected:
  virtual void __fastcall HandleRecivedCommand(AnsiString Command);
  virtual void __fastcall ClientExecute(void);
public:
    __fastcall TiuNNTPServerThread(bool CreateSuspended, TServerClientWinSocket* ASocket);
    __fastcall virtual ~TiuNNTPServerThread(void);
  __property TiuNNTPServer *NNTPServer={read=GetNNTPServer};
  __property AnsiString ArticleFileName[int index]={read=GetArticleFileName};
//  __property AnsiString ArticleNomber[int index]={read=GetArticleFileName};

};
//---------------------------------------------------------------------------
inline int __fastcall TiuNNTPServerThread::ArticleNom(int Index)
{

int N=0;
  if((Index>=0) && (Index<FArticles->Count))
    sscanf(FArticles->Strings[Index].c_str(),"%d.n",&N);
  return N;

}
//---------------------------------------------------------------------------
*/
#endif
