#include "data/student.h"

Student::Student() 
  : m_id(),
    m_studentId(),
    m_first(),
    m_last(),
    m_grades() {

}

Student::Student(const wxString &id)
  : m_id(id),
    m_studentId(),
    m_first(),
    m_last(),
    m_grades() {

}

Student::~Student() {

}

void Student::AddGrade(Grade *Grade) {
  m_grades.push_back(Grade);
}

Grade Student::GetGrade(int index) const {
  return *m_grades[index];
}

Grade Student::GetGradeByAssessmentId(const wxString &id) const {
  for (int i = 0; i < m_grades.size(); ++i) {
    if (id.IsSameAs(m_grades[i]->AssessmentId())) {
      return *m_grades[i];
    }
  }

	return Grade("-1");
}

int Student::GradeCount() {
  return m_grades.size();
}
