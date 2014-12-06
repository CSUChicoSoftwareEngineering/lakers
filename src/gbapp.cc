#include "gbapp.h"
#include "gui/views/gbframeView.h"
#include "sql/gbsql.h"
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <iostream>

using namespace std;
#ifdef __GUI__
IMPLEMENT_APP(GBApp)
#endif

bool GBApp::OnInit() {

  wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI";
  wxString ExecutablePath = wxStandardPaths::Get().GetExecutablePath();
  wxString DatabasePath;
  wxFileConfig *config;

  ifstream InFile(ini_filename);

  if(!InFile){

    config = new wxFileConfig( "", "", ini_filename);
    ExecutablePath.Replace("gbapp.exe","");
    DatabasePath = ExecutablePath + "gb.db";
    config->Write( wxT("/gbDataBasePath"),  DatabasePath );
    config->Flush();
    delete config;
  }
  else{

    config = new wxFileConfig( "", "", ini_filename);
    DatabasePath = config->Read(wxT("gbDataBasePath"), DatabasePath) ;
    delete config;
    InFile.close();
  }

  GBSql::Instance()->Initialize(DatabasePath);

  GBFrameView *pGBBase = new GBFrameView("Grade Book", wxPoint(0,0), GBAPPSIZE);

  pGBBase->Show();

  SetTopWindow(pGBBase);

    return true;
}

int GBApp::OnExit() {
  GBSql::Instance()->Close();

  return 0;
}
