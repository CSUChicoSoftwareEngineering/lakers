#include "gtest/gtest.h"

#include <vector>

using std::vector;

#include "data/course.h"
#include "sql/gbsql.h"

class GBSqlTest : public ::testing::Test 
{
  protected:
    virtual void SetUp() 
    {
      remove("gb.db");
      
      sql = GBSql::Instance();    

      sql->Import("gb.db", "tests/data/gb.backup"); 
    }

    virtual void TearDown()
    {
      sql->Close(); 
    }

    GBSql *sql;
};

TEST_F(GBSqlTest, SelectCourses) {
  vector<Course*> result;

  int r = sql->SelectCourses(&result);

  ASSERT_EQ(2, r);
}

TEST_F(GBSqlTest, InsertCourse) {
  Course c("3");

  c.SetTitle("CSCI-580");

  int r = sql->InsertCourse(c);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, UpdateCourse) {
  Course c1("1");
  vector<Course*> result;

  c1.SetTitle("CSCI-590");

  int r = sql->UpdateCourse(c1);

  ASSERT_EQ(1, r);

  r = sql->SelectCourses(&result);

  ASSERT_STREQ("CSCI-590", result[0]->Title().c_str());
}

TEST_F(GBSqlTest, DeleteCourse) {
  Course c("1");

  c.SetTitle("CSCI-217");

  int r = sql->DeleteCourse(c);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, SelectStudentByCourse) {
  Course c("1");

  c.SetTitle("CSCI-217");

  int r = sql->SelectStudentsByCourse(c);

  ASSERT_EQ(32, r);
}

TEST_F(GBSqlTest, InsertStudentIntoCourse) {
  Student s("82098310928");

  s.SetFirst("Joe");
  s.SetLast("Montana");

  Course c("1");

  int r = sql->InsertStudentIntoCourse(s, c);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, UpdateStudent) {
  Student s("1");

  s.SetStudentId("916683");
  s.SetFirst("Jane");
  s.SetLast("Lewis");

  int r = sql->UpdateStudent(s);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, DeleteStudent) {
  Student s("1");

  int r = sql->DeleteStudent(s);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, SelectAssessmentsByCourse) {
  Course c("1");

  int r = sql->SelectAssessmentsByCourse(c);

  ASSERT_EQ(20, r);
}

TEST_F(GBSqlTest, InsertAssessmentIntoCourse) {
  Assessment a;

  a.SetTitle("Test 1");

  Course c("1");

  int r = sql->InsertAssessmentIntoCourse(a, c);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, UpdateAssessment) {
  Assessment a("1");

  a.SetTitle("Test2");

  int r = sql->UpdateAssessment(a);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, DeleteAssessment) {
  Assessment a("1");

  int r = sql->DeleteAssessment(a);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, SelectGradesForStudentInCourse) {
  Student s("1");

  Course c("1");

  int r = sql->SelectGradesForStudentInCourse(s, c);

  ASSERT_EQ(20, r);
}

TEST_F(GBSqlTest, InsertGradeForStudent) {
  Grade g;

  g.SetValue("100");

  Student s("0");

  Course c("1");

  Assessment a("100");

  int r = sql->InsertGradeForStudent(g, s, c, a);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, UpdateGrade) {
  Grade g("2");
  
  g.SetValue("0");

  int r = sql->UpdateGrade(g);

  ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, DeleteGrade) {
  Grade g("1");

  int r = sql->DeleteGrade(g);

  ASSERT_EQ(1, r);
}
