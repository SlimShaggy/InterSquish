//---------------------------------------------------------------------------

#ifndef CmdLineH
#define CmdLineH
//#define __USING_STD_NAMES__
#include <string>
#include <list>
using namespace std;
//---------------------------------------------------------------------------
struct TCmdLineSwitch
{
  string Name;
  string Value;
};
//---------------------------------------------------------------------------
class TCommandLine
{
list <TCmdLineSwitch> SwitchesList;
public:  
  __fastcall TCommandLine();
  __fastcall ~TCommandLine();
  bool __fastcall SwitchExists(char *SwitchName);
  string __fastcall ValueByName(const string Name);
};
//---------------------------------------------------------------------------
#endif
