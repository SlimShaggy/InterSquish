//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MakeKey.res");
USEFORM("mkMainForm.cpp", Form1);
USEFORM("mkTables.cpp", dmTables);
USEFORM("mkRandomInput.cpp", fRandomInput);
USELIB("C:\Program Files\Borland\CBuilder5\Projects\Lib\iuRSA.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TForm1), &Form1);
     Application->CreateForm(__classid(TdmTables), &dmTables);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
