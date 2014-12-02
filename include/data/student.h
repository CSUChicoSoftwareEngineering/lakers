#ifndef _STUDENT_H
#define _STUDENT_H

#include <vector>

using std::vector;

#include <wx/string.h>

#include "data/grade.h"

class Student {
  public:
    Student();
    Student(const wxString &id);
    ~Student();

    wxString Id() const { return m_id; }
    wxString StudentId() const { return m_studentId; }
    wxString First() const { return m_first; }
    wxString Last() const { return m_last; }

    void SetStudentId(const wxString &id) { m_studentId = id; }
    void SetFirst(const wxString &first) { m_first = first; }
    void SetLast(const wxString &last) { m_last = last; }

    void AddGrade(Grade *grade);
    Grade GetGrade(int index) const;
    Grade GetGradeByAssessmentId(const wxString &id) const;
    int GradeCount();

    void Clear() { m_grades.clear(); }

  private:
    wxString m_id;
    wxString m_studentId;
    wxString m_first;
    wxString m_last;
    vector<Grade*> m_grades;
};

#endif
