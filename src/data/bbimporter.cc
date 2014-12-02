#include "data/bbimporter.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <vector>

#define MAX_COLUMNS 100

using namespace std;

// prototype
//void csvline_populate(std::vector<Student> *, const string& , char );



BBImporter::BBImporter() {

}

BBImporter::~BBImporter() {


}

// might rename this Get Course     add integer for failure code
std::vector<Student*> *BBImporter::GetCourse(const char *Path) {

	std::cout << "GetCourse Called \n";

    // needs to get deleted somewhere
	std::vector<Student*> *Course = new vector<Student*>;
	string Line;

	// open file from path
    ifstream InFile(Path);

	 // check file is open
     if (InFile.fail())  {
		cout << "File not found" <<endl; return NULL;
	}

	while(getline(InFile, Line)  && InFile.good() )
    {
	    getLineCounter ++;

	    // send a line of student info to be set to
		// a student object and push the student
		// object onto a course vector

        BBImporter::csvline_populate(Course, Line, ',');
    }

	InFile.close();
	courseEmpty = Course->size();
	std::cout << "There are " << courseEmpty << " Student classes in the vector \n";
    return Course;
}

void BBImporter::csvline_populate(vector<Student*> *Course, const string &Line, char Delimiter){

	int LinePos = 0;
    char Character;
    int i;
    int LineMax = Line.length();
    string CurString;
	Student *CurStudent = new Student();
	BBImporter::setFirstCounter = 0;

	for (int Column = 0; Column < MAX_COLUMNS; Column++)
	{
		while(LinePos <= (LineMax))
		{
			Character = Line[LinePos];

			// Start checking characters
			// end of field; if line is incomplete,
			// student object will still be pushed
			if (Character == Delimiter || Character == '\0')
			{
				// convert field to wxString
			    wxString wxCurField(CurString);


				//if curfield.is_empty



				//wstring check_string = wxString::ToStdWstring(wxCurField);
				wstring check_string = wstring(wxCurField);

				// set field to the corresponding student member
				switch (Column)
				{
					case 0:
					{
						//Sending username to student id
						//CurStudent->SetStudentId(   );
						break;
					}
					case 2:
					{
						CurStudent->SetFirst(wxCurField);
						break;
					}
					case 3:
					{
						CurStudent->SetLast(wxCurField);
						break;
					}
					default:
					    break;
				}

				// end of line
				if (Character == '\0')
				{

					Course->push_back(CurStudent);

					return;
				}

				CurString = "";
				Column++;
			}

			// just a character
			else
			{
				CurString.push_back(Character);
			    //cout << CurString << "/n";
				BBImporter::setFirstCounter++;
			}
			LinePos++;
		}
	    LinePos = 0;
	}

    return;
}
