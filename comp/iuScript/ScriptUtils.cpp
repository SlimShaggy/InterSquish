//---------------------------------------------------------------------------

#include <vcl.h>
#include <SysUtils.hpp>
#include <StrUtils.hpp>
#include <idcoder3to4.hpp>
#include <idcodertext.hpp>
#include "Transliterates.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString __fastcall DecodeValue(AnsiString value, int charsToSkip, TIdCoder* decoder)
{
    AnsiString input=value.SubString(charsToSkip + 1,value.Length() - (charsToSkip + 2));
    decoder->CodeString(input);
    AnsiString decodedString=decoder->CompletedInput();
    AnsiString result=decodedString.SubString(3,decodedString.Length());
    return result;
}

AnsiString __fastcall DecodeBase64Value(AnsiString value, int charsToSkip)
{
    TIdBase64Decoder *decoder = new TIdBase64Decoder(NULL);
    AnsiString result = DecodeValue(value, charsToSkip, decoder);
    delete decoder;
    return result;
}

AnsiString __fastcall DecodeQuotedPrintableValue(AnsiString value, int charsToSkip)
{
    TIdQuotedPrintableDecoder *decoder = new TIdQuotedPrintableDecoder(NULL);
    AnsiString result = DecodeValue(StringReplace(value, "_", "=20", TReplaceFlags() << rfReplaceAll), charsToSkip, decoder);
    delete decoder;
    return result;
}

AnsiString __fastcall DecodeMimeHeader(AnsiString value)
{
    const AnsiString Koi8BinaryHeader = "=?koi8-r?B?";
    const AnsiString Koi8QPHeader = "=?koi8-r?Q?";
    const AnsiString Utf8BinaryHeader = "=?utf-8?B?";
    const AnsiString Utf8QPHeader = "=?utf-8?Q?";

    if (!(AnsiContainsText(value, Koi8BinaryHeader) || AnsiContainsText(value, Koi8QPHeader)
          || AnsiContainsText(value, Utf8BinaryHeader) || AnsiContainsText(value, Utf8QPHeader)))
    {
        return value;
    }

    AnsiString result;

    TStringList *stringList = new TStringList;
    stringList->Delimiter = '\t';
    //stringList->Clear();
    stringList->DelimitedText=value;

    for (int i = 0; i < stringList->Count; i++)
    {
        AnsiString encodedString=stringList->Strings[i];
        AnsiString decodedString;

        if(AnsiStartsText(Koi8BinaryHeader, encodedString))
        {
            decodedString = DecodeBase64Value(encodedString, Koi8BinaryHeader.Length());
            KOI2OEM(decodedString.c_str(),decodedString.c_str());
        }
        else if(AnsiStartsText(Koi8QPHeader, encodedString))
        {
            decodedString = DecodeQuotedPrintableValue(encodedString, Koi8QPHeader.Length());
            KOI2OEM(decodedString.c_str(),decodedString.c_str());
        }
        else if (AnsiStartsText(Utf8BinaryHeader, encodedString))
        {
            decodedString = DecodeBase64Value(encodedString, Utf8BinaryHeader.Length());
            decodedString = Utf8ToAnsi(decodedString);
            AnsiToOem(decodedString.c_str(),decodedString.c_str());
        }
        else if (AnsiStartsText(Utf8QPHeader, encodedString))
        {
            decodedString = DecodeQuotedPrintableValue(encodedString, Utf8QPHeader.Length());
            decodedString = Utf8ToAnsi(decodedString);
            AnsiToOem(decodedString.c_str(),decodedString.c_str());
        }
        else
        {
            decodedString = encodedString;
        }

        result+=decodedString;
    }

    delete stringList;

    return result;
}
