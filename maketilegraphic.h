#ifndef DEF_MakeTileGrahic
#define DEF_MakeTileGrahic

#include "define.h"
#include "Dxlib.h"

#include "tileset.h"

class TileImage;
class MapAdmin;
class Map;
class TileSetAdmin;
class TileSet;


class MakeTileGraphic {
protected:
	//MapAdmin* map_admin;
	TileSetAdmin* tile_set_admin;
	TileSet* tile_set;
	//TileSet* share_tile_set;

	Map* map;

	//TileImage* cell_image[CELLTYPE_NUM];

public:
	static const enum DIRECTION {
		UP_LEFT,
		UP,
		UP_RIGHT,
		LEFT,
		CENTER,
		RIGHT,
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT,
		DIRECTION_NUM,
	} dire;

	MakeTileGraphic();
	~MakeTileGraphic();

	void Init(MapAdmin*, TileSetAdmin*);

	void MakeGraphic(int);

	bool MakeTileGraphic::SetSimpleGraphicHandle(int, int, TileImage*);
	void MakeTileGraphic::SetGraphicHandle(int, int, TileImage*, int, int);
	void MakeTileGraphic::SetGraphicHandle(int, int, TileImage*, DIRECTION, int);

	boolean  SetTilePiece(int, int, TileSet*, TileSet::TILETYPE);

	void GetCellType(int, int, CELLTYPE*);
	TileSet::TILETYPE GetTileType(int, int, TileSet*);
	void GetTileTypeNine(int, int, TileSet::TILETYPE*, TileSet*);


};

#endif
