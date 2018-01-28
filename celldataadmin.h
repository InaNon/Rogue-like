#ifndef DEF_CelldataAdmin
#define DEF_CellDataAdmin

#include "define.h"
#include "Dxlib.h"

#include <vector>
#include "celldata.h"

class CellDataAdmin {
protected:
	std::vector<CellData*> celldata;

public:
	CellDataAdmin();
	~CellDataAdmin();

	void Init();

	CellData* GetCellData(int);
	void SetCellData(CellData*);
};

#endif
