#ifndef _GBDIALOGCOURSECONTROLLER
#define _GBDIALOGCOURSECONTROLLER

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "sql/gbsql.h"

#define GB_COURSE_DIALOGSIZE wxSize(350,500)

class GBDialogCourseView;

class  GBDialogCourseController
{
	public:
    GBDialogCourseController(GBDialogCourseView *view);
    void AddButtonWasClicked(wxCommandEvent& event);
    void FileHasBeenSelected(wxFileDirPickerEvent& event);
    void StudentHasBeenUnchecked(wxCommandEvent& event);
    void DialogIsBeingClosed(wxCloseEvent& event);

	private:
    void ImportStudents();
    wxArrayString StudentSelection;
    std::vector<Student*> *csv_Ptr;
    vector<Course*>     m_courses;
    Course              *m_pCurrentCourse;
    GBSql *m_pSql;
    GBDialogCourseView *m_pDialogView;
};

#endif
