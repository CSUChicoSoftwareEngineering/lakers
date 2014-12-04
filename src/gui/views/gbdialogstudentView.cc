#include <wx/gbsizer.h>

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
  : wxDialog(parent, wxID_ANY, wxT("Student"), wxDefaultPosition, wxDefaultSize),
		m_pStudentIDTextCtrl(NULL),
		m_pStudentFirstNameTextCtrl(NULL),
		m_pStudentLastNameTextCtrl(NULL),
		m_pModifyStudentGrid(NULL) {
	wxButton *button;
	wxStaticBoxSizer *idSizer;
	wxStaticBoxSizer *firstSizer;
	wxStaticBoxSizer *lastSizer;

	wxSize defaultTextCtrl(250, 25);
	wxGridBagSizer *sizer = new wxGridBagSizer(2, 2);

  if(style == 0){
		idSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Student Id");
		m_pStudentIDTextCtrl = new wxTextCtrl(idSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, defaultTextCtrl);
		idSizer->Add(m_pStudentIDTextCtrl, wxSizerFlags().Border(wxALL, 2));

		firstSizer = new wxStaticBoxSizer(wxVERTICAL, this, "First Name");
		m_pStudentFirstNameTextCtrl = new wxTextCtrl(firstSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, defaultTextCtrl);
		firstSizer->Add(m_pStudentFirstNameTextCtrl, wxSizerFlags().Border(wxALL, 2));
			
		lastSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Last Name");
		m_pStudentLastNameTextCtrl = new wxTextCtrl(lastSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, defaultTextCtrl);
		lastSizer->Add(m_pStudentLastNameTextCtrl, wxSizerFlags().Border(wxALL, 2));

		sizer->Add(idSizer, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALL, 2);
		sizer->Add(firstSizer, wxGBPosition(1, 0), wxGBSpan(1, 2), wxALL, 2);
		sizer->Add(lastSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALL, 2);

		m_pAddStudentButton = new wxButton(this, ID_AddStudentButton, "Add Student");
		sizer->Add(m_pAddStudentButton, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL | wxALIGN_RIGHT, 2);

		button = new wxButton(this, ID_CloseDialog, "Close");
		sizer->Add(button, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALL | wxALIGN_RIGHT, 2);

		// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);
    // Connect Events Handler(s) to Controller
    m_pAddStudentButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
		button->Bind(wxEVT_BUTTON, &GBDialogStudentView::OnCloseClicked, this);
    m_pStudentIDTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentFirstNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
    m_pStudentLastNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogStudentController::AddStudentButtonWasClicked, m_pCon);
  } else if(style == 1) {
    m_pModifyStudentGrid = new wxGrid(this, ID_ModifyStudentGrid, wxDefaultPosition, wxSize(400, 400));
		sizer->Add(m_pModifyStudentGrid, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALL, 2);

    m_pSaveStudentChangesButton = new wxButton(this, ID_SaveStudentChangesButton, "Save");
		sizer->Add(m_pSaveStudentChangesButton, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL, 2);

		button = new wxButton(this, ID_CloseDialog, "Close");
		button->Bind(wxEVT_BUTTON, &GBDialogStudentView::OnCloseClicked, this);
		sizer->Add(button, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 2);

		// Connect Controller
    m_pCon = new GBDialogStudentController(this, CourseTitle, style);

    // Connect Events Handler(s) to Controller
    m_pSaveStudentChangesButton->Bind(wxEVT_BUTTON, &GBDialogStudentController::SaveStudentChangesButtonWasClicked, m_pCon);
    m_pModifyStudentGrid->Bind(wxEVT_GRID_CELL_CHANGED, &GBDialogStudentController::GridCellChanged, m_pCon);
  }

	SetSizer(sizer);
	Fit();
}

GBDialogStudentView::~GBDialogStudentView(){
	if (m_pStudentIDTextCtrl != NULL) delete m_pStudentIDTextCtrl;
	if (m_pStudentFirstNameTextCtrl != NULL) delete m_pStudentFirstNameTextCtrl;
	if (m_pStudentLastNameTextCtrl != NULL) delete m_pStudentLastNameTextCtrl;
	if (m_pModifyStudentGrid != NULL) delete m_pModifyStudentGrid;
}

void GBDialogStudentView::OnCloseClicked(wxCommandEvent &event) {
	EndModal(0);
}
