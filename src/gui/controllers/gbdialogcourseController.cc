#include "gui/controllers/gbdialogcourseController.h"
#include "sql/gbsql.h"
#include "gui/views/gbdialogcourseView.h"
#include "data/bbimporter.h"
#include "data/student.h"
#include <iostream>
#include <wx/msgdlg.h>
#include <cstdlib>

using namespace std;

GBDialogCourseController::GBDialogCourseController(GBDialogCourseView *view, int style)
  : m_pSql(GBSql::Instance()),
    m_pDialogView(view) {


  wxGrid *grid = m_pDialogView->m_pModifyCourseGrid;
  wxButton *SaveAssessmentChangesButton = m_pDialogView->m_pSaveCourseChangesButton;
  if( style == 0){

   (m_pDialogView->m_pcsvFileViewListBox)->Disable();
  }
  else if(style == 1){
    grid->CreateGrid(0, 1);
    grid->SetColLabelValue(0, "Course Name");
    LoadCourses();
  }

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
  * @brief  Loads the Assessment from the currently selected course into the grid view for editing.
  * @param  none.
  * @retval none.
  */
void GBDialogCourseController::LoadCourses(){

  wxGrid *grid = m_pDialogView->m_pModifyCourseGrid;

  //m_pCurrentCourse->ClearAssessments();
  m_courses.clear();

  if( m_pSql->SelectCourses(&m_courses) == -1 ) return;

  if(grid->GetNumberRows() == 0){

    grid->AppendRows(m_courses.size());
  }
  else{

    grid->ClearGrid();
  }

  // Populate Courses
  for (int i = 0; i < m_courses.size(); ++i) {

    Course *c = m_courses[i];

    // Populate Assessment Names
    for (int x = 0; x < grid->GetNumberCols(); ++x) {

      if(grid->GetColLabelValue(x).IsSameAs("Course Name")){
        grid->SetCellValue(i, x, c->Title());
      }
    }

    // Populate row labels
    grid->SetRowLabelValue(i, wxString::Format("%s", c->Title()));
  }

  // Refresh grid
  grid->SetRowLabelSize(wxGRID_AUTOSIZE);
  grid->AutoSize();
  grid->Refresh();

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
  * @brief  The "Save" Button was clicked so we will save any rows that need to be Updated.
  * @param  wxEVT_BUTTON
  * @retval none.
  */
void GBDialogCourseController::SaveCourseChangesButtonWasClicked(wxCommandEvent& event){

  SaveChanges();
  LoadCourses();
}

/**
  * @brief  This function will use the rows stored in m_RowsNeedToBeUpdated to
  *         commit an Update transaction for each row to the DataBase.
  * @param  none.
  * @retval none.
  */
void GBDialogCourseController::SaveChanges(){

  wxGrid *grid = m_pDialogView->m_pModifyCourseGrid;

  //if(m_pCurrentCourse != NULL){

    for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

      Course *c = m_courses[m_RowsNeedToBeUpdated[i]];

      for (int x = 0; x < grid->GetNumberCols(); ++x) {

        if(grid->GetColLabelValue(x).IsSameAs("Course Name")){

          c->SetTitle(grid->GetCellValue(m_RowsNeedToBeUpdated[i], x));
        }

      }
      m_pSql->UpdateCourse(*c);
    }

    m_RowsNeedToBeUpdated.clear();
  //}

}


/**
  * @brief  A cell in the grid view has changed and the row will be stored
  *         so an Update transaction to the DataBase can be committed.
  * @param  wxEVT_GRID_CELL_CHANGED
  * @retval none.
  */
void GBDialogCourseController::GridCellChanged(wxGridEvent& event){

  wxGrid *grid = m_pDialogView->m_pModifyCourseGrid;

  if(!RowAlreadyNeedsToBeUpdated(event.GetRow())){

    m_RowsNeedToBeUpdated.push_back(event.GetRow());
    grid->AutoSize();
    grid->Refresh();
  }

}

/**
  * @brief  If a row already needs to be Updated then return true, otherwise false.
  * @param  int: row
  * @retval bool: True, if row already needs to be Updated; False, otherwise.
  */
bool GBDialogCourseController::RowAlreadyNeedsToBeUpdated(int row){

  for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

    if(row == m_RowsNeedToBeUpdated[i]) return true;
  }

  return false;
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


