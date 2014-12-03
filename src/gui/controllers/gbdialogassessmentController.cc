#include "gui/controllers/gbdialogassessmentController.h"
#include "sql/gbsql.h"
#include "gui/views/gbdialogassessmentView.h"
#include <iostream>
using namespace std;

// Constructor 1
GBDialogAssessmentController::GBDialogAssessmentController(){}

/**
  * @brief  Constructor to connect GBDialogAssessmentController with a view.
  * @param  GBDialogAssessmentView * view: The view to connect the Controller to.
  *         wxString CourseTitle: The course selected to add or modify Assessment(s).
  *         int style: When Style = 0 the controller will connect to a view to Add an Assessment
                       When Style = 1 the controller will connect to a view to Modify Assessment(s).
  * @retval none.
  */
GBDialogAssessmentController::GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle, int style)
  : m_pDialogView(view), m_pSql(GBSql::Instance()) {

  wxGrid *grid = m_pDialogView->m_pModifyAssessmentGrid;
  wxButton *button = m_pDialogView->m_pAddAssessmentButton;

  if( GetCurrentCourse(CourseTitle) == -1){

     if(style == 0){
       button->Disable();
     }
     else if(style == 1){

       grid->CreateGrid(0, 0);
       grid->Disable();

     }

    wxMessageBox( wxString::Format("Please select a course."), "Error", wxOK | wxICON_INFORMATION );
    return;
  }
  else{

    if(style == 0){


    }
    else if(style == 1){

      grid->CreateGrid(0, 1);
      grid->SetColLabelValue(0, "Assessment Name");
      LoadAssessments();
    }
  }
}

// Destructor
GBDialogAssessmentController::~GBDialogAssessmentController() {

  delete m_pCurrentCourse;
}

/**
  * @brief  A cell in the grid view has changed and the row will be stored
  *         so an Update transaction to the DataBase can be committed.
  * @param  wxEVT_GRID_CELL_CHANGED
  * @retval none.
  */
void GBDialogAssessmentController::GridCellChanged(wxGridEvent& event){

  if(!RowAlreadyNeedsToBeUpdated(event.GetRow())){

    m_RowsNeedToBeUpdated.push_back(event.GetRow());
  }
}

/**
  * @brief  The Add Assessment Button Was Clicked. Validation will be processed on the TextBox Control
  *         to verify the Assessment Name is not empty. If Assessment Name is not empty then the Assessment
  *         will be inserted into the DataBase.
  * @param  wxEVT_BUTTON
  * @retval none.
  */
void GBDialogAssessmentController::AddAssessmentButtonWasClicked(wxCommandEvent& event){

  wxTextCtrl    *AssessmentName = m_pDialogView->m_pAssessmentNameTextCtrl;
  wxString      ErrorMessage;
  Assessment    a;

  if( AssessmentName->IsEmpty() ||  m_pCurrentCourse == NULL  ){

        if( m_pCurrentCourse == NULL ){

            ErrorMessage = wxString::Format("Please select a course.");
        }
        else{

            ErrorMessage = wxString::Format("Please enter a name for your Assessment.");
        }

      wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
  }
  else{

    a.SetTitle( AssessmentName->GetValue() );

    if( m_pSql->InsertAssessmentIntoCourse( a , *m_pCurrentCourse) == -1 ){    cerr << "Failed to insert assessment in course" << endl;}

    m_pDialogView->EndModal(0);
    m_pDialogView->Destroy();
  }

}

/**
  * @brief  If a row already needs to be Updated then return true, otherwise false.
  * @param  int: row
  * @retval bool: True, if row already needs to be Updated; False, otherwise.
  */
bool GBDialogAssessmentController::RowAlreadyNeedsToBeUpdated(int row){

  for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

    if(row == m_RowsNeedToBeUpdated[i]) return true;
  }

  return false;
}

/**
  * @brief  This function will use the rows stored in m_RowsNeedToBeUpdated to
  *         commit an Update transaction for each row to the DataBase.
  * @param  none.
  * @retval none.
  */
void GBDialogAssessmentController::SaveChanges(){

  wxGrid *grid = m_pDialogView->m_pModifyAssessmentGrid;

  if(m_pCurrentCourse != NULL){

    for(int i = 0; i < m_RowsNeedToBeUpdated.size(); ++i){

      Assessment a = m_pCurrentCourse->GetAssessment(m_RowsNeedToBeUpdated[i]);

      for (int x = 0; x < grid->GetNumberCols(); ++x) {

        if(grid->GetColLabelValue(x).IsSameAs("Assessment Name")){

          a.SetTitle(grid->GetCellValue(m_RowsNeedToBeUpdated[i], x));
        }

      }
      m_pSql->UpdateAssessment(a);
    }

    m_RowsNeedToBeUpdated.clear();
    LoadAssessments();
  }

}


/**
  * @brief  Get the Current Course selected from the main frame.
  * @param  wxString CourseTitle
  * @retval int: Returns the status of the Database transaction.
  *         Returns -1 if transaction fails or no course was selected.
  */
int GBDialogAssessmentController::GetCurrentCourse(wxString CourseTitle){

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
  * @brief  Loads the Assessment from the currently selected course into the grid view for editing.
  * @param  none.
  * @retval none.
  */
void GBDialogAssessmentController::LoadAssessments(){

  wxGrid *grid = m_pDialogView->m_pModifyAssessmentGrid;

  m_pCurrentCourse->ClearAssessments();

  if( m_pSql->SelectAssessmentsByCourse(*m_pCurrentCourse) == -1 ) return;

  if(grid->GetNumberRows() == 0){

    grid->AppendRows(m_pCurrentCourse->AssessmentCount());
  }
  else{

    grid->ClearGrid();
  }

  // Populate Assessment data
  for (int i = 0; i < m_pCurrentCourse->AssessmentCount(); ++i) {

    Assessment a = m_pCurrentCourse->GetAssessment(i);

    // Populate Assessment Names
    for (int x = 0; x < grid->GetNumberCols(); ++x) {

      if(grid->GetColLabelValue(x).IsSameAs("Assessment Name")){
        grid->SetCellValue(i, x, a.Title());
      }
    }

    // Populate row labels
    grid->SetRowLabelValue(i, wxString::Format("%s", a.Title()));
  }

  // Refresh grid
  grid->SetRowLabelSize(wxGRID_AUTOSIZE);
  grid->AutoSize();
  grid->Refresh();
}

/**
  * @brief  The "Save" Button was clicked so we will save any rows that need to be Updated.
  * @param  wxEVT_BUTTON
  * @retval none.
  */
void GBDialogAssessmentController::SaveAssessmentChangesButtonWasClicked(wxCommandEvent& event){

  SaveChanges();
  LoadAssessments();

}

/**
  * @brief  Makes the Database transactions when Dialog is being close by the User.
  * @param  wxEVT_CLOSE_WINDOW
  * @retval none.
  */
void GBDialogAssessmentController::DialogIsBeingClosed(wxCloseEvent& event){

  // Handle Event

  SaveChanges();
  m_pDialogView->EndModal(0);
  m_pDialogView->Destroy();
}
