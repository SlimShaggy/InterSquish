#include <string.h>
#include "iuString.h"
//---------------------------------------------------------------------------
char* __fastcall TrimLeft(char *cString)
{
int i=0;
unsigned char * ucString=(unsigned char*)cString;
  while((ucString[i]<=32) && ucString[i])
    i++;
  if(i)
    strcpy(cString,&cString[i]);
  return cString;
}
//---------------------------------------------------------------------------
char* __fastcall  TrimRight(char *cString)
{
int i,j;
  i=j=strlen(cString);
  while((unsigned char)cString[i]<=32)
    if(--i<0)
      break;
  if(i!=j)
    cString[i+1]=0;
  return cString;
}
