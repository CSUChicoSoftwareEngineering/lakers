#ifndef _GBAPP_H
#define _GBAPP_H

#include <wx/app.h>

class GBApp : public wxApp {
    public:
        virtual bool OnInit();
        virtual int OnExit();
};

#endif
