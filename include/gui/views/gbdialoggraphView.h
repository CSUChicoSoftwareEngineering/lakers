#ifndef _GBDIALOGGRAPH
#define _GBDIALOGGRAPH

#include "data/assessment.h"
#include "gui/controllers/gbdialoggraphController.h"

#include <wx/dialog.h>

#include <mathplot.h>

class BasicGraph : public mpFXY {
	public:
		BasicGraph(const Assessment &a);
		~BasicGraph();

		virtual double GetMinX() { return 0.0; };
		virtual double GetMaxX() { return m_assessment.GradeCount()+1; };
		virtual double GetMinY() { return 0.0; };
		virtual double GetMaxY() { return 101.0; };

		virtual void Rewind();
		virtual bool GetNextXY(double &x, double &y);

	private:
		int m_index;
		Assessment m_assessment;
};

class GBDialogGraphView : public wxDialog {
	public:
		GBDialogGraphView(wxWindow *parent, const Assessment &a);
		~GBDialogGraphView();

		mpWindow *m_pPlot;
		mpLayer *m_pGraphLayer;

		Assessment m_assessment;

	private:
		void BuildGui();

		GBDialogGraphController *m_pCon;
};

#endif // _GBDIALOGGRAPH
