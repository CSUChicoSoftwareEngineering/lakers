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

        std::vector<Student*> *GetCourse(const char *, int csvFormat);
		void csvline_populate(std::vector<Student*> *Course, const std::string &Line, char Delimiter, int csvFormat);
        int getLineCounter;
		int setFirstCounter = 0;
		int courseEmpty;
    private:
       int csvFormat;

};

#endif
