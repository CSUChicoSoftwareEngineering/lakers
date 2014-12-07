#ifndef _ASSESSMENT_H
#define _ASSESSMENT_H

#include "data/grade.h"

#include <wx/string.h>

#include <vector>

using  std::vector;

class Assessment {
  public:
    Assessment();
    Assessment(const wxString &id);
    ~Assessment();

    wxString Id() const { return m_id; }
    wxString Title() const { return m_title; }

    void SetTitle(const wxString &title) { m_title = title; }

		int GradeCount() { return m_grades.size(); }
		void AddGrade(Grade *g) { m_grades.push_back(g); };
		Grade *GradeAt(int index) { return m_grades[index]; };

  private:
    wxString m_id;
    wxString m_title;
		vector<Grade*> m_grades;
};

#endif
