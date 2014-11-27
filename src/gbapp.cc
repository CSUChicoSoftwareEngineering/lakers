#include "gbapp.h"
#include "gui\views\gbframeview.h"
#include "sql\gbsql.h"

IMPLEMENT_APP(GBApp)

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
