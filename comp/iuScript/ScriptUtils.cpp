//---------------------------------------------------------------------------

#include <vcl.h>
#include <idcoder3to4.hpp>
#pragma hdrstop

#include "ScriptUtils.h"
#include "transliterates.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString __fastcall DecodeBase64New(AnsiString value)
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
        input=encodedString.SubString(12,encodedString.Length()-13);
        decoder->CodeString(input);
        AnsiString decodedString=decoder->CompletedInput();
        result+=decodedString.SubString(3,decodedString.Length());
    }

    delete decoder;
    delete stringList;

    KOI2OEM(result.c_str(),result.c_str());

    return result;
}

