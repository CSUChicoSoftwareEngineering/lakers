#include "Main.h"
#include <wx/string.h>

wxBEGIN_EVENT_TABLE(BaseFrame, wxFrame)
    EVT_MENU(ID_AddCourseMenuSelect,   BaseFrame::AddCourse)
    EVT_MENU(wxID_EXIT,                BaseFrame::OnExit)
    EVT_MENU(wxID_ABOUT,               BaseFrame::OnAbout)
wxEND_EVENT_TABLE()


BaseFrame::BaseFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// create standard generic pbjects
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_AddCourseMenuSelect, "&Add Course...\tCtrl-G",
                     "Add a course to your GradeBook");
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

	// Applies BaseBoxSizer to BaseFrame and applies BaseFramePanel inside BaseBoxSizer.
    wxBoxSizer *BaseBoxSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel *BaseFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), gbAppSize, wxTAB_TRAVERSAL, "BaseFramePanel");
    BaseBoxSizer->Add(BaseFramePanel,0,0,0);
	
	// Puts dropdown and text control boxes in front sizer
	wxBoxSizer *FrontBoxSizer = new wxBoxSizer(wxVERTICAL);
	DropDown = new wxChoicebook(BaseFramePanel, ID_ChoiceBook, wxPoint(30,30), wxSize(150,20), 0, "DropDownChoice");
	FrontBoxSizer->Add(ID_ChoiceBook, 1, wxEXPAND | wxALL, 10);
	CourseDisplay = new wxTextCtrl(BaseFramePanel, ID_CourseDisplay, _("<Enter text here to open dialog box>"), wxPoint(100,100), wxSize(300,100), wxTE_MULTILINE, wxDefaultValidator, _T("ID_CourseDisplay"));
	FrontBoxSizer->Add(ID_CourseDisplay, 1, wxEXPAND | wxALL, 10);
	
	// Causes parents objects to fit
    BaseBoxSizer->Fit(this);
	FrontBoxSizer->Fit(BaseFramePanel);
	

}
void BaseFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void BaseFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "Grade Book Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}
void BaseFrame::AddCourse(wxCommandEvent& event)
{
    wxLogMessage("Dialog Box Screen Next ... needs development ");
}