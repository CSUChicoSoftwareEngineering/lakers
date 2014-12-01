#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "gui/controllers/gbframeController.h"

#define GBAPPSIZE wxSize(800,600)
#define GBDIALOGSIZE wxSize(350,450)

class GradeTable : public wxGridTableBase {
	public:
		GradeTable();

		virtual int GetNumberRows();
		virtual int GetNumberCols();

		virtual wxString GetValue(int row, int col);
		virtual void SetValue(int row, int col, const wxString &value);

		virtual void Clear();

		virtual wxString GetRowLabelValue(int row);
		virtual wxString GetColLabelValue(int col);

		void AddStudent(int index, const Student &s);
		void AddAssessment(int index, const Assessment &s);
		void AddGrade(int row, int col, const Grade &g);

		Student &GetStudent(int index);
		Assessment &GetAssessment(int index);

	private:
		vector<Student> m_rows;	
		vector<Assessment> m_cols;
		vector<vector<Grade> > m_grades;
};

class GBFrameView : public wxFrame {
  public:
    GBFrameView(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxBoxSizer 					*m_pCourseDropDownListSizer;
    wxBoxSizer 					*m_pGBFrameSizer;
  	wxComboBox 					*m_pCourseComboBox;
    wxPanel						*m_pGBFramePanel;
    wxGrid						*m_pGridView;
    wxDialog					*m_pGBDialog;
    wxPanel						*m_pGBDialogPanel;
		GradeTable				*m_pGradeTable;
		wxMenu *m_pLabelMenu;

	protected:
    GBFrameController			*m_pCon;

	private:
		void OnLabelRightClick(wxGridEvent &event);
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
	ID_AddStudentMenuSelect = 8,
	ID_ModifyStudentMenuSelect = 9,
	ID_LabelDelete,
};
