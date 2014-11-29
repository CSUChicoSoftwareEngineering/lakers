#include "data/observer.h"

// Pushes subscriber
void Observer::AddSubscriber(Subscriber *sub) {
  m_subscribers.push_back(sub);
}

// Iterates over subscribers to find match to remove
void Observer::RemoveSubscriber(Subscriber *sub) {
  vector<Subscriber*>::iterator it;

  for (it = m_subscribers.begin(); it != m_subscribers.end(); ++it) {
    if (*it == sub) {
      m_subscribers.erase(it);

      break;
    }
  }
}

// Notifies on student update
void Observer::NotifyStudentUpdate(SubscriberUpdateType type) {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnStudentUpdate(type);
  }
}

// Notifies on course update
void Observer::NotifyCourseUpdate(SubscriberUpdateType type) {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnCourseUpdate(type);
  }
}

// Notifies on assessment update
void Observer::NotifyAssessmentUpdate(SubscriberUpdateType type) {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnAssessmentUpdate(type);
  }
}

// Notifies on grade update
void Observer::NotifyGradeUpdate(SubscriberUpdateType type) {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnGradeUpdate(type);
  }
}
