#ifndef _GBDIALOGASSIGNMENTSCONTROLLER
#define _GBDIALOGASSIGNMENTSCONTROLLER

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/editlbox.h>
#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include <wx/msgdlg.h>
#include "data/assessment.h"
#include "sql/gbsql.h"
#include <wx/grid.h>

class GBDialogAssessmentView;

class GBDialogAssessmentController{

  public:
  GBDialogAssessmentController();
  GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle, int style);
  ~GBDialogAssessmentController();
  // Events
  void DialogIsBeingClosed(wxCloseEvent& event);
  void GridCellChanged(wxGridEvent& event);
  void AddAssessmentButtonWasClicked(wxCommandEvent& event);
  void CloseButtonWasClicked(wxCommandEvent& event);
  void SaveAssessmentChangesButtonWasClicked(wxCommandEvent& event);

  private:
  // Helper functions
  int  GetCurrentCourse(wxString CourseTitle);
  void LoadAssessments();
  void SaveChanges();
  bool RowAlreadyNeedsToBeUpdated(int row);

  // Member Variables
  GBDialogAssessmentView    *m_pDialogView;
  Course                    *m_pCurrentCourse;
  GBSql                     *m_pSql;
  vector<Course*>           m_courses;
  vector<int >              m_RowsNeedToBeUpdated;

};

#endif
