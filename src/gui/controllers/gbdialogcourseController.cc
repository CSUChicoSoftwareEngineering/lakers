#include "gui/controllers/gbdialogcourseController.h"
#include "sql/gbsql.h"
#include "gui/views/gbdialogcourseView.h"
#include "data/bbimporter.h"
#include "data/student.h"
#include <iostream>
#include <wx/msgdlg.h>
#include <cstdlib>

using namespace std;

GBDialogCourseController::GBDialogCourseController(GBDialogCourseView *view)
  : m_pSql(GBSql::Instance()),
    m_pDialogView(view) {

 (m_pDialogView->m_pcsvFileViewListBox)->Disable();

}

/**
  * @brief  The "Add Course" Button was clicked, therefore an Insert transaction to the DataBase
  *         will be committed.
  * @param  wxCommandEvent wxEVT_BUTTON: An event from a button.
  * @retval none.
  */
void GBDialogCourseController::AddButtonWasClicked(wxCommandEvent& event){

  wxTextCtrl *name = m_pDialogView->m_pCourseNameTextCtrl;
  wxString  ErrorMessage = wxString::Format("Course name is empty.");
  wxCheckListBox *StudentSelectionListBox = m_pDialogView->m_pcsvFileViewListBox;
  Student *importStudent;
  wxString StudentName;

  if (name->GetValue().IsEmpty()) {

     wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
    return;
  }

  Course c;

  c.SetTitle(name->GetValue());

  if (m_pSql->InsertCourse(c) == -1) {
    cout << "Failed to insert course" << endl;

    return;
  }

  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }

  for (int i = 0; i < m_courses.size(); ++i) {
    if (m_courses[i]->Title().IsSameAs(m_pDialogView->m_pCourseNameTextCtrl->GetValue())) {
        m_pCurrentCourse = m_courses[i];
    }
  }

  for(int i = 0; i < StudentSelectionListBox->GetCount(); ++i ){
    if(StudentSelectionListBox->IsChecked(i)){
			for (std::vector<Student*>::iterator it = csv_Ptr->begin(); it != csv_Ptr->end(); ++it){
				importStudent = *it;
				StudentName = wxString::Format("%s, %s", importStudent->Last() , importStudent->First());

				if(StudentSelectionListBox->GetString(i).IsSameAs(StudentName)) {

					cout << i << " Insert Result: " << m_pSql->InsertStudentIntoCourse(*importStudent , *m_pCurrentCourse) << endl;
				}
			}
		}
  }

	m_pDialogView->EndModal(0);
}

/**
  * @brief  The "Browse" Button was clicked and a file was selected.
  * @param  wxFileDirPickerEvent wxEVT_FILEPICKER_CHANGED: An event from a FileLocationCtrl.
  * @retval none.
  */
void GBDialogCourseController::FileHasBeenSelected(wxFileDirPickerEvent& event){
	// Handle Event
  wxCheckListBox *StudentSelectionListBox = m_pDialogView->m_pcsvFileViewListBox;
  wxRadioBox  *csvFormatRadioBox =  m_pDialogView->m_pcsvFormatOptionsRadioBox;
  BBImporter cur_Importer;
  wxString Path = event.GetPath();
  wxString  StudentName ;
  Student *importStudent;

  csv_Ptr = cur_Importer.GetCourse(Path.mb_str(), csvFormatRadioBox->GetSelection());

  StudentSelectionListBox->Enable();
  for (std::vector<Student*>::iterator it = csv_Ptr->begin(); it != csv_Ptr->end(); ++it){
    importStudent = *it;
    StudentName = wxString::Format("%s, %s", importStudent->Last() , importStudent->First());
    StudentSelection.Add(StudentName);
  }

  StudentSelectionListBox->InsertItems( StudentSelection , 0);

  for(int i = 0; i < StudentSelectionListBox->GetCount(); ++i ){

    StudentSelectionListBox->Check(i);
  }


}

/**
  * @brief  The "Clear" Button was clicked, therefore the object will be cleared.
  * @param  wxCommandEvent wxEVT_BUTTON: An event from a button.
  * @retval none.
  */
void GBDialogCourseController::ClearButtonWasClicked(wxCommandEvent& event){

  (m_pDialogView->m_pCourseNameTextCtrl)->Clear();
  (m_pDialogView->m_pcsvFileViewListBox)->Clear();
  StudentSelection.clear();
}


/**
  * @brief  The "Close" Button was clicked, therefore the dialog will be closed.
  * @param  wxCommandEvent wxEVT_BUTTON: An event from a button.
  * @retval none.
  */
void GBDialogCourseController::CloseButtonWasClicked(wxCommandEvent& event){

  m_pDialogView->Close();
}

/**
  * @brief  Makes the Database transactions when Dialog is being close by the User.
  * @param  wxCloseEvent wxEVT_CLOSE_WINDOW: An event from a window/dialog being closed.
  * @retval none.
  */
void GBDialogCourseController::DialogIsBeingClosed(wxCloseEvent& event){

  m_pDialogView->EndModal(0);
  m_pDialogView->Destroy();
}


