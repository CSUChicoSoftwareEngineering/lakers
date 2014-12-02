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


  m_pDialogView->Close();

}

void GBDialogCourseController::FileHasBeenSelected(wxFileDirPickerEvent& event){
	// Handle Event
  wxCheckListBox *StudentSelectionListBox = m_pDialogView->m_pcsvFileViewListBox;
  BBImporter cur_Importer;
  wxString Path = event.GetPath();
  wxString  StudentName ;
  Student *importStudent;

  cout << Path << endl;


  csv_Ptr = cur_Importer.GetCourse(Path.mb_str());


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

void GBDialogCourseController::DialogIsBeingClosed(wxCloseEvent& event){

  cout << "closing . . ." << endl;
  wxCheckListBox *StudentSelectionListBox = m_pDialogView->m_pcsvFileViewListBox;
  Student *importStudent;
  wxString StudentName;

  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }


  for (int i = 0; i < m_courses.size(); ++i) {

    if (m_courses[i]->Title().IsSameAs(m_pDialogView->m_pCourseNameTextCtrl->GetValue())) {

        m_pCurrentCourse = m_courses[i];
    }
  }

  cout << "Course Has Now Been Selected . . . " << m_pCurrentCourse->Title() << endl;

  for(int i = 0; i < StudentSelectionListBox->GetCount(); ++i ){

    if(StudentSelectionListBox->IsChecked(i)){

        for (std::vector<Student*>::iterator it = csv_Ptr->begin(); it != csv_Ptr->end(); ++it){
          importStudent = *it;
          StudentName = wxString::Format("%s, %s", importStudent->Last() , importStudent->First());

          if(StudentSelectionListBox->GetString(i).IsSameAs(StudentName)){

            importStudent->SetStudentId(  wxString::Format("%d", rand() % 1000000) );
            cout << "Insert Result: " << m_pSql->InsertStudentIntoCourse(*importStudent , *m_pCurrentCourse) << endl;
            //cout << "Inserted! " << wxString::Format("%s, %s, %s  into  %s", importStudent->StudentId(), importStudent->Last() , importStudent->First(), c.Title()) << endl;
          }
      }
    }
  }
   m_pDialogView->EndModal(0);

  m_pDialogView->Destroy();
}

void GBDialogCourseController::StudentHasBeenUnchecked(wxCommandEvent& event){
	// Handle Event
}

void GBDialogCourseController::ImportStudents(){
	// Handle Event
}
