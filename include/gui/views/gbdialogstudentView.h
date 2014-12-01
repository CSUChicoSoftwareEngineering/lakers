#ifndef _GBDIALOGSTUDENTVIEW
#define _GBDIALOGSTUDENTVIEW

#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/grid.h>

#include "gui/controllers/gbdialogstudentController.h"

#define GB_ADD_STUDENT_DIALOGSIZE wxSize(350,220)
#define GB_MODIFY_STUDENT_DIALOGSIZE wxSize(550,550)

class GBDialogStudentView : public wxDialog {

  public:
  GBDialogStudentView();
  GBDialogStudentView(wxWindow *parent, wxString CourseTitle, int style);
  ~GBDialogStudentView();

  wxTextCtrl    *m_pStudentIDTextCtrl;
  wxTextCtrl    *m_pStudentFirstNameTextCtrl;
  wxTextCtrl    *m_pStudentLastNameTextCtrl;
  wxButton      *m_pAddStudentButton;
  wxButton      *m_pSaveStudentChangesButton;
  wxGrid        *m_pModifyStudentGrid;

  private:
  // Member Variables
  GBDialogStudentController *m_pCon;
  wxPanel                   *m_pGBDialogPanel;
  wxBoxSizer                *m_pGridSizer;
  wxBoxSizer                *m_pDialogSizer;

};

enum{

  ID_AddStudentButton = 1 ,
  ID_ModifyStudentGrid = 2,
  ID_SaveStudentChangesButton = 3,

};

#endif