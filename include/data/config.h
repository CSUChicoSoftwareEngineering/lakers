#ifndef _CONFIG
#define _CONFIG

#include <wx/string.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <fstream>
#include <iostream>

using namespace std;

class Config {
  public:
    static Config *Instance();
    wxString GetDataBasePath(wxString Key, wxString value);
    long GetStudentFormat(wxString Key, long value);
    void SetDataBasePath(wxString path);
    void SetStudentFormat(long format);

  private:
    const wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI"; ;
    wxString ExecutablePath;
    wxString DatabasePath;
    wxFileConfig *config;
    // Default constructor
    Config();
    // Override copy constructor for singleton
    Config(Config const &) { };
    // Override move assignment
    Config& operator=(Config const&) { };

    static Config *m_pInstance;

};

#endif
