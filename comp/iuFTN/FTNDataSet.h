//---------------------------------------------------------------------------
#ifndef FTNDataSetH
#define FTNDataSetH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>

#include "ftnmsg.h"
#include "Kludges.h"
#include <Db.hpp>
#include "API_SQ.H"
#include "JAM.H"

#include <prog.h>

//---------------------------------------------------------------------------
struct TField_Info
{
  char *Name;
  TFieldType Type;
  WORD Size;
  WORD Offset;
};
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TTransliterateEvent)(TObject* Sender,char* Src,char* Dest,bool ToOEM);
//---------------------------------------------------------------------------
//enum TLockedAreaBehavior {labAbort,labWait};
//---------------------------------------------------------------------------
class PACKAGE TFTNDataSet : public TDataSet
{
private:
  AnsiString FBasePath;
  Word FRecInfoOfs;
  Word FBookmarkOfs;
  Word FRecBufSize;
  TTransliterateEvent FTransliterate;
  int FCurrent;
  bool FBaseOpen;//Указывает на то, что все файлы/пути найдены и открыты
  void __fastcall InitBufferPointers(void);

protected:
  int __fastcall CreateField(TField_Info &FieldInfo);
  virtual bool __fastcall ReadMsg(int MsgNum,char *Buffer)=0;
  char * __fastcall GetActiveRecBuf(void);
  virtual void __fastcall SetPath(AnsiString Value);
  virtual TField_Info* __fastcall GetFieldsInfo(void)=0;
	virtual char * __fastcall AllocRecordBuffer(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalLast(void);
	virtual Word __fastcall GetRecordBufSize(void);
	virtual bool __fastcall IsCursorOpen(void);
	virtual void __fastcall GetBookmarkData(char * Buffer, void * Data);
	virtual TBookmarkFlag __fastcall GetBookmarkFlag(char * Buffer);
	virtual void __fastcall InternalSetToRecord(char * Buffer);
	virtual void __fastcall SetBookmarkFlag(char * Buffer, TBookmarkFlag Value);
	virtual void __fastcall SetBookmarkData(char * Buffer, void * Data);
	virtual void __fastcall InternalGotoBookmark(void * Bookmark);
  virtual bool __fastcall GetFieldData(TField* Field, void * Buffer);
  virtual bool __fastcall GetFieldData(TField* Field, void * Buffer, bool NativeFormat){return TDataSet::GetFieldData(Field, Buffer, NativeFormat);};
	virtual bool __fastcall GetFieldData(int FieldNo, void * Buffer){return TDataSet::GetFieldData(FieldNo, Buffer);};
	virtual void __fastcall SetFieldData(TField* Field, void * Buffer);
	virtual void __fastcall SetFieldData(TField* Field, void * Buffer, bool NativeFormat){TDataSet::SetFieldData(Field, Buffer,NativeFormat);};
	virtual TGetResult __fastcall GetRecord(char * Buffer, TGetMode GetMode, bool DoCheck);
	virtual int __fastcall GetRecNo(void);
	virtual void __fastcall ClearCalcFields(char * Buffer);
  virtual int __fastcall Translate(char * Src, char * Dest, bool ToOem);
	virtual void __fastcall InternalHandleException(void) {};
  TStream* __fastcall CreateBlobStream(TField* Field, TBlobStreamMode Mode);
  virtual unsigned int __fastcall GetMsgNo(unsigned int Index){return 0;};
  __property TField_Info *FieldsInfo={read=GetFieldsInfo};
public:
  __fastcall TFTNDataSet(TComponent* Owner);
  __property char *ActiveRecordBuf={read=GetActiveRecBuf};
  __property TTransliterateEvent OnTransliterate={read=FTransliterate, write=FTransliterate};
  __property unsigned int MsgNo[unsigned int Index]={read=GetMsgNo};
  virtual void __fastcall MoveTo(int RecordNumber, bool Exist=true);
  virtual bool __fastcall FindByMsgNom(unsigned int MsgNom);
__published:
//	__property Filter;
	__property Filtered;
//	__property TFilterOptions;
  __property AnsiString BasePath={read=FBasePath, write=SetPath};
	__property Active;
	__property AutoCalcFields;
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeInsert;
	__property AfterInsert;
	__property BeforeEdit;
	__property AfterEdit;
	__property BeforePost;
	__property AfterPost;
	__property BeforeCancel;
	__property AfterCancel;
	__property BeforeDelete;
	__property AfterDelete;
	__property BeforeScroll;
	__property AfterScroll;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnFilterRecord;
	__property OnNewRecord;
	__property OnPostError;

};
//---------------------------------------------------------------------------
#pragma pack (push,1)
//---------------------------------------------------------------------------
struct TSqMsgHeader
{//Порядок следования полей важен!!!
  TXMsgAttr attr;

