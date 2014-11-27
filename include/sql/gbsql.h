#ifndef _GBSQL_H
#define _GBSQL_H

#include <vector>

using std::vector;

#include <wx/wxsqlite3.h>

#include "data/course.h"
#include "data/student.h"
#include "data/assessment.h"
#include "data/observer.h"

// Stores model in a sql database. The class utilizes the singleton and
// observer patterns. Initialize or Open are required before making any
// other calls
// Class is not thread safe
class GBSql : public Observer {
  public:
    // Returns singleton instances of GBSql
    static GBSql *Instance();
    // Initializes database by calling Open and creating tables
    int Initialize(const wxString &file);
    // Open connection to database
    int Open(const wxString &file);
    // Closes connection to database
    int Close();
    // Opens database and restores image file
    int Import(const wxString &file, const wxString &backup);
    // Populates result with all courses
    int SelectCourses(vector<Course*> *result);
    // Inserts course into database
    int InsertCourse(const Course &c);
    // Deletes a course from the database
    int DeleteCourse(const Course &c);
    // Populates course with all students
    int SelectStudentsByCourse(Course &c);
    // Inserts student into database
    int InsertStudent(const Student &s);
    // Inserts student into database and adds student to course
    int InsertStudentIntoCourse(const Student &s, const Course &c);
    // Deletes student from database
    int DeleteStudent(const Student &s);
    // Populates course with all assessments
    int SelectAssessmentsByCourse(Course &c);
    // Inserts assessment for course
    int InsertAssessmentIntoCourse(const Assessment &a, const Course &c);
    // Updates assessment for course
    int UpdateAssessmentIntoCourse(wxString newTitle, wxString currentTitle, const Course &c);
    // Deletes assessment from database
    int DeleteAssessment(const Assessment &a);
    // Populates student with all grades
    int SelectGradesForStudentInCourse(Student &s, const Course &c);
    // Inserts grade for student into database
    int InsertGradeForStudent(const Grade &g, const Student &s, const Course &c, const Assessment &a);
    // Deletes grade from database
    int DeleteGrade(const Grade &g);

  private:
    // Default constructor
    GBSql();
    // Override copy constructor for singleton
    GBSql(GBSql const &) { };
    // Override move assignment
    GBSql& operator=(GBSql const&) { };
    // Executes sql update statement
    int Update(const wxString &sql);
    // Executes sql query statement
    wxSQLite3ResultSet *Query(const wxString &sql);
    // Singleton instance
    static GBSql *m_pInstance;
    // sqlite3 instance variable
    wxSQLite3Database m_db;
};

#endif
