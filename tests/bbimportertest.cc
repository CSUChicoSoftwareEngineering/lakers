#include <gtest/gtest.h>
#include "data/bbimporter.h"
#include <wx/filefn.h>
#include <iostream>
#include <vector>
#include <string>
using std::vector;

class BBImporterTest : public ::testing::Test {
    protected:
        
        virtual void SetUp() {
            if (wxFileExists("gb.db")) {
                wxRemoveFile("gb.db");
            }

          
        };

        virtual void TearDown() {
           
        }
};

TEST_F(BBImporterTest, testPathToPointer) {

    BBImporter d;
	d.getLineCounter = 0;
	const char* courseCSV = "c:/csv_example.csv";
	std::vector<Student*> *VectorOfStudents = d.GetCourse(courseCSV);
	//std::cout << courseCSV << "\n";
	Student *testStudent = VectorOfStudents->back();
	
    wxString expected_str = "Tee";
    if ((testStudent->First()) == expected_str)
	{
		std::cout << "Test Passed\n";
    //ASSERT_STREQ(expected_str, *(testStudent->GetFirst()));
	//ASSERT_TRUE(d.setFirstCounter > 54);
		ASSERT_TRUE(VectorOfStudents->size() == 11);
	//ASSERT_TRUE(d.getLineCounter == 11);
	//ASSERT_TRUE(d.courseEmpty = 1);
	}
}


