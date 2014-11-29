#ifndef _SUBSCRIBER_H_
#define _SUBSCRIBER_H_

enum SubscriberUpdateType {
  SQL_INSERT,
  SQL_UPDATE,
  SQL_DELETE
};

// Defines possible updates
class Subscriber {
  public:
    // Called on student update
    virtual void OnStudentUpdate(SubscriberUpdateType type);
    // Called on course update
    virtual void OnCourseUpdate(SubscriberUpdateType type);
    // Called on assessment update
    virtual void OnAssessmentUpdate(SubscriberUpdateType type);
    // Called on grade update
    virtual void OnGradeUpdate(SubscriberUpdateType type);
};

#endif
