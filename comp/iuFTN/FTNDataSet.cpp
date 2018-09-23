//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <io.h>
#include <stdlib.h>
#include <dos.h>
#include <assert.h>
#include <log.h>
#include "FTNDataSet.h"

#include <prog.h>

#pragma package(smart_init)

//---------------------------------------------------------------------------
namespace Ftndataset
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[3] = { __classid(TSquishBase),
                                    __classid(TJAMBase),
                                    __classid(TMsgBase)
                                  };
     RegisterComponents("FIDO Tech", classes, 2);
  }
}
//---------------------------------------------------------------------------
TField_Info TSquishBase::FFieldsInfo[]={//Порядок следования важен!!!
  {"Attr",        ftInteger,    0,    0},    //1
  {"From",        ftString,     35,   0},    //2
  {"To",          ftString,     35,   0},    //3
  {"Subj",        ftString,     71,   0},    //4
  {"OrigZone",    ftWord,       0,    0},    //5
  {"OrigNet",     ftWord,       0,    0},    //6
  {"OrigNode",    ftWord,       0,    0},    //7
  {"OrigPoint",   ftWord,       0,    0},    //8
  {"DestZone",    ftWord,       0,    0},    //9
  {"DestNet",     ftWord,       0,    0},    //10
  {"DestNode",    ftWord,       0,    0},    //11
  {"DestPoint",   ftWord,       0,    0},    //12
  {"TimeWritten", ftTime,       0,    0},    //13
  {"DateWritten", ftDate,       0,    0},    //14
  {"UTC_Offs",    ftSmallint,   0,    0},    //15
  {"ReplyTo",     ftInteger,    0,    0},    //16
  {"Replies",     ftBytes,      40,   0},    //17
  {"FTSC_date",   ftString,     19,   0},    //18
  {"TimeArrived", ftTime,       0,    0},    //19
  {"DateArrived", ftDate,       0,    0},    //20
  {"MsgNo",       ftAutoInc,    0,    0},    //21
  {"MsgID",       ftInteger,    0,    0},    //22
  {"Kludges",     ftMemo,       0,    0},    //23
  {"Text",        ftMemo,       0,    0}     //24
  };
//---------------------------------------------------------------------------
TField_Info TJAMBase::FFieldsInfo[]={//Порядок следования важен!!!
  {"Attr",        ftInteger,    0,    0},    //1
  {"From",        ftString,     35,   0},    //2
  {"To",          ftString,     35,   0},    //3
  {"Subj",        ftString,     71,   0},    //4
  {"OrigZone",    ftWord,       0,    0},    //5
  {"OrigNet",     ftWord,       0,    0},    //6
  {"OrigNode",    ftWord,       0,    0},    //7
  {"OrigPoint",   ftWord,       0,    0},    //8
  {"DestZone",    ftWord,       0,    0},    //9
  {"DestNet",     ftWord,       0,    0},    //10
  {"DestNode",    ftWord,       0,    0},    //11
  {"DestPoint",   ftWord,       0,    0},    //12
  {"TimeWritten", ftTime,       0,    0},    //13
  {"DateWritten", ftDate,       0,    0},    //14
  {"UTC_Offs",    ftSmallint,   0,    0},    //15
  {"ReplyTo",     ftInteger,    0,    0},    //16
  {"Replies",     ftBytes,      40,   0},    //17
  {"FTSC_date",   ftString,     19,   0},    //18
  {"TimeArrived", ftTime,       0,    0},    //19
  {"DateArrived", ftDate,       0,    0},    //20
  {"MsgNo",       ftAutoInc,    0,    0},    //21
  {"MsgID",       ftInteger,    0,    0},    //22
  {"Kludges",     ftMemo,       0,    0},    //23
  {"Text",        ftMemo,       0,    0}     //24
  };
//---------------------------------------------------------------------------
/*
TField_Info TJAMBase::FFieldsInfo[]={//Порядок следования важен!!!
  {"Attr",        ftInteger,    0,    0},    //1
  {"From",        ftString,     35,   0},    //2
  {"To",          ftString,     35,   0},    //3
  {"Subj",        ftString,     71,   0},    //4
  {"OrigZone",    ftWord,       0,    0},    //5
  {"OrigNet",     ftWord,       0,    0},    //6
  {"OrigNode",    ftWord,       0,    0},    //7
  {"OrigPoint",   ftWord,       0,    0},    //8
  {"DestZone",    ftWord,       0,    0},    //9
  {"DestNet",     ftWord,       0,    0},    //10
  {"DestNode",    ftWord,       0,    0},    //11
  {"DestPoint",   ftWord,       0,    0},    //12
  {"TimeWritten", ftTime,       0,    0},    //13
  {"DateWritten", ftDate,       0,    0},    //14
  {"UTC_Offs",    ftSmallint,   0,    0},    //15
  {"ReplyTo",     ftInteger,    0,    0},    //16
  {"Reply1st",    ftInteger,     0,    0},    //17
  {"FTSC_date",   ftString,     19,   0},    //18
  {"TimeArrived", ftTime,       0,    0},    //19
  {"DateArrived", ftDate,       0,    0},    //20
  {"MsgNo",       ftAutoInc,    0,    0},    //21
  {"MsgID",       ftInteger,    0,    0},    //22
  {"Kludges",     ftMemo,       0,    0},    //23
  {"Text",        ftMemo,       0,    0}     //24
  };
*/  
//--------------------------------------------------------------------------
  TField_Info TMsgBase::FFieldsInfo[]={//Порядок следования важен!!!
  {"From",        ftString,     35,   0},    //1
  {"To",          ftString,     35,   0},    //2
  {"Subj",        ftString,     71,   0},    //3
  {"FTSC_date",   ftString,     19,   0},    //4
  {"TimesRead",   ftWord,       0,    0},    //5
  {"DestNode",    ftWord,       0,    0},    //6
  {"OrigNode",    ftWord,       0,    0},    //7
  {"Cost",        ftWord,       0,    0},    //8
  {"OrigNet",     ftWord,       0,    0},    //9
  {"DestNet",     ftWord,       0,    0},    //10
  {"DestZone",    ftWord,       0,    0},    //11
  {"OrigZone",    ftWord,       0,    0},    //12
  {"DestPoint",   ftWord,       0,    0},    //13
  {"OrigPoint",   ftWord,       0,    0},    //14
  {"ReplyTo",     ftWord,       0,    0},    //15
  {"Attr",        ftWord,       0,    0},    //16
  {"ReplyNext",   ftWord,       0,    0},    //17
  {"MsgNo",       ftInteger,    0,    0},    //18
  {"Kludges",     ftMemo,       0,    0},    //19
  {"Text",        ftMemo,       0,    0},    //20
  {"MsgSize",     ftInteger,    0,    0},    //21
  {"FileName",    ftString,     8,    0}     //22
  };
//---------------------------------------------------------------------------

inline void __fastcall FreeMem(char * &Ptr)
{
TraceS(__FUNC__);  
  if(Ptr)
  {
      delete [] Ptr;
      Ptr=NULL;
  }
TraceS(__FUNC__);  
}
//---------------------------------------------------------------------------
class TSpecMemStream : public TStream
{
private:
  int	FPosition;
  int FSize;
  char ** FMem;
protected:
	virtual void __fastcall SetSize(int NewSize)
  {
  TraceS(__FUNC__);
    if(NewSize!=FSize)
    {
      if(NewSize>FSize)
      {
        char *tmp=*FMem;
        *FMem=new char[NewSize];
        memcpy(*FMem,tmp,FPosition/*FSize*/);
        FreeMem(tmp);
//        delete [] tmp;
      }
      FSize=NewSize;
      if(FPosition>FSize)
        FPosition=FSize;
    }
  }
  //---
public:
	virtual int __fastcall Read(void *Buffer, int Count)
  {
  TraceS(__FUNC__);
    if(Count>(FSize-FPosition))
      Count=FSize-FPosition;
    FPosition+=Count;
    if(Count)
      memmove(Buffer,*FMem,Count);
    TraceS(__FUNC__);
    return Count;
  };
  //---
	virtual int __fastcall Write(const void *Buffer, int Count)
  {
  register int i,j;
    char *cpSource=(char *)Buffer;
    char *cpDest;
    if(FPosition+Count>FSize)
      SetSize(FPosition+Count);
    cpDest=*FMem;
    for(i=0,j=FPosition;i<Count;i++)
      if(cpSource[i]=='\n')
        continue;
      else
        cpDest[j++]=cpSource[i];
    cpDest[j]=0;
    FPosition+=j;
    return Count;
  };
  //---
	virtual int __fastcall Seek(int Offset, Word Origin)
  {
    FPosition = Offset>=FSize ? FPosition : Offset;
    switch(Origin)
    {
      case soFromBeginning: FPosition = Offset;break;
      case soFromCurrent:   FPosition+= Offset;break;
      case soFromEnd:       FPosition = FSize + Offset;break;
    }
    return FPosition;
  };
public:
	 __fastcall TSpecMemStream(char **Mem,int Size) : TStream()
   {
      FMem=Mem;
      FPosition=0;
      FSize=Size;
   };
};

