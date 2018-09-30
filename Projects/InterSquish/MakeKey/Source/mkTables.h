//---------------------------------------------------------------------------
#ifndef mkTablesH
#define mkTablesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <inifiles.hpp>
#include "rsaref.h"

//---------------------------------------------------------------------------
class TdmTables : public TDataModule
{
__published:	// IDE-managed Components
  TTable *tRegData;
  TDataSource *DataSource2;
  TStringField *tRegDataFamily;
  TStringField *tRegDataName;
  TStringField *tRegDataAddresses;
  TStringField *tRegDataPassword;
  TCurrencyField *tRegDataUsCost;
  TCurrencyField *tRegDataRate;
  TStringField *tRegDataRemark;
  TAutoIncField *tRegDataRegistryNo;
  TMemoField *tRegDataSerialNo;
  TIntegerField *tRegDataSecRecNo;
  void __fastcall XXAfterPost(TDataSet *DataSet);
  void __fastcall tRegDataCalcFields(TDataSet *DataSet);
private:	// User declarations
  TIniFile *ifKeys;
public:		// User declarations
R_RANDOM_STRUCT RandomStruct;
  __fastcall TdmTables(TComponent* Owner);
  virtual __fastcall ~TdmTables();
  void __fastcall NewMkGen(AnsiString SectionName);
  void __fastcall GenSNs(int NomCount);
  void __fastcall ExportSNtoRC(void);
  void __fastcall GenRegKey(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmTables *dmTables;
//---------------------------------------------------------------------------
#endif
