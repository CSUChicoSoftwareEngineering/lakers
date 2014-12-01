#ifndef _GBDIALOGCOURSE
#define _GBDIALOGCOURSE

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "gui/controllers/gbdialogcourseController.h"

#define GB_COURSE_DIALOGSIZE wxSize(350,500)

class  GBDialogCourseView : public wxDialog {

	public:
    GBDialogCourseView(wxWindow *parent);
    ~GBDialogCourseView();

    wxTextCtrl					*m_pCourseNameTextCtrl;
    wxFilePickerCtrl 			*m_pSelectFileLocationCtrl;
    wxCheckListBox				*m_pcsvFileViewListBox;
    wxButton					*m_pImportButton;

	private:
    // Member Variables
    GBDialogCourseController 	*m_pController;
    wxPanel						*m_pGBDialogPanel;

};

enum{
	ID_AddButton = 1,
	ID_FileSelect = 2,
	ID_StudentSelection = 3
};

#endif
