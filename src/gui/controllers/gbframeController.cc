#include "gui/controllers/gbframeController.h"
#include "sql/gbsql.h"
#include "gui/views/gbframeView.h"

#include <iostream>

using namespace std;

GBFrameController::GBFrameController(GBFrameView *view)
  : m_pMainFrameView(view),
    m_pSql(GBSql::Instance()) {

  m_pSql->AddSubscriber(this);

  PopulateCourseDropDownList();

  CreateGridView();
}

GBFrameController::~GBFrameController() {
  delete m_pMainFrameView;

  m_pSql->RemoveSubscriber(this);

  for (int i = 0; i < m_courses.size(); ++i) {
    delete m_courses[i];
  }
}

// *** Modify grid to populate it with data pulled from DB ***
void GBFrameController::CreateGridView(){
	// Create Student Grid view.
	// Number of students in course = rows
	// Total assessments = columns
	//  (m_pMainFrameView->m_pGridView)->CreateGrid(0, 0);
	//  (m_pMainFrameView->m_pGridView)->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0)));
	//	(m_pMainFrameView->m_pGridView)->EnableDragColMove(true);
	//	(m_pMainFrameView->m_pGridView)->EnableEditing(true);

  UpdateGridView();
}

// Updates grid with new data
// TODO 
// This needs to be refactored at some point
// UpdateGridView
// UpdateStudents
// UpdateAssessments
// UpdateGrades
void GBFrameController::UpdateGridView() {
  Course *course(NULL);
  wxGrid *grid = m_pMainFrameView->m_pGridView;
	GradeTable *table = m_pMainFrameView->m_pGradeTable;
  wxComboBox *combo = m_pMainFrameView->m_pCourseComboBox;
  wxString strSelection = combo->GetValue();

  // Determine selected course
  for (int i = 0; i < m_courses.size(); ++i) {
    if (m_courses[i]->Title().IsSameAs(strSelection)) {
      course = m_courses[i];

      break;
    }
  }

  if (course == NULL) {
    cerr << "Failed to find selected course" << endl;

    return;
  }

  // Ensure course is empty
  course->Clear();

	table->Clear();

  // Populate course with assessments
  if (m_pSql->SelectAssessmentsByCourse(*course) == -1) {
    cerr << "Failed to select assessments in course" << endl;

    return;
  }

	for (int i = 0; i < course->AssessmentCount(); ++i) {
		table->AddAssessment(i, course->GetAssessment(i));
	}	

 	// Populate course with students
  if (m_pSql->SelectStudentsByCourse(*course) == -1) {
    cerr << "Failed to select students in course" << endl;

    return;
  }

	for (int i = 0; i < course->StudentCount(); ++i) {
		Student s = course->GetStudent(i);

		table->AddStudent(i, s);

		if (m_pSql->SelectGradesForStudentInCourse(s, *course) == -1) {
			continue;
		}

		for (int x = 0; x < grid->GetNumberCols(); ++x) {
			Assessment a = course->GetAssessmentByTitle(grid->GetColLabelValue(x));

			Grade g = s.GetGradeByAssessmentId(a.Id());

			table->AddGrade(i, x, g);	
		}
	}

  // Refresh grid
  grid->SetRowLabelSize(wxGRID_AUTOSIZE);
  grid->Refresh();
}

void  GBFrameController::NewCourseSelected(wxCommandEvent& event){
  UpdateGridView();
}

void GBFrameController::OnLabelDelete(wxCommandEvent &event) {
	wxGrid *grid = m_pMainFrameView->m_pGridView;
	GradeTable *table = m_pMainFrameView->m_pGradeTable;

	wxArrayInt selectedRows = grid->GetSelectedRows();
	wxArrayInt selectedCols = grid->GetSelectedCols();	

	// Delete selected rows or cols
	if (selectedRows.GetCount() > 0) {
		for (int x = 0; x < selectedRows.GetCount(); ++x) {
			Student s = table->GetStudent(selectedRows.Item(x));

			m_pSql->DeleteStudent(s);
		}	
	} else if (selectedCols.GetCount() > 0) {
		for (int x = 0; x < selectedCols.GetCount(); ++x) {
			Assessment a = table->GetAssessment(selectedCols.Item(x));

			m_pSql->DeleteAssessment(a);
		}
	}
}

void GBFrameController::OnCourseUpdate(SubscriberUpdateType type) {
  PopulateCourseDropDownList();
}

void GBFrameController::OnStudentUpdate(SubscriberUpdateType type){
	UpdateGridView();
}

void GBFrameController::OnAssessmentUpdate(SubscriberUpdateType type){
	UpdateGridView();
}

// *** Need to pull data from DB to populate Dropdown list ***
void GBFrameController::PopulateCourseDropDownList(){
  wxComboBox *course = m_pMainFrameView->m_pCourseComboBox;

  m_courses.clear();

  course->Clear();

  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }

  for (int i = 0; i < m_courses.size(); ++i) {
    course->Append(m_courses[i]->Title());
  }

  if (course->GetCount() > 0) {
    course->SetValue(m_courses[0]->Title());
  }

  course->SetSelection(0);
}

void GBFrameController::ModifyAssignments(wxCommandEvent& event){
	GBDialogAssessmentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection());

	dlg.ShowModal();
}


void GBFrameController::AddCourse(wxCommandEvent& event){
  GBDialogCourseView dlg(m_pMainFrameView);

  dlg.ShowModal();
}

void GBFrameController::AddStudent(wxCommandEvent& event){
  GBDialogStudentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), AddStudentStyleView);

  dlg.ShowModal();
}

void GBFrameController::ModifyStudent(wxCommandEvent& event){
	// Handle Event
  GBDialogStudentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), ModifyStudentStyleView);

  dlg.ShowModal();
}

void GBFrameController::OnExit(wxCommandEvent& event) {
	// Handle Event
    (m_pMainFrameView->Close)( true );
}

void GBFrameController::OnAbout(wxCommandEvent& event) {
	// Handle Event
    wxMessageBox( "GradeBook Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}
