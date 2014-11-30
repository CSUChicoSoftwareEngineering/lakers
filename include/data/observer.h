#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "data/subscriber.h"

#include <vector>

using std::vector;

// Observer declaration of Observer pattern
class Observer {
  public:
    // Adds listening subscriber
    void AddSubscriber(Subscriber *sub);
    // Remove listening subscriber
    void RemoveSubscriber(Subscriber *sub);

  protected:
    // Notify all subscribers on student table update
    void NotifyStudentUpdate(SubscriberUpdateType type);
    // Notify all subscribers on course table update
    void NotifyCourseUpdate(SubscriberUpdateType type);
    // Notify all subscribers on assessment table update
    void NotifyAssessmentUpdate(SubscriberUpdateType type);
    // Notify all subscribers on grade table update
    void NotifyGradeUpdate(SubscriberUpdateType type);

  private:
    // Vector for storing subscribers
    vector<Subscriber *> m_subscribers;
};

#endif
