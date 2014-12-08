#include "gui/views/gbdialogcourseView.h"
#include "sql/gbsql.h"

/**
  * @brief  Constructor to create a GBDialogCourseView. To display the view one must
  *         call the virtual function ShowModal().
  * @param  wxWindow *parent: The parent of the dialog.
  * @retval none.
  */
GBDialogCourseView::GBDialogCourseView(wxWindow *parent)
  : wxDialog(parent, wxID_ANY, wxT("Add Course"), wxDefaultPosition, GB_COURSE_DIALOGSIZE) {

    wxStaticBox         *CourseNameStaticBox;
	wxStaticBox         *ImportStudentCSVStaticBox;
	wxStaticBox         *SelectStudentsToImportStaticBox;

    FormatOptions.Add("Moodle *.csv format");
    FormatOptions.Add("BlackBoard *.csv format");

    // Create Sizers
    m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);
	m_pDialogSizer = new wxBoxSizer(wxVERTICAL);
	m_pRadioSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create Dialog
	SetClientSize(GB_COURSE_DIALOGSIZE);
	// Create Panel
	m_pGBDialogPanel = new wxPanel(this);

	// Create Static Boxes
	CourseNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Course Name", wxDefaultPosition, wxDefaultSize, 0,"Course Name");
	m_pCourseNameStaticBoxSizer = new wxStaticBoxSizer(CourseNameStaticBox, wxHORIZONTAL);
    m_pCourseNameTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE, wxDefaultValidator);

    m_pcsvFormatOptionsRadioBox = new wxRadioBox(m_pGBDialogPanel,
                                                 ID_csvFormatOptions,
                                                 "Select *.csv Format",
                                                 wxDefaultPosition,
                                                 wxDefaultSize,
                                                 FormatOptions,
                                                 NumberOfStudentNameFormatOptions,
                                                 wxRA_SPECIFY_ROWS,
                                                 wxDefaultValidator);

    m_pRadioSizer->Add(m_pcsvFormatOptionsRadioBox, 1,  wxEXPAND | wxTOP | wxBOTTOM, 10);


	ImportStudentCSVStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Import Students (File: *.csv)", wxDefaultPosition, wxDefaultSize, 0,"Import Students");
    m_pImportStudentCSVBoxSizer = new wxStaticBoxSizer(ImportStudentCSVStaticBox, wxVERTICAL);
    m_pSelectFileLocationCtrl = new wxFilePickerCtrl(m_pGBDialogPanel, ID_FileSelect, wxEmptyString, "Select .csv file", "*.csv", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator, "ImportStudentCSVFilePickerCtrl");

    SelectStudentsToImportStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select Students To Import", wxDefaultPosition, wxDefaultSize, 0);
	m_pStudenSelectToImportBoxSizer = new wxStaticBoxSizer(SelectStudentsToImportStaticBox, wxVERTICAL);
    m_pcsvFileViewListBox = new  wxCheckListBox (m_pGBDialogPanel, ID_StudentSelection,  wxDefaultPosition, wxDefaultSize);


    m_pCourseNameStaticBoxSizer->Add(m_pCourseNameTextCtrl, 1, wxEXPAND | wxALL, 2);
    m_pImportStudentCSVBoxSizer->Add(m_pSelectFileLocationCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
    m_pStudenSelectToImportBoxSizer->Add(m_pcsvFileViewListBox, 1, wxEXPAND | wxALL, 2);

    // Create Button
	m_pImportButton = new wxButton(m_pGBDialogPanel, ID_AddButton, "Add", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator, "ImportButton");
    m_pCloseButton = new wxButton(m_pGBDialogPanel, -1, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);
    m_pClearButton = new wxButton(m_pGBDialogPanel, -1, "Clear", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);

    m_pButtonSizer->Add(m_pImportButton, 1, wxSHAPED | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizer->Add(m_pClearButton, 1, wxALIGN_LEFT , 0);
    m_pButtonSizer->Add(m_pCloseButton, 1, wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizers to Dialog
    m_pDialogSizer->Add(m_pCourseNameStaticBoxSizer, 0, wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pRadioSizer, 0, wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pImportStudentCSVBoxSizer, 0, wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pStudenSelectToImportBoxSizer, 1, wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pButtonSizer, 0, wxEXPAND | wxBOTTOM | wxALIGN_BOTTOM , 2);

	// Set m_pGridSizer as primary sizer
	m_pGBDialogPanel->SetSizer(m_pDialogSizer);

	// Connect Controller
	m_pController = new GBDialogCourseController(this);
	// Connect Events Handler(s) to Controller
    Bind(wxEVT_CLOSE_WINDOW, &GBDialogCourseController::DialogIsBeingClosed, m_pController);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogCourseController::CloseButtonWasClicked, m_pController);
	m_pSelectFileLocationCtrl->Bind(wxEVT_FILEPICKER_CHANGED, &GBDialogCourseController::FileHasBeenSelected, m_pController);
	m_pImportButton->Bind(wxEVT_BUTTON, &GBDialogCourseController::AddButtonWasClicked, m_pController);
    m_pClearButton->Bind(wxEVT_BUTTON, &GBDialogCourseController::ClearButtonWasClicked, m_pController);

}

GBDialogCourseView::~GBDialogCourseView(){
	delete m_pController, m_pGBDialogPanel, m_pCourseNameTextCtrl,
			m_pSelectFileLocationCtrl, m_pImportButton;
}
