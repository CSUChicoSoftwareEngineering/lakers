#include "gui/controllers/gbdialoguseroptionsController.h"
#include "gui/views/gbdialoguseroptionsView.h"
#include "sql/gbsql.h"
#include "data/student.h"
#include <iostream>
#include <wx/msgdlg.h>

using namespace std;

GBDialogUserOptionsController::GBDialogUserOptionsController(){}


GBDialogUserOptionsController::GBDialogUserOptionsController(GBDialogUserOptionsView *view, int style)
  : m_pSql(GBSql::Instance()),
    m_pDialogView(view) {


  wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI";
  wxString ExecutablePath = wxStandardPaths::Get().GetExecutablePath();
  wxString DatabasePath ;
  wxFileConfig *config;

  if(style == 0){

    wxTextCtrl *currentDbPathTextCtrl = m_pDialogView->m_pCurrentDbFilePathTextCtrl;
    config = new wxFileConfig( "", "", ini_filename);
    DatabasePath = config->Read(wxT("gbDataBasePath"), DatabasePath) ;
    delete config;
    currentDbPathTextCtrl->SetValue( DatabasePath );
  }
  else if (style == 1){

    wxRadioBox  *Radio = m_pDialogView->m_pStudentNameFormatOptions;
    long SavedStudentNameFormat;
    config = new wxFileConfig( "", "", ini_filename);
    DatabasePath = config->Read(wxT("gbDataBasePath"), DatabasePath) ;
    SavedStudentNameFormat = config->Read(wxT("StudentNameDisplayFormat"), SavedStudentNameFormat) ;
    delete config;
    Radio->SetSelection(  SavedStudentNameFormat );

  }


}

/**
  * @brief  The "Save" Button was clicked, therefore the file path will be store
  * @param  wxCommandEvent wxEVT_BUTTON: An event from a button.
  * @retval none.
  */
void GBDialogUserOptionsController::SaveFileLocationButtonWasClicked(wxCommandEvent& event){

  wxTextCtrl *dbPathTextCtrl = m_pDialogView->m_pDbFilePathTextCtrl;
  wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI";
  wxString ExecutablePath = wxStandardPaths::Get().GetExecutablePath();
  wxFileConfig *config;

  if(!dbPathTextCtrl->IsEmpty()){

    config = new wxFileConfig( "","", ini_filename);
    config->Write( wxT("/gbDataBasePath"),  dbPathTextCtrl->GetValue() );
    config->Flush();
    delete config;
    m_pDialogView->Close();
    wxMessageBox( "Please restart program for Database change to take place.", "Warning", wxOK | wxICON_INFORMATION );
  }
  else
  {

    wxMessageBox( "Please select a Database file (*.db) to use.", "Error", wxOK | wxICON_INFORMATION );
  }

}

/**
  * @brief  The "Browse" Button was clicked and a file was selected.
  * @param  wxFileDirPickerEvent wxEVT_FILEPICKER_CHANGED: An event from a FileLocationCtrl.
  * @retval none.
  */
void GBDialogUserOptionsController::FileHasBeenSelected(wxFileDirPickerEvent& event){
	// Handle Event

    wxTextCtrl *dbPathTextCtrl = m_pDialogView->m_pDbFilePathTextCtrl;
    dbPathTextCtrl->SetValue(event.GetPath());
}


/**
  * @brief  The "Close" Button was clicked, therefore the dialog will be closed.
  * @param  wxCommandEvent wxEVT_BUTTON: An event from a button.
  * @retval none.
  */
void GBDialogUserOptionsController::CloseButtonWasClicked(wxCommandEvent& event){

  m_pDialogView->Close();
}


void GBDialogUserOptionsController::StudentFormatHasChanged(wxCommandEvent& event){

  wxRadioBox  *Radio = m_pDialogView->m_pStudentNameFormatOptions;
  cout << "Radio" << endl;
  cout << Radio->GetSelection() << endl;

  wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI";
  wxFileConfig *config = new wxFileConfig( "","", ini_filename);

    config->Write( wxT("/StudentNameDisplayFormat"),  Radio->GetSelection() );
    config->Flush();
    delete config;

}

/**
  * @brief  Dialog is being close by the User or by the programmer.
  * @param  wxCloseEvent wxEVT_CLOSE_WINDOW: An event from a window/dialog being closed.
  * @retval none.
  */
void GBDialogUserOptionsController::DialogIsBeingClosed(wxCloseEvent& event){

  m_pDialogView->EndModal(0);
  m_pDialogView->Destroy();
}


