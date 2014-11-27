#include "gui\views\gbdialogassessmentView.h"
#include "sql\gbsql.h"


GBDialogAssessmentView::GBDialogAssessmentView() { }

GBDialogAssessmentView::GBDialogAssessmentView(wxWindow *parent): wxDialog(parent, wxID_ANY, wxT("Modify Assessment(s)"), wxDefaultPosition, GB_ASSIGNMENT_DIALOGSIZE)
{
	wxStaticBox				*CourseSelectStaticBox;
	wxStaticBox 			*ModifyAssignmentStaticBox;

	// Create Panel
	m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), GB_ASSIGNMENT_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Static Boxes
	CourseSelectStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select Course", wxPoint(10,10), wxSize(325,75), 0,"Select Course");
	// Create ComboBox
	m_pCourseComboBox = new wxComboBox(m_pGBDialogPanel, ID_CourseDropDownListAssessment, "", wxPoint(20,40), wxSize(100, 25));
	// Create Assignment EditableListBox
	m_pModifyAssignmentListBox = new wxEditableListBox(m_pGBDialogPanel, ID_ModifyAssignmentListBox, "Modify Assessment(s)", wxPoint(10,100), wxSize(325, 355), wxEL_DEFAULT_STYLE | wxEL_NO_REORDER, "Modify Assessment(s)");
	// Connect Controller
	m_pCon = new GBDialogAssessmentController(this);
	// Connect Event Handler to Controller
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_BEGIN_LABEL_EDIT, &GBDialogAssessmentController::BeginAssessmentLabelEdit, m_pCon);
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_END_LABEL_EDIT, &GBDialogAssessmentController::EndAssessmentLabelEdit, m_pCon);
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_DELETE_ITEM, &GBDialogAssessmentController::AssessmentHasBeenDeleted, m_pCon);

}
GBDialogAssessmentView::GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle): wxDialog(parent, wxID_ANY, wxT("Modify Assessment(s)"), wxDefaultPosition, GB_ASSIGNMENT_DIALOGSIZE){


	wxStaticBox				*CourseSelectStaticBox;
	wxStaticBox 			*ModifyAssignmentStaticBox;

	// Create Panel
	m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), GB_ASSIGNMENT_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Assignment EditableListBox
	m_pModifyAssignmentListBox = new wxEditableListBox(m_pGBDialogPanel, ID_ModifyAssignmentListBox, "Modify Assessment(s)", wxPoint(10,10), wxSize(325, 450), wxEL_DEFAULT_STYLE | wxEL_NO_REORDER, "Modify Assessment(s)");
	// Connect Controller
	m_pCon = new GBDialogAssessmentController(this, CourseTitle);
	// Connect Event Handler to Controller
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_BEGIN_LABEL_EDIT, &GBDialogAssessmentController::BeginAssessmentLabelEdit, m_pCon);
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_END_LABEL_EDIT, &GBDialogAssessmentController::EndAssessmentLabelEdit, m_pCon);
	m_pModifyAssignmentListBox->Bind(wxEVT_LIST_DELETE_ITEM, &GBDialogAssessmentController::AssessmentHasBeenDeleted, m_pCon);
	Bind(wxEVT_CLOSE_WINDOW, &GBDialogAssessmentController::DialogIsBeingClosed, m_pCon);

}

