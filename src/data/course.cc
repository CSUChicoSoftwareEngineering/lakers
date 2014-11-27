#include "data/course.h"

#include <iostream>
using namespace std;

Course::Course()
  : m_id(),
    m_title(),
    m_students(),
    m_assessments() {

}

Course::Course(const wxString &id)
  : m_id(id),
    m_title(),
    m_students(),
    m_assessments() {

}

Course::~Course() {

}

void Course::AddStudent(Student *student) {
  m_students.push_back(student);
}

Student &Course::GetStudent(int index) const {
  return *m_students[index];
}

int Course::StudentCount() {
  return m_students.size();
}

void Course::AddAssessment(Assessment *assessment) {
  m_assessments.push_back(assessment);
}

Assessment Course::GetAssessment(int index) const {
  return *m_assessments[index];
}

Assessment Course::GetAssessmentByTitle(const wxString &title) const {
  for (int i = 0; i < m_assessments.size(); ++i) {
    if (title.IsSameAs(m_assessments[i]->Title())) {
      return *m_assessments[i];
    }
  }
}

int Course::AssessmentCount() {
  return m_assessments.size();
}

bool Course::AssessmentExist(const wxString &title){

  if(!title.IsEmpty()){
	  for (int i = 0; i < m_assessments.size(); ++i) {
		if (title.IsSameAs(m_assessments[i]->Title())) {
		  return true;
		}
	  }
  }

  return false;
}
