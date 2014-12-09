#ifndef _GRADE_H_
#define _GRADE_H_

#include <wx/string.h>

class Grade {
  public:
    Grade();
    Grade(const wxString &id);
    ~Grade();

    wxString Id() const { return m_id; }
    wxString Value() const { return m_value; }
		wxString AdjValue() const { return m_adjValue; }
    wxString AssessmentId() const { return m_assessmentId; }
		wxString StudentId() const { return m_studentId; };

    void SetValue(const wxString &value) { m_value = value; }
		void SetAdjValue(const wxString &value) { m_adjValue = value; }
    void SetAssessmentId(const wxString &aid) { m_assessmentId = aid; }
		void SetStudentId(const wxString &sid) { m_studentId = sid; }
		void SetId(const wxString &id) { m_id = id; }

  private:
    wxString m_id;
    wxString m_assessmentId;
    wxString m_value;
		wxString m_adjValue;
		wxString m_studentId;
};

#endif
