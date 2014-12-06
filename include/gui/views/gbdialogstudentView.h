#ifndef _GBDIALOGSTUDENTVIEW
#define _GBDIALOGSTUDENTVIEW

#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/grid.h>

#include "gui/controllers/gbdialogstudentController.h"

class GBDialogStudentView : public wxDialog {
  public:
		GBDialogStudentView();
		GBDialogStudentView(wxWindow *parent, wxString CourseTitle, int style);
		~GBDialogStudentView();

		wxTextCtrl    *m_pStudentIDTextCtrl;
		wxTextCtrl    *m_pStudentFirstNameTextCtrl;
		wxTextCtrl    *m_pStudentLastNameTextCtrl;
		wxButton 	  *m_pAddStudentButton;
		wxButton      *m_pSaveStudentChangesButton;
		wxGrid        *m_pModifyStudentGrid;

  private:
		// Member Variables
		GBDialogStudentController *m_pCon;

		void OnCloseClicked(wxCommandEvent &event);
};

enum{
  ID_AddStudentButton = 1 ,
  ID_ModifyStudentGrid = 2,
  ID_SaveStudentChangesButton = 3,
	ID_CloseDialog,
};

#endif
