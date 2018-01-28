#ifndef DEF_CellGraphic
#define DEF_CellGraphic

#include "define.h"
#include <vector>

class Camera;
class Cell;
class CellGraphic {
protected:
	int cx;
	int cy;

	int graphic_handle[4][6];
	int anime;

	Cell* cell;

public:

	static const int ANIME_TIME;
	static const int CELL_GRAPHIC_X;
	static const int CELL_GRAPHIC_Y;

	CellGraphic();
	CellGraphic(int, int);
	CellGraphic(int, int, Cell*);
	~CellGraphic();

	void Clear();

	void SetCx(int);
	void SetCy(int);
	void SetGraphicHandle(int, int, int);
	void SetAnime(int);
	void SetCell(Cell*);

	Cell* GetCell();

	void Draw(Camera*, bool, int);
};


#endif
