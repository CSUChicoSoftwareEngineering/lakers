#include "gui/views/gbdialoggraphView.h"

#include <wx/sizer.h>

GBDialogGraphView::GBDialogGraphView(wxWindow *parent, const Assessment &a) 
	:	wxDialog(parent, wxID_ANY, "Grade Graph", wxDefaultPosition, wxSize(500, 400), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
		m_assessment(a) {
	BuildGui();

	m_pCon = new GBDialogGraphController(this);

	m_pGraphLayer = new BasicGraph(m_assessment);

	m_pPlot->AddLayer(m_pGraphLayer);

	m_pPlot->UpdateAll();
	m_pPlot->Fit();
}

GBDialogGraphView::~GBDialogGraphView() {
	delete m_pCon;
}

void GBDialogGraphView::BuildGui() {
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	m_pPlot = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mpScaleX *xAxis = new mpScaleX(wxT("Students"), mpALIGN_CENTER, true, mpX_NORMAL);
	mpScaleY *yAxis = new mpScaleY(wxT("Grades"), mpALIGN_CENTER, true);

	xAxis->SetFont(graphFont);
	xAxis->SetDrawOutsideMargins(true);
	yAxis->SetFont(graphFont);
	yAxis->SetDrawOutsideMargins(true);

	m_pPlot->SetMargins(30, 30, 50, 100);

	m_pPlot->AddLayer(xAxis);
	m_pPlot->AddLayer(yAxis);

	m_pPlot->EnableDoubleBuffer(true);
	m_pPlot->Fit();

	sizer->Add(m_pPlot, 1, wxEXPAND);

	SetAutoLayout(true);
	SetSizer(sizer);
}

BasicGraph::BasicGraph(const Assessment &a) 
	:	m_assessment(a) {
	SetPen(wxPen(*wxBLACK, 4));
	SetContinuity(true);
	SetDrawOutsideMargins(false);
}

BasicGraph::~BasicGraph() {

}

void BasicGraph::Rewind() {
	m_index = 0;
}

bool BasicGraph::GetNextXY(double &x, double &y) {
	if (m_index > GetMaxX()) {
		return false;
	}

	x = m_index;

	y = 0.0;

	if (m_index > 0 && m_index <= m_assessment.GradeCount()) {
		y = wxAtof(m_assessment.GradeAt(m_index-1)->Value());
	}	

	++m_index;

	return true;
}
