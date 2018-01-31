#ifndef DEF_Map
#define DEF_Map

#include "define.h"
#include "cell.h"
#include "Dxlib.h"
#include <vector>

class Camera;
class Map {
protected:
	//Cell* cell[MAP_X_MAX][MAP_Y_MAX];
	Cell* cell[EXPMAP_X_MAX][EXPMAP_Y_MAX];

	int sizex;
	int sizey;

public:

	Map(int,int);
	~Map();

	void Clear();
	Cell* GetCell(int, int);
	bool GetMovef(int, int);
	bool GetMovef_Conv(int, int, int, int);

	bool GetCellAcsessf(int, int);

	int GetSizeX();
	int GetSizeY();


	void Draw(Camera*,bool);

};

#endif
