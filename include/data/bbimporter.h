#ifndef _BBIMPORTER_H
#define _BBIMPORTER_H

#include <wx/string.h>
#include "data/student.h"
#include <vector>
#include <string>

class BBImporter {
    public:

        
        BBImporter();
        ~BBImporter();

        std::vector<Student*> *GetCourse(const char *);
		void csvline_populate(std::vector<Student*> *Course, const std::string &Line, char Delimiter);
        int getLineCounter;
		int setFirstCounter = 0;
		int courseEmpty;
    private:

};

#endif
