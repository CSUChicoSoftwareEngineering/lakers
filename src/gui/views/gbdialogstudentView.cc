#include "gui\views\gbdialogstudentView.h"


GBDialogStudentView::GBDialogStudentView(){}

GBDialogStudentView::GBDialogStudentView(wxWindow *parent, wxString CourseTitle, int style)
  : wxDialog(parent, wxID_ANY, wxT("Student"), wxDefaultPosition, wxDefaultSize) {

  wxStaticBox         *StudentIDStaticBox;
  wxStaticBox         *StudentFirstNameStaticBox;
  wxStaticBox         *StudentLastNameStaticBox;

  if(style == 0){

	// Create Dialog
    SetClientSize(GB_ADD_STUDENT_DIALOGSIZE);
	// Create Panel
    m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), GB_ADD_STUDENT_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");

    StudentIDStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student ID", wxPoint(10,10), wxSize(325,50), 0,"StudentID");
    m_pStudentIDTextCtrl	= new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,30), wxSize(300,25), wxTE_CAPITALIZE | wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentIDTextCtrl");


    StudentFirstNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student First Name", wxPoint(10,60), wxSize(325,50), 0,"StudentFirstName");
    m_pStudentFirstNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,80), wxSize(300,25), wxTE_CAPITALIZE | wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentFirstNameTextCtrl");


    StudentLastNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student Last Name", wxPoint(10,120), wxSize(325,50), 0,"StudentLastName");
    m_pStudentLastNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,140), wxSize(300,25), wxTE_CAPITALIZE |wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentLastNameTextCtrl");

    m_pAddStudentButton = new wxButton(m_pGBDialogPanel, ID_AddStudentButton, "Add Student", wxPoint(20, 180),wxDefaultSize, 0,wxDefaultValidator, "AddStudentButton");
	// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);
    // Connect Events Handler(s) to Controller
    m_pAddStudentButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentIDTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentFirstNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentLastNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
  }
  else if( style == 1){

    // Create Dialog Sizers
	m_pGridSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDialogSizer = new wxBoxSizer(wxVERTICAL);

	// Create Dialog
    SetClientSize(GB_MODIFY_STUDENT_DIALOGSIZE);
    //SetWindowStyle(wxRESIZE_BORDER);

	// Create Panel
    m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, "ID_GBDialogPanel");

    m_pModifyStudentGrid = new wxGrid(m_pGBDialogPanel, ID_ModifyStudentGrid, wxDefaultPosition, GB_MODIFY_STUDENT_DIALOGSIZE, 0, "ID_GridView" );
    m_pSaveStudentChangesButton = new wxButton(m_pGBDialogPanel, ID_SaveStudentChangesButton, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "SaveStudentChangesButton");

	// Apply Sizer to Button and GridView
	m_pGridSizer->Add(m_pModifyStudentGrid, 1, 0);

    m_pDialogSizer->Add(m_pGridSizer, 1 , 0);
    m_pDialogSizer->Add(m_pSaveStudentChangesButton,0, wxSHAPED | wxALL, 10);

	// Set m_pGridSizer as primary sizer
	m_pGBDialogPanel->SetSizer(m_pDialogSizer);
	//m_pDialogSizer->Fit(this);

	// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);
    // Connect Events Handler(s) to Controller
	Bind(wxEVT_CLOSE_WINDOW, &GBDialogStudentController::DialogIsBeingClosed, m_pCon);
    m_pModifyStudentGrid->Bind(wxEVT_GRID_CELL_CHANGED, &GBDialogStudentController::GridCellChanged, m_pCon);
    m_pSaveStudentChangesButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::SaveStudentChangesButtonWasClicked, m_pCon);
  }

}

GBDialogStudentView::~GBDialogStudentView(){

  delete m_pGBDialogPanel, m_pGridSizer, m_pDialogSizer,
  m_pStudentIDTextCtrl, m_pStudentFirstNameTextCtrl, m_pStudentLastNameTextCtrl,
  m_pAddStudentButton, m_pSaveStudentChangesButton, m_pModifyStudentGrid;
}
