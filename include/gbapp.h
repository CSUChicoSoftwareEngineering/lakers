#ifndef _GBAPP_H
#define _GBAPP_H

#include <wx/app.h>
#include <wx/cmdline.h>

class GBApp : public wxApp {
	public:
		virtual bool OnInit();
		virtual int OnExit();
		virtual void OnInitCmdLine(wxCmdLineParser &parser);
		virtual bool OnCmdLineParsed(wxCmdLineParser &parser);
};

#endif
