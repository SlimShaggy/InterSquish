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

struct TEmojiMap
{
    unsigned int Code;
    const char *Text;
};

static const TEmojiMap EmojiMap[] = {
    {0x1F642, ":)"},   {0x1F60A, ":)"},   {0x263A,  ":)"},   {0x1F609, ";)"},
    {0x1F600, ":-D"},  {0x1F601, ":-D"},  {0x1F603, ":-D"},  {0x1F604, ":-D"},
    {0x1F606, ":-D"},  {0x1F602, ":-D"},  {0x1F923, ":-D"},  {0x1F641, ":("},
    {0x2639,  ":("},   {0x1F61E, ":("},   {0x1F622, ":'("},  {0x1F62D, ":'("},
    {0x1F61B, ":P"},   {0x1F61C, ";P"},   {0x1F61D, ":P"},   {0x1F62E, ":O"},
    {0x1F60E, "8-)"},  {0x1F610, ":|"},   {0x1F44D, "(+)"},  {0x1F44E, "(-)"},
    {0x2764,  "<3"}
};

static void TrimTrailingSpaces(AnsiString &s)
{
    int n = s.Length();
    while (n > 0 && s[n] == ' ')
        n--;
    s.SetLength(n);
}

// Преобразует UTF-8 строку в Ansi (CP_ACP). В отличие от Utf8ToAnsi из VCL,
// которая при встрече 4-байтной последовательности (например, эмодзи) или
// любого некорректного байта возвращает пустую строку целиком, здесь
// известные эмодзи заменяются ASCII-смайликами (см. EmojiMap), а остальные
// непредставимые символы (в том числе суррогатные пары, модификаторы
// U+FE0F и т.п.) отбрасываются вместе с пробелами перед концом строки.
static AnsiString Utf8ToAnsiLenient(AnsiString utf8Value)
{
    if (utf8Value == "")
        return utf8Value;
    int wLen = MultiByteToWideChar(CP_UTF8, 0, utf8Value.c_str(), utf8Value.Length(), NULL, 0);
    if (wLen <= 0)
        return "";
    wchar_t *wBuf = new wchar_t[wLen];
    AnsiString result;
    try
    {
        MultiByteToWideChar(CP_UTF8, 0, utf8Value.c_str(), utf8Value.Length(), wBuf, wLen);
        bool dropped = false;
        for (int i = 0; i < wLen; i++)
        {
            unsigned int code = wBuf[i];
            if (code >= 0xD800 && code <= 0xDBFF && i + 1 < wLen
                && wBuf[i + 1] >= 0xDC00 && wBuf[i + 1] <= 0xDFFF)
            {
                code = 0x10000 + ((code - 0xD800) << 10) + (wBuf[i + 1] - 0xDC00);
                i++;
            }
            const char *emoticon = NULL;
            for (int k = 0; k < (int)(sizeof(EmojiMap) / sizeof(EmojiMap[0])); k++)
            {
                if (EmojiMap[k].Code == code)
                {
                    emoticon = EmojiMap[k].Text;
                    break;
                }
            }
            if (emoticon)
            {
                result += emoticon;
                dropped = false;
                continue;
            }
            char aBuf[8];
            BOOL usedDefault = FALSE;
            int aLen = 0;
            if (code < 0x10000)
                aLen = WideCharToMultiByte(CP_ACP, 0, &wBuf[i], 1, aBuf, sizeof(aBuf), NULL, &usedDefault);
            if (aLen <= 0 || usedDefault)
            {
                dropped = true;
                continue;
            }
            if (dropped && (aBuf[0] == '\r' || aBuf[0] == '\n'))
                TrimTrailingSpaces(result);
            dropped = false;
            result += AnsiString(aBuf, aLen);
        }
        if (dropped)
            TrimTrailingSpaces(result);
    }
    __finally
    {
        delete[] wBuf;
    }
    return result;
}

// Преобразует необработанную UTF-8 строку заголовка в Ansi (CP1251),
// заменяя знаки препинания, которые иначе были бы потеряны или испорчены
// при последующем преобразовании в OEM: неразрывный дефис Unicode (U+2011,
// не представленный в CP1251) заменяется обычным дефисом, кириллические
// угловые кавычки - обычными двойными кавычками, а многоточие - на "...".
AnsiString __fastcall NormalizeUtf8Punctuation(AnsiString utf8Value)
{
    utf8Value = StringReplace(utf8Value, AnsiString("\xE2\x80\x91"), "-",
                  TReplaceFlags() << rfReplaceAll);
    AnsiString ansiValue = Utf8ToAnsiLenient(utf8Value);
    for (int qi = 1; qi <= ansiValue.Length(); qi++)
    {
        unsigned char qc = (unsigned char)ansiValue[qi];
        if (qc == 0xAB || qc == 0xBB)
            ansiValue[qi] = '"';
    }
    ansiValue = StringReplace(ansiValue, AnsiString((char)0x85), "...",
                  TReplaceFlags() << rfReplaceAll);
    return ansiValue;
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
            char* buf = new char[decodedString.Length() + 1];
            strcpy(buf, decodedString.c_str());
            KOI2OEM(buf, buf);
            decodedString = buf;
            delete[] buf;
        }
        else if(AnsiStartsText(Koi8QPHeader, encodedString))
        {
            decodedString = DecodeQuotedPrintableValue(encodedString, Koi8QPHeader.Length());
            char* buf = new char[decodedString.Length() + 1];
            strcpy(buf, decodedString.c_str());
            KOI2OEM(buf, buf);
            decodedString = buf;
            delete[] buf;
        }
        else if (AnsiStartsText(Utf8BinaryHeader, encodedString))
        {
            decodedString = DecodeBase64Value(encodedString, Utf8BinaryHeader.Length());
            decodedString = NormalizeUtf8Punctuation(decodedString);
            char* buf = new char[decodedString.Length() + 1];
            strcpy(buf, decodedString.c_str());
            AnsiToOem(buf, buf);
            decodedString = buf;
            delete[] buf;
        }
        else if (AnsiStartsText(Utf8QPHeader, encodedString))
        {
            decodedString = DecodeQuotedPrintableValue(encodedString, Utf8QPHeader.Length());
            decodedString = NormalizeUtf8Punctuation(decodedString);
            char* buf = new char[decodedString.Length() + 1];
            strcpy(buf, decodedString.c_str());
            AnsiToOem(buf, buf);
            decodedString = buf;
            delete[] buf;
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
