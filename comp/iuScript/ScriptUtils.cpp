//---------------------------------------------------------------------------

#include <vcl.h>
#include <idcoder3to4.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString __fastcall DecodeBase64Header(AnsiString value, int charsToSkip)
{
    AnsiString result;
    AnsiString input;

    TStringList *stringList = new TStringList;
    stringList->Delimiter = '\t';
    stringList->Clear();
    stringList->DelimitedText=value;

    TIdBase64Decoder *decoder;
    decoder=new TIdBase64Decoder(NULL); //.Create

    for (int i = 0; i < stringList->Count; i++)
    {
        AnsiString encodedString=stringList->Strings[i];
        input=encodedString.SubString(charsToSkip + 1,encodedString.Length() - (charsToSkip + 2));
        decoder->CodeString(input);
        AnsiString decodedString=decoder->CompletedInput();
        result+=decodedString.SubString(3,decodedString.Length());
    }

    delete decoder;
    delete stringList;

    return result;
}
