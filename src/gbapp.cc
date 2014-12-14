#include "gbapp.h"
#include "gui/views/gbframeView.h"
#include "data/config.h"
#include "sql/gbsql.h"
#include <wx/string.h>
#include <iostream>
using namespace std;

using namespace std;
#ifdef __GUI__
IMPLEMENT_APP(GBApp)
#endif

bool GBApp::OnInit() {

  wxString DatabasePath ;//= Config::Instance()->GetDataBasePath(wxT("gbDataBasePath"), DatabasePath);
  DatabasePath = Config::Instance()->GetDataBasePath(wxT("gbDataBasePath"), DatabasePath);

  std::cout << DatabasePath << std::endl;

  GBSql::Instance()->Initialize(DatabasePath);

	if (!wxApp::OnInit()) {
		return false;
	}

  GBFrameView *pGBBase = new GBFrameView("Gradebook", wxPoint(0,0), GBAPPSIZE);

  pGBBase->Show();

  SetTopWindow(pGBBase);

    return true;
}

int GBApp::OnExit() {
  GBSql::Instance()->Close();

  return 0;
}

void GBApp::OnInitCmdLine(wxCmdLineParser &parser) {
	parser.AddOption("d", "dummy");
}

bool GBApp::OnCmdLineParsed(wxCmdLineParser &parser) {
	wxString database;

	if (parser.Found("d", &database)) {
		GBSql::Instance()->Close();
		GBSql::Instance()->Initialize(database);
		GBSql::Instance()->PopulateDummy();
	}

	return true;
}
