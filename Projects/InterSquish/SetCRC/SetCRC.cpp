
#include <condefs.h>
#pragma hdrstop
#include <stdio.h>
#include "CRC32.h"


//---------------------------------------------------------------------------
USEUNIT("..\..\..\comp\iuMisc\CRC32.cpp");
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  if(argc<2)
  {
    puts("\nUsage:\n");
    puts("SetCRC <App> <Sign>\n");
    return 1;
  }
  int h=FileOpen(AnsiString(argv[1]),fmOpenRead/*Write*/);
  if(h>=0)
  {
  long *Ptr;
    int iSize=GetFileSize((void*)h,0);
    unsigned char *mem=new unsigned char[iSize];
    Ptr=(long*)mem;
    FileRead(h,mem,iSize);
    FileClose(h);
    long lSign=*((long *)argv[2]);
    for(int i=0;i<iSize/4;i++)
      if(*(Ptr++)==lSign)
        break;


    *Ptr=0;
    *Ptr=crnc32(mem,iSize);
    h=FileCreate(AnsiString(argv[1]));
    if(h)
    {
      FileWrite(h,mem,iSize);
      FileClose(h);
      puts("\nOkey!\n");
    }
    delete [] mem;
    return 0;
  }
  return 2;
}
