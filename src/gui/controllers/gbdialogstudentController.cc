#include "gui\controllers\gbdialogstudentController.h"
#include "gui\views\gbdialogstudentView.h"
#include "sql\gbsql.h"
#include <iostream>
#include <wx/msgdlg.h>

using namespace std;

// Default Constructor
GBDialogStudentController::GBDialogStudentController(){}

// Destructor
GBDialogStudentController::~GBDialogStudentController(){

  delete m_pCurrentCourse;
}

// Constructor 1
GBDialogStudentController::GBDialogStudentController(GBDialogStudentView *view, wxString CourseTitle, int style)
  : m_pSql(GBSql::Instance()),
    m_pDialogView(view) {

  wxGrid *grid = m_pDialogView->m_pModifyStudentGrid;


  if( GetCurrentCourse(CourseTitle) == -1){
     if(style == 0){

       (m_pDialogView->m_pAddStudentButton)->Disable();
     }
     else if(style == 1){

       grid->CreateGrid(0, 0);
       (m_pDialogView->m_pSaveStudentChangesButton)->Disable();

     }

    wxMessageBox( wxString::Format("Please select a course."), "Error", wxOK | wxICON_INFORMATION );
    return;
  }
  else{

    if(style == 1){

      grid->CreateGrid(0, 3);
      grid->SetColLabelValue(0, "Student ID");
      grid->SetColLabelValue(1, "First Name");
      grid->SetColLabelValue(2, "Last Name");
      LoadStudents();
    }
  }

 }

/**
  * @brief  Loads the students from the currently selected course into the grid view for editing.
  * @param  none.
  * @retval none.
  */
void GBDialogStudentController::LoadStudents(){

  wxGrid *grid = m_pDialogView->m_pModifyStudentGrid;

  if( m_pSql->SelectStudentsByCourse(*m_pCurrentCourse) == -1 ) return;

  grid->AppendRows(m_pCurrentCourse->StudentCount());

  // Populate student data
  for (int i = 0; i < m_pCurrentCourse->StudentCount(); ++i) {

    Student s = m_pCurrentCourse->GetStudent(i);

    // Populate assessments for students
    for (int x = 0; x < grid->GetNumberCols(); ++x) {

      if(grid->GetColLabelValue(x).IsSameAs("Student ID")){
        grid->SetCellValue(i, x, s.StudentId());
      }
      else if(grid->GetColLabelValue(x).IsSameAs("First Name")){
        grid->SetCellValue(i, x, s.First());
      }
      else if(grid->GetColLabelValue(x).IsSameAs("Last Name")){
        grid->SetCellValue(i, x, s.Last());
      }
    }

    // Populate row labels
    grid->SetRowLabelValue(i, wxString::Format("%s, %s", s.Last(), s.First()));
  }

  // Refresh grid
  grid->SetRowLabelSize(wxGRID_AUTOSIZE);
  grid->AutoSize();
  grid->Refresh();
}

/**
  * @brief  The "Add Student" Button was clicked, therefore an Insert transaction to the DataBase
  *         will be committed.
  * @param  wxEVT_BUTTON
  * @retval none.
  */
void GBDialogStudentController::AddStudentButtonWasClicked(wxCommandEvent& event){

  wxTextCtrl    *StudentId = m_pDialogView->m_pStudentIDTextCtrl;
  wxTextCtrl    *FirstName = m_pDialogView->m_pStudentFirstNameTextCtrl;
  wxTextCtrl    *LastName = m_pDialogView->m_pStudentLastNameTextCtrl;
  wxString      ErrorMessage;
  Student       s;

  if( StudentId->IsEmpty() || FirstName->IsEmpty() || LastName->IsEmpty() ||  m_pCurrentCourse == NULL  ){

        if( m_pCurrentCourse == NULL ){

            ErrorMessage = wxString::Format("Please select a course.");
        }
        else if(StudentId->IsEmpty()){

            ErrorMessage = wxString::Format("Please enter a Student ID.");
        }
        else if(FirstName->IsEmpty()){

            ErrorMessage = wxString::Format("Please enter a First Name.");
        }
        else{

            ErrorMessage = wxString::Format("Please enter a Last Name.");
        }

      wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
  }
  else{

    s.SetStudentId( StudentId->GetValue() );
    s.SetFirst( FirstName->GetValue() );
    s.SetLast( LastName->GetValue() );


    if( m_pSql->InsertStudentIntoCourse( s , *m_pCurrentCourse) == -1 ){    cerr << "Failed to insert student in course" << endl;}

    m_pDialogView->EndModal(0);
    m_pDialogView->Destroy();

  }

}

