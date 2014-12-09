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
	friend class GBSqlTest;

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
    // Updates course in database
    int UpdateCourse(const Course &c);
    // Deletes a course from the database
    int DeleteCourse(const Course &c);
    // Populates course with all students
    int SelectStudentsByCourse(Course &c);
    // Inserts student into database
    int InsertStudent(const Student &s);
    // Inserts student into database and adds student to course
    int InsertStudentIntoCourse(const Student &s, const Course &c);
    // Updates student in database
    int UpdateStudent(const Student &s);
    // Deletes student from database
    int DeleteStudent(const Student &s);
		// Deletes student from course
		int DeleteStudentFromCourse(const Student &s, const Course &c);
		// Deletes students for a course
		int DeleteStudentsForCourse(const Course &c);
    // Populates course with all assessments
    int SelectAssessmentsByCourse(Course &c);
    // Inserts assessment for course
    int InsertAssessmentIntoCourse(const Assessment &a, const Course &c);
    // Updates assessment for course
    int UpdateAssessmentIntoCourse(wxString newTitle, wxString currentTitle, const Course &c);
    // Updates assessment in database
    int UpdateAssessment(const Assessment &a);
    // Deletes assessment from database
    int DeleteAssessment(const Assessment &a);
		// Deletes all assessments for a course
		int DeleteAssessmentsForCourse(const Course &c);
    // Populates student with all grades
    int SelectGradesForStudentInCourse(Student &s, const Course &c);
		// Selects all grades for an assessment
		int SelectGradesForAssessment(Assessment &a);
		// Test is a grade exists
		int GradeExistsForStudent(const Grade &g);
    // Inserts grade for student into database
    int InsertGradeForStudent(const Grade &g, const Student &s, const Course &c, const Assessment &a);
    // Updates grade in database
    int UpdateGrade(const Grade &g);
    // Deletes grade from database
    int DeleteGrade(const Grade &g);
		// Deletes all grades for an assessment
		int DeleteGradesForAssessment(const Assessment &a);
		// Deletes all grades for a student in a course	
		int DeleteGradesForStudentInCourse(const Student &s, const Course &c);
		// Deletes all grades for a course
		int DeleteGradesForCourse(const Course &c);
		// Populates current database with dummy data
		void PopulateDummy();

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
		// Executes sql scalar
		int Scalar(const wxString &sql);
    // Singleton instance
    static GBSql *m_pInstance;
    // sqlite3 instance variable
    wxSQLite3Database m_db;
};

#endif
