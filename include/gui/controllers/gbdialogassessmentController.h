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
#include "data\assessment.h"
#include "sql/gbsql.h"

class GBDialogAssessmentView;

class GBDialogAssessmentController{

  public:
  GBDialogAssessmentController();
  GBDialogAssessmentController(GBDialogAssessmentView *view);
  GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle);
  ~GBDialogAssessmentController();
  // Events
  void BeginAssessmentLabelEdit(wxListEvent& event);
  void EndAssessmentLabelEdit(wxListEvent& event);
  void AssessmentHasBeenDeleted(wxListEvent& event);
  void DialogIsBeingClosed(wxCloseEvent& event);

  private:
  // Helper functions
  void PopulateAssessmentListBoxByCourse();
  int  GetCurrentCourse(wxString CourseTitle);
  bool AssessmentExistsInRuntime(wxString title);
  int  DuplicateAssessmentInNeedToBeRenamed(wxString title);
  int  DuplicateAssessmentInRuntime(wxString title);
  bool AssessmentExistsInDB(wxString title);
  bool AssessmentNeedsToBeDeletedFromDB(wxString title);
  bool AssessmentNeedsToBeDeletedFromRuntime(wxString title);
  bool AssessmentNeedsToBeRenamed(wxString title);
  // Member Variables
  GBDialogAssessmentView    *m_pDialogView;
  Course                    *m_pCurrentCourse;
  GBSql                     *m_pSql;
  vector<Course*>           m_courses;
  wxArrayString             m_RuntimeAssessments;
  wxArrayString             m_AssessmentsNeedsToBeRenamedOldName;
  wxArrayString             m_AssessmentsNeedsToBeRenamedNewName;
  wxArrayString             m_AssessmentsNeedsToBeInserted;
  wxArrayString             m_AssessmentsNeedsToBeDeletedFromDB;
  wxArrayString             m_AssessmentsNeedsToBeDeletedFromRuntime;
  vector<wxString>          m_AssessmentsMustBeDeletedFromDB;
  wxString                  m_currentAssessmentSelected;

};

#endif
