#ifndef _COURSE_H
#define _COURSE_H

#include <vector>

using std::vector;

#include <wx/string.h>

#include "data/student.h"
#include "data/assessment.h"

class Course {
  public:
    Course();
    Course(const wxString &id);
    ~Course();

    wxString Id() const { return m_id; }
    wxString Title() const { return m_title; }

    void SetTitle(const wxString &title) { m_title = title; }

    void AddStudent(Student *student);
    Student &GetStudent(int index) const;
    int StudentCount();

    void AddAssessment(Assessment *assessment);
    Assessment GetAssessment(int index) const;
    Assessment GetAssessmentByTitle(const wxString &title) const;
    int AssessmentCount();
    void Clear() { m_assessments.clear(); m_students.clear(); }
    void ClearAssessments() {m_assessments.clear();}
    void ClearStudents(){ m_students.clear(); }
    bool AssessmentExist(const wxString &title);

  private:
    wxString m_id;
    wxString m_title;
    vector<Student*> m_students;
    vector<Assessment*> m_assessments;
};

#endif
