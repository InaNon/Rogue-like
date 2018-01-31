#ifndef DEF_MakeMapGrahic
#define DEF_MakeMapGrahic

#include "define.h"
#include "Dxlib.h"

class CellImage;
class Map;
class MakeMapGraphic {
protected:
	Map* map;

	CellImage* cell_image[CELLTYPE_NUM];

public:

	MakeMapGraphic();
	~MakeMapGraphic();

	void MakeMapGraphicInit(Map*);
	void MakeGraphic();
	void SetAutoCellGrahic(int, int, CELLTYPE);
	void SetCellGrahic(int, int, CELLTYPE);
};

#endif