  char from[36];
  char to[36];
  char subj[72];

  TNetAddr orig;        /* Origination and destination addresses             */
  TNetAddr dest;

  TStamp date_written;   /* When user wrote the msg (UTC)            */
  TStamp date_arrived;   /* When msg arrived on-line (UTC)           */
  signed short  utc_ofs; /* Offset from UTC of message writer, in    *
                          * minutes.                                 */

  #define MAX_REPLY 10   /* Max number of stored replies to one msg  */

  DWORD replyto;
  DWORD replies[MAX_REPLY];

  char ftsc_date[20];  /* Obsolete date information.  If it weren't for the *
                        * fact that FTSC standards say that one cannot      *
                        * modify an in-transit message, I'd be VERY         *
                        * tempted to axe this field entirely, and recreate  *
                        * an FTSC-compatible date field using               *
                        * the information in 'date_written' upon            *
                        * export.  Nobody should use this field, except     *
                        * possibly for tossers and scanners.  All others    *
                        * should use one of the two binary datestamps,      *
                        * above.                                            */
//  TFTNXMsgHeader& __fastcall operator =(const TMsgInfo &MsgInfo);
};
//---------------------------------------------------------------------------
struct TFTNBaseRecord
{
  TXMsgAttr Attr;
  char From[36];
  char To[36];
  char Subj[72];
  TNetAddr Orig;
  TNetAddr Dest;
  TTimeStamp DateWritten;

  signed short  UTCOfs;
  DWORD ReplyTo;
  DWORD Replies[MAX_REPLY];

  char FTSCDate[20];
  TTimeStamp DateArrived;
  int MsgNo;
  int MsgID;
  char *Kludges;
  char *Text;

};
//---------------------------------------------------------------------------
struct TSquishRecord : public TFTNBaseRecord
{//Порядок следования полей важен!!!
  _sqidx SqIdx;
  _sqhdr SqHdr;
};
//---------------------------------------------------------------------------
struct TJAMRecord : public TFTNBaseRecord
{//Порядок следования полей важен!!!
/*
  DWORD Attr;
  char From[36];
  char To[36];
  char Subj[72];
  TNetAddr Orig;
  TNetAddr Dest;
  TTimeStamp DateWritten;

  signed short  UTCOfs;
  DWORD ReplyTo;
  DWORD Reply1st;

  char FTSCDate[20];
  TTimeStamp DateArrived;
  int MsgNo;
  int MsgID;
  char *Kludges;
  char *Text;
*/  
  JAMHDR MsgHeader;
};
//---------------------------------------------------------------------------
struct TMsgRecord
{//Порядок следования полей важен!!!
  TFTNMsgHeader Header;
  int MsgNo;
  char *Kludges;
  char *Text;
  int MsgSize;
  char FileName[9];
};
//---------------------------------------------------------------------------
struct TJamIndexRec
{
  unsigned int umsgid;
  unsigned int offset;
};
//---------------------------------------------------------------------------
#pragma pack (pop)
//---------------------------------------------------------------------------
class PACKAGE TSquishBase : public TFTNDataSet
{
private:
  _sqbase FBaseHeader;
  int fhSQD,fhSQI;
  _sqidx *FIndexes;
//  TKludges *FKludges;
  static TField_Info FFieldsInfo[];
  AnsiString FSQDPath;
  AnsiString FSQIPath;
  AnsiString FSQLPath;
  DWORD __fastcall SquishHash(char *f);
  DWORD __fastcall FindFreeFrame(DWORD *FrameLength);
  DWORD __fastcall AppendNewFreeFrame(DWORD Size);
  void __fastcall InsertMsg(int FrameOfs,_sqhdr *pSqHdr);
  void __fastcall AddFrameToFreeChain(int FrameOffset,_sqhdr *pSqHdr);
  void __fastcall ExcludeFromFreeChain(int FrameOffset,_sqhdr *pSqHdr);
  bool __fastcall OpenSquishFiles(void);
  void __fastcall CloseSquishFiles(void);
  void __fastcall SaveIndexes(void);
  void __fastcall SaveIndex(int IndexNo);
  void __fastcall SaveFrameHeader(_sqhdr *FrameHeader, DWORD Offset);
  void __fastcall SaveBaseHeader(void);
  void __fastcall LoadFrameHeader(_sqhdr *FrameHeader, DWORD Offset);
  void __fastcall RelocateMsg(int MsgNum,int NewFrameOfs, _sqhdr *pSqHdr);
  void __fastcall FreeFrame(int FrameIndex);