//---------------------------------------------------------------------------
__fastcall TFTNDataSet::TFTNDataSet(TComponent* Owner)
  : TDataSet(Owner)
{
TraceS(__FUNC__);
  BookmarkSize=5;
}
//---------------------------------------------------------------------------
int __fastcall TFTNDataSet::CreateField(TField_Info &FieldInfo)
{
TraceS(__FUNC__);
  TFieldDef *FieldDef=FieldDefs->AddFieldDef();
  FieldDef->Name=AnsiString(FieldInfo.Name);
  FieldDef->DataType=FieldInfo.Type;
  FieldDef->Size=FieldInfo.Size;
  FieldDef->FieldNo=FieldDefs->Count;
  TraceS(__FUNC__);
  return FieldDef->FieldNo;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::ClearCalcFields(char * Buffer)
{
  memset(&Buffer[RecordSize],0,CalcFieldsSize);
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalOpen(void)
{
TraceS(__FUNC__);
  InternalInitFieldDefs();
  if(DefaultFields)
    CreateFields();
  BindFields(True);
  InitBufferPointers();
  for(int i=1;i<FieldDefs->Count;i++)
    if(!FieldsInfo[i].Offset)
    {
      if(FieldsInfo[i-1].Type==ftMemo)
        FieldsInfo[i].Offset=(Word)(FieldsInfo[i-1].Offset+sizeof(void *));
      else
        FieldsInfo[i].Offset=(Word)(FieldsInfo[i-1].Offset+FieldByNumber(i)->DataSize);
    }
  FCurrent=-1;
  FBaseOpen=true;
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalClose(void)
{
  FBaseOpen=false;
  BindFields(False);
  if(DefaultFields) DestroyFields();
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InitBufferPointers(void)
{
TraceS(__FUNC__);
  FRecInfoOfs= Word(RecordSize + CalcFieldsSize);
//  FBookmarkOfs = Word(FRecInfoOfs + sizeof(TRecInfo));
  FBookmarkOfs = Word(FRecInfoOfs + sizeof(TBookmarkFlag));
  FRecBufSize = Word(FBookmarkOfs + BookmarkSize);
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::SetPath(AnsiString Value)
{
  if(State==dsInactive)
  {
    FBasePath=Value;
  }
  else
    throw Exception("Unable change path in Active state");
}
//---------------------------------------------------------------------------
Word __fastcall TFTNDataSet::GetRecordBufSize(void)
{
  return FRecBufSize;
}
//---------------------------------------------------------------------------
bool __fastcall TFTNDataSet::IsCursorOpen(void)
{
  return FBaseOpen;
}
//---------------------------------------------------------------------------
char * __fastcall TFTNDataSet::AllocRecordBuffer(void)
{
  char *Result=new char[GetRecordBufSize()];
  ZeroMemory(Result,GetRecordBufSize());
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::FreeRecordBuffer(char * &Buffer)
{
  FreeMem(Buffer);
TraceS(__FUNC__);
//  if(Buffer)
//  {
//    delete [] Buffer;
//    Buffer=NULL;
//  }

}
//---------------------------------------------------------------------------
char * __fastcall TFTNDataSet::GetActiveRecBuf(void)
{
TraceS(__FUNC__);
char *RecBuf=NULL;
  switch(State)
  {
    case dsBrowse:
      if(!IsEmpty())
        RecBuf=ActiveBuffer();
      break;
    case dsEdit:
    case dsInsert:
    case dsNewValue:
      RecBuf = ActiveBuffer();
      break;
//    dsSetKey: RecBuf := PChar(FKeyBuffer) + SizeOf(TKeyBuffer);
    case dsCalcFields:
      RecBuf = CalcBuffer;
      break;
//    case dsFilter:
//      RecBuf = FFilterBuffer;
//      break;
//    case dsOldValue:
//      RecBuf = GetOldRecord();
//      break;
  }
  TraceS(__FUNC__);
  return RecBuf;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalSetToRecord(char * Buffer)
{
  InternalGotoBookmark(Buffer + FBookmarkOfs);
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::GetBookmarkData(char * Buffer, void * Data)
{
  *((int*)Data)=*((int*)(Buffer+(int)FBookmarkOfs));
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::SetBookmarkData(char * Buffer, void * Data)
{
  *((int*)(Buffer+(int)FBookmarkOfs))=*((int*)Data);
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalGotoBookmark(void * Bookmark)
{
int iBookMark=*((int*)Bookmark);
  FCurrent=iBookMark-1;
}
//---------------------------------------------------------------------------
TBookmarkFlag __fastcall TFTNDataSet::GetBookmarkFlag(char * Buffer)
{
  return *((TBookmarkFlag*)(Buffer + FRecInfoOfs));
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::SetBookmarkFlag(char * Buffer, TBookmarkFlag Value)
{
  *((TBookmarkFlag*)(Buffer + FRecInfoOfs)) = Value;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalLast(void)
{
  FCurrent=RecordCount;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::InternalFirst(void)
{
  FCurrent=-1;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::MoveTo(int RecordNumber, bool Exist)
{
//    CheckBrowseMode();
TraceS(__FUNC__);
TResyncMode Mode;
    DoBeforeScroll();
TraceS(__FUNC__);
    FCurrent=RecordNumber-1;
    if(FCurrent>RecordCount)
      FCurrent=RecordCount;
    if(Exist)
      Mode<<rmExact<<rmCenter;
    Resync(Mode);
TraceS(__FUNC__);
    DoAfterScroll();
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
TGetResult __fastcall TFTNDataSet::GetRecord(char * Buffer, TGetMode GetMode, bool DoCheck)
{
TraceS(__FUNC__);
TGetResult Result=grOK;
TraceS(__FUNC__);
  int Index=FCurrent;
  if(!RecordCount)
    return grError;
TraceS(__FUNC__);
  switch(GetMode)
  {
//    case gmCurrent:
//      break;
    case   gmNext:
      Index++;
      break;
    case   gmPrior:
      Index--;
      break;
//    default:
//    break;
  }
  if((Index>=0) &&(Index<RecordCount))
  {
    if(ReadMsg(Index,Buffer))
    {
      FCurrent=Index;
      GetCalcFields(Buffer);
      *((int *)&Buffer[FBookmarkOfs])=Index+1;
    }else Result=grError;
  }else
    if(Index<0)
      Result=grBOF;
    else
      if(Index>=RecordCount)
        Result=grEOF;

TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
bool __fastcall TFTNDataSet::GetFieldData(TField* Field, void * Buffer)
{
char *cpRecBuf;
bool  Result = false;
TraceS(__FUNC__);
    if (Field->FieldNo > 0)
    {
      cpRecBuf=GetActiveRecBuf();
      Result=FieldsInfo && Buffer && cpRecBuf;
      if(Result)
        memmove(Buffer,cpRecBuf+FieldsInfo[Field->FieldNo-1].Offset,Field->DataSize);
    }
    else
      if((State==dsBrowse)|| (State==dsEdit)|| (State==dsInsert)|| (State==dsCalcFields))
      {
        cpRecBuf=CalcBuffer+RecordSize + Field->Offset;
        Result = cpRecBuf[0];
        if(Result && Buffer)
          Move(&cpRecBuf[1], Buffer, Field->DataSize);
      }
TraceS(__FUNC__);      
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TFTNDataSet::SetFieldData(TField* Field, void * Buffer)
{
char *cpRecBuf;
  if(!((State==dsEdit) || (State==dsInsert) || (State==dsCalcFields) ||
   (State==dsFilter) || (State==dsNewValue)))
    throw Exception("Base is not in Edit mode");

  cpRecBuf=GetActiveRecBuf();
  if (Field->FieldNo > 0)
  {
    if(State == dsCalcFields)
      throw Exception("Base is not in Edit mode");
    if(Field->ReadOnly && !((State==dsSetKey)||(State==dsFilter)))
      throw Exception(Field->DisplayName+" - is readonly field");
    memmove(cpRecBuf+FieldsInfo[Field->FieldNo-1].Offset,Buffer,Field->DataSize);
    Field->Validate(Buffer);
  }
  else// fkCalculated, fkLookup
  {
    cpRecBuf+=RecordSize + Field->Offset;
    cpRecBuf[0]=(char) Buffer;
    if(cpRecBuf[0])
    Move(Buffer, &cpRecBuf[1], Field->DataSize);
  }
 if(!((State==dsCalcFields)|| (State==dsFilter)||(State==dsNewValue)))
    DataEvent(deFieldChange, int(Field));
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TStream* __fastcall TFTNDataSet::CreateBlobStream(TField* Field, TBlobStreamMode Mode)
{
TraceS(__FUNC__);
char **cpMemo;
int iSize=0;
char *ActiveRecBuf=GetActiveRecBuf();
  if(ActiveRecBuf)
  {
    cpMemo=(char **)(ActiveRecBuf+FieldsInfo[Field->FieldNo-1].Offset);
    iSize=strlen(*cpMemo)+1;
  }
TraceS(__FUNC__);
  return new TSpecMemStream(cpMemo,iSize);
}

//---------------------------------------------------------------------------
int __fastcall TFTNDataSet::GetRecNo(void)
{
char *cpBuffer=GetActiveRecBuf();
  return cpBuffer ? *((int*)(cpBuffer+FBookmarkOfs)):0;
}
//---------------------------------------------------------------------------
int __fastcall TFTNDataSet::Translate(char * Src, char * Dest, bool ToOem)
{
TraceS(__FUNC__);
  if(FTransliterate)
    FTransliterate(this,Src,Dest,ToOem);
  else
    if(ToOem)
      CharToOem(Src,Dest);
    else
      OemToChar(Src,Dest);
  return 0;
}
//---------------------------------------------------------------------------
bool __fastcall TFTNDataSet::FindByMsgNom(unsigned int MsgNom)
{
  return false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TMsgBase::TMsgBase(TComponent* Owner)
:TFTNDataSet(Owner)
{
TraceS(__FUNC__);
  FMsgList=new TStringList;
  FMsgList->Sorted=true;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TMsgBase::~TMsgBase(void)
{
TraceS(__FUNC__);
  delete FMsgList;
  FMsgList=NULL;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
int __fastcall TMsgBase::GetRecordCount(void)
{
  return IsCursorOpen() ? FMsgList->Count:0;
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::FreeRecordBuffer(char * &Buffer)
{
  FreeMem(((TMsgRecord *)Buffer)->Kludges);
//  FreeMem(((TMsgRecord *)Buffer)->Text);
  TFTNDataSet::FreeRecordBuffer(Buffer);
}
//---------------------------------------------------------------------------
TField_Info* __fastcall TMsgBase::GetFieldsInfo(void)
{
  return FFieldsInfo;
}
//---------------------------------------------------------------------------
Word __fastcall TMsgBase::GetRecordSize(void)
{
  return sizeof(TMsgRecord);
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalInitFieldDefs(void)
{
  FieldDefs->Clear();
  for(int i=0;i<(sizeof(FFieldsInfo)/sizeof(TField_Info));i++)
    CreateField(FFieldsInfo[i]);
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalAddRecord(void * Buffer, bool Append)
{
}
//---------------------------------------------------------------------------
bool __fastcall TMsgBase::ImportMsgFolder(void)
{
WIN32_FIND_DATA FindData;
HANDLE fh;
TraceS(__FUNC__);
FMsgList->Clear();
  AnsiString FindPath=BasePath+"\\*.msg";
  fh=FindFirstFile(FindPath.c_str(),&FindData);
  int lasterr=GetLastError();
  if(fh!=INVALID_HANDLE_VALUE)
  {
    do
    {
        FMsgList->Add(AnsiString(FindData.cFileName));
        if(FindNextFile(fh,&FindData)==0)
            break;
        //FMsgList->Add(AnsiString::StringOfChar('0',12-strlen(FindData.cFileName))+AnsiString(FindData.cFileName));
        //FMsgList->Add(AnsiString::StringOfChar('0',12-strlen(FindData.cFileName))+AnsiString(FindData.cFileName));
    }while (/*FindNextFile(fh,&FindData)*/true);
    FindClose(fh);
    return true;
  }
TraceS(__FUNC__);
  return (lasterr==ERROR_FILE_NOT_FOUND); //Просто нет ни одного *.msg файла
}
//)---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalOpen(void)
{
TraceS(__FUNC__);
  if(ImportMsgFolder())
  {
    TraceS(__FUNC__);
    TFTNDataSet::InternalOpen();
  }
  else
    throw EDatabaseError("Unable open base");
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::SetFiltered(bool Value)
{
bool Accept;
TraceS(__FUNC__);
  TFTNDataSet::SetFiltered(Value);
TraceS(__FUNC__);
  if(Active)
  {
  TResyncMode Mode;
//    Mode<<rmExact;
    if(Value)
    {
      TStringList *slTmp=new TStringList;
      try
      {
        for(int i=0;i<FMsgList->Count;i++)
        {
          Accept=true;
          if(OnFilterRecord)
            OnFilterRecord(this,Accept);
          if(Accept)
            slTmp->Add(FMsgList->Strings[i]);
          Next();
        }
        FMsgList->Clear();
        FMsgList->AddStrings(slTmp);
      }
      __finally
      {
        delete slTmp;
      }
    }
    else
      ImportMsgFolder();
    First();
    Resync(Mode);
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalClose(void)
{
  if(FMsgList)
    FMsgList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalDelete(void)
{
TraceS(__FUNC__);
  AnsiString asFileName="\\"+ExtractFileName(FMsgList->Strings[RecNo-1]);
  AnsiString asExistingFileName=BasePath+asFileName;
  TraceS(asExistingFileName.c_str());
  if(FDeletedPath=="")
  {
    if(DeleteFile(asExistingFileName.c_str()))
      FMsgList->Delete(RecNo-1);
  }
  else
  {
TraceS(__FUNC__);
    if(FDeletedPath==BasePath)
    {
      FDeletedPath=BasePath+".DEL";
    }
    CreateDirectory(FDeletedPath.c_str(),	NULL);
    AnsiString asNewFileName=FDeletedPath+asFileName;
    if(MoveFileEx(asExistingFileName.c_str(),asNewFileName.c_str(),MOVEFILE_REPLACE_EXISTING))
      FMsgList->Delete(RecNo-1);
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalInitRecord(char * Buffer)
{
TraceS(__FUNC__);
  memset(Buffer,0,GetRecordBufSize());
  ((TMsgRecord *)Buffer)->Text=((TMsgRecord *)Buffer)->Kludges=new char[1];

}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalEdit(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalPost(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TMsgBase::InternalCancel(void)
{
}
//---------------------------------------------------------------------------
char * __fastcall TMsgBase::FoundBeginText(char *MsgBuf)
{
//BYTE *Ptr;
    int offs;

    offs=1;
    while(*MsgBuf)
    {
        if (*MsgBuf=='\r') //закончилась 1 строка в клуджах
        {
            if (*(MsgBuf+1)=='\n')
            {
                offs=2;
            }else offs=1;

            if (*(MsgBuf+offs)!=1) //это уже не клуджи
            {
                break;
            }
        }
        MsgBuf++;
    }
    /*
    if((*MsgBuf=='\r') && (*(MsgBuf+1)!=1))
      break;
    else
      MsgBuf++;
   */
   *MsgBuf=0;

  //*MsgBuf=0;
  return ++MsgBuf;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMsgBase::ExtractFileName(AnsiString Name)
{
TraceS(Name.c_str());
  Name.Unique();
  for(int i=0;i<8;i++)
  if(Name[i+1]!='0')
  {
    Name.Delete(1,i);
    break;
  }
TraceS(Name.c_str());  
  return Name;
}
//---------------------------------------------------------------------------
bool __fastcall TMsgBase::ReadMsg(int MsgNum,char *Buffer)
{
bool Result=true;
char *MsgBuf;
TraceS(__FUNC__);
  int iMsg;
  if(FMsgList->Count>MsgNum)
  {
    TMsgRecord *MsgRecord=(TMsgRecord *)Buffer;
    iMsg=FileOpen(BasePath+"\\"+ExtractFileName(FMsgList->Strings[MsgNum]),fmOpenRead+fmShareDenyNone);
    Result=iMsg>=0;
    if(Result)
    {
      try
      {
        int iBytesRead=FileRead(iMsg,&MsgRecord->Header,sizeof(TFTNMsgHeader));
        Result=iBytesRead==sizeof(TFTNMsgHeader);
        if(Result)
        {
        TraceS(__FUNC__);
          DWORD iBodySize=GetFileSize((void*)iMsg,NULL)-iBytesRead;
          if(iBodySize)
          {
//        SquishRecord->DateArrived=TimeDOS2VCL(SqMsgHeader->date_arrived);//порядок
//        SquishRecord->DateWritten=TimeDOS2VCL(SqMsgHeader->date_written);//важен!
            MsgRecord->MsgNo=MsgNum+1;
            MsgBuf=new char[iBodySize+1];
            MsgRecord->MsgSize=FileRead(iMsg,MsgBuf,iBodySize);
            MsgBuf[MsgRecord->MsgSize]=0;
            TraceS(__FUNC__);
            if(OnTransliterate)
              OnTransliterate(this, MsgBuf, MsgBuf, false);
            else
              OemToChar(MsgBuf, MsgBuf);
            FreeMem(MsgRecord->Kludges);//Удаляем старое
            MsgRecord->Kludges=MsgBuf;
            MsgRecord->Text=FoundBeginText(MsgBuf);
            strncpy(MsgRecord->FileName,FMsgList->Strings[MsgNum].c_str(),8);
//        int iTextLength=SquishRecord->SqHdr.msg_length-SquishRecord->SqHdr.clen-sizeof(TSqMsgHeader);

//      FreeMem(SquishRecord->Kludges);
/*
        delete [] SquishRecord->Kludges;
        SquishRecord->Kludges=new char[SquishRecord->SqHdr.clen+1];
        FileRead(iSQD,SquishRecord->Kludges,SquishRecord->SqHdr.clen);
        if(OnTransliterate)
          OnTransliterate(this,SquishRecord->Kludges,SquishRecord->Kludges,false);
        else
          OemToChar(SquishRecord->Kludges,SquishRecord->Kludges);

//      FreeMem(SquishRecord->Text);

        delete [] SquishRecord->Text;
        SquishRecord->Text=new char[iTextLength+1];
        FileRead(iSQD,SquishRecord->Text,iTextLength);
        SquishRecord->Text[iTextLength]=0;
        if(OnTransliterate)
          OnTransliterate(this,SquishRecord->Text,SquishRecord->Text,false);
        else
          OemToChar(SquishRecord->Text,SquishRecord->Text);
*/
          }
        }
      }
      __finally
      {
//        delete [] MsgBuf;
        FileClose(iMsg);
      }
    }
  }
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//--- TSquishBase -----------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TSquishBase::TSquishBase(TComponent* Owner)
  : TFTNDataSet(Owner)
{
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TSquishBase::~TSquishBase(void)
{
TraceS(__FUNC__);
  if(FIndexes)
  {
  TraceS(__FUNC__);
    delete [] FIndexes;
    FIndexes=NULL;
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::SetPath(AnsiString Value)
{
TraceS(__FUNC__);
  TFTNDataSet::SetPath(Value);
  FSQDPath=BasePath+".sqd";
  FSQIPath=BasePath+".sqi";
  FSQLPath=BasePath+".sql";
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
int __fastcall TSquishBase::GetRecordCount(void)
{
  return IsCursorOpen() ? FBaseHeader.num_msg:0;
}
//---------------------------------------------------------------------------
Word __fastcall TSquishBase::GetRecordSize(void)
{
  return sizeof(TSquishRecord);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::FreeRecordBuffer(char * &Buffer)
{
TraceS(__FUNC__);
  FreeMem(((TSquishRecord *)Buffer)->Kludges);
//  FreeMem(((TSquishRecord *)Buffer)->Text);
//  delete [] ((TSquishRecord *)Buffer)->Kludges;
//  delete [] ((TSquishRecord *)Buffer)->Text;
  TFTNDataSet::FreeRecordBuffer(Buffer);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalAddRecord(void * Buffer, bool Append)
{
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalInitFieldDefs(void)
{
TraceS(__FUNC__);
  FieldDefs->Clear();
  for(int i=0;i<(sizeof(FFieldsInfo)/sizeof(TField_Info));i++)
    CreateField(FFieldsInfo[i]);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalOpen(void)
{
bool OpenResult=false;
TraceS(__FUNC__);
  try
  {
      OpenResult=OpenSquishFiles();
  }
  __finally
  {
    CloseSquishFiles();
  }
  if(OpenResult)
    TFTNDataSet::InternalOpen();
  else
    throw EDatabaseError("Unable open base");
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalClose(void)
{
TraceS(__FUNC__);
  TFTNDataSet::InternalClose();

  if(FIndexes)
  {
    delete [] FIndexes;
    FIndexes=NULL;
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalInitRecord(char * Buffer)
{
TraceS(__FUNC__);
  memset(Buffer,0,GetRecordBufSize());
  ((TSquishRecord *)Buffer)->Text=((TSquishRecord *)Buffer)->Kludges=new char[1];
  TraceS(__FUNC__);
//  ((TSquishRecord *)Buffer)->Text=new char[1];
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalEdit(void)
{
//  OpenSquishFiles();
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalPost(void)
{
DWORD iMsgSize;
DWORD iClen;
char *ActiveRecBuf=GetActiveRecBuf();
_sqhdr *pSqHdr;

  OpenSquishFiles();

  pSqHdr=&(((TSquishRecord *)ActiveRecBuf)->SqHdr);
  iClen=strlen(((TSquishRecord *)ActiveRecBuf)->Kludges)+1;
     iMsgSize=iClen+strlen(((TSquishRecord *)ActiveRecBuf)->Text)+1+sizeof(TSqMsgHeader);
  if(State==dsEdit)
  {
    if(iMsgSize<=pSqHdr->frame_length)
    {
      pSqHdr->msg_length=iMsgSize;
      pSqHdr->clen=iClen;
      WriteMsg(RecNo-1,ActiveRecBuf);
    }
    else
    { //Если измененное сообщение не умещается в текущий фрейм...
    DWORD FrameLength=iMsgSize;

      RelocateMsg(RecNo-1,FindFreeFrame(&FrameLength),pSqHdr);
      pSqHdr->msg_length=iMsgSize;
      pSqHdr->frame_length=FrameLength;
      pSqHdr->clen=iClen;
      WriteMsg(RecNo-1,ActiveRecBuf);
    }
  }
  else if(State==dsInsert)
  {
  DWORD FrameLength=iMsgSize;
  DWORD FrameOfs=FindFreeFrame(&FrameLength);
    InsertMsg(FrameOfs,pSqHdr);
    pSqHdr->msg_length=iMsgSize;
    pSqHdr->clen=iClen;
    WriteMsg(RecordCount-1,ActiveRecBuf);
  }
  CloseSquishFiles();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InsertMsg(int FrameOfs, _sqhdr *pSqHdr)
{
TraceS(__FUNC__);
  FIndexes[FBaseHeader.num_msg].ofs=FrameOfs;
  FIndexes[FBaseHeader.num_msg].umsgid=FBaseHeader.uid;

  LoadFrameHeader(pSqHdr,FrameOfs);
  ExcludeFromFreeChain(FrameOfs,pSqHdr);
  if(FBaseHeader.num_msg)
  {
    UpdateSqHeaderNext(FIndexes[FBaseHeader.num_msg-1].ofs,FrameOfs);
    pSqHdr->prev_frame=FIndexes[FBaseHeader.num_msg-1].ofs;
  }
  else
    pSqHdr->prev_frame=0;
  pSqHdr->next_frame=0;
  if(FBaseHeader.last_frame<FrameOfs)
    FBaseHeader.last_frame=FrameOfs;
  FBaseHeader.num_msg++;
  FBaseHeader.high_msg++;
  FBaseHeader.high_water++;
  FBaseHeader.uid++;

  SaveBaseHeader();
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::RelocateMsg(int MsgNum,int NewFrameOfs,_sqhdr *pSqHdr)
{
_sqhdr FrameHeader;

  LoadFrameHeader(&FrameHeader,NewFrameOfs);
  ExcludeFromFreeChain(NewFrameOfs,&FrameHeader);
  SaveFrameHeader(&FrameHeader,NewFrameOfs);
  FreeFrame(MsgNum);
  UpdateSqHeaderNext(pSqHdr->prev_frame,NewFrameOfs);
  UpdateSqHeaderPrev(pSqHdr->next_frame,NewFrameOfs);
  AddFrameToFreeChain(FIndexes[MsgNum].ofs,pSqHdr);
  FIndexes[MsgNum].ofs=NewFrameOfs;
  if(FBaseHeader.last_frame<NewFrameOfs)
    FBaseHeader.last_frame=NewFrameOfs;

  SaveIndex(MsgNum);
  SaveBaseHeader();
}
//---------------------------------------------------------------------------
DWORD __fastcall TSquishBase::FindFreeFrame(DWORD *FrameLength)
{
_sqhdr SqHdr;

  int dwFindedOfs=FBaseHeader.free_frame;
  while(dwFindedOfs)
  {
    if(FileSeek(fhSQD,dwFindedOfs,0)>=0)
    {
      FileRead(fhSQD,&SqHdr,sizeof(SqHdr));
      if(SqHdr.frame_length<*FrameLength)
        dwFindedOfs=SqHdr.next_frame;
      else
      {
        *FrameLength=SqHdr.frame_length;
        return dwFindedOfs;
      }
    }
    else
      break;
  }
  return AppendNewFreeFrame(*FrameLength);
}
//---------------------------------------------------------------------------
DWORD __fastcall TSquishBase::AppendNewFreeFrame(DWORD Size)
{
_sqhdr FrameHeader={SQHDRID,0,0,Size,0,FRAME_free,0};

  AddFrameToFreeChain(FBaseHeader.end_frame,&FrameHeader);
  FBaseHeader.end_frame+=Size+sizeof(_sqhdr);
  SaveFrameHeader(&FrameHeader,FBaseHeader.last_free_frame);
  return FBaseHeader.last_free_frame;
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalCancel(void)
{
  CloseSquishFiles();
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::InternalDelete(void)
{
int iDelIndex;
char *cpBuffer;
  try
  {
    OpenSquishFiles();
    if(!((bool)(cpBuffer=GetActiveRecBuf())))
      return;
    if(memcmp(&FIndexes[RecNo-1],&(((TSquishRecord *)cpBuffer)->SqIdx),sizeof(_sqidx)))
    {//если база была изменена другой прогой, ищем нужную мессагу
      // ... пока не ищем :(
    }
    else
    {
      iDelIndex=RecNo-1;
      DoDelete(iDelIndex);//Собственно отсюда начинается процедура удаления.
    }
  }
  __finally
  {
    CloseSquishFiles();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::CreateSQD(AnsiString SqdName)
{
TraceS(__FUNC__);
  memset(&FBaseHeader,0,sizeof(_sqbase));
  FBaseHeader.len=sizeof(_sqbase);
//  FBaseHeader.num_msg=0L;
//  FBaseHeader.high_msg=0L;
//  FBaseHeader.high_water=0L;

//  FBaseHeader.begin_frame=NULL_FRAME;
//  FBaseHeader.free_frame=NULL_FRAME;
//  FBaseHeader.last_free_frame=NULL_FRAME;
//  FBaseHeader.last_frame=NULL_FRAME;
//    FBaseHeader.max_msg=0L;
//    FBaseHeader.skip_msg=0L;
//    FBaseHeader.keep_days=0;

  FBaseHeader.end_frame=FBaseHeader.len;
  FBaseHeader.sz_sqhdr=sizeof(SQHDR);
  FBaseHeader.uid=1L;
  strncpy((char *)FBaseHeader.base,SqdName.c_str(),79);
  fhSQD=FileCreate(SqdName);
  SaveBaseHeader();
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::CreateSQI(AnsiString SqiName)
{
TraceS(__FUNC__);
  fhSQI=FileCreate(SqiName);
  if(FIndexes) delete [] FIndexes;
  FIndexes=new _sqidx[1];
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TSquishBase::OpenSquishFiles(void)
{
TraceS(__FUNC__);
  fhSQI=fhSQD=-1;
  if(!FileExists(FSQDPath))
  {
    CreateSQD(FSQDPath);
    CreateSQI(FSQIPath);
  }
  else
  {
    fhSQD=FileOpen(FSQDPath,fmOpenReadWrite+fmShareDenyNone);
    if(fhSQD>=0)//Читаем заголовок базы
    {
      if(FileRead(fhSQD,&FBaseHeader,sizeof(_sqbase))==sizeof(_sqbase))
      {
        if(!FileExists(FSQIPath))
          CreateSQI(FSQIPath);
        else
        {
          fhSQI=FileOpen(FSQIPath,fmOpenReadWrite+fmShareDenyNone);
          if(fhSQI>=0)//Считываем Индекс в память
          {
            int IndexSize=GetFileSize((void *) fhSQI,NULL);
            if(FIndexes)
            {
            TraceS(__FUNC__);
              delete [] FIndexes;
              FIndexes=NULL;
            }
            if(IndexSize!=0xFFFFFFFF)
            {
            TraceS(__FUNC__);
              FIndexes=new _sqidx[IndexSize+1];
              FileRead(fhSQI,FIndexes,IndexSize);
              TraceS(__FUNC__);
            }
  //          else
  //          {
  //            throw Exception("Bad .SQI file");
  //          }
          }
        }
      }
    }
  }
TraceS(__FUNC__);
  return (fhSQI>=0) && (fhSQD>=0) && (FIndexes);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::CloseSquishFiles(void)
{
TraceS(__FUNC__);
  if(fhSQI>=0)
    FileClose(fhSQI);
  if(fhSQD>=0)
    FileClose(fhSQD);
  fhSQI=fhSQD=-1;
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::UpdateSqHeaderNext(int iOffset,int Value)
{
  if(iOffset)
  {
  _sqhdr shTmpFrame;
    LoadFrameHeader(&shTmpFrame,iOffset);
    shTmpFrame.next_frame=Value;
    SaveFrameHeader(&shTmpFrame,iOffset);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::UpdateSqHeaderPrev(int iOffset,int Value)
{
  if(iOffset)
  {
  _sqhdr shTmpFrame;
    LoadFrameHeader(&shTmpFrame,iOffset);
    shTmpFrame.prev_frame=Value;
    SaveFrameHeader(&shTmpFrame,iOffset);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::ExcludeFromFreeChain(int FrameOffset,_sqhdr *pSqHdr)
{
  if(FrameOffset==FBaseHeader.free_frame)
    FBaseHeader.free_frame=pSqHdr->next_frame;
  if(FrameOffset==FBaseHeader.last_free_frame)
    FBaseHeader.last_free_frame=pSqHdr->prev_frame;

  if(FrameOffset != FBaseHeader.end_frame)
  {
    UpdateSqHeaderNext(pSqHdr->prev_frame, pSqHdr->next_frame);
    UpdateSqHeaderPrev(pSqHdr->next_frame, pSqHdr->prev_frame);
  }
  pSqHdr->frame_type=FRAME_normal;
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::AddFrameToFreeChain(int FrameOffset,_sqhdr *pSqHdr)
{
  if(FBaseHeader.begin_frame==FrameOffset)
    FBaseHeader.begin_frame=pSqHdr->next_frame;
  if(FBaseHeader.last_frame==FrameOffset)
    FBaseHeader.last_frame=pSqHdr->prev_frame;

  if(!FBaseHeader.free_frame || !FBaseHeader.last_free_frame)
  {
    FBaseHeader.last_free_frame=FBaseHeader.free_frame=FrameOffset;
    pSqHdr->prev_frame=pSqHdr->next_frame=NULL_FRAME;
  }
  else
  { 
    pSqHdr->next_frame=NULL_FRAME;
    pSqHdr->prev_frame=FBaseHeader.last_free_frame;
    UpdateSqHeaderNext(FBaseHeader.last_free_frame,FrameOffset);
    FBaseHeader.last_free_frame=FrameOffset;
  }
  pSqHdr->frame_type=FRAME_free;
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::FreeFrame(int FrameIndex)
{
int iKillOffs;
_sqhdr pSqHdr;

  iKillOffs=FIndexes[FrameIndex].ofs;
  pSqHdr=((TSquishRecord *)GetActiveRecBuf())->SqHdr;

  UpdateSqHeaderNext(pSqHdr.prev_frame,pSqHdr.next_frame);
  UpdateSqHeaderPrev(pSqHdr.next_frame,pSqHdr.prev_frame);
  AddFrameToFreeChain(iKillOffs,&pSqHdr);
  SaveFrameHeader(&pSqHdr,iKillOffs);
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::DoDelete(int iDelIndex)
{

  FreeFrame(iDelIndex);
  FBaseHeader.num_msg--;
  FBaseHeader.high_msg--;

  memmove(FIndexes+iDelIndex,FIndexes+iDelIndex+1,(FBaseHeader.num_msg-iDelIndex)*sizeof(_sqidx));

  SaveIndexes();
  SaveBaseHeader();
}
//---------------------------------------------------------------------------
inline void __fastcall TSquishBase::SaveIndex(int IndexNo)
{
  FileSeek(fhSQI, (__int64)(IndexNo*sizeof(_sqidx)), 0);
  FileWrite(fhSQI,FIndexes+IndexNo,sizeof(_sqidx));
}
//---------------------------------------------------------------------------
inline void __fastcall TSquishBase::SaveIndexes(void)
{
  FileSeek(fhSQI, 0, 0);
  FileWrite(fhSQI,FIndexes,FBaseHeader.num_msg*sizeof(_sqidx));
  SetEndOfFile((void *)fhSQI);
}
//---------------------------------------------------------------------------
inline void __fastcall TSquishBase::SaveFrameHeader(_sqhdr *FrameHeader, DWORD Offset)
{
  FileSeek(fhSQD,(__int64)Offset, 0);
  FileWrite(fhSQD,FrameHeader,sizeof(_sqhdr));
}
//---------------------------------------------------------------------------
inline void __fastcall TSquishBase::LoadFrameHeader(_sqhdr *FrameHeader, DWORD Offset)
{
  FileSeek(fhSQD,(__int64)Offset, 0);
  FileRead(fhSQD,FrameHeader,sizeof(_sqhdr));
}
//---------------------------------------------------------------------------
inline void __fastcall TSquishBase::SaveBaseHeader(void)
{
  FileSeek(fhSQD, 0, 0);
  FileWrite(fhSQD,&FBaseHeader,sizeof(_sqbase));
}
//---------------------------------------------------------------------------
DWORD __fastcall TSquishBase::SquishHash(char *f)
{
TraceS(__FUNC__);
DWORD hash=0, g;
char *p;
  for (p=f; *p; p++)
  {
    hash=(hash << 4) + tolower(*p);
    if ((g=(hash & 0xf0000000L)) != 0L)
    {
      hash |= g >> 24;
      hash |= g;
    }
  }
  return (hash & 0x7fffffffLu);
}
//---------------------------------------------------------------------------
/*
TStream* __fastcall TSquishBase::CreateBlobStream(TField* Field, TBlobStreamMode Mode)
{
char **cpMemo;
int iSize=0;
char *ActiveRecBuf=GetActiveRecBuf();
  if(ActiveRecBuf)
  {
    cpMemo=(char **)(ActiveRecBuf+FieldsInfo[Field->FieldNo-1].Offset);
    iSize=strlen(*cpMemo)+1;
  }
  return new TSpecMemStream(cpMemo,iSize);
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TSquishBase::ReadMsg(int MsgNum,char *Buffer)
{
bool Result=true;
TraceS(__FUNC__);
  if(FIndexes)
  {
  TSquishRecord *SquishRecord=(TSquishRecord *)Buffer;
  TSqMsgHeader *SqMsgHeader=(TSqMsgHeader *)Buffer;
  int iSQD;
    iSQD=FileOpen(FSQDPath,fmOpenRead+fmShareDenyNone);
    Result=iSQD>=0;
    TraceS(__FUNC__);
    if(Result)
    {
      try
      {
        FileSeek(iSQD,(__int64)FIndexes[MsgNum].ofs,0);
        FileRead(iSQD,&SquishRecord->SqHdr,FBaseHeader.sz_sqhdr);
        FileRead(iSQD,SqMsgHeader,sizeof(TSqMsgHeader));
        if (strlen(SqMsgHeader->from)==0 && strlen(SqMsgHeader->to)==0)
        {
            //FileClose(iSQD);
            return false;
        }
TraceS(__FUNC__);
        SquishRecord->DateArrived=TimeDOS2VCL(SqMsgHeader->date_arrived);//порядок
TraceS(__FUNC__);
        SquishRecord->DateWritten=TimeDOS2VCL(SqMsgHeader->date_written);//важен!
TraceS(__FUNC__);
        SquishRecord->MsgNo=MsgNum+1;
TraceS(__FUNC__);
        SquishRecord->MsgID=FIndexes[MsgNum].umsgid;
TraceS(__FUNC__);
        SquishRecord->SqIdx=FIndexes[MsgNum];

        int iTextLength=SquishRecord->SqHdr.msg_length-SquishRecord->SqHdr.clen-sizeof(TSqMsgHeader);
TraceS(__FUNC__);
//      FreeMem(SquishRecord->Kludges);

        delete [] SquishRecord->Kludges;
        SquishRecord->Kludges=new char[SquishRecord->SqHdr.clen+iTextLength+2];
TraceS(__FUNC__);
        FileRead(iSQD,SquishRecord->Kludges,SquishRecord->SqHdr.clen);

        SquishRecord->Kludges[SquishRecord->SqHdr.clen]=0;

TraceS(__FUNC__);
        if(OnTransliterate)
          OnTransliterate(this,SquishRecord->Kludges,SquishRecord->Kludges,false);
        else
          OemToChar(SquishRecord->Kludges,SquishRecord->Kludges);

//      FreeMem(SquishRecord->Text);

//        delete [] SquishRecord->Text;
//        SquishRecord->Text=new char[iTextLength+1];
        SquishRecord->Text=SquishRecord->Kludges+SquishRecord->SqHdr.clen+1;
        FileRead(iSQD,SquishRecord->Text,iTextLength);
        SquishRecord->Text[iTextLength]=0;
        if(OnTransliterate)
          OnTransliterate(this,SquishRecord->Text,SquishRecord->Text,false);
        else
          OemToChar(SquishRecord->Text,SquishRecord->Text);
      }
      __finally
      {
        FileClose(iSQD);
      }
    }
  }
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TSquishBase::WriteMsg(int MsgNum,char *Buffer)
{
  TSquishRecord *SquishRecord=(TSquishRecord *)Buffer;
  TSqMsgHeader *SqMsgHeader=(TSqMsgHeader *)Buffer;

  FileSeek(fhSQD,(__int64)FIndexes[MsgNum].ofs,soFromBeginning);
  FileWrite(fhSQD,&SquishRecord->SqHdr,FBaseHeader.sz_sqhdr);
  SqMsgHeader->date_written=TimeVCL2DOS(SquishRecord->DateWritten);//порядок
  SqMsgHeader->date_arrived=TimeVCL2DOS(SquishRecord->DateArrived);//важен!

  FileWrite(fhSQD,SqMsgHeader,sizeof(TSqMsgHeader));

  if(OnTransliterate)
    OnTransliterate(this,SquishRecord->Kludges,SquishRecord->Kludges,true);
  else
   CharToOem(SquishRecord->Kludges,SquishRecord->Kludges);
  FileWrite(fhSQD,SquishRecord->Kludges,strlen(SquishRecord->Kludges)+1);

  if(OnTransliterate)
    OnTransliterate(this,SquishRecord->Text,SquishRecord->Text,true);
  else
    CharToOem(SquishRecord->Text,SquishRecord->Text);
  FileWrite(fhSQD,SquishRecord->Text,strlen(SquishRecord->Text)+1);

  FIndexes[MsgNum].hash=SquishHash(SquishRecord->To);
  SaveIndex(MsgNum);
}
//---------------------------------------------------------------------------
bool __fastcall TSquishBase::FindByMsgNom(unsigned int MsgNom)
{
bool Result=false;
TraceS(__FUNC__);
  for(int i=0;i<RecordCount;i++)
    if(FIndexes[i].umsgid==MsgNom)
    {
      MoveTo(i+1);
      Result=true;
      break;
    }
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
unsigned int __fastcall TSquishBase::GetMsgNo(unsigned int Index)
{
  //return Index<=(unsigned int )RecordCount ? FIndexes[Index].umsgid : 0;
TraceS(__FUNC__);
  if(!Index && !RecordCount)
    return 0;
  return Index<=(unsigned int )RecordCount ? FIndexes[Index].umsgid : 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TJAMBase::TJAMBase(TComponent* Owner):TFTNDataSet(Owner)
{
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
__fastcall TJAMBase::~TJAMBase(void)
{
TraceS(__FUNC__);
  if(FIndexes)
  {
   delete [] FIndexes;
    FIndexes=NULL;
  }
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::SetPath(AnsiString Value)
{
TraceS(__FUNC__);
  TFTNDataSet::SetPath(Value);
  FJHRPath=BasePath+EXT_HDRFILE;
  FJDXPath=BasePath+EXT_IDXFILE;
  FJDTPath=BasePath+EXT_TXTFILE;
}
//---------------------------------------------------------------------------
int __fastcall TJAMBase::GetRecordCount(void)
{
TraceS(__FUNC__);
   return IsCursorOpen() ? FBaseHeader.ActiveMsgs:0;
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::FreeRecordBuffer(char * &Buffer)
{
 // FreeMem(((TJAMRecord *)Buffer)->Kludges);
 delete [] ((TJAMRecord *)Buffer)->Kludges;
  TFTNDataSet::FreeRecordBuffer(Buffer);
}
//---------------------------------------------------------------------------
Word __fastcall TJAMBase::GetRecordSize(void)
{
  return sizeof(TJAMRecord);
}
//---------------------------------------------------------------------------
TField_Info* __fastcall TJAMBase::GetFieldsInfo(void)
{
  return FFieldsInfo;
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalInitFieldDefs(void)
{
TraceS(__FUNC__);
  FieldDefs->Clear();
  for(int i=0;i<(sizeof(FFieldsInfo)/sizeof(TField_Info));i++)
    CreateField(FFieldsInfo[i]);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalAddRecord(void * Buffer, bool Append)
{
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalOpen(void)
{
bool OpenResult=false;
TraceS(__FUNC__);
  try
  {
    OpenResult=OpenJAMFiles();
  }
  __finally
  {
    CloseJAMFiles();
  }
  if(OpenResult)
    TFTNDataSet::InternalOpen();
  else
    throw EDatabaseError("Unable open base");
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalClose(void)
{
TraceS(__FUNC__);
  TFTNDataSet::InternalClose();
  if(FIndexes)
  {
    delete [] FIndexes;
    FIndexes=NULL;
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalDelete(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalInitRecord(char * Buffer)
{
TraceS(__FUNC__);
  memset(Buffer,0,GetRecordBufSize());
  ((TJAMRecord *)Buffer)->Text=((TJAMRecord *)Buffer)->Kludges=new char[1];
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalEdit(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalPost(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::InternalCancel(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::CreateJDT(AnsiString APath)
{
TraceS(__FUNC__);
  int iHandle=FileCreate(APath);
  if(iHandle!=-1)
    FileClose(iHandle);
  else
    throw Exception("Unable create file: "+APath);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::CreateJHR(AnsiString APath)
{
TraceS(__FUNC__);
  ZeroMemory(&FBaseHeader,sizeof(JAMHDRINFO));
  strcpy(FBaseHeader.Signature,"JAM");
  FBaseHeader.DateCreated=TimeVCL2UNIX(Now());
  FBaseHeader.ModCounter=1;
  FBaseHeader.ActiveMsgs=0;
  FBaseHeader.PasswordCRC=0xffffffff;
  FBaseHeader.BaseMsgNum=1;
  int iHandle=FileCreate(APath);
  if(iHandle!=-1)
  {
    FileWrite(iHandle,&FBaseHeader,sizeof(JAMHDRINFO));
    FileClose(iHandle);
  }
  else
    throw Exception("Unable create file: "+APath);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::CreateJDX(AnsiString APath)
{
TraceS(__FUNC__);
  int iHandle=FileCreate(APath);
  if(iHandle!=-1)
    FileClose(iHandle);
  else
    throw Exception("Unable create file: "+APath);
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TJAMBase::OpenJAMFiles(void)
{
TraceS(__FUNC__);
DWORD dwMaxJHROffset;
  fhJHR=fhJDX=fhJDT=-1;
  if(!FileExists(FJDTPath))
  {
    CreateJDT(FJDTPath);
    CreateJHR(FJHRPath);
    CreateJDX(FJDXPath);
  }
//  else
  {
    fhJHR=FileOpen(FJHRPath,fmOpenReadWrite+fmShareDenyNone);
    if(fhJHR>=0)//Читаем заголовок базы
    {
      dwMaxJHROffset=GetFileSize((void *) fhJHR, NULL);
      if(FileRead(fhJHR,&FBaseHeader,sizeof(JAMHDRINFO))==sizeof(JAMHDRINFO))
      {
//        if(!FileExists(FJDXPath))
//          CreateSDX(FJDXPath);
//        else
        {
          fhJDX=FileOpen(FJDXPath,fmOpenReadWrite+fmShareDenyNone);
          if(fhJDX>=0)//Считываем Индекс в память
          {
            int IndexSize=GetFileSize((void *) fhJDX,NULL);
            if(FIndexes)
            {
              delete [] FIndexes;
              FIndexes=NULL;
            }
            if(IndexSize!=0xFFFFFFFF)
            {
            TraceS(__FUNC__);
//              FIndexes=new JAMIDXREC[IndexSize+1];
              JAMIDXREC *JAMIndex=new JAMIDXREC[IndexSize+1];
              try
              {
                if(FileRead(fhJDX, JAMIndex, IndexSize)==IndexSize)
                {
                int j=0;

                  FIndexes=new TJamIndexRec[FBaseHeader.ActiveMsgs];
                  ZeroMemory(FIndexes,FBaseHeader.ActiveMsgs*sizeof(TJamIndexRec));
                  TraceS(__FUNC__);
                  for(unsigned int i=0;i<FBaseHeader.ActiveMsgs;i++)
                  {
//                    while(JAMIndex[j].UserCRC==0xffffffff)
//                      j++;
                    while(JAMIndex[j].UserCRC==0xffffffff)
                    {
                    static JAMHDR MsgHdr;
                      if(JAMIndex[j].HdrOffset<dwMaxJHROffset)
                        if(FileSeek(fhJHR,(__int64)(JAMIndex[j].HdrOffset),0)>0)
                        {
                          FileRead(fhJHR,&MsgHdr,sizeof(JAMHDR));
                          if(!(MsgHdr.Attribute & MSG_DELETED))
                            break;
                        }
                      j++;
                    }

                    FIndexes[i].offset=JAMIndex[j++].HdrOffset;
                  }
                }

              }
              __finally
              {
                delete [] JAMIndex;
              }
              fhJDT=FileOpen(FJDTPath,fmOpenReadWrite+fmShareDenyNone);
            }
  //          else
  //          {
  //            throw Exception("Bad .SQI file");
  //          }
          }
        }
      }
    }
  }
TraceS(__FUNC__);
  return (fhJDT>=0) &&(fhJDX>=0) && (fhJHR>=0) && (FIndexes);
}
/*
DWORD dwMaxJHROffset;
  fhJHR=fhJDX=fhJDT=-1;
  if(!FileExists(FJDTPath))
  {
//    CreateJDT(FJDTPath);
//    CreateJHR(FJHRPath);
//    CreateJDX(FJDXPath);
  }
  else
  {
    fhJHR=FileOpen(FJHRPath,fmOpenRead+fmShareDenyNone);
    if(fhJHR>=0)//Читаем заголовок базы
    {
      dwMaxJHROffset=GetFileSize((void *) fhJHR, NULL);
      if(FileRead(fhJHR,&FBaseHeader,sizeof(JAMHDRINFO))==sizeof(JAMHDRINFO))
      {
//        if(!FileExists(FJDXPath))
//          CreateSDX(FJDXPath);
//        else
        {
          fhJDX=FileOpen(FJDXPath,fmOpenRead+fmShareDenyNone);
          if(fhJDX>=0)//Считываем Индекс в память
          {
            DWORD IndexSize=GetFileSize((void *) fhJDX,NULL);
            if(FIndexes)
            {
              delete [] FIndexes;
              FIndexes=NULL;
            }
            if(IndexSize!=0xFFFFFFFF)
            {
//              FIndexes=new JAMIDXREC[IndexSize+1];
              JAMIDXREC *JAMIndex=new JAMIDXREC[IndexSize+1];
              try
              {
                if(FileRead(fhJDX, JAMIndex, IndexSize)==IndexSize)
                {
                  FIndexes=new TJamIndexRec[FBaseHeader.ActiveMsgs];
                  int j=0;
                  __int64 SeekResilt;
                  ZeroMemory(FIndexes,FBaseHeader.ActiveMsgs*sizeof
(TJamIndexRec));
                  for(unsigned int i=0;i<FBaseHeader.ActiveMsgs;i++)
                  {
                    while(JAMIndex[j].UserCRC==0xffffffff)
                    {
                    static JAMHDR MsgHdr;
                      if(JAMIndex[j].HdrOffset<dwMaxJHROffset)
                        if(FileSeek(fhJHR,(__int64)(JAMIndex[j].HdrOffset),0)>
0)
                        {
                          FileRead(fhJHR,&MsgHdr,sizeof(JAMHDR));
                          if(!(MsgHdr.Attribute & MSG_DELETED))
                            break;
                        }
                      j++;
                    }
                    FIndexes[i].offset=JAMIndex[j++].HdrOffset;
                  }
                }

              }
              __finally
              {
                delete [] JAMIndex;
              }
              fhJDT=FileOpen(FJDTPath,fmOpenRead+fmShareDenyNone);
            }
  //          else
  //          {
  //            throw Exception("Bad .SQI file");
  //          }
          }
        }
      }
    }
  }
  return (fhJDT>=0) &&(fhJDX>=0) && (fhJHR>=0) && (FIndexes);
*/
//---------------------------------------------------------------------------
void __fastcall TJAMBase::CloseJAMFiles(void)

{
TraceS(__FUNC__);
  if(fhJHR>=0)
    FileClose(fhJHR);
  if(fhJDX>=0)
    FileClose(fhJDX);
  if(fhJDT>=0)
    FileClose(fhJDT);
  fhJHR=fhJDX=fhJDT=-1;
TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TJAMBase::ProcessSubfields(void *Subfields,int Length,TJAMRecord *JAMRecord, TKludges &Kludges)
{
int offset=0;
JAMSUBFIELDptr SubField=(JAMSUBFIELDptr) Subfields;
TraceS(__FUNC__);
  while(offset<Length)
  {
    switch(SubField->LoID)
    {
      case JAMSFLD_OADDRESS:
        {
          TCommonAddress caTmp(AnsiString(SubField->Buffer,SubField->DatLen));
          JAMRecord->Orig=caTmp.AsFTSStruct;
        }
        break;
      case JAMSFLD_DADDRESS:
        {
          TCommonAddress caTmp(AnsiString(SubField->Buffer,SubField->DatLen));
          JAMRecord->Dest=caTmp.AsFTSStruct;
        }
        break;
      case JAMSFLD_SENDERNAME:
        strncpy(JAMRecord->From,SubField->Buffer,(int)min(SubField->DatLen,sizeof(JAMRecord->From)-1));
        break;
      case JAMSFLD_RECVRNAME:
        strncpy(JAMRecord->To,SubField->Buffer,(int)min(SubField->DatLen,sizeof(JAMRecord->To)-1));
        break;

      case JAMSFLD_REPLYID:
           {
            AnsiString asKludgeLine(SubField->Buffer,SubField->DatLen);
            asKludgeLine="\x1REPLY: "+asKludgeLine;
            TKludge *Kludge=new TKludge(asKludgeLine);
            Kludges.Add(Kludge);
           }
           break;

      case JAMSFLD_SUBJECT:
        strncpy(JAMRecord->Subj,SubField->Buffer,(int)min(SubField->DatLen,sizeof(JAMRecord->Subj)-1));
        break;
//        break;
      case JAMSFLD_TRACE:
        break;
      case JAMSFLD_ENCLFILE:
        break;
      case JAMSFLD_ENCLFWALIAS:
        break;
//      case JAMSFLD_ENCLFREQ:
//        break;
      case JAMSFLD_ENCLFILEWC:
        break;
      case JAMSFLD_ENCLINDFILE:
        break;
//      case JAMSFLD_EMBINDAT:
//        break;
      case JAMSFLD_MSGID:
        {
          AnsiString asKludgeLine(SubField->Buffer,SubField->DatLen);
          asKludgeLine="\x1MSGID: "+asKludgeLine;
          TKludge *Kludge=new TKludge(asKludgeLine);
          Kludges.Add(Kludge);
        }

        break;
      case JAMSFLD_PID:
        {
          AnsiString asKludgeLine(SubField->Buffer,SubField->DatLen);
          asKludgeLine="\x1PID: "+asKludgeLine;
          TKludge *Kludge=new TKludge(asKludgeLine);
          Kludges.Add(Kludge);
        }
        break;
      case JAMSFLD_FTSKLUDGE:
        {
          AnsiString asKludgeLine(SubField->Buffer,SubField->DatLen);
          TKludge *Kludge=new TKludge(asKludgeLine);
          Kludges.Add(Kludge);
        }
        break;
      case JAMSFLD_SEENBY2D:
        break;
      case JAMSFLD_PATH2D:
        break;
      case JAMSFLD_FLAGS:
        break;
      case JAMSFLD_TZUTCINFO:
        break;
    }
    offset+=SubField->DatLen+sizeof(JAMBINSUBFIELD);
    SubField=(JAMSUBFIELDptr)(((char *) Subfields)+offset);
  }
  TraceS(__FUNC__);
}
//---------------------------------------------------------------------------
bool __fastcall TJAMBase::ReadMsg(int MsgNum,char *Buffer)
{
bool Result=true;

  if(FIndexes)
  {
  TKludges Kludges;
try
{
TraceS(__FUNC__);
  TJAMRecord *JAMRecord=(TJAMRecord *)Buffer;
  ZeroMemory(JAMRecord, sizeof(TJAMRecord));
  JAMHDR *JAMHeader=&(((TJAMRecord *)Buffer)->MsgHeader);
  JAMHDR *JAMHeaderReplyTo=&(((TJAMRecord *)Buffer)->MsgHeader);
  int iJHR;
    iJHR=FileOpen(FJHRPath,fmOpenRead+fmShareDenyNone);
    Result=iJHR>=0;
    if(Result)
    {
      try
      {
//      ZeroMemory(JAMRecord,sizeof(TJAMRecord));
        FileSeek(iJHR,(__int64)FIndexes[MsgNum].offset,0);
        Result=FileRead(iJHR,JAMHeader,sizeof(JAMHDR))==sizeof(JAMHDR);
        if(Result)
        {
          JAMRecord->MsgNo=MsgNum+1;

          FIndexes[MsgNum].umsgid=JAMRecord->MsgID=JAMHeader->MsgNum;
          JAMRecord->DateWritten=TimeUNIX2VCL(JAMHeader->DateWritten);
          JAMRecord->DateArrived=TimeUNIX2VCL(JAMHeader->DateReceived);
          AnsiString asFTSDate=FormatDateTime("dd mmm yy  hh:nn:ss",TimeStampToDateTime(JAMRecord->DateWritten));
          strncpy(JAMRecord->FTSCDate,asFTSDate.c_str(),19);
//        JAMRecord->Attr=JAMHeader->Attribute;
          unsigned char *Subfields=new unsigned char[JAMHeader->SubfieldLen];
          try
          {
            FileRead(iJHR,Subfields,JAMHeader->SubfieldLen);
            /*if (JAMRecord->MsgHeader.ReplyTo!=0) //это ответ на какое-то письмо
            {
                FileSeek(iJHR,(__int64)FIndexes[JAMRecord->MsgHeader.ReplyTo].offset,0);
                Result=FileRead(iJHR,JAMHeaderReplyTo,sizeof(JAMHDR))==sizeof(JAMHDR);
                if(Result)
                {

                }
            }*/
            ProcessSubfields(Subfields,JAMHeader->SubfieldLen,JAMRecord,Kludges);
          }
          __finally
          {
            delete [] Subfields;
          }
        }
//        SquishRecord->SqIdx=FIndexes[MsgNum];

      }
      __finally
      {
        FileClose(iJHR);

      }
    }
    int iJDT=FileOpen(FJDTPath,fmOpenRead+fmShareDenyNone);
    Result=iJDT>=0;
    TraceS(__FUNC__);
    if(Result)
    {
    AnsiString asKludhes=Kludges.Body;
      try
      {
        int iTextLength=JAMHeader->TxtLen+1;
        int iKludgesLength=asKludhes.Length()+1;

        delete [] JAMRecord->Kludges;
        JAMRecord->Kludges=new char[iTextLength+iKludgesLength];
        strcpy(JAMRecord->Kludges, asKludhes.c_str());
        if(OnTransliterate)
          OnTransliterate(this,JAMRecord->Kludges,JAMRecord->Kludges,false);
        else
          OemToChar(JAMRecord->Kludges,JAMRecord->Kludges);

        JAMRecord->Text=JAMRecord->Kludges+iKludgesLength;
        FileSeek(iJDT,(__int64)JAMHeader->TxtOffset,0);

        FileRead(iJDT,JAMRecord->Text,iTextLength);
        JAMRecord->Text[iTextLength-1]=0;
        if(OnTransliterate)
          OnTransliterate(this,JAMRecord->Text,JAMRecord->Text,false);
        else
          OemToChar(JAMRecord->Text,JAMRecord->Text);
      }
      __finally
      {
        FileClose(iJDT);
      }
    }
  }
  __finally
  {
    Kludges.Clear();
  }

  }
  TraceS(__FUNC__);
  return Result;

}
//---------------------------------------------------------------------------
bool __fastcall TJAMBase::FindByMsgNom(unsigned int MsgNom)
{
bool Result=false;
TraceS(__FUNC__);
int iJhr=FileOpen(FJHRPath,fmOpenRead+fmShareDenyNone);
TraceS(__FUNC__);
  try
  {
    for(int i=0;i<RecordCount;i++)
    {
      if(!FIndexes[i].umsgid && iJhr>=0)
      {
        if(FileSeek(iJhr,(__int64)FIndexes[i].offset+48,0)>0)
        {
          FileRead(iJhr,&FIndexes[i].umsgid,4);
        }
      }
      if(FIndexes[i].umsgid==MsgNom)
      {
        Result=true;
        MoveTo(i+1);
        break;
      }
    }
  }
  __finally
  {
    if(iJhr>=0)
      FileClose(iJhr);
  }
TraceS(__FUNC__);
  return Result;
}
//---------------------------------------------------------------------------
unsigned int __fastcall TJAMBase::GetMsgNo(unsigned int Index)
{
TraceS(__FUNC__);
//  Index;//--;
  if(Index>=(unsigned int)RecordCount)
    return 0;
  if(!FIndexes[Index].umsgid)
  {
    TraceS(__FUNC__);
    int iJhr=FileOpen(FJHRPath,fmOpenRead+fmShareDenyNone);
    if(iJhr>=0)
    {
        if(FileSeek(iJhr,(__int64)(FIndexes[Index].offset+48),0)>0)
        {
          TraceS(__FUNC__);
          FileRead(iJhr,&FIndexes[Index].umsgid,4);
        }
        FileClose(iJhr);
    }
  }
  TraceS(__FUNC__);
  return FIndexes[Index].umsgid;
}
//---------------------------------------------------------------------------

