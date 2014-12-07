#ifndef _GBDIALOGUSEROPTIONSVIEW
#define _GBDIALOGUSEROPTIONSVIEW

#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/window.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "gui/controllers/gbdialoguseroptionsController.h"

#define GB_USEROPTIONS_DIALOGSIZE wxSize(350,175)

class  GBDialogUserOptionsView : public wxDialog{

  public:
	GBDialogUserOptionsView();
    GBDialogUserOptionsView(wxWindow *parent);
    ~GBDialogUserOptionsView();

    wxTextCtrl					*m_pCurrentDbFilePathTextCtrl;
    wxTextCtrl					*m_pDbFilePathTextCtrl;
    wxFilePickerCtrl 			*m_pSelectFileLocationCtrl;
    wxButton					*m_pSaveFileLocationButton;
    wxButton                    *m_pSaveStudentNameFormatButton;
    wxButton					*m_pCloseButton;
    wxRadioBox                  *m_pStudentNameFormatOptions;

  private:
    // Member Variables
    wxWindow *ChangeDbLocation(wxWindow *parent, wxWindowID id);
    wxWindow *ChangeStudentNameFormat(wxWindow *parent, wxWindowID id);
    GBDialogUserOptionsController 	*m_pCon;

    wxStaticBoxSizer                *m_pSelectDbFileStaticBoxSizer;
    wxStaticBoxSizer                *m_pCurrentDbFileStaticBoxSizer;
    wxBoxSizer                      *m_pButtonSizerForChangeDbLocationView;
    wxBoxSizer                      *m_pButtonSizerForChangeStudentNameFormatView;
    wxBoxSizer                      *m_pRadioSizer;
    wxBoxSizer                      *m_pWindowSizerForChangeDbLocationView;
    wxBoxSizer                      *m_pWindowSizerForChangeStudentNameFormatView;
    wxArrayString                   FormatOptions;
    wxNotebook                      *m_pUserOptionsTabs;
    wxWindow                        *m_pDbLocation;
    wxWindow                        *m_pStudentNameFormat;
    const int                       NumberOfStudentNameFormatOptions = 3;
    const int                       ChangeDbLocationView = 0;
    const int                       ChangeStudentNameFormatView = 1;



};



enum{
	ID_DbFileSelect = 1,
	ID_OptionsTab = 2,
	ID_StudentNameFormatOptions = 3,
};

#endif