  void __fastcall DoDelete(int iDelIndex);
  void __fastcall UpdateSqHeaderNext(int iOffset,int Value);
  void __fastcall UpdateSqHeaderPrev(int iOffset,int Value);
  void __fastcall CreateSQD(AnsiString SqdName);
  void __fastcall CreateSQI(AnsiString SqiName);
protected:
  virtual void __fastcall SetPath(AnsiString Value);
  virtual TField_Info* __fastcall GetFieldsInfo(void){return FFieldsInfo;};
  virtual void __fastcall WriteMsg(int MsgNum,char *Buffer);
  virtual bool __fastcall ReadMsg(int MsgNum,char *Buffer);
	virtual Word __fastcall GetRecordSize(void);
//	virtual Word __fastcall GetRecordBufSize(void);

	virtual int __fastcall GetRecordCount(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);
  virtual void __fastcall InternalInitFieldDefs(void);
	virtual void __fastcall InternalAddRecord(void * Buffer, bool Append);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	virtual void __fastcall InternalDelete(void);
	virtual void __fastcall InternalInitRecord(char * Buffer);
	virtual void __fastcall InternalEdit(void);
	virtual void __fastcall InternalPost(void);
	virtual void __fastcall InternalCancel(void);
  virtual unsigned int __fastcall GetMsgNo(unsigned int Index);

public:
  __fastcall TSquishBase(TComponent* Owner);
  virtual __fastcall ~TSquishBase(void);
  virtual bool __fastcall FindByMsgNom(unsigned int MsgNom);

  __property _sqidx *Indexes={read=FIndexes};
__published:
  __property  OnTransliterate;
};
//---------------------------------------------------------------------------
class PACKAGE TJAMBase : public TFTNDataSet
{
private:
  JAMHDRINFO FBaseHeader;
  AnsiString FJHRPath;
  AnsiString FJDXPath;
  AnsiString FJDTPath;
  int fhJHR,fhJDX,fhJDT;
//  JAMIDXREC *FIndexes;
  TJamIndexRec *FIndexes;
  static TField_Info FFieldsInfo[];

  bool __fastcall OpenJAMFiles(void);
  void __fastcall CloseJAMFiles(void);
  void __fastcall ProcessSubfields(void *Subfields,int Length,TJAMRecord *JAMRecord, TKludges &Kludges);

  void __fastcall CreateJDT(AnsiString APath);
  void __fastcall CreateJHR(AnsiString APath);
  void __fastcall CreateJDX(AnsiString APath);
protected:
  virtual void __fastcall SetPath(AnsiString Value);
  virtual int __fastcall GetRecordCount(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);

  virtual bool __fastcall ReadMsg(int MsgNum,char *Buffer);
	virtual Word __fastcall GetRecordSize(void);
  virtual TField_Info* __fastcall GetFieldsInfo(void);
  virtual void __fastcall InternalInitFieldDefs(void);
	virtual void __fastcall InternalAddRecord(void * Buffer, bool Append);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	virtual void __fastcall InternalDelete(void);
	virtual void __fastcall InternalInitRecord(char * Buffer);
	virtual void __fastcall InternalEdit(void);
	virtual void __fastcall InternalPost(void);
	virtual void __fastcall InternalCancel(void);
  virtual unsigned int __fastcall GetMsgNo(unsigned int Index);
public:
 __fastcall TJAMBase(TComponent* Owner);
  virtual bool __fastcall FindByMsgNom(unsigned int MsgNom);

  virtual __fastcall ~TJAMBase(void);

__published:
  __property  OnTransliterate;

//  __property Filtered;
};

//---------------------------------------------------------------------------
class PACKAGE TMsgBase : public TFTNDataSet
{
private:
  AnsiString FDeletedPath;
  TStringList *FMsgList;
  static TField_Info FFieldsInfo[];
  bool __fastcall ImportMsgFolder(void);
  char * __fastcall FoundBeginText(char *MsgBuf);
  AnsiString __fastcall ExtractFileName(AnsiString Name);
protected:
  virtual int __fastcall GetRecordCount(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);

  virtual bool __fastcall ReadMsg(int MsgNum,char *Buffer);
	virtual Word __fastcall GetRecordSize(void);
  virtual TField_Info* __fastcall GetFieldsInfo(void);
  virtual void __fastcall InternalInitFieldDefs(void);
	virtual void __fastcall InternalAddRecord(void * Buffer, bool Append);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	virtual void __fastcall InternalDelete(void);
	virtual void __fastcall InternalInitRecord(char * Buffer);
	virtual void __fastcall InternalEdit(void);
	virtual void __fastcall InternalPost(void);
	virtual void __fastcall InternalCancel(void);
	virtual void __fastcall SetFiltered(bool Value);

public:
  __fastcall TMsgBase(TComponent* Owner);
 __fastcall ~TMsgBase(void);

__published:
  __property AnsiString DeletedPath={read=FDeletedPath, write=FDeletedPath};
  __property  OnTransliterate;

//  __property Filtered;
};

//---------------------------------------------------------------------------
#endif
