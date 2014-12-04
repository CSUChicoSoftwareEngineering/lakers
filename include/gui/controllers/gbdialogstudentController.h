#ifndef _GBDIALOGSTUDENTCONTROLLER
#define _GBDIALOGSTUDENTCONTROLLER

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "sql/gbsql.h"
#include <wx/grid.h>

#define GB_STUDENT_DIALOGSIZE wxSize(350,500)

class GBDialogStudentView;

class GBDialogStudentController {
  public:
		GBDialogStudentController();
		GBDialogStudentController(GBDialogStudentView *view, wxString CourseTitle, int style);
		~GBDialogStudentController();

		//Events
		void AddStudentButtonWasClicked(wxCommandEvent& event);
		void GridCellChanged(wxGridEvent& event);
		void SaveStudentChangesButtonWasClicked(wxCommandEvent& event);

  private:
		int  GetCurrentCourse(wxString CourseTitle);
		void LoadStudents();
		void SaveChanges();
		bool RowAlreadyNeedsToBeUpdated(int row);

		GBSql               *m_pSql;
		GBDialogStudentView *m_pDialogView;
		Course              *m_pCurrentCourse;
		vector<Course*>     m_courses;
		vector<int >        m_RowsNeedToBeUpdated;
};

#endif
