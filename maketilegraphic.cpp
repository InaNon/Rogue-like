#include "maketilegraphic.h"
#include "tileimage.h"
#include "map.h"
#include "mapadmin.h"
#include "cell.h"
#include "celldata.h"
#include "tileset.h"
#include "tilesetadmin.h"
#include "autotileimage.h"

MakeTileGraphic::MakeTileGraphic() {
};
MakeTileGraphic::~MakeTileGraphic() {
};

void MakeTileGraphic::Init(MapAdmin* _map_admin, TileSetAdmin* _tile_set_admin) {
	map = _map_admin->GetMap();
	tile_set_admin = _tile_set_admin;
}

void MakeTileGraphic::MakeGraphic(int element) {
	tile_set = tile_set_admin->GetTileSet(element);


	TileSet::TILETYPE tile_type;

	for (int i = 0; i < map->GetSizeX(); i++) {
		for (int j = 0; j < map->GetSizeY(); j++) {
			tile_type = GetTileType(i, j, tile_set);
			if (SetTilePiece(i, j, tile_set, tile_type)) {
			}
			else {
				printfDx("Cannot SetTilePiece\n");
			};
		}
	}
	
	/*
	for (int i = 0; i < map->GetGraphicSizeX(); i++) {
		for (int j = 0; j < map->GetGraphicSizeY(); j++) {
			tile_type = GetTileType(i, j, tile_set);
			if (SetTilePiece(i, j, tile_set, tile_type)) {
			}
			else {
				printfDx("Cannot SetTilePiece\n");
			};
		}
	}
	*/

	return;
}
bool MakeTileGraphic::SetSimpleGraphicHandle(int _x, int _y, TileImage* _tile_image) {
	if (!_tile_image->IsSimple()) {
		return false;
	}
	for (int i = 0; i < 4 ; i++) {
		map->GetCell(_x, _y)->SetGraphicHandle(_tile_image->GetGraphicHandle(i), i , 0);
	}
	map->GetCell(_x, _y)->SetAnime(_tile_image->GetAnime());

	return true;
}

void MakeTileGraphic::SetGraphicHandle(int _x, int _y, TileImage* _tile_image, int onefromfour, int i) {
	for (int k = 0; k < _tile_image->GetAnime(); k++) {// Anime分をまとめて渡すループ
		map->GetCell(_x, _y)->SetGraphicHandle(_tile_image->GetGraphicHandle(i, onefromfour, k), onefromfour, k);
	}
	map->GetCell(_x, _y)->SetAnime(_tile_image->GetAnime());
}

void MakeTileGraphic::SetGraphicHandle(int _x, int _y, TileImage* _tile_image, DIRECTION _dir, int i) {
	int onefromfour = 0;
	if (_dir == UP_LEFT) {
		onefromfour = 0;
	}
	if (_dir == UP_RIGHT) {
		onefromfour = 1;
	}
	if (_dir == DOWN_LEFT) {
		onefromfour = 2;
	}
	if (_dir == DOWN_RIGHT) {
		onefromfour = 3;
	}
	return SetGraphicHandle(_x, _y, _tile_image, onefromfour, i);
}
/*
void MakeTileGraphic::SetGraphicHandle(int m_x, int m_y, TileSet* _tile_set, TileSet::TILETYPE _tyle_type, int onefromfour, int i) {
	SetGraphicHandle(m_x, m_y, _tile_set->GetTileImage(_tyle_type, 0), onefromfour, i); //0=種類
}
*/

boolean  MakeTileGraphic::SetTilePiece(int _x, int _y, TileSet* _tile_set, TileSet::TILETYPE _tile_type) {
	TileImage* _tile_image = _tile_set->GetTileImage(_tile_type, 0);

	if (_tile_image == NULL) {
		return false;
	}

	if (_tile_image->IsSimple()) {
		SetSimpleGraphicHandle(_x, _y, _tile_image);
		return true;
	}

	if (!_tile_image->IsAuto()) {
		return false;
	}
	//Autoなら以下の処理を行う

	TileSet::TILETYPE tile_type[(int)DIRECTION_NUM];
	GetTileTypeNine(_x, _y, tile_type, _tile_set);

	bool is_equal[(int)DIRECTION_NUM];

	for (int i = 0; i < (int)DIRECTION_NUM; i++) {
		is_equal[i] = false;

		if (tile_type[CENTER] == tile_type[i]) {
			is_equal[i] = true;
		}
		if ((i == (int)LEFT || i == (int)RIGHT) && tile_type[CENTER] == TileSet::WALL_FOUND && tile_type[i] == TileSet::WALL_WRAPPER) {
			is_equal[i] = true;
		}
		if ((i == (int)LEFT || i == (int)RIGHT) && tile_type[CENTER] == TileSet::HOLE_FOUND && tile_type[i] == TileSet::HOLE_WRAPPER) {
			is_equal[i] = true;
		}
	}

	bool flag = false;

	if (is_equal[(int)UP_LEFT] && is_equal[(int)UP] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_LEFT, AutoTileImage::ALL); }
	if (is_equal[(int)UP_RIGHT] && is_equal[(int)UP] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_RIGHT, AutoTileImage::ALL); }
	if (is_equal[(int)DOWN_LEFT] && is_equal[(int)DOWN] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_LEFT, AutoTileImage::ALL); }
	if (is_equal[(int)DOWN_RIGHT] && is_equal[(int)DOWN] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_RIGHT, AutoTileImage::ALL); }

	if (!is_equal[(int)UP_LEFT] && is_equal[(int)UP] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_LEFT, AutoTileImage::DENT); }
	if (!is_equal[(int)UP_RIGHT] && is_equal[(int)UP] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_RIGHT, AutoTileImage::DENT); }
	if (!is_equal[(int)DOWN_LEFT] && is_equal[(int)DOWN] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_LEFT, AutoTileImage::DENT); }
	if (!is_equal[(int)DOWN_RIGHT] && is_equal[(int)DOWN] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_RIGHT, AutoTileImage::DENT); }

	if (!is_equal[(int)UP] && !is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_LEFT, AutoTileImage::HOLD); }
	if (!is_equal[(int)UP] && !is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_RIGHT, AutoTileImage::HOLD); }
	if (!is_equal[(int)DOWN] && !is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_LEFT, AutoTileImage::HOLD); }
	if (!is_equal[(int)DOWN] && !is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_RIGHT, AutoTileImage::HOLD); }

	if (!is_equal[(int)UP] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_LEFT, AutoTileImage::SIDE); }
	if (!is_equal[(int)UP] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_RIGHT, AutoTileImage::SIDE); }
	if (!is_equal[(int)DOWN] && is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_LEFT, AutoTileImage::SIDE); }
	if (!is_equal[(int)DOWN] && is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_RIGHT, AutoTileImage::SIDE); }

	if (is_equal[(int)UP] && !is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_LEFT, AutoTileImage::LENG); }
	if (is_equal[(int)UP] && !is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, UP_RIGHT, AutoTileImage::LENG); }
	if (is_equal[(int)DOWN] && !is_equal[(int)LEFT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_LEFT, AutoTileImage::LENG); }
	if (is_equal[(int)DOWN] && !is_equal[(int)RIGHT]) { flag = true; SetGraphicHandle(_x, _y, _tile_image, DOWN_RIGHT, AutoTileImage::LENG); }

	return flag;
}


