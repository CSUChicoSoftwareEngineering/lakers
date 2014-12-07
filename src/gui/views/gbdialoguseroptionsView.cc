#include "gui/views/gbdialoguseroptionsView.h"
#include "sql/gbsql.h"

#include <iostream>

using namespace std;

GBDialogUserOptionsView::GBDialogUserOptionsView(wxWindow *parent)
  : wxDialog(parent, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize) {

    m_pUserOptionsTabs = new wxNotebook(this,ID_OptionsTab);
    wxWindow *DbLocationWindow = ChangeDbLocation(m_pUserOptionsTabs, wxID_ANY);
    wxWindow *StudentNameFormatWindow = ChangeStudentNameFormat(m_pUserOptionsTabs, wxID_ANY);

    m_pUserOptionsTabs->AddPage(StudentNameFormatWindow ,"Student Name Format");
    m_pUserOptionsTabs->AddPage(DbLocationWindow ,"Database Location");

}

wxWindow *GBDialogUserOptionsView::ChangeStudentNameFormat(wxWindow *parent, wxWindowID id){

    wxStaticBox         *SelectStudentFormatStaticBox;
    wxStaticBoxSizer    *SelectStudentFormatBoxSizer;


    FormatOptions.Add("Last Name, First Name");
    FormatOptions.Add("First Name, Last Name");
    FormatOptions.Add("Student ID");

    m_pButtonSizerForChangeStudentNameFormatView = new  wxBoxSizer(wxHORIZONTAL);
	m_pWindowSizerForChangeStudentNameFormatView = new wxBoxSizer(wxVERTICAL);
	m_pRadioSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pStudentNameFormat = new wxWindow(parent, id);

    m_pStudentNameFormatOptions = new wxRadioBox(m_pStudentNameFormat,
                                                 ID_StudentNameFormatOptions,
                                                 "Change Student Name Format",
                                                 wxDefaultPosition,
                                                 wxDefaultSize,
                                                 FormatOptions,
                                                 NumberOfStudentNameFormatOptions,
                                                 wxRA_SPECIFY_ROWS,
                                                 wxDefaultValidator);

    m_pRadioSizer->Add(m_pStudentNameFormatOptions, 1,  wxEXPAND | wxTOP , 20);

      // Create Button
	m_pSaveStudentNameFormatButton = new wxButton(m_pStudentNameFormat, -1, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);
    m_pCloseButton = new wxButton(m_pStudentNameFormat, -1, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);

    m_pButtonSizerForChangeStudentNameFormatView->Add(m_pSaveStudentNameFormatButton, 0,  wxEXPAND | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizerForChangeStudentNameFormatView->Add(m_pCloseButton, 1,  wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizers to Window
    m_pWindowSizerForChangeStudentNameFormatView->Add(m_pRadioSizer, 0,  wxEXPAND | wxALL, 2);
    m_pWindowSizerForChangeStudentNameFormatView->Add(m_pButtonSizerForChangeStudentNameFormatView, 1, wxSHAPED | wxEXPAND | wxTOP | wxALIGN_BOTTOM , 20);

	// Set m_pWindowSizerForChangeStudentNameFormatView as primary sizer
	m_pStudentNameFormat->SetSizer(m_pWindowSizerForChangeStudentNameFormatView);

	// Connect Controller
	m_pCon = new GBDialogUserOptionsController(this, ChangeStudentNameFormatView);
	// Connect Events Handler(s) to Controller
    Bind(wxEVT_CLOSE_WINDOW, &GBDialogUserOptionsController::DialogIsBeingClosed, m_pCon);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::CloseButtonWasClicked, m_pCon);
	m_pSaveStudentNameFormatButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::StudentFormatHasChanged, m_pCon);


    return m_pStudentNameFormat;


}

