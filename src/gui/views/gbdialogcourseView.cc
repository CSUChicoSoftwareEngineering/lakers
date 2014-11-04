#include "gui\views\gbdialogcourseView.h"
#include "sql\gbsql.h"

GBDialogCourseView::GBDialogCourseView(wxWindow *parent){

	wxStaticBox				*CourseNameStaticBox;
	wxStaticBox				*CourseNumberStaticBox;
	wxStaticBox				*ImportStudentCSVStaticBox;
	wxStaticBox				*SelectStudentsToImportStaticBox;

	// Create Dialog
	m_pDialog = new  wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, GB_COURSE_DIALOGSIZE, wxDEFAULT_DIALOG_STYLE, "GBDialog");
	m_pDialog->SetTitle("Add Course(s)");
	m_pDialog->SetClientSize(GB_COURSE_DIALOGSIZE);
	// Create Panel
	m_pGBDialogPanel = new wxPanel(m_pDialog, wxID_ANY, wxPoint(0,0), GB_COURSE_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Static Boxes
	CourseNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Course Name", wxPoint(10,10), wxSize(325,50), 0,"Course Name");
	CourseNumberStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Course Number", wxPoint(10,75), wxSize(325,50), 0,"Course Number");
	SelectStudentsToImportStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select Students To Import", wxPoint(20,210), wxSize(325,200), 0,"Course Number");
	ImportStudentCSVStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Import Students (File: *.csv)", wxPoint(10,140), wxSize(325,50), 0,"Import Students");
	// Create TextCtrl and FileCtrl
	m_pCourseNameTextCtrl	= new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,30), wxSize(300,25), wxTE_CAPITALIZE, wxDefaultValidator, "CourseNameTextCtrl");
	m_pCourseNumberTextCtrl  = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,95), wxSize(300,25), wxTE_CAPITALIZE, wxDefaultValidator, "CourseNumberTextCtrl");
	m_pSelectFileLocationCtrl = new wxFilePickerCtrl(m_pGBDialogPanel, ID_FileSelect, wxEmptyString, "Select .csv file", "*.csv", wxPoint(20,160),  wxDefaultSize, wxFLP_DEFAULT_STYLE, wxDefaultValidator, "ImportStudentCSVFilePickerCtrl");
	// Create Button
	m_pImportButton = new wxButton(m_pGBDialogPanel, ID_AddButton, "Add", wxPoint(20, 430),wxDefaultSize, 0,wxDefaultValidator, "ImportButton");
	// Connect Controller
	m_pController = new GBDialogCourseController(this);
	// Connect Events Handler(s) to Controller
	m_pSelectFileLocationCtrl->Bind(wxEVT_FILEPICKER_CHANGED, &GBDialogCourseController::FileHasBeenSelected, m_pController);
	m_pImportButton->Bind(wxEVT_BUTTON, &GBDialogCourseController::AddButtonWasClicked, m_pController);

}

GBDialogCourseView::~GBDialogCourseView(){
	delete m_pController, m_pDialog, m_pGBDialogPanel, m_pCourseNameTextCtrl,
			m_pCourseNumberTextCtrl, m_pSelectFileLocationCtrl, m_pImportButton;
}