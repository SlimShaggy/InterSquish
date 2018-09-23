//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ISSetup.res");
USEFORM("fISSetup.cpp", isMainForm);
USEFORM("fConfig.cpp", fSetup);
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
      Application->Initialize();
      Application->CreateForm(__classid(TisMainForm), &isMainForm);
     Application->Run();
    }
    catch (Exception &exception)
    {
       Application->ShowException(&exception);
    }
  return 0;
}

/*
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TisMainForm), &isMainForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
*/
//---------------------------------------------------------------------------
