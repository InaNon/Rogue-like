#include "MapAdmin.h"
#include "DxLib.h"
#include "map.h"
#include "cell.h"
#include "celldata.h"
#include "DxLib.h"
#include "sectionadmin.h"
#include "makemapgraphic.h"
#include "celldataadmin.h"
#include "trapdataadmin.h"
#include "room.h"
#include "dungeondata.h"


MapAdmin::MapAdmin() {

};
MapAdmin::~MapAdmin() {
	delete map;
	delete section_admin;
	//delete expmap;
};

void MapAdmin::Init(CellDataAdmin* m_celldata_admin, TrapDataAdmin* m_trapdata_admin) {
	celldata_admin = m_celldata_admin;
	trapdata_admin = m_trapdata_admin;

	map = new Map(MAP_X_MAX, MAP_Y_MAX);
	make_map_graphic = new MakeMapGraphic();
}

Map* MapAdmin::GetMap() {
	return map;
}
/*
Map* MapAdmin::GetExpMap() {
	return expmap;
}
*/


Cell* MapAdmin::GetMapCell(int m_x, int m_y) {
	return map->GetCell(m_x, m_y);
};

CellData* MapAdmin::GetMapCellData(int m_x, int m_y) {
	return GetMapCell(m_x, m_y)->GetCellData();
};

CELLTYPE MapAdmin::GetMapCellType(int m_x, int m_y) {
	return GetMapCellData(m_x, m_y)->GetCellType();
};

bool MapAdmin::GetSpawnf_Conv(int m_x, int m_y) {
	return GetMapCellData(m_x, m_y)->GetSpawnf();
}

bool MapAdmin::GetMovef_Conv(int m_x, int m_y, COMMAND m_dir) {
	int m_move_x = 0;
	int m_move_y = 0;
	if (m_dir == UP)			{ m_move_x = 0; m_move_y = -1; }
	if (m_dir == UP_RIGHT)		{ m_move_x = 1; m_move_y = -1; }
	if (m_dir == UP_LEFT)		{ m_move_x = -1; m_move_y = -1; }
	if (m_dir == RIGHT)			{ m_move_x = 1; m_move_y = 0; }
	if (m_dir == LEFT)			{ m_move_x = -1; m_move_y = 0; }
	if (m_dir == DOWN_RIGHT)	{ m_move_x = 1; m_move_y = 1; }
	if (m_dir == DOWN_LEFT)		{ m_move_x = -1; m_move_y = 1; }
	if (m_dir == DOWN)			{ m_move_x = 0; m_move_y = 1; }
	if (m_move_x == 0 && m_move_y == 0) {
		return false;
	}
	return map->GetMovef_Conv(m_x, m_y, m_move_x, m_move_y);
}

bool MapAdmin::GetMovef_Conv(int m_x, int m_y,int m_move_x,int m_move_y) {
	return map->GetMovef_Conv(m_x, m_y, m_move_x, m_move_y);
}

bool MapAdmin::GetCellAcsessf(int m_x, int m_y) {

	return map->GetCellAcsessf(m_x, m_y);
}

void MapAdmin::GetRespawnCell(int* m_x, int* m_y) {
	Room* room;
	int x, y, c1, c2;
	c1 = 0;
	while (1) {
		if (c1++ > 1000) { break; }
		room = section_admin->GetRandomRoom_Square();
		c2 = 0;
		while (1) {
			if (c2++ > 1000) { break; }
			x = room->GetX()+GetRand(room->GetSizeX() - 1);
			y = room->GetY()+GetRand(room->GetSizeY() - 1);
			if (GetSpawnf_Conv(x, y)) {
				*m_x = x;
				*m_y = y;
				return;
			}
		}
	}

	*m_x = -1;
	*m_y = -1;
	return;
};


SectionAdmin* MapAdmin::GetSectionAdmin() {
	return section_admin;
}


void MapAdmin::GraphLoad() {
	LoadDivGraph("image/map.png", NUM_MAPCHIP, NUM_MAPCHIP, 1, CHIP_X_SIZE, CHIP_Y_SIZE, graphic_handle);
}


void MapAdmin::Draw(Camera* m_camera,bool trapdrawmode) {
	map->Draw(m_camera, trapdrawmode);
}



void MapAdmin::MakeMap(DungeonData* m_dungeondata,int step) {

	map->Clear();

	section_admin = new SectionAdmin(this, celldata_admin, trapdata_admin);
	section_admin->SetDungeonData(m_dungeondata);
	section_admin->SetFloorData(step);


	section_admin->DungeonMake();

	make_map_graphic->MakeMapGraphicInit(map);

	make_map_graphic->MakeGraphic();

}