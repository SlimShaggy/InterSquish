//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "iuEncoders.h"
#include "rsaref.h"
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>





//#include "rsaref.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define ENC(c) ((c) ? ((c) & 077) + ' ': '`')
//---------------------------------------------------------------------------
AnsiString __fastcall EncodeBase64(AnsiString Value)
{
AnsiString asResult="";
//int __fastcall R_EncodePEMBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int);
//int __fastcall R_EncodePEMBlock (//encodedBlock, encodedBlockLen, block, blockLen)
  return asResult;
}
//---------------------------------------------------------------------------
AnsiString __fastcall DecodeBase64(AnsiString Value)
{
unsigned char *decodedBlock;
static unsigned int decodedBlockLen;
AnsiString asResult="";
  decodedBlock=new unsigned char[Value.Length()];
  if(!R_DecodePEMBlock(decodedBlock, &decodedBlockLen, (unsigned char *) Value.c_str(),Value.Length()))
    asResult=AnsiString((const char*) decodedBlock,decodedBlockLen);
  delete [] decodedBlock;
  return asResult;
}
//---------------------------------------------------------------------------
/*
 * output one group of 3 bytes, pointed at by p, on file f.
 */
inline void __fastcall OutDec(char *p, char *b)
{
  char c=*p;
  char c1=p[1];
  char c2=p[2];

    b[0] = ENC(c >> 2);
    b[1] = ENC((c << 4) & 060 | (c1 >> 4) & 017);
    b[2] = ENC((c1 << 2) & 074 | (c2 >> 6) & 03);
    b[3] = ENC(c2 /*& 077*/);
}
//---------------------------------------------------------------------------
AnsiString __fastcall UUEncodeFile(int in)
{
char buf[80];
char buf2[160];
short i,j, n;
AnsiString Result="";
//  buf2[1]=0;
  for (;;) {
        n = read(in,buf, 45);

        buf2[0]=ENC(n);
        for (i=0,j=1; i<n; i += 3,j+=4)
        {
            OutDec(&buf[i],&buf2[j]);
        }
        buf2[j]='\n';
        j++;
        buf2[j]=0;
        Result+=AnsiString(buf2);

        Sleep(0);
        if (n <= 0)
            break;
    }
  return Result;
}
//---------------------------------------------------------------------------
void PACKAGE __fastcall IncludeAttachAsUUE(AnsiString &Msg, AnsiString FileName)
{
  int in=open(FileName.c_str(),O_RDONLY|O_BINARY,S_IREAD|S_IWRITE	);
  if(in>=0)
  {
    Msg+="\r\nbegin 666 "+ExtractFileName(FileName)+"\r\n"+UUEncodeFile(in)+"end";
  }
}
void dummy(void)
{
  asm
  {
    mov ax,ax
  }
}

//---------------------------------------------------------------------------