/**
  * @brief  Get the Current Course has selected from the main frame.
  * @param  wxString CourseTitle
  * @retval int: Returns the status of the Database transaction.
  *         Returns -1 if transaction fails or no course was selected.
  */
int GBDialogStudentController::GetCurrentCourse(wxString CourseTitle){

  if (m_pSql->SelectCourses(&m_courses) == -1) {
    m_pCurrentCourse == NULL;
  }

  if(!CourseTitle.IsEmpty() && m_courses.size() > 0){

	  for (int i = 0; i < m_courses.size(); ++i) {

		if (m_courses[i]->Title().IsSameAs(CourseTitle)) {
		  m_pCurrentCourse = m_courses[i];
		  return m_pSql->SelectAssessmentsByCourse(*m_pCurrentCourse);
		}
	  }
	}
  else{

      m_pCurrentCourse = NULL;
      return -1;
	}
}

/**
  * @brief  A cell in the grid view has changed and the row will be stored
  *         so an Update transaction to the DataBase can be committed.
  * @param  wxEVT_GRID_CELL_CHANGED
  * @retval none.
  */
void GBDialogStudentController::GridCellChanged(wxGridEvent& event){

  if(!RowAlreadyNeedsToBeUpdated(event.GetRow())){

    m_RowsNeedToBeUpdated.push_back(event.GetRow());
  }
}

/**
  * @brief  If a row already needs to be Updated then return true, otherwise false.
  * @param  int: row
  * @retval bool: True, if row already needs to be Updated; False, otherwise.
  */
bool GBDialogStudentController::RowAlreadyNeedsToBeUpdated(int row){

  for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

    if(row == m_RowsNeedToBeUpdated[i]) return true;

  }

  return false;
}

/**
  * @brief  The "Save" Button was clicked so we will save any rows that need to be Updated.
  * @param  wxEVT_BUTTON
  * @retval none.
  */
void GBDialogStudentController::SaveStudentChangesButtonWasClicked(wxCommandEvent& event){

  SaveChanges();
}

/**
  * @brief  This function will use the rows stored in m_RowsNeedToBeUpdated to
  *         commit an Update transaction for each row to the DataBase.
  * @param  none.
  * @retval none.
  */
void GBDialogStudentController::SaveChanges(){

  wxGrid *grid = m_pDialogView->m_pModifyStudentGrid;

  if(m_pCurrentCourse != NULL){

    for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

      Student s = m_pCurrentCourse->GetStudent(m_RowsNeedToBeUpdated[i]);

      for (int x = 0; x < grid->GetNumberCols(); ++x) {

        if(grid->GetColLabelValue(x).IsSameAs("Student ID")){

          s.SetStudentId(grid->GetCellValue(m_RowsNeedToBeUpdated[i], x));
        }
        else if(grid->GetColLabelValue(x).IsSameAs("First Name")){

          s.SetFirst(grid->GetCellValue(m_RowsNeedToBeUpdated[i], x));
        }
        else if(grid->GetColLabelValue(x).IsSameAs("Last Name")){

          s.SetLast(grid->GetCellValue(m_RowsNeedToBeUpdated[i], x));
        }
      }
      m_pSql->UpdateStudent(s);
    }

    m_RowsNeedToBeUpdated.clear();
  }

}

/**
  * @brief  Makes the Database transactions when Dialog is being close by the User.
  * @param  wxEVT_CLOSE_WINDOW
  * @retval none.
  */
void GBDialogStudentController::DialogIsBeingClosed(wxCloseEvent& event){

  SaveChanges();
  m_pDialogView->EndModal(0);
  m_pDialogView->Destroy();
}
