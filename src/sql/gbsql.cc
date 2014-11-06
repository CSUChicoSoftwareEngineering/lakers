#include "gbsql.h"

#include <iostream>
#include <wx/string.h>

using namespace std;

GBSql *GBSql::m_pInstance = NULL;

GBSql::GBSql() {

}

GBSql *GBSql::Instance() {
  if (!m_pInstance) {
    m_pInstance = new GBSql;
  }

  return m_pInstance;
}

int GBSql::Update(const wxString &sql) {
  try {
    return m_db.ExecuteUpdate(sql);
  } catch (wxSQLite3Exception &e) {
    cerr << e.GetMessage() << endl;

    return -1;
  }
}

wxSQLite3ResultSet *GBSql::Query(const wxString &sql) {
  try {
    return new wxSQLite3ResultSet(m_db.ExecuteQuery(sql));
  } catch (wxSQLite3Exception &e) {
    cerr << e.GetMessage() << endl;

    return NULL;
  }
}

int GBSql::Initialize(const wxString &file) {
  static char tables[5][1024] = {
    "CREATE TABLE IF NOT EXISTS students (\
      id integer primary key, \
      sid text not null unique, \
      first text not null, \
      last text not null)",
    "CREATE TABLE IF NOT EXISTS courses ( \
      id integer primary key, \
      title text not null)",
    "CREATE TABLE IF NOT EXISTS assessments ( \
      id integer primary key, \
      title text not null, \
      cid text not null)",
    "CREATE TABLE IF NOT EXISTS grades ( \
      id integer primary key, \
      sid text not null, \
      cid text not null, \
      aid text not null, \
      value text not null)",
    "CREATE TABLE IF NOT EXISTS course_student (\
      id integer primary key, \
      sid text not null, \
      cid text not null)",
  };

  if (Open(file)) {
    cerr << "Error opening database: " << file << endl;

    return 1;
  }

  for (int i = 0; i < 5; ++i) {
    if (Update(tables[i]) == -1) {
      cerr << "Failed to create table" << endl;

      return 1;
    }
  }

  return 0;
}

int GBSql::Open(const wxString &file) {
  try {
    m_db.Open(file);

    return 0;
  } catch (wxSQLite3Exception &e) {
    cerr << e.GetMessage() << endl;

    return 1;
  }
}

int GBSql::Close() {
  try {
    m_db.Close();

    return 0;
  } catch (wxSQLite3Exception &e) {
    cerr << e.GetMessage() << endl;

    return 1;
  }
}

int GBSql::Import(const wxString &file, const wxString &backup) {
  if (Open(file)) {
    return 1;
  }

  try {
    m_db.Restore(backup);

    return 0;
  } catch (wxSQLite3Exception &e) {
    cerr << e.GetMessage() << endl;

    return 1;
  }
}

int GBSql::SelectCourses(vector<Course*> *result) {
  wxString sql = wxString::Format("SELECT * FROM courses");

  Course *c;
  wxSQLite3ResultSet *r = Query(sql);

  while (r->NextRow()) {
    c = new Course(r->GetAsString("id"));

    c->SetTitle(r->GetAsString("title"));

    result->push_back(c);
  }

  return result->size();
}

int GBSql::InsertCourse(const Course &c) {
  wxString sql = wxString::Format("INSERT INTO courses \
      VALUES (NULL, '%s')", c.Title());

  int r = Update(sql);

  NotifyCourseUpdate();

  return r;
}

int GBSql::DeleteCourse(const Course &c) {
  wxString sql = wxString::Format("DELETE FROM courses \
      WHERE title='%s'", c.Title());

  return Update(sql);
}

int GBSql::SelectStudentsByCourse(Course &c) {
  wxString sql = wxString::Format("SELECT students.sid, first, last \
     FROM students \
     INNER JOIN course_student \
     ON students.sid=course_student.sid \
     WHERE course_student.cid='%s'", c.Id());

  Student *s;
  wxSQLite3ResultSet *r = Query(sql);

  c.Clear();

  while (r->NextRow()) {
    s = new Student(r->GetAsString("sid"));

    s->SetFirst(r->GetAsString("first"));
    s->SetLast(r->GetAsString("last"));

    c.AddStudent(s);
  }

  return c.StudentCount();
}

int GBSql::InsertStudentIntoCourse(const Student &s, const Course &c) {
  wxString sql = wxString::Format("INSERT INTO students \
      VALUES (NULL, '%s', '%s', '%s')", s.Id(), s.First(), s.Last());

  if (Update(sql) == -1) {
    return -1;
  }

  sql = wxString::Format("INSERT INTO course_student \
      VALUES (NULL, '%s', '%s')", s.Id(), c.Id());

  int r = Update(sql);

  NotifyStudentUpdate();

  return r;
}

int GBSql::DeleteStudent(const Student &s) {
  wxString sql = wxString::Format("DELETE FROM students \
      WHERE sid='%s'", s.Id());

  return Update(sql);
}

int GBSql::SelectAssessmentsByCourse(Course &c) {
  wxString sql = wxString::Format("SELECT * FROM assessments \
      WHERE cid='%s'", c.Id());

  Assessment *a;
  wxSQLite3ResultSet *r = Query(sql);

	c.Clear();

  while (r->NextRow()) {
    a = new Assessment(r->GetAsString("id"));

    a->SetTitle(r->GetAsString("title"));

    c.AddAssessment(a);
  }

  return c.AssessmentCount();
}

int GBSql::InsertAssessmentIntoCourse(const Assessment &a, const Course &c) {
  wxString sql = wxString::Format("INSERT INTO assessments \
      VALUES (NULL, '%s', '%s')", a.Title(), c.Id());

  int r = Update(sql);

  NotifyAssessmentUpdate();

  return r;
}

int GBSql::DeleteAssessment(const Assessment &a) {
  wxString sql = wxString::Format("DELETE FROM assessments \
     WHERE id='%s'", a.Id());

  return Update(sql);
}

int GBSql::SelectGradesForStudentInCourse(Student &s, const Course &c) {
  wxString sql = wxString::Format("SELECT * FROM grades \
      WHERE sid='%s' AND cid='%s'", s.Id(), c.Id());

  Grade *g;
  wxSQLite3ResultSet *r = Query(sql);

  s.Clear();

  while (r->NextRow()) {
    g = new Grade(r->GetAsString("id"));

    g->SetValue(r->GetAsString("value"));
    g->SetAssessmentId(r->GetAsString("aid"));

    s.AddGrade(g);
  }

  return s.GradeCount();
}

int GBSql::InsertGradeForStudent(const Grade &g, const Student &s, const Course &c, const Assessment &a) {
  wxString sql = wxString::Format("INSERT INTO grades \
      VALUES (NULL, '%s', '%s', '%s', '%s')", \
      s.Id(), c.Id(), a.Id(), g.Value());

  return Update(sql);

}

int GBSql::DeleteGrade(const Grade &g) {
  wxString sql = wxString::Format("DELETE FROM grades \
     WHERE id='%s'", g.Id());

  return Update(sql);
}
