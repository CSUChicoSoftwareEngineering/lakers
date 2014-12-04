#ifndef _GBDIALOGASSESSMENT
#define _GBDIALOGASSESSMENT

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/editlbox.h>
#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include "gui/controllers/gbdialogassessmentController.h"
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/sizer.h>

#define GB_MODIFY_ASSESSNMENT_DIALOGSIZE wxSize(350,500)
#define GB_ADD_ASSESSNMENT_DIALOGSIZE wxSize(350,100)

class GBDialogAssessmentView: public wxDialog
{
	public:
	GBDialogAssessmentView();
	GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle, int style);
	~GBDialogAssessmentView()
		{delete m_pCon, m_pGBDialogPanel;}

    wxGrid        *m_pModifyAssessmentGrid;
    wxTextCtrl    *m_pAssessmentNameTextCtrl;
    wxButton      *m_pAddAssessmentButton;
	wxButton      *m_pSaveAssessmentChangesButton;
	wxButton      *m_pCloseButton;

	private:
	GBDialogAssessmentController	*m_pCon;
	wxPanel							*m_pGBDialogPanel;
    wxBoxSizer                      *m_pGridSizer;
    wxBoxSizer                      *m_pDialogSizer;
    wxBoxSizer                      *m_pButtonSizer;
    wxStaticBoxSizer                *m_pStudentLastNameBoxSizer;

};

enum {
	ID_CourseDropDownListAssessment = 1,
	ID_ModifyAssignmentListBox = 2,
	ID_ModifyAssessmentGrid = 3,
	ID_AddAssessmentButton = 4,
	ID_SaveAssessmentChangesButton = 5,
	ID_CloseAssessmentButton = 6,
};

#endif
