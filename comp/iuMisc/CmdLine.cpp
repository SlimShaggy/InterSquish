//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CmdLine.h"
#include <algorithm>

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall SwitchSplit(AnsiString Switch, string &Name, string &Value)
{
char *pcSwitch=Switch.c_str();
  int iPos=Switch.Pos(":");
  if((*pcSwitch=='/') || (*pcSwitch=='-'))
  {
    pcSwitch++;
    iPos--;
  }
  if(iPos)
  {
    Name=string(pcSwitch,iPos-1);
    Value=string(pcSwitch+iPos);
  }
  else
  {
    Name=pcSwitch;
    Value="";
  }

}
//---------------------------------------------------------------------------
__fastcall TCommandLine::TCommandLine()
{
char *pcTmp;
TCmdLineSwitch cms;
  for(int i=1;i<=ParamCount();i++)
  {
    SwitchSplit(ParamStr(i), cms.Name, cms.Value);
    SwitchesList.insert(SwitchesList.end(),cms);
  }
}
//---------------------------------------------------------------------------
__fastcall TCommandLine::~TCommandLine()
{
}
//---------------------------------------------------------------------------
bool __fastcall TCommandLine::SwitchExists(char *SwitchName)
{

//SwitchesList.
}
//---------------------------------------------------------------------------
string __fastcall TCommandLine::ValueByName(const string Name)
{
  //TODO: Add your source code here
}
