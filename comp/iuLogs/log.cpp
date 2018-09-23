//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "log.h"
#ifdef _DEBUG
FILE * TLog::fLog=NULL;
int TLog::InstanceCount=0;
#endif
FILE *fLog=NULL;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

