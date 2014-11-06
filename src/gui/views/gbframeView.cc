#include "gui\views\gbframeView.h"
#include "sql\gbsql.h"

GBFrameView::GBFrameView(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size)
{

	// Create File Menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_AddCourseMenuSelect, "&Add Course...\tCtrl-G", "Add a course to your GradeBook");
    menuFile->AppendSeparator();
    menuFile->Append(ID_AddAssignmentMenuSelect, "&Add Assignment...\tCtrl-J", "Add an assignment");
	menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to GradeBook!" );

	// Create Frame Sizers
	m_pCourseDropDownListSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pGBFrameSizer = new wxBoxSizer(wxVERTICAL);

	// Create Base Panel
    m_pGBFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), GBAPPSIZE, wxTAB_TRAVERSAL, "GBFramePanel");
	m_pGBFramePanel->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));//wxWHITE

	// Add CourseDropDownList and GridView to Panel
	m_pCourseComboBox = new wxComboBox(m_pGBFramePanel, ID_CourseDropDownList,  wxEmptyString, wxDefaultPosition, wxSize(200, 20));
	m_pCourseComboBox->SetEditable(false);

  	m_pGridView = new wxGrid(m_pGBFramePanel, ID_GridView, wxDefaultPosition, GBAPPSIZE, 0, "ID_GridView" );

	// Apply Sizer to CourseDropDownList and GridView
	m_pCourseDropDownListSizer->Add(m_pCourseComboBox, 0, wxLEFT | wxTOP, 25);
	m_pGBFrameSizer->Add(m_pCourseDropDownListSizer, 0 , 0);
	m_pGBFrameSizer->Add(m_pGridView, 0, wxEXPAND | wxALL, 25);

	// Set GBFrameSizer as primary sizer
	m_pGBFramePanel->SetSizer(m_pGBFrameSizer);

	// Connect Controller
	m_pCon = new GBFrameController(this);

	// Conencts Event Handle(s) to Controller
	Bind(wxEVT_MENU, &GBFrameController::OnExit, m_pCon, wxID_EXIT);
	Bind(wxEVT_MENU, &GBFrameController::OnAbout, m_pCon, wxID_ABOUT);
	Bind(wxEVT_MENU, &GBFrameController::AddCourse, m_pCon, ID_AddCourseMenuSelect);
	Bind(wxEVT_MENU, &GBFrameController::ModifyAssignments, m_pCon, ID_AddAssignmentMenuSelect);
	Bind(wxEVT_COMBOBOX, &GBFrameController::NewCourseSelected, m_pCon, ID_CourseDropDownList);

}
