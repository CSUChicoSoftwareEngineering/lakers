#include "gui\controllers\gbdialogcourseController.h"
#include "sql\gbsql.h"
#include "gui\views\gbdialogcourseView.h"

#include <iostream>

using namespace std;

GBDialogCourseController::GBDialogCourseController(GBDialogCourseView *view)
  : m_pSql(GBSql::Instance()),
    m_pDialogView(view) {

}

void GBDialogCourseController::AddButtonWasClicked(wxCommandEvent& event){
  wxTextCtrl *name = m_pDialogView->m_pCourseNameTextCtrl;

  if (name->GetValue().IsEmpty()) {
    cout << "empty selection" << endl;
    return;
  }

  Course c;

  c.SetTitle(name->GetValue());

  if (m_pSql->InsertCourse(c) == -1) {
    cout << "Sql error" << endl;
    return;
  }

  m_pDialogView->EndModal(0);

  m_pDialogView->Destroy();
}

void GBDialogCourseController::FileHasBeenSelected(wxFileDirPickerEvent& event){
	// Handle Event

}

void GBDialogCourseController::ImportStudents(){
	// Handle Event
}
