#include "gui/views/gbdialogstudentView.h"
#include <wx/stattext.h>
GBDialogStudentView::GBDialogStudentView(){}

/**
  * @brief  Constructor to create a GBDialogStudentView. To display the view one must
  *         call the virtual function ShowModal().
  * @param  wxWindow *parent: The parent of the dialog.
  *         wxString CourseTitle: The course selected to add or modify Student(s).
  *         int style: When Style = 0 the view will create a view to Add a Student(s)
                       When Style = 1 the view will create a view to Modify Student(s).
  * @retval none.
  */
GBDialogStudentView::GBDialogStudentView(wxWindow *parent, wxString CourseTitle, int style)
  : wxDialog(parent, wxID_ANY, wxT("Student"), wxDefaultPosition, wxDefaultSize) {

  wxStaticBox         *StudentIDStaticBox;
  wxStaticBox         *StudentFirstNameStaticBox;
  wxStaticBox         *StudentLastNameStaticBox;

  if(style == 0){

    // Create  Sizers
	m_pDialogSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);

	// Create Dialog
    SetClientSize(GB_ADD_STUDENT_DIALOGSIZE);
	// Create Panel
    m_pGBDialogPanel = new wxPanel(this);

	// Create StaticBox, StaticBoxSize, and TextCtrl for Student ID
    StudentIDStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student ID", wxDefaultPosition, wxDefaultSize, 0,"StudentID");
    m_pStudentIDStaticBoxSizer = new wxStaticBoxSizer(StudentIDStaticBox, wxHORIZONTAL);
    m_pStudentIDTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE | wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentIDTextCtrl");

    // Create StaticBox, StaticBoxSize, and TextCtrl for Student First Name
    StudentFirstNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student First Name", wxDefaultPosition, wxDefaultSize, 0,"StudentFirstName");
    m_pStudentFirstNameBoxSizer = new wxStaticBoxSizer(StudentFirstNameStaticBox, wxHORIZONTAL);
    m_pStudentFirstNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE | wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentFirstNameTextCtrl");

    // Create StaticBox, StaticBoxSize, and TextCtrl for Student Last Name
    StudentLastNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Student Last Name", wxDefaultPosition, wxDefaultSize, 0,"StudentLastName");
    m_pStudentLastNameBoxSizer = new wxStaticBoxSizer(StudentLastNameStaticBox, wxHORIZONTAL);
    m_pStudentLastNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE |wxTE_PROCESS_ENTER, wxDefaultValidator, "StudentLastNameTextCtrl");

    // Create Save and Close Button
    m_pAddStudentButton = new wxButton(m_pGBDialogPanel, ID_AddStudentButton, "Add Student", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "AddStudentButton");
    m_pCloseButton = new wxButton(m_pGBDialogPanel, ID_CloseButton, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "CloseButton");

	// Apply Sizers to Buttons
    m_pButtonSizer->Add(m_pAddStudentButton, 1, wxSHAPED | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizer->Add(m_pCloseButton, 1, wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizers to StaticBox
    m_pStudentIDStaticBoxSizer->Add(m_pStudentIDTextCtrl, 1, wxEXPAND | wxBOTTOM, 10);
    m_pStudentFirstNameBoxSizer->Add(m_pStudentFirstNameTextCtrl, 1, wxEXPAND | wxBOTTOM , 10);
    m_pStudentLastNameBoxSizer->Add(m_pStudentLastNameTextCtrl, 1, wxEXPAND | wxBOTTOM , 10);

	// Apply Sizers to Dialog
    m_pDialogSizer->Add(m_pStudentIDStaticBoxSizer, 1, wxEXPAND | wxALL, 10);
    m_pDialogSizer->Add(m_pStudentFirstNameBoxSizer, 1, wxEXPAND | wxALL, 10);
    m_pDialogSizer->Add(m_pStudentLastNameBoxSizer, 1, wxEXPAND | wxALL, 10);
    m_pDialogSizer->Add(m_pButtonSizer, 1, wxEXPAND | wxSHAPED | wxBOTTOM | wxALIGN_BOTTOM , 10);

	// Set m_pGridSizer as primary sizer
	m_pGBDialogPanel->SetSizer(m_pDialogSizer);

	// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);
    // Connect Events Handler(s) to Controller
    m_pAddStudentButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::CloseButtonWasClicked, m_pCon);
    m_pStudentIDTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentFirstNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentLastNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
  }
  else if( style == 1){

    // Create Sizers
    m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);
	m_pGridSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDialogSizer = new wxBoxSizer(wxVERTICAL);

	// Create Dialog
    SetClientSize(GB_MODIFY_STUDENT_DIALOGSIZE);

	// Create Panel
    m_pGBDialogPanel = new wxPanel(this);

    m_pModifyStudentGrid = new wxGrid(m_pGBDialogPanel, ID_ModifyStudentGrid, wxDefaultPosition, wxDefaultSize, 0, "ID_GridView" );

    // Create Buttons
    m_pSaveStudentChangesButton = new wxButton(m_pGBDialogPanel, ID_SaveStudentChangesButton, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "SaveStudentChangesButton");
    m_pCloseButton = new wxButton(m_pGBDialogPanel, ID_CloseButton, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "CloseButton");

    // Apply Sizers to Buttons
    m_pButtonSizer->Add(m_pSaveStudentChangesButton, 1, wxSHAPED | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizer->Add(m_pCloseButton, 1, wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizer to GridView
	m_pGridSizer->Add(m_pModifyStudentGrid, 1, wxSHAPED, 0);

    // Apply Sizer to Dialog
    m_pDialogSizer->Add(m_pGridSizer, 1 , wxEXPAND ,  0);
    m_pDialogSizer->Add(m_pButtonSizer, 0, wxEXPAND | wxBOTTOM | wxALIGN_BOTTOM , 10);

	// Set m_pGridSizer as primary sizer
	m_pGBDialogPanel->SetSizer(m_pDialogSizer);

	// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);
    // Connect Events Handler(s) to Controller
	Bind(wxEVT_CLOSE_WINDOW, &GBDialogStudentController::DialogIsBeingClosed, m_pCon);
    m_pModifyStudentGrid->Bind(wxEVT_GRID_CELL_CHANGED, &GBDialogStudentController::GridCellChanged, m_pCon);
    m_pSaveStudentChangesButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::SaveStudentChangesButtonWasClicked, m_pCon);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::CloseButtonWasClicked, m_pCon);
  }

}

GBDialogStudentView::~GBDialogStudentView(){

  delete m_pGBDialogPanel, m_pGridSizer, m_pDialogSizer,
  m_pStudentIDTextCtrl, m_pStudentFirstNameTextCtrl, m_pStudentLastNameTextCtrl,
  m_pAddStudentButton, m_pSaveStudentChangesButton, m_pModifyStudentGrid;
}
