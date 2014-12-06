#include "gui/views/gbdialoguseroptionsView.h"
#include "sql/gbsql.h"

#include <iostream>

using namespace std;

GBDialogUserOptionsView::GBDialogUserOptionsView(wxWindow *parent)
  : wxDialog(parent, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize) {

    wxStaticBox         *SelectDataBaseFileStaticBox;
    wxStaticBox         *CurrentDataBaseFileStaticBox;

    // Create Sizers
    m_pButtonSizer = new  wxBoxSizer(wxHORIZONTAL);
	m_pDialogSizer = new wxBoxSizer(wxVERTICAL);

	// Create Dialog
	SetClientSize(GB_USEROPTIONS_DIALOGSIZE);
	// Create Panel
	m_pGBDialogPanel = new wxPanel(this);

    CurrentDataBaseFileStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Current Database file (*.db) in use.", wxDefaultPosition, wxDefaultSize, 0);
    m_pCurrentDbFileStaticBoxSizer = new wxStaticBoxSizer(CurrentDataBaseFileStaticBox, wxHORIZONTAL);
    m_pCurrentDbFilePathTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CAPITALIZE, wxDefaultValidator);

	// Create Static Boxes
	SelectDataBaseFileStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select new Database file (*.db)", wxDefaultPosition, wxDefaultSize, 0);
    m_pSelectDbFileStaticBoxSizer = new wxStaticBoxSizer(SelectDataBaseFileStaticBox, wxHORIZONTAL);
    m_pSelectFileLocationCtrl = new wxFilePickerCtrl(m_pGBDialogPanel, ID_DbFileSelect, wxEmptyString, "Select Database file", "*.db", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator);
    m_pDbFilePathTextCtrl = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CAPITALIZE, wxDefaultValidator);

    m_pCurrentDbFileStaticBoxSizer->Add(m_pCurrentDbFilePathTextCtrl, 2, wxEXPAND  , 0);

    m_pSelectDbFileStaticBoxSizer->Add(m_pDbFilePathTextCtrl, 2, wxEXPAND  , 0);
    m_pSelectDbFileStaticBoxSizer->Add(m_pSelectFileLocationCtrl, 1, wxSHAPED | wxALIGN_RIGHT | wxALL, 2);

    // Create Button
	m_pSaveFileLocationButton = new wxButton(m_pGBDialogPanel, -1, "Save", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);
    m_pCloseButton = new wxButton(m_pGBDialogPanel, -1, "Close", wxDefaultPosition, wxDefaultSize, 0,wxDefaultValidator);

    m_pButtonSizer->Add(m_pSaveFileLocationButton, 1,  wxSHAPED | wxLEFT | wxALIGN_LEFT , 10);
    m_pButtonSizer->Add(m_pCloseButton, 1,  wxSHAPED | wxALIGN_RIGHT | wxRIGHT, 10);

	// Apply Sizers to Dialog
    m_pDialogSizer->Add(m_pCurrentDbFileStaticBoxSizer, 0,  wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pSelectDbFileStaticBoxSizer, 0,  wxEXPAND | wxALL, 2);
    m_pDialogSizer->Add(m_pButtonSizer, 0, wxEXPAND | wxTOP | wxALIGN_BOTTOM , 20);

	// Set m_pGridSizer as primary sizer
	m_pGBDialogPanel->SetSizer(m_pDialogSizer);

	// Connect Controller
	m_pCon = new GBDialogUserOptionsController(this);
	// Connect Events Handler(s) to Controller
    Bind(wxEVT_CLOSE_WINDOW, &GBDialogUserOptionsController::DialogIsBeingClosed, m_pCon);
    m_pCloseButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::CloseButtonWasClicked, m_pCon);
	m_pSelectFileLocationCtrl->Bind(wxEVT_FILEPICKER_CHANGED, &GBDialogUserOptionsController::FileHasBeenSelected, m_pCon);
	m_pSaveFileLocationButton->Bind(wxEVT_BUTTON, &GBDialogUserOptionsController::SaveFileLocationButtonWasClicked, m_pCon);

}

GBDialogUserOptionsView::~GBDialogUserOptionsView(){

}
