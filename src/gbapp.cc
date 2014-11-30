#include "gbapp.h"
#include "gui/views/gbframeView.h"
#include "sql/gbsql.h"

#ifdef __GUI__
IMPLEMENT_APP(GBApp)
#endif

bool GBApp::OnInit() {
  GBSql::Instance()->Initialize("gb.db");

	GBFrameView *pGBBase = new GBFrameView("Grade Book", wxPoint(0,0), GBAPPSIZE);

	pGBBase->Show();

	SetTopWindow(pGBBase);

  return true;
}

int GBApp::OnExit() {
  GBSql::Instance()->Close();

  return 0;
}
