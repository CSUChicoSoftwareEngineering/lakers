#ifndef _GBFRAMECONTROLLER
#define _GBFRAMECONTROLLER

#include <stdlib.h>
#include <wx/wxprec.h>
#include <fstream>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/editlbox.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/filepicker.h>
#include <wx/combobox.h>
#include "sql/gbsql.h"
#include "gui/views/gbdialogassessmentView.h"
#include "gui/views/gbdialogcourseView.h"
#include "gui/views/gbdialogstudentView.h"
#include "gui/views/gbdialoguseroptionsView.h"
#include "data/subscriber.h"

class GBFrameView;

class GBFrameController : public Subscriber {
  public:
    GBFrameController(GBFrameView *view);
    ~GBFrameController();

    // Events
    void AddCourse(wxCommandEvent& event);
    void AddStudent(wxCommandEvent& event);
    void ModifyStudent(wxCommandEvent& event);
    void AddAssessment(wxCommandEvent& event);
    void ModifyAssessment(wxCommandEvent& event);
    void AssignmentSelected(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void NewCourseSelected(wxCommandEvent& event);
    void OnLabelDelete(wxCommandEvent &event);
		void OnRemoveCourse(wxCommandEvent &event);
		void UserOptions(wxCommandEvent &event);
		void OnGradeCellChanged(wxGridEvent &event);
		void OnGraphClicked(wxCommandEvent &event);

    virtual void OnCourseUpdate(SubscriberUpdateType type);
    virtual void OnAssessmentUpdate(SubscriberUpdateType type);
    virtual void OnStudentUpdate(SubscriberUpdateType type);

  private:
    void PopulateCourseDropDownList();
    void CreateGridView();
    void UpdateGridView();
    const int AddStudentStyleView = 0;
    const int ModifyStudentStyleView = 1;
    const int AddAssessmentStyleView = 0;
    const int ModifyAssessmentStyleView = 1;

    GBSql           *m_pSql;
    GBFrameView 	*m_pMainFrameView;
    vector<Course*> m_courses;
    wxArrayString   m_StudentList;
};

#endif
