#include "gtest/gtest.h"

#include <vector>

using std::vector;

#include "data/course.h"
#include "sql/gbsql.h"

class GBSqlTest : public ::testing::Test {
  protected:
		const wxString kTitle = "MATH-217";
		const wxString kStudentId = "1234";
		const wxString kFirst = "Joe";
		const wxString kLast = "Doe";
		const wxString kAssessment = "Project 1";
		const wxString kValue = "75"; 

		const wxString kInsertCourse = "INSERT INTO courses VALUES (NULL, '%s')";
		const wxString kInsertStudent = "INSERT INTO students VALUES (NULL, '%s', '%s', '%s')";
		const wxString kCourseStudent = "INSERT INTO course_student VALUES (NULL, '%s', '%s')";
		const wxString kInsertAssessment = "INSERT INTO assessments VALUES (NULL, '%s', '%s')";
		const wxString kInsertGrade = "INSERT INTO grades VALUES (NULL, '%s', '%s', '%s', '%s')";

		void DefaultCourse() {
			sql->Update(wxString::Format(kInsertCourse, kTitle));
		}

		void DefaultStudent() {
			sql->Update(wxString::Format(kInsertStudent, kStudentId, kFirst, kLast));
		}

		void DefaultCourseStudent() {
			sql->Update(wxString::Format(kCourseStudent, kStudentId, "1"));
		}

		void DefaultAssessment() {
			sql->Update(wxString::Format(kInsertAssessment, kAssessment, "1"));
		}

		void DefaultGrade() {
			sql->Update(wxString::Format(kInsertGrade, kStudentId, "1", "1", kValue));
		}

		wxSQLite3ResultSet* Query(const wxString &s) {
			return sql->Query(s);
		}

		int Count(const wxString &s) {
			int count = 0;
			wxSQLite3ResultSet *rs = Query(s);

			while (rs->NextRow()) ++count;

			return count;	
		}

		int CourseCount() {
			return Count("SELECT * FROM courses");
		}

		int StudentCount() {
			return Count("SELECT * FROM students");
		}

		int AssessmentCount() {
			return Count("SELECT * FROM assessments");
		}

		int GradeCount() {
			return Count("SELECT * FROM grades");
		}

		int CourseStudentCount() {
			return Count("SELECT * FROM course_student");
		}

    virtual void SetUp() {
      remove("gb.db");
      
      sql = GBSql::Instance();    

			sql->Initialize("gb.db");
    }

    virtual void TearDown() {
      sql->Close(); 
    }

    GBSql *sql;
};

TEST_F(GBSqlTest, SelectCourses) {
	DefaultCourse();

	vector<Course*> courses;

	int r = sql->SelectCourses(&courses);

	EXPECT_EQ(1, r);
	EXPECT_EQ(1, courses.size());

	ASSERT_STREQ(kTitle.mb_str(), courses[0]->Title().mb_str());
}

TEST_F(GBSqlTest, InsertCourse) {
	Course c;

	c.SetTitle(kTitle);

	int r = sql->InsertCourse(c);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM courses");

	rs->NextRow();

	ASSERT_STREQ(kTitle.mb_str(), rs->GetString("title").mb_str());
}

TEST_F(GBSqlTest, UpdateCourse) {
	DefaultCourse();

	Course c("1");

	c.SetTitle("CSCI-217");

	int r = sql->UpdateCourse(c);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM courses");

	rs->NextRow();

	ASSERT_STREQ("CSCI-217", rs->GetString("title").mb_str());
}

TEST_F(GBSqlTest, DeleteCourse) {
	DefaultCourse();

	Course c("1");

	int r = sql->DeleteCourse(c);

	EXPECT_EQ(1, r);

	ASSERT_EQ(0, CourseCount());
}

TEST_F(GBSqlTest, SelectStudentByCourse) {
	DefaultStudent();
	DefaultCourseStudent();

	Course c("1");

	int r = sql->SelectStudentsByCourse(c);

	EXPECT_EQ(1, r);
	EXPECT_EQ(1, c.StudentCount());
	
	ASSERT_STREQ(kStudentId.mb_str(), c.GetStudent(0).StudentId().mb_str());
	ASSERT_STREQ(kFirst.mb_str(), c.GetStudent(0).First().mb_str());
	ASSERT_STREQ(kLast.mb_str(), c.GetStudent(0).Last().mb_str());	
}

TEST_F(GBSqlTest, InsertStudentIntoCourse) {
	Student s;

	s.SetStudentId(kStudentId);
	s.SetFirst(kFirst);
	s.SetLast(kLast);

	Course c("1");

	int r = sql->InsertStudentIntoCourse(s, c);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM students");

	rs->NextRow();

	ASSERT_STREQ(kStudentId.mb_str(), rs->GetString("sid").mb_str());
	ASSERT_STREQ(kFirst.mb_str(), rs->GetString("first").mb_str());
	ASSERT_STREQ(kLast.mb_str(), rs->GetString("last").mb_str());	

	rs = Query("SELECT * FROM course_student");

	rs->NextRow();

	ASSERT_STREQ(kStudentId.mb_str(), rs->GetString("sid").mb_str());
	ASSERT_STREQ("1", rs->GetString("cid").mb_str());
}

