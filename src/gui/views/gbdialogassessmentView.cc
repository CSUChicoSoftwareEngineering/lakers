#include "gui/views/gbdialogassessmentView.h"
#include "sql/gbsql.h"

// Default Constructor
GBDialogAssessmentView::GBDialogAssessmentView() { }

/**
  * @brief  Constructor to create a GBDialogAssessmentView. To display the view one must
  *         call the virtual function ShowModal().
  * @param  wxWindow *parent: The parent of the dialog.
  *         wxString CourseTitle: The course selected to add or modify Assessment(s).
  *         int style: When Style = 0 the view will create a view to Add an Assessment
                       When Style = 1 the view will create a view to Modify Assessment(s).
  * @retval none.
  */
GBDialogAssessmentView::GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle, int style)
  : wxDialog(parent, wxID_ANY, wxT("Modify Assessment(s)"), wxDefaultPosition, wxDefaultSize){

	wxStaticBox				*AssessmentNameStaticBox;

	if(style == 0){

      // Create  Sizers
	  m_pDialogSizer = new wxBoxSizer(wxVERTICAL);
      m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);

      SetClientSize(GB_ADD_ASSESSNMENT_DIALOGSIZE);

	  // Create Panel
	  m_pGBDialogPanel = new wxPanel(this);

      // Create StaticBox, StaticBoxSize, and TextCtrl for Assessment Name
      AssessmentNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Assessment Name", wxDefaultPosition, wxDefaultSize, 0, "AssessmentName");
      m_pStudentLastNameBoxSizer = new wxStaticBoxSizer(AssessmentNameStaticBox, wxHORIZONTAL);
      m_pAssessmentNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE |wxTE_PROCESS_ENTER, wxDefaultValidator);

      // Create Buttons
      m_pAddAssessmentButton = new wxButton(m_pGBDialogPanel, ID_AddAssessmentButton, "Add Assessment",  wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "AddAssessmentButton");
      m_pCloseButton = new wxButton(m_pGBDialogPanel, ID_CloseAssessmentButton, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "CloseButton");

      // Apply Sizers to BoxSizer
      m_pStudentLastNameBoxSizer->Add(m_pAssessmentNameTextCtrl, 1, wxEXPAND | wxALL, 2);

	  // Apply Sizers to Buttons
      m_pButtonSizer->Add(m_pAddAssessmentButton, 1, wxSHAPED | wxLEFT | wxALIGN_LEFT , 2);
      m_pButtonSizer->Add(m_pCloseButton, 1, wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 2);

	  // Apply Sizers to Dialog
      m_pDialogSizer->Add(m_pStudentLastNameBoxSizer, 0, wxEXPAND | wxALL, 2);
      m_pDialogSizer->Add(m_pButtonSizer, 0, wxEXPAND | wxALL | wxALIGN_BOTTOM , 2);

	  // Set m_pGridSizer as primary sizer
	  m_pGBDialogPanel->SetSizer(m_pDialogSizer);

      // Connect Controller
      m_pCon = new GBDialogAssessmentController(this, CourseTitle, style);
	  // Connect Event Handler to Controller
	  Bind(wxEVT_CLOSE_WINDOW, &GBDialogAssessmentController::DialogIsBeingClosed, m_pCon);
      m_pAssessmentNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogAssessmentController::AddAssessmentButtonWasClicked, m_pCon);
      m_pAddAssessmentButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::AddAssessmentButtonWasClicked, m_pCon);
      m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::CloseButtonWasClicked, m_pCon);
	}
	else if(style == 1){

      // Create Dialog Sizers
	  m_pGridSizer = new wxBoxSizer(wxVERTICAL);
	  m_pDialogSizer = new wxBoxSizer(wxVERTICAL);
      m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);

      SetClientSize(GB_MODIFY_ASSESSNMENT_DIALOGSIZE);

	  // Create Panel
	  m_pGBDialogPanel = new wxPanel(this);

      // Create Grid
      m_pModifyAssessmentGrid = new wxGrid(m_pGBDialogPanel, ID_ModifyAssessmentGrid, wxDefaultPosition, wxDefaultSize, 0, "ID_GridView" );

	  // Create Buttons
	  m_pSaveAssessmentChangesButton = new wxButton(m_pGBDialogPanel, ID_SaveAssessmentChangesButton, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "SaveAssessmentChangesButton");
      m_pCloseButton = new wxButton(m_pGBDialogPanel, ID_CloseAssessmentButton, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "CloseButton");

      // Apply Sizers to Buttons
      m_pButtonSizer->Add(m_pSaveAssessmentChangesButton, 1, wxSHAPED | wxLEFT | wxALIGN_LEFT , 2);
      m_pButtonSizer->Add(m_pCloseButton, 1, wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 2);

	  // Apply Sizer to GridView
	  m_pGridSizer->Add(m_pModifyAssessmentGrid, 1, wxEXPAND , 2);

      // Apply Sizer to Dialog
      m_pDialogSizer->Add(m_pGridSizer, 1 , wxEXPAND ,  2);
      m_pDialogSizer->Add(m_pButtonSizer, 0, wxEXPAND | wxALL | wxALIGN_BOTTOM , 2);

	  // Set m_pDialogSizer as primary sizer
	  m_pGBDialogPanel->SetSizer(m_pDialogSizer);

	  // Connect Controller
	  m_pCon = new GBDialogAssessmentController(this, CourseTitle, style);
	  // Connect Event Handler to Controller
	  Bind(wxEVT_CLOSE_WINDOW, &GBDialogAssessmentController::DialogIsBeingClosed, m_pCon);
      m_pModifyAssessmentGrid->Bind(wxEVT_GRID_CELL_CHANGED, &GBDialogAssessmentController::GridCellChanged, m_pCon);
      m_pSaveAssessmentChangesButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::SaveAssessmentChangesButtonWasClicked, m_pCon);
      m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::CloseButtonWasClicked, m_pCon);
	}
}

