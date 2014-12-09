#include "gui/controllers/gbframeController.h"
#include "sql/gbsql.h"
#include "gui/views/gbframeView.h"
#include "gui/views/gbdialoggraphView.h"

#include <wx/msgdlg.h>

#include <iostream>

using namespace std;

/**
  * @brief  Constructor to connect GBFrameController with a view.
  * @param  GBFrameView * view: The view to connect the Controller to.
  * @retval none.
  */
GBFrameController::GBFrameController(GBFrameView *view)
  : m_pMainFrameView(view),
    m_pSql(GBSql::Instance()) {

  m_pSql->AddSubscriber(this);

  PopulateCourseDropDownList();
  (m_pMainFrameView->m_pCourseComboBox)->SetSelection(0);
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
  UpdateGridView();
}

// Updates grid with new data
// TODO
// This needs to be refactored at some point
// UpdateGridView
// UpdateStudents
// UpdateAssessments
// UpdateGrades
/**
  * @brief  Updates the Grid view rows and columns.
  * @param  none.
  * @retval none.
  */
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

			if (!g.Id().IsSameAs("-1")) {
				table->AddGrade(i, x, g);
			}
		}
	}

  // Refresh grid
  grid->SetRowLabelSize(wxGRID_AUTOSIZE);
  grid->Refresh();
}

/**
  * @brief  If a New Course is Selected then update the grid view with the appropriate Students and Assessments.
  * @param  wxCommandEvent wxEVT_COMBOBOX: An event from a combo box.
  * @retval none.
  */
void  GBFrameController::NewCourseSelected(wxCommandEvent& event){
  UpdateGridView();
}

/**
  * @brief  On a right click on the Grid rows or columns and the label "delete" is selected.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
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

/**
  * @brief  If a course is selected to be removed from the menu then delete from the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::OnRemoveCourse(wxCommandEvent &event) {
  Course *course(NULL);
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

	m_pSql->DeleteCourse(*course);
}

void GBFrameController::OnGradeCellChanged(wxGridEvent &event) {
	GradeTable *table = m_pMainFrameView->m_pGradeTable;
  Course *course(NULL);
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

	Assessment a = table->GetAssessment(event.GetCol());
	Student s = table->GetStudent(event.GetRow());
	Grade g = table->GetGrade(event.GetRow(), event.GetCol());

	if (m_pSql->GradeExistsForStudent(g) == 0) {
		m_pSql->InsertGradeForStudent(g, s, *course, a);

		table->AddGrade(event.GetRow(), event.GetCol(), g);
	} else {
		m_pSql->UpdateGrade(g);
	}
}


/**
  * @brief  If a Course was updated in another view then update the Course on the Main Frame as well.
  * @param  SubscriberUpdateType type: type can be one of the following; SQL_INSERT, SQL_UPDATE, SQL_DELETE
  * @retval none.
  */
void GBFrameController::OnCourseUpdate(SubscriberUpdateType type) {

  PopulateCourseDropDownList();

  UpdateGridView();

  m_courses.clear();
  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }

  (m_pMainFrameView->m_pCourseComboBox)->SetSelection(m_courses.size() - 1);
}

/**
  * @brief  If a Student was updated in another view then update the Student on the Main Frame as well.
  * @param  SubscriberUpdateType type: type can be one of the following; SQL_INSERT, SQL_UPDATE, SQL_DELETE
  * @retval none.
  */
void GBFrameController::OnStudentUpdate(SubscriberUpdateType type){
	UpdateGridView();
}

/**
  * @brief  If an Assessment was updated in another view then update the Assessment on the Main Frame as well.
  * @param  SubscriberUpdateType type: type can be one of the following; SQL_INSERT, SQL_UPDATE, SQL_DELETE
  * @retval none.
  */
void GBFrameController::OnAssessmentUpdate(SubscriberUpdateType type){
	UpdateGridView();
}

/**
  * @brief  Will populate the Dropdown List with all the Courses from the Database.
  * @param  none.
  * @retval none.
  */
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

}

/**
  * @brief  Will display a view to add Assessment(s) into the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::AddAssessment(wxCommandEvent& event){
    GBDialogAssessmentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), AddAssessmentStyleView);

	dlg.ShowModal();
}


/**
  * @brief  Will display a view to modify Assessment(s) in the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::ModifyAssessment(wxCommandEvent& event){
	GBDialogAssessmentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), ModifyAssessmentStyleView);

	dlg.ShowModal();
}

/**
  * @brief  Will display a view to add Course(s) in the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::AddCourse(wxCommandEvent& event){
  GBDialogCourseView dlg(m_pMainFrameView);

  dlg.ShowModal();
}

/**
  * @brief  Will display a view to add Student(s) in the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::AddStudent(wxCommandEvent& event){
  GBDialogStudentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), AddStudentStyleView);

  dlg.ShowModal();
}

/**
  * @brief  Will display a view to modify Student(s) in the Database.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::ModifyStudent(wxCommandEvent& event){
	// Handle Event
  GBDialogStudentView dlg(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection(), ModifyStudentStyleView);

  dlg.ShowModal();
}


/**
  * @brief  Will display a view with user Options.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::UserOptions(wxCommandEvent &event){


  GBDialogUserOptionsView dlg(m_pMainFrameView);

  dlg.ShowModal();
  UpdateGridView();
}

/**
  * @brief  Will display a view with graph of students grades.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::OnGraphClicked(wxCommandEvent &event) {
	wxGrid *grid = m_pMainFrameView->m_pGridView;
	GradeTable *table = m_pMainFrameView->m_pGradeTable;

	wxArrayInt cols = grid->GetSelectedCols();

	if (cols.GetCount() > 1) {
		wxMessageDialog msg(m_pMainFrameView, wxT("Select one column please."));

		msg.ShowModal();

		return;
	}

	Assessment a = table->GetAssessment(cols.Item(0));

	GBDialogGraphView dlg(m_pMainFrameView, a);

	dlg.ShowModal();
}

/**
  * @brief  Will close the Main Frame.
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::OnExit(wxCommandEvent& event) {
	// Handle Event
    (m_pMainFrameView->Close)( true );
}

/**
  * @brief  Will display an "about" dialog with information about the GradeBook Application
  * @param  wxCommandEvent wxEVT_MENU: An event from a menu.
  * @retval none.
  */
void GBFrameController::OnAbout(wxCommandEvent& event) {
	// Handle Event
	wxString msg = "GradeBook Application version 1.0.0 \n\nAuthors:" ;
             msg.Append("\nJason Boutte, \nAlejandro Velazquez, \nDarren Reitan\n");
             msg.Append("\nFrom: California State University, Chico");
             msg.Append("\nTo: Open Source Community");
    wxMessageBox( msg, "About", wxOK | wxICON_INFORMATION );
}
