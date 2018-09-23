#ifndef IUSTRING_H
#define IUSTRING_H

char* __fastcall TrimLeft(char *cString);
char* __fastcall TrimRight(char *cString);

//---------------------------------------------------------------------------
static inline char* Trim(char *cString)
{
  return TrimRight(TrimLeft(cString));
}
//---------------------------------------------------------------------------
#endif
