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


  if(style == 0){

    wxTextCtrl *currentDbPathTextCtrl = m_pDialogView->m_pCurrentDbFilePathTextCtrl;
    wxString DatabasePath ;
    DatabasePath = Config::Instance()->GetDataBasePath(wxT("gbDataBasePath"), DatabasePath);
    currentDbPathTextCtrl->SetValue( DatabasePath );
  }
  else if (style == 1){

    wxRadioBox  *Radio = m_pDialogView->m_pStudentNameFormatOptions;
    long SavedStudentNameFormat ;
    SavedStudentNameFormat = Config::Instance()->GetStudentFormat(wxT("StudentNameDisplayFormat"), SavedStudentNameFormat);
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

  if(!dbPathTextCtrl->IsEmpty()){

    Config::Instance()->SetDataBasePath( dbPathTextCtrl->GetValue() );
    wxString DatabasePath ;
    DatabasePath = Config::Instance()->GetDataBasePath(wxT("gbDataBasePath"), DatabasePath);
    GBSql::Instance()->Initialize( DatabasePath );
    m_pDialogView->Close();
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

  Config::Instance()->SetStudentFormat( Radio->GetSelection() );
  wxMessageBox( "Saved.", "Success", wxOK | wxICON_INFORMATION );
  m_pDialogView->Close();
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


