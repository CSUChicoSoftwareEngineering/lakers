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

      SetClientSize(GB_ADD_ASSESSNMENT_DIALOGSIZE);
	  // Create Panel
	  m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), GB_ADD_ASSESSNMENT_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
      AssessmentNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Assessment Name", wxPoint(10,10), wxSize(325,50), 0,"AssessmentName");
      m_pAssessmentNameTextCtrl	= new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,30), wxSize(300,25), wxTE_CAPITALIZE | wxTE_PROCESS_ENTER, wxDefaultValidator, "AssessmentNameTextCtrl");
      m_pAddAssessmentButton = new wxButton(m_pGBDialogPanel, ID_AddAssessmentButton, "Add Assessment", wxPoint(20, 180),wxDefaultSize, 0,wxDefaultValidator, "AddAssessmentButton");
      // Connect Controller
      m_pCon = new GBDialogAssessmentController(this, CourseTitle, style);
	  // Connect Event Handler to Controller
	  Bind(wxEVT_CLOSE_WINDOW, &GBDialogAssessmentController::DialogIsBeingClosed, m_pCon);
      m_pAssessmentNameTextCtrl->Bind(wxEVT_TEXT_ENTER, &GBDialogAssessmentController::AddAssessmentButtonWasClicked, m_pCon);
      m_pAddAssessmentButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::AddAssessmentButtonWasClicked, m_pCon);
	}
	else if(style == 1){

      // Create Dialog Sizers
	  m_pGridSizer = new wxBoxSizer(wxHORIZONTAL);
	  m_pDialogSizer = new wxBoxSizer(wxVERTICAL);

      SetClientSize(GB_MODIFY_ASSESSNMENT_DIALOGSIZE);
	  // Create Panel
	  m_pGBDialogPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
      // Create Grid
      m_pModifyAssessmentGrid = new wxGrid(m_pGBDialogPanel, ID_ModifyAssessmentGrid, wxDefaultPosition, GB_MODIFY_ASSESSNMENT_DIALOGSIZE, 0, "ID_GridView" );
	  m_pSaveAssessmentChangesButton = new wxButton(m_pGBDialogPanel, ID_SaveAssessmentChangesButton, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "SaveAssessmentChangesButton");
	  // Apply Sizer to Button and GridView
	  m_pGridSizer->Add(m_pModifyAssessmentGrid, 1, 0);
      m_pDialogSizer->Add(m_pGridSizer, 1 , 0);
      m_pDialogSizer->Add(m_pSaveAssessmentChangesButton,0, wxSHAPED | wxALL, 10);
	  // Set m_pGridSizer as primary sizer
	  m_pGBDialogPanel->SetSizer(m_pDialogSizer);
	  // Connect Controller
	  m_pCon = new GBDialogAssessmentController(this, CourseTitle, style);
	  // Connect Event Handler to Controller
	  Bind(wxEVT_CLOSE_WINDOW, &GBDialogAssessmentController::DialogIsBeingClosed, m_pCon);
      m_pModifyAssessmentGrid->Bind(wxEVT_GRID_CELL_CHANGED, &GBDialogAssessmentController::GridCellChanged, m_pCon);
      m_pSaveAssessmentChangesButton->Bind(wxEVT_BUTTON, &GBDialogAssessmentController::SaveAssessmentChangesButtonWasClicked, m_pCon);
	}
}

