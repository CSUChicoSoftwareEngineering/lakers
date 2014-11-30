#include "gui/controllers/gbdialogassessmentController.h"
#include "sql/gbsql.h"
#include "gui/views/gbdialogassessmentView.h"
#include <iostream>
using namespace std;

// Constructor 1
GBDialogAssessmentController::GBDialogAssessmentController(){}

// Constructor 2
GBDialogAssessmentController::GBDialogAssessmentController(GBDialogAssessmentView *view)
  : m_pDialogView(view),
    m_pSql(GBSql::Instance()){
}

// Constructor 3
GBDialogAssessmentController::GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle)
  : m_pDialogView(view), m_pSql(GBSql::Instance()) {

  if( GetCurrentCourse(CourseTitle) == -1) return;

  PopulateAssessmentListBoxByCourse();
}

// Destructor
GBDialogAssessmentController::~GBDialogAssessmentController() {

  //delete  m_pDialogView, m_pCurrentCourse;
}


/**
  * @brief  Loads any assessments stores in the Database onto to ListBox Control.
  * @param  None
  * @retval None
  */
void GBDialogAssessmentController::PopulateAssessmentListBoxByCourse(){

  for (int i = 0; i < m_pCurrentCourse->AssessmentCount(); ++i) {

	m_RuntimeAssessments.Add(m_pCurrentCourse->GetAssessment(i).Title());
  }

  m_pDialogView->m_pModifyAssignmentListBox->SetStrings(m_RuntimeAssessments);
}


/**
  * @brief  Determines if user is trying to rename, delete, or insert an assessment.
  * @param  wxEVT_LIST_END_LABEL_EDIT
  * @retval None
  */
void GBDialogAssessmentController::EndAssessmentLabelEdit(wxListEvent& event){

  wxString ErrorMessage;
  wxEditableListBox *listBox    = m_pDialogView->m_pModifyAssignmentListBox;
  bool newAssessmentExistsInDB  = AssessmentExistsInDB(event.GetLabel());
  bool oldAssessmentExistsInDB  = AssessmentExistsInDB(m_currentAssessmentSelected);
  bool existsInRuntime          = AssessmentExistsInRuntime(event.GetLabel());
  bool deletedFromDB            = AssessmentNeedsToBeDeletedFromDB(event.GetLabel());
  bool deletedFromRuntime       = AssessmentNeedsToBeDeletedFromRuntime(event.GetLabel());
  int  duplicateRuntime         = DuplicateAssessmentInRuntime(event.GetLabel());
  int  duplicateRenamed         = DuplicateAssessmentInNeedToBeRenamed(event.GetLabel());
  bool existsInRename           = AssessmentNeedsToBeRenamed(event.GetLabel());
  bool textIsTheSame            = event.GetLabel().IsSameAs(m_currentAssessmentSelected);


  if(!m_currentAssessmentSelected.IsEmpty()){

    if( !textIsTheSame && !newAssessmentExistsInDB  && !existsInRuntime){
      // Rename Assessment If (newly inserted Assessment does not exists in the Runtime list
      // AND in the Database)
      m_AssessmentsNeedsToBeRenamedOldName.Add(m_currentAssessmentSelected);
      m_AssessmentsNeedsToBeRenamedNewName.Add(event.GetLabel());
      m_RuntimeAssessments.Insert(event.GetLabel(), event.GetIndex());
    }
    else if(existsInRuntime && deletedFromRuntime && duplicateRenamed < 1){

      // Rename Assessment If (newly inserted Assessment exists in the Runtime list
      // but it has been deleted and there are not duplicates)
      m_AssessmentsNeedsToBeRenamedOldName.Add(m_currentAssessmentSelected);
      m_AssessmentsNeedsToBeRenamedNewName.Add(event.GetLabel());
      m_RuntimeAssessments.Insert(event.GetLabel(), event.GetIndex());
    }
    else if(newAssessmentExistsInDB && deletedFromDB ){

      // Rename Assessment If (newly inserted Assessment exists in the Database
      // but it has been deleted)
      m_AssessmentsNeedsToBeRenamedOldName.Add(m_currentAssessmentSelected);
      m_AssessmentsNeedsToBeRenamedNewName.Add(event.GetLabel());
      m_RuntimeAssessments.Insert(event.GetLabel(), event.GetIndex());
      m_AssessmentsNeedsToBeDeletedFromDB.Remove(event.GetLabel());
    }
    else{
      // User Error
      ErrorMessage = wxString::Format("Assessment %s already exists.", event.GetLabel());
      wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
      event.Veto();
    }
  }
  else if( !event.GetLabel().IsEmpty() && !oldAssessmentExistsInDB && !newAssessmentExistsInDB && !existsInRuntime || deletedFromDB){

     // Insert Assessment If (newly inserted Assessment is not empty and it does not exists in the Database or in the
     // Runtime list)
     if(deletedFromDB){

        m_AssessmentsMustBeDeletedFromDB.push_back(event.GetLabel());
        m_AssessmentsNeedsToBeDeletedFromDB.Remove(event.GetLabel());
     }

      m_AssessmentsNeedsToBeInserted.Add(event.GetLabel());
      m_RuntimeAssessments.Add(event.GetLabel());
      listBox->SetStrings(m_RuntimeAssessments);
  }
  else{
    // User Error
    if(!event.GetLabel().IsEmpty()){

      ErrorMessage = wxString::Format("Assessment %s already exists.", event.GetLabel());
      wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
    }
    else{

      ErrorMessage = wxString::Format("Please enter a name.");
      wxMessageBox( ErrorMessage, "Error", wxOK | wxICON_INFORMATION );
    }
    event.Veto();
  }

  // If previous Assessment exists in the Database but not in the Runtime list and there are no duplicate then delete previous Assessment from Database
  if(oldAssessmentExistsInDB && !existsInRuntime && duplicateRuntime < 1)
  {m_AssessmentsNeedsToBeDeletedFromDB.Add(m_currentAssessmentSelected);}
  // If previous Assessment exists in the Runtime list but new Assessment does not exists in the Runtime list then delete previous Assessment from Runtime list
  if(AssessmentExistsInRuntime(m_currentAssessmentSelected) && !existsInRuntime)
  {m_RuntimeAssessments.Remove(m_currentAssessmentSelected);}

  listBox->Refresh();
}

