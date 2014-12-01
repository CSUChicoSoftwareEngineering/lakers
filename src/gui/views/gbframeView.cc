#include "gui/views/gbframeView.h"
#include "sql/gbsql.h"

GBFrameView::GBFrameView(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size)
{

	// Create File Menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
     // Create Student Menu
    wxMenu *menuStudent = new wxMenu;
    menuStudent->Append(ID_AddStudentMenuSelect, "&Add Student \tCtrl-S", "Add an individual to your GradeBook");
    menuStudent->AppendSeparator();
    menuStudent->Append(ID_ModifyStudentMenuSelect, "&Modify Student(s) ", "Modify student information in your GradeBook");
    // Create Course Menu
    wxMenu *menuCourse = new wxMenu;
    menuCourse->Append(ID_AddCourseMenuSelect, "&Add Course \tCtrl-C", "Add a course to your GradeBook");
    // Create Assessment Menu
    wxMenu *menuAssessment = new wxMenu;
    menuAssessment->Append(ID_AddAssignmentMenuSelect, "&Modify Assessments \tCtrl-A", "Add assessment(s) to your GradBook");
   // Create Help Menu
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    // Adds Menus to MenuBar
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuStudent, "&Student");
    menuBar->Append( menuCourse, "&Course" );
    menuBar->Append( menuAssessment, "&Assessments" );
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

	// Connects Event Handler(s) to Controller
	Bind(wxEVT_MENU, &GBFrameController::OnExit, m_pCon, wxID_EXIT);
	Bind(wxEVT_MENU, &GBFrameController::OnAbout, m_pCon, wxID_ABOUT);
	Bind(wxEVT_MENU, &GBFrameController::AddStudent, m_pCon, ID_AddStudentMenuSelect);
    Bind(wxEVT_MENU, &GBFrameController::ModifyStudent, m_pCon, ID_ModifyStudentMenuSelect);
	Bind(wxEVT_MENU, &GBFrameController::AddCourse, m_pCon, ID_AddCourseMenuSelect);
	Bind(wxEVT_MENU, &GBFrameController::ModifyAssignments, m_pCon, ID_AddAssignmentMenuSelect);
	Bind(wxEVT_COMBOBOX, &GBFrameController::NewCourseSelected, m_pCon, ID_CourseDropDownList);

}
