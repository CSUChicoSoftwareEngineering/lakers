#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "gui/controllers/gbframeController.h"
#define GBAPPSIZE wxSize(800,600)
#define GBDIALOGSIZE wxSize(350,450)


class GBFrameView: public wxFrame {
  public:
    GBFrameView(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxBoxSizer 					*m_pCourseDropDownListSizer;
    wxBoxSizer 					*m_pGBFrameSizer;
  	wxComboBox 					*m_pCourseComboBox;
    wxPanel						*m_pGBFramePanel;
    wxGrid						*m_pGridView;
    wxDialog					*m_pGBDialog;
    wxPanel						*m_pGBDialogPanel;

	protected:
    GBFrameController			*m_pCon;
};


enum
{
	ID_AddCourseMenuSelect = 1,
	ID_CourseDropDownList = 2,
	ID_GradeBookPanel = 3,
	ID_GridView = 4,
	ID_AddAssignmentMenuSelect = 5,
	ID_ModifyAssignmentToolBarButton = 6,
	ID_GBDialogPanel = 7,
};