/**
  * @brief  Determines the total number of the same Assessments there are
  *         in the Runtime list.
  * @param  wxString title
  * @retval int: Total number of the same Assessments in the Runtime list.
  */
int GBDialogAssessmentController::DuplicateAssessmentInRuntime(wxString title){

  int match = 0;

  for (int i = 0; i < m_RuntimeAssessments.size(); ++i) {

      if(title.IsSameAs(m_RuntimeAssessments[i])){

          match++;
      }
  }

  return match;

}

/**
  * @brief  Determines the total number of the same Assessments there are
  *         that need to be renamed.
  * @param  wxString title
  * @retval int: Total number of the same Assessments in the Runtime list.
  */
int GBDialogAssessmentController::DuplicateAssessmentInNeedToBeRenamed(wxString title){

  int match = 0;

  for (int i = 0; i < m_AssessmentsNeedsToBeRenamedNewName.size(); ++i) {

      if(title.IsSameAs(m_AssessmentsNeedsToBeRenamedNewName[i])){

          match++;
      }
  }

  return match;
}

/**
  * @brief  Determines if the Assessment needs to be deleted from the Runtime list
  * @param  wxString title
  * @retval bool: True if the Assessment needs to be deleted from the Runtime list
  *         False otherwise.
  */
bool GBDialogAssessmentController::AssessmentNeedsToBeDeletedFromRuntime(wxString title){

  for (int i = 0; i < m_AssessmentsNeedsToBeDeletedFromRuntime.size(); ++i) {

      if(title.IsSameAs(m_AssessmentsNeedsToBeDeletedFromRuntime[i])){

          return true;
      }
  }

  return false;
}

/**
  * @brief  Determines if the Assessment needs to be deleted from the Database
  * @param  wxString title
  * @retval bool: True if the Assessment needs to be deleted from the Database
  *         False otherwise.
  */
bool GBDialogAssessmentController::AssessmentNeedsToBeDeletedFromDB(wxString title){

  for (int i = 0; i < m_AssessmentsNeedsToBeDeletedFromDB.size(); ++i) {

      if(title.IsSameAs(m_AssessmentsNeedsToBeDeletedFromDB[i])){

          return true;
      }
  }

  return false;
}

/**
  * @brief  Determines if the Assessment needs to be renamed
  * @param  wxString title
  * @retval bool: True if the Assessment needs to be renamed
  */
bool GBDialogAssessmentController::AssessmentNeedsToBeRenamed(wxString title){

  for (int i = 0; i < m_AssessmentsNeedsToBeRenamedNewName.size(); ++i) {

      if(title.IsSameAs(m_AssessmentsNeedsToBeRenamedNewName[i])){

          return true;
      }
  }

  return false;
}

/**
  * @brief  Determines if the Assessment has been deleted by the User
  * @param  wxEVT_LIST_DELETE_ITEM
  * @retval none.
  */
