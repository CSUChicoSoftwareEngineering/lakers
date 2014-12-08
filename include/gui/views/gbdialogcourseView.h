#ifndef _GBDIALOGCOURSE
#define _GBDIALOGCOURSE

#include <wx/dialog.h>
#include <wx/radiobox.h>
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
    wxButton					*m_pCloseButton;
    wxButton                    *m_pClearButton;
    wxRadioBox                  *m_pcsvFormatOptionsRadioBox;

	private:
    // Member Variables
    GBDialogCourseController 	*m_pController;
    wxPanel						*m_pGBDialogPanel;
    wxStaticBoxSizer            *m_pCourseNameStaticBoxSizer;
    wxStaticBoxSizer            *m_pStudenSelectToImportBoxSizer;
    wxStaticBoxSizer            *m_pImportStudentCSVBoxSizer;
    wxBoxSizer                  *m_pButtonSizer;
    wxBoxSizer                  *m_pDialogSizer;
    wxBoxSizer                  *m_pRadioSizer;
    wxArrayString               FormatOptions;
    const int                   NumberOfStudentNameFormatOptions = 2;

};

enum{
	ID_AddButton = 1,
	ID_FileSelect = 2,
	ID_StudentSelection = 3,
	ID_csvFormatOptions,

};

#endif
