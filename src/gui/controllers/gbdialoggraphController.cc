#include "gui/controllers/gbdialoggraphController.h"

#include "gui/views/gbdialoggraphView.h"

GBDialogGraphController::GBDialogGraphController(GBDialogGraphView *view) 
	:	m_pSql(GBSql::Instance()),
		m_pView(view) {
	m_pSql->SelectGradesForAssessment(m_pView->m_assessment);
}

GBDialogGraphController::~GBDialogGraphController() {

}
