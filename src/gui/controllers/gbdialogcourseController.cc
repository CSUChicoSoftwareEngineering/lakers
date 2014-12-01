#include "gui/controllers/gbdialogcourseController.h"
#include "sql/gbsql.h"
#include "gui/views/gbdialogcourseView.h"
#include "data/bbimporter.h"
#include "data/student.h"
#include <iostream>
#include <wx/msgdlg.h>

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

    return;
  }

  for(int i = 0; i < StudentSelectionListBox->GetCount(); ++i ){

    if(StudentSelectionListBox->IsChecked(i)){

        for (std::vector<Student*>::iterator it = csv_Ptr->begin(); it != csv_Ptr->end(); ++it){
          importStudent = *it;
          StudentName = wxString::Format("%s, %s", importStudent->Last() , importStudent->First());

          if(StudentSelectionListBox->GetString(i).IsSameAs(StudentName)){

            //m_pSql->InsertStudentIntoCourse(*importStudent , c);
          }
      }
    }
  }

  m_pDialogView->EndModal(0);

  m_pDialogView->Destroy();
}

void GBDialogCourseController::FileHasBeenSelected(wxFileDirPickerEvent& event){
	// Handle Event
  wxCheckListBox *StudentSelectionListBox = m_pDialogView->m_pcsvFileViewListBox;
  BBImporter cur_Importer;
  wxString Path = event.GetPath();
  wxString  StudentName ;
  Student *importStudent;

  csv_Ptr = cur_Importer.GetCourse(Path.mb_str());


  (m_pDialogView->m_pcsvFileViewListBox)->Enable();
  for (std::vector<Student*>::iterator it = csv_Ptr->begin(); it != csv_Ptr->end(); ++it){
    importStudent = *it;
    StudentName = wxString::Format("%s, %s", importStudent->Last() , importStudent->First());
    StudentSelection.Add(StudentName);
  }

  StudentSelection.Sort();
  StudentSelectionListBox->InsertItems( StudentSelection , 0);

  for(int i = 0; i < StudentSelectionListBox->GetCount(); ++i ){

    StudentSelectionListBox->Check(i);
  }

}

void GBDialogCourseController::StudentHasBeenUnchecked(wxCommandEvent& event){
	// Handle Event
}

void GBDialogCourseController::ImportStudents(){
	// Handle Event
}
