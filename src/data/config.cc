#include "data/config.h"



Config *Config::m_pInstance = NULL;

Config::Config() {
}

// Singleton mutator
Config *Config::Instance() {

  if (!m_pInstance) {

    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "GbUserOptions.INI";
    wxString ExePath = wxStandardPaths::Get().GetExecutablePath();
    wxString dbPath;
    wxFileConfig *init_config;
    std::ifstream InFile(ini_filename.c_str());

    if(!InFile){

      std::cout << "File Does Not Exist!" << std::endl;
      init_config = new wxFileConfig( "", "", ini_filename);
      ExePath.Replace("gbapp.exe","");
      dbPath = ExePath + "gb.db";
      init_config->Write( wxT("/gbDataBasePath"),  dbPath );
      init_config->Write( wxT("/StudentNameDisplayFormat"), 0 );
      init_config->Flush();
      delete init_config ;
    }
    else{

      std::cout << "File Exist!" << std::endl;
    }
    m_pInstance = new Config;
  }

  return m_pInstance;
}

void Config::SetDataBasePath(wxString path){

  config = new wxFileConfig( "", "", ini_filename);
  config->Write( wxT("/gbDataBasePath"),  path );
  config->Flush();
  delete config;
}


void Config::SetStudentFormat(long format){

  config = new wxFileConfig( "", "", ini_filename);
  config->Write( wxT("/StudentNameDisplayFormat"),  format );
  config->Flush();
  delete config;
}


wxString Config::GetDataBasePath(wxString Key, wxString value){

  config = new wxFileConfig( "", "", ini_filename);
  value = config->Read(Key, value) ;
  delete config ;
  return value;
}


long Config::GetStudentFormat(wxString Key, long value){

  config = new wxFileConfig( "", "", ini_filename);
  value = config->Read(Key, value) ;
  delete config ;
  return value;
}


