#ifndef _GBDIALOGUSEROPTIONSVIEW
#define _GBDIALOGUSEROPTIONSVIEW

#include <wx/dialog.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "gui/controllers/gbdialoguseroptionsController.h"

#define GB_USEROPTIONS_DIALOGSIZE wxSize(350,175)

class  GBDialogUserOptionsView : public wxDialog {

  public:
	GBDialogUserOptionsView();
    GBDialogUserOptionsView(wxWindow *parent);
    ~GBDialogUserOptionsView();

    wxTextCtrl					*m_pCurrentDbFilePathTextCtrl;
    wxTextCtrl					*m_pDbFilePathTextCtrl;
    wxFilePickerCtrl 			*m_pSelectFileLocationCtrl;
    wxButton					*m_pSaveFileLocationButton;
    wxButton					*m_pCloseButton;

  private:
    // Member Variables
    GBDialogUserOptionsController 	*m_pCon;
    wxPanel                         *m_pGBDialogPanel;
    wxStaticBoxSizer                *m_pSelectDbFileStaticBoxSizer;
    wxStaticBoxSizer                *m_pCurrentDbFileStaticBoxSizer;
    wxBoxSizer                      *m_pButtonSizer;
    wxBoxSizer                      *m_pDialogSizer;


};

enum{
	ID_DbFileSelect = 1,
};

#endif
