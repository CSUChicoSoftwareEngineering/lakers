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
#define GB_ADD_ASSESSNMENT_DIALOGSIZE wxSize(350,250)

class GBDialogAssessmentView: public wxDialog
{
	friend class GBDialogAssessmentController;
	public:
	GBDialogAssessmentView();
	GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle, int style);
	~GBDialogAssessmentView()
		{delete m_pCon, m_pGBDialogPanel, m_pCourseComboBox, m_pModifyAssignmentListBox;}

    wxGrid        *m_pModifyAssessmentGrid;
    wxTextCtrl    *m_pAssessmentNameTextCtrl;
    wxButton      *m_pAddAssessmentButton;
	wxButton      *m_pSaveAssessmentChangesButton;

	protected:
	GBDialogAssessmentController	*m_pCon;
	wxPanel							*m_pGBDialogPanel;
	wxComboBox 						*m_pCourseComboBox;
	wxEditableListBox				*m_pModifyAssignmentListBox;
    wxBoxSizer                      *m_pGridSizer;
    wxBoxSizer                      *m_pDialogSizer;

};

enum {
	ID_CourseDropDownListAssessment = 1,
	ID_ModifyAssignmentListBox = 2,
	ID_ModifyAssessmentGrid = 3,
	ID_AddAssessmentButton = 4,
	ID_SaveAssessmentChangesButton = 5,
};



#endif