void GBDialogAssessmentController::AssessmentHasBeenDeleted(wxListEvent& event){

  if(AssessmentExistsInDB(event.GetLabel())){

    m_AssessmentsNeedsToBeDeletedFromDB.Add(event.GetLabel());
  }
  else{

    m_AssessmentsNeedsToBeDeletedFromRuntime.Add(event.GetLabel());
  }

  if(AssessmentExistsInRuntime(event.GetLabel()))
    { m_RuntimeAssessments.Remove(event.GetLabel()); }


  for (int i = 0; i < m_AssessmentsNeedsToBeInserted.size(); ++i) {

      if(event.GetLabel().IsSameAs(m_AssessmentsNeedsToBeInserted[i])){

          m_AssessmentsNeedsToBeInserted.Remove(event.GetLabel());
      }
  }

  for (int i = 0; i < m_AssessmentsNeedsToBeRenamedNewName.size(); ++i) {

      if(event.GetLabel().IsSameAs(m_AssessmentsNeedsToBeRenamedNewName[i])){

          m_AssessmentsNeedsToBeRenamedNewName.RemoveAt(i);
          m_AssessmentsNeedsToBeRenamedOldName.RemoveAt(i);
      }
  }

}

/**
  * @brief  Determines what the assessment was previously named
  * @param  wxEVT_LIST_BEGIN_LABEL_EDIT
  * @retval none.
  */
void GBDialogAssessmentController::BeginAssessmentLabelEdit(wxListEvent& event){

  m_currentAssessmentSelected = event.GetLabel();
}

/**
  * @brief  Determines if the Assessment exists in the Runtime list
  * @param  wxString title
  * @retval bool: True if the Assessment exists in the Runtime list
  */
bool GBDialogAssessmentController::AssessmentExistsInRuntime(wxString title){

  if(!title.IsEmpty()){
	  for (int i = 0; i < m_RuntimeAssessments.size(); ++i) {
		if (title.IsSameAs(m_RuntimeAssessments[i])) {
		  return true;
		}
	  }
  }

  return false;
}

/**
  * @brief  Determines if the Assessment exists in the Database
  * @param  wxString title
  * @retval bool: True if the Assessment exists in the Database
  */
bool GBDialogAssessmentController::AssessmentExistsInDB(wxString title){

  if(!title.IsEmpty()){
    for (int i = 0; i < m_pCurrentCourse->AssessmentCount(); ++i) {
      if (title.IsSameAs(m_pCurrentCourse->GetAssessment(i).Title())) {
        return true;
      }
    }
  }

  return false;
}

/**
  * @brief  Get the Current Course has selected from the main frame.
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
	  (m_pDialogView->m_pModifyAssignmentListBox)->Disable();
      return -1;
	}
}

/**
  * @brief  Makes the Database transactions when Dialog is being close by the User.
  * @param  wxEVT_CLOSE_WINDOW
  * @retval none.
  */
void GBDialogAssessmentController::DialogIsBeingClosed(wxCloseEvent& event){

  // Handle Event

  if( m_pCurrentCourse != NULL){

    Assessment a;

    for(int i = 0 ; i < m_AssessmentsNeedsToBeDeletedFromDB.size(); ++i){

      m_AssessmentsMustBeDeletedFromDB.push_back(m_AssessmentsNeedsToBeDeletedFromDB[i]);
    }

    // Inserting Assessments ...
    for (int i = 0; i < m_AssessmentsNeedsToBeInserted.size(); ++i) {

      a.SetTitle(m_AssessmentsNeedsToBeInserted[i]);
      m_pSql->InsertAssessmentIntoCourse(a , *m_pCurrentCourse);
    }

    // Renaming Assessments ...
    m_pSql->SelectAssessmentsByCourse(*m_pCurrentCourse);
    for (int i = 0; i < m_AssessmentsNeedsToBeRenamedOldName.size(); ++i) {

      for(int j = 0; j < m_pCurrentCourse->AssessmentCount(); ++j){

        if ( m_AssessmentsNeedsToBeRenamedOldName[i].IsSameAs( m_pCurrentCourse->GetAssessment(j).Title() )){

            m_pSql->UpdateAssessmentIntoCourse(m_AssessmentsNeedsToBeRenamedNewName[i] , m_AssessmentsNeedsToBeRenamedOldName[i] , *m_pCurrentCourse);
        }
      }
    }

    // Get current Assessments
    if(m_pCurrentCourse->AssessmentCount() > 0){

      m_pCurrentCourse->ClearAssessments();
      m_pSql->SelectAssessmentsByCourse(*m_pCurrentCourse);
    }

    // Deleting Assessments ...
    for (int i = 0; i < m_AssessmentsMustBeDeletedFromDB.size(); ++i) {

      for (int j = 0; j < m_pCurrentCourse->AssessmentCount(); ++j) {

        if ( m_AssessmentsMustBeDeletedFromDB[i].IsSameAs( m_pCurrentCourse->GetAssessment(j).Title() )){

          m_pSql->DeleteAssessment(m_pCurrentCourse->GetAssessmentByTitle(m_AssessmentsMustBeDeletedFromDB[i]));
        }
      }

    }
  }

  m_pDialogView->Destroy();
}
