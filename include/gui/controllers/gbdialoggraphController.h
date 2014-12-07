#ifndef _GBDIALOGGRAPHCONTROLLER
#define _GBDIALOGGRAPHCONTROLLER

#include "sql/gbsql.h"

class GBDialogGraphView;

class GBDialogGraphController {
	public:
		GBDialogGraphController(GBDialogGraphView *view);
		~GBDialogGraphController();

		GBDialogGraphView *m_pView;	

	private:
		GBSql *m_pSql;
};

#endif // _GBDIALOGGRAPHCONTROLLER
