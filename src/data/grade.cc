#include "data/grade.h"

Grade::Grade()
  : m_id("-1"),
    m_assessmentId(),
    m_value() {

}

Grade::Grade(const wxString &id)
  : m_id(id),
    m_assessmentId(),
    m_value() {

}

Grade::~Grade() {

}
