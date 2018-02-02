#ifndef DEF_Map
#define DEF_Map

#include "define.h"
#include "cell.h"
#include "cellgraphic.h"
#include "Dxlib.h"
#include <vector>

class Camera;
class Map {
protected:
	//Cell* cell[MAP_X_MAX][MAP_Y_MAX];
	Cell* cell[EXPMAP_X_MAX][EXPMAP_Y_MAX];
	CellGraphic* cellGraphic[EXPMAP_X_MAX*2][EXPMAP_Y_MAX*2];
	int sizex;
	int sizey;
	int graphicSizeX;
	int graphicSizeY;

	int anime_time;

public:

	Map(int,int);
	~Map();

	void Clear();
	Cell* GetCell(int, int);
	CellGraphic* GetCellGraphic(int, int);
	bool GetMovef(int, int);
	bool GetMovef_Conv(int, int, int, int);

	bool GetCellAcsessf(int, int);
	bool GetCellGraphicAcsessf(int, int);

	int GetSizeX();
	int GetSizeY();
	int GetGraphicSizeX();
	int GetGraphicSizeY();

	int GetAnimeTime();
	void AnimeTimeUpdate();

	void Draw(Camera*,bool);

};

#endif
