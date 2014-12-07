#ifndef _GBDIALOGUSEROPTIONSCONTROLLER
#define _GBDIALOGUSEROPTIONSCONTROLLER

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/radiobox.h>
#include <wx/checklst.h>
#include "sql/gbsql.h"

//#define GB_COURSE_DIALOGSIZE wxSize(350,500)

class GBDialogUserOptionsView;

class GBDialogUserOptionsController
{
  public:
	GBDialogUserOptionsController();
	GBDialogUserOptionsController(GBDialogUserOptionsView *view, int style);
	// Events
	void StudentFormatHasChanged(wxCommandEvent& event);
    void SaveFileLocationButtonWasClicked(wxCommandEvent& event);
    void CloseButtonWasClicked(wxCommandEvent& event);
    void FileHasBeenSelected(wxFileDirPickerEvent& event);
    void DialogIsBeingClosed(wxCloseEvent& event);

  private:

    GBSql *m_pSql;
    GBDialogUserOptionsView *m_pDialogView;
};

#endif