wxWindow *GBDialogUserOptionsView::ChangeDbLocation(wxWindow *parent, wxWindowID id){

    wxStaticBox         *SelectDataBaseFileStaticBox;
    wxStaticBox         *CurrentDataBaseFileStaticBox;

    m_pDbLocation = new wxWindow(parent, id);

    // Create Sizers
    m_pButtonSizerForChangeDbLocationView = new  wxBoxSizer(wxHORIZONTAL);
	m_pWindowSizerForChangeDbLocationView = new wxBoxSizer(wxVERTICAL);

    CurrentDataBaseFileStaticBox =  new wxStaticBox(m_pDbLocation, wxID_ANY, "Current Database file (*.db) in use.", wxDefaultPosition, wxDefaultSize, 0);
    m_pCurrentDbFileStaticBoxSizer = new wxStaticBoxSizer(CurrentDataBaseFileStaticBox, wxHORIZONTAL);
    m_pCurrentDbFilePathTextCtrl = new wxTextCtrl(m_pDbLocation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CAPITALIZE, wxDefaultValidator);

	// Create Static Boxes
	SelectDataBaseFileStaticBox =  new wxStaticBox(m_pDbLocation, wxID_ANY, "Select new Database file (*.db)", wxDefaultPosition, wxDefaultSize, 0);
    m_pSelectDbFileStaticBoxSizer = new wxStaticBoxSizer(SelectDataBaseFileStaticBox, wxHORIZONTAL);
    m_pSelectFileLocationCtrl = new wxFilePickerCtrl(m_pDbLocation, ID_DbFileSelect, wxEmptyString, "Select Database file", "*.db", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator);
    m_pDbFilePathTextCtrl = new wxTextCtrl(m_pDbLocation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CAPITALIZE, wxDefaultValidator);

    m_pCurrentDbFileStaticBoxSizer->Add(m_pCurrentDbFilePathTextCtrl, 2, wxEXPAND , 0);

    m_pSelectDbFileStaticBoxSizer->Add(m_pDbFilePathTextCtrl, 2, wxEXPAND  , 0);
    m_pSelectDbFileStaticBoxSizer->Add(m_pSelectFileLocationCtrl, 1, wxSHAPED | wxALIGN_RIGHT | wxALL, 2);

    // Create Button
	m_pSaveFileLocationButton = new wxButton(m_pDbLocation, -1, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);
    m_pCloseButton = new wxButton(m_pDbLocation, -1, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);

    m_pButtonSizerForChangeDbLocationView->Add(m_pSaveFileLocationButton, 0,  wxEXPAND | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizerForChangeDbLocationView->Add(m_pCloseButton, 1,  wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizers to Dialog
    m_pWindowSizerForChangeDbLocationView->Add(m_pCurrentDbFileStaticBoxSizer, 0,  wxEXPAND | wxTOP, 20);
    m_pWindowSizerForChangeDbLocationView->Add(m_pSelectDbFileStaticBoxSizer, 0,  wxEXPAND | wxALL, 2);
    m_pWindowSizerForChangeDbLocationView->Add(m_pButtonSizerForChangeDbLocationView, 1, wxSHAPED | wxEXPAND | wxTOP | wxALIGN_BOTTOM , 20);

	// Set m_pGridSizer as primary sizer
	m_pDbLocation->SetSizer(m_pWindowSizerForChangeDbLocationView);

	// Connect Controller
	m_pCon = new GBDialogUserOptionsController(this, ChangeDbLocationView);
	// Connect Events Handler(s) to Controller
    Bind(wxEVT_CLOSE_WINDOW, &GBDialogUserOptionsController::DialogIsBeingClosed, m_pCon);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::CloseButtonWasClicked, m_pCon);
	m_pSelectFileLocationCtrl->Bind(wxEVT_FILEPICKER_CHANGED, &GBDialogUserOptionsController::FileHasBeenSelected, m_pCon);
	m_pSaveFileLocationButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::SaveFileLocationButtonWasClicked, m_pCon);

	return m_pDbLocation;

}

GBDialogUserOptionsView::~GBDialogUserOptionsView(){

}
