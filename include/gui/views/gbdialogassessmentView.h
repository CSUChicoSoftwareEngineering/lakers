#ifndef _GBDIALOGASSESSMENT
#define _GBDIALOGASSESSMENT

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/editlbox.h>
#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include "gui\controllers\gbdialogassessmentController.h"


#define GB_ASSIGNMENT_DIALOGSIZE wxSize(350,500)

class GBDialogAssessmentView: public wxDialog
{
	friend class GBDialogAssessmentController;
	public:
	GBDialogAssessmentView();
	GBDialogAssessmentView(wxWindow *parent);
	GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle);
	~GBDialogAssessmentView()
		{delete m_pCon, m_pGBDialogPanel, m_pCourseComboBox, m_pModifyAssignmentListBox;}

	protected:
	GBDialogAssessmentController	*m_pCon;
	wxPanel							*m_pGBDialogPanel;
	wxComboBox 						*m_pCourseComboBox;
	wxEditableListBox				*m_pModifyAssignmentListBox;

};

enum {
	ID_CourseDropDownListAssessment = 1,
	ID_ModifyAssignmentListBox = 2,
};



#endif
