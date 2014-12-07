#include "data/assessment.h"

Assessment::Assessment() 
  : m_id(),
    m_title(),
		m_grades() {

}

Assessment::Assessment(const wxString &id)
  : m_id(id),
    m_title(),
		m_grades() {

}

Assessment::~Assessment() {

}