TEST_F(GBSqlTest, UpdateStudent) {
	DefaultStudent();

	Student s("1");

	s.SetStudentId(kStudentId);
	s.SetFirst("Joe");
	s.SetLast("Montana");

	int r = sql->UpdateStudent(s);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM students");

	rs->NextRow();

	ASSERT_STREQ(kStudentId.mb_str(), rs->GetString("sid").mb_str());
	ASSERT_STREQ("Joe", rs->GetString("first").mb_str());
	ASSERT_STREQ("Montana", rs->GetString("last").mb_str());	
}

TEST_F(GBSqlTest, DeleteStudent) {
	DefaultStudent();

	Student s("1");
	
	s.SetStudentId(kStudentId);

	int r = sql->DeleteStudent(s);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, StudentCount());
}

TEST_F(GBSqlTest, DeleteStudentFromCourse) {
	DefaultCourseStudent();

	Student s("1");

	s.SetStudentId(kStudentId);

	Course c("1");

	int r = sql->DeleteStudentFromCourse(s, c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, CourseStudentCount());
}

TEST_F(GBSqlTest, DeleteStudentsForCourse) {
	DefaultCourseStudent();

	Course c("1");
	
	int r = sql->DeleteStudentsForCourse(c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, CourseStudentCount());
}

TEST_F(GBSqlTest, SelectAssessmentsByCourse) {
	DefaultAssessment();

	Course c("1");

	int r = sql->SelectAssessmentsByCourse(c);

	EXPECT_EQ(1, r);
	EXPECT_EQ(1, c.AssessmentCount());

	ASSERT_STREQ(kAssessment.mb_str(), c.GetAssessment(0).Title().mb_str());
}

TEST_F(GBSqlTest, InsertAssessmentIntoCourse) {
	Assessment a;

	a.SetTitle(kAssessment);

	Course c("1");

	int r = sql->InsertAssessmentIntoCourse(a, c);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM assessments");

	rs->NextRow();

	ASSERT_STREQ(kAssessment.mb_str(), rs->GetString("title").mb_str());
}

TEST_F(GBSqlTest, UpdateAssessment) {
	DefaultAssessment();

	Assessment a("1");

	a.SetTitle("Test 2");

	int r = sql->UpdateAssessment(a);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM assessments");

	rs->NextRow();

	ASSERT_STREQ("Test 2", rs->GetString("title").mb_str());
}

TEST_F(GBSqlTest, DeleteAssessment) {
	DefaultAssessment();
	DefaultGrade();

	Assessment a("1");

	int r = sql->DeleteAssessment(a);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, AssessmentCount());
}

TEST_F(GBSqlTest, DeleteAssessmentsForCourse) {
	DefaultAssessment();

	Course c("1");

	int r = sql->DeleteAssessmentsForCourse(c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, AssessmentCount());
}

TEST_F(GBSqlTest, SelectGradesForStudentInCourse) {
	DefaultCourse();
	DefaultStudent();
	DefaultAssessment();
	DefaultCourseStudent();
	DefaultGrade();

	Student s("1");

	s.SetStudentId(kStudentId);

	Course c("1");

	int r = sql->SelectGradesForStudentInCourse(s, c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(1, s.GradeCount());
}

TEST_F(GBSqlTest, InsertGradeForStudent) {
	Course c("1");
		
	Student s("1");

	s.SetStudentId(kStudentId);

	Assessment a("1");

	Grade g;

	g.SetValue(kValue);

	int r = sql->InsertGradeForStudent(g, s, c, a);

	EXPECT_EQ(1, r);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM grades");

	rs->NextRow();

	ASSERT_STREQ(kStudentId.mb_str(), rs->GetString("sid").mb_str());
	ASSERT_STREQ("1", rs->GetString("cid").mb_str());
	ASSERT_STREQ("1", rs->GetString("aid").mb_str());
	ASSERT_STREQ(kValue.mb_str(), rs->GetString("value").mb_str());
}

TEST_F(GBSqlTest, UpdateGrade) {
	DefaultGrade();

	Grade g("1");	
	
	g.SetAssessmentId("1");
	g.SetValue("1");

	int r = sql->UpdateGrade(g);

	wxSQLite3ResultSet *rs = Query("SELECT * FROM grades");

	rs->NextRow();

	ASSERT_STREQ(kStudentId.mb_str(), rs->GetString("sid").mb_str());
	ASSERT_STREQ("1", rs->GetString("cid").mb_str());
	ASSERT_STREQ("1", rs->GetString("aid").mb_str());
	ASSERT_STREQ("1", rs->GetString("value").mb_str());
}

TEST_F(GBSqlTest, DeleteGrade) {
	DefaultGrade();

	Grade g("1");

	int r = sql->DeleteGrade(g);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, GradeCount());
}

TEST_F(GBSqlTest, DeleteGradesForAssessment) {
	DefaultGrade();

	Assessment a("1");
	
	int r = sql->DeleteGradesForAssessment(a);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, GradeCount());
}

TEST_F(GBSqlTest, DeleteGradesForStudentInCourse) {
	DefaultGrade();

	Student s("1");

	s.SetStudentId(kStudentId);

	Course c("1");
	
	int r = sql->DeleteGradesForStudentInCourse(s, c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, GradeCount());
}

TEST_F(GBSqlTest, DeleteGradesForCourse) {
	DefaultGrade();

	Course c("1");

	int r = sql->DeleteGradesForCourse(c);

	EXPECT_EQ(1, r);
	ASSERT_EQ(0, GradeCount());
}