void MakeTileGraphic::GetCellType(int _x, int _y, CELLTYPE* _cell_type) {

	int buf_param[9][2] = {
		{ -1,-1 },
		{ 0,-1 },
		{ 1,-1 },
		{ -1,0 },
		{ 0,0 },
		{ 1,0 },
		{ -1,1 },
		{ 0,1 },
		{ 1,1 },
	};

	int buf_x, buf_y;

	for (int i = 0; i < 9; i++) {
		buf_x = _x + buf_param[i][0];
		buf_y = _y + buf_param[i][1];

		if (map->GetCellAcsessf(buf_x, buf_y)) {
		//if (map->GetCellGraphicAcsessf(buf_x, buf_y)) {
			_cell_type[i] = map->GetCell(buf_x, buf_y)->GetCellData()->GetCellType();
			//_cell_type[i] = map->GetCellGraphic(buf_x, buf_y)->GetCell()->GetCellData()->GetCellType();
		}
		else {
			_cell_type[i] = BOX_WALL; //近くとおなじに種類、に修正すべきかも
		}
	}

}


TileSet::TILETYPE MakeTileGraphic::GetTileType(int _x, int _y, TileSet* _tile_set) {
	//そのマスには、どのTileTypeが当てはまるかを返す

	CELLTYPE cell_type[(int)DIRECTION_NUM];
	GetCellType(_x, _y, cell_type);

	//周りのCellTypeと、そしてTileSetにラッパーがあるかないかによって決まる。なので、TlleSetの床穴壁に、ラッパーがあるかないかの関数を実装してやる必要がある
	if (cell_type[(int)CENTER] == ROOM_FLOOR || cell_type[(int)CENTER] == ROAD_FLOOR || cell_type[(int)CENTER] == TRAP_FLOOR) {
		return TileSet::FLOOR;
	}

	if (cell_type[(int)CENTER] == ROOM_STEP) {
		return TileSet::STEP_FLOOR;
	}

	/* WALL_STEPが未実装のため
	if (cell_type[(int)CENTER] == WALL_STEP) {
		return TileSet::STEP_WALL;
	}
	*/

	if (cell_type[(int)CENTER] == BOX_WALL) {
		if (_tile_set->isWrapperWall()) {
			if (cell_type[DOWN] == BOX_WALL) {
				return TileSet::WALL_WRAPPER;
			} else {
				if (cell_type[UP] == BOX_WALL) {
					return TileSet::WALL_FOUND;
				} else {
					return TileSet::WALL_MINI;
				}
			}
		}
		else {
			return TileSet::WALL;
		}
	}

	if (cell_type[(int)CENTER] == SLANT_WALL) {
		if (_tile_set->isWrapperHole()) {
			if (cell_type[UP] != SLANT_WALL) {
				return TileSet::HOLE_WRAPPER;
			} else {
				if (cell_type[UP] == SLANT_WALL) {
					return TileSet::HOLE_FOUND;
				}
				else {
					return TileSet::HOLE_MINI;
				}
			}
		}
		else {
			return TileSet::HOLE;
		}
	}

	if (cell_type[(int)CENTER] == SHOP_FLOOR) {
		return TileSet::SHOP_FLOOR;
	}

	return TileSet::WALL;
}

void MakeTileGraphic::GetTileTypeNine(int _x, int _y, TileSet::TILETYPE* _tile_type, TileSet* _tile_set) {

	int buf_param[9][2] = {
		{ -1,-1 },
		{ 0,-1 },
		{ 1,-1 },
		{ -1,0 },
		{ 0,0 },
		{ 1,0 },
		{ -1,1 },
		{ 0,1 },
		{ 1,1 },
	};

	int buf_x, buf_y;

	for (int i = 0; i < 9; i++) {
		buf_x = _x + buf_param[i][0];
		buf_y = _y + buf_param[i][1];

		if (map->GetCellAcsessf(buf_x, buf_y)) {
			_tile_type[i] = GetTileType(buf_x, buf_y, _tile_set);
		}
		else {
			_tile_type[i] = TileSet::WALL; //近くとおなじに種類、に修正すべきかも
		}
	}
}



