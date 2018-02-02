#include "MapAdmin.h"
#include "DxLib.h"
#include "map.h"
#include "cell.h"
#include "celldata.h"
#include "DxLib.h"
#include "sectionadmin.h"
#include "celldataadmin.h"
#include "trapdata.h"
#include "trapprocess.h"
#include "trapdataadmin.h"
#include "room.h"
#include "dungeondata.h"
#include "maketilegraphic.h"
#include "floordata.h"
#include "camera.h"
#include "mymethod.h"


MapAdmin::MapAdmin() {

};
MapAdmin::~MapAdmin() {
	delete map;
	delete section_admin;
	//delete expmap;
};

void MapAdmin::Init(CellDataAdmin* m_celldata_admin, TrapDataAdmin* m_trapdata_admin, TileSetAdmin* _tile_set_admin, Camera* _camera, TrapProcess* _trapProcess) {
	celldata_admin = m_celldata_admin;
	trapdata_admin = m_trapdata_admin;
	trapProcess = _trapProcess;
	camera = _camera;

	map = new Map(MAP_X_MAX, MAP_Y_MAX);
	//make_map_graphic = new MakeMapGraphic();

	make_tile_graphic = new MakeTileGraphic();
	make_tile_graphic->Init(this, _tile_set_admin);
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
	if (m_dir == UP) { m_move_x = 0; m_move_y = -1; }
	if (m_dir == UP_RIGHT) { m_move_x = 1; m_move_y = -1; }
	if (m_dir == UP_LEFT) { m_move_x = -1; m_move_y = -1; }
	if (m_dir == RIGHT) { m_move_x = 1; m_move_y = 0; }
	if (m_dir == LEFT) { m_move_x = -1; m_move_y = 0; }
	if (m_dir == DOWN_RIGHT) { m_move_x = 1; m_move_y = 1; }
	if (m_dir == DOWN_LEFT) { m_move_x = -1; m_move_y = 1; }
	if (m_dir == DOWN) { m_move_x = 0; m_move_y = 1; }
	if (m_move_x == 0 && m_move_y == 0) {
		return false;
	}
	return map->GetMovef_Conv(m_x, m_y, m_move_x, m_move_y);
}

bool MapAdmin::GetMovef_Conv(int m_x, int m_y, int m_move_x, int m_move_y) {
	return map->GetMovef_Conv(m_x, m_y, m_move_x, m_move_y);
}

bool MapAdmin::GetCellAcsessf(int m_x, int m_y) {

	return map->GetCellAcsessf(m_x, m_y);
}

void MapAdmin::GetRespawnCell(int* m_x, int* m_y) {
	Room* room;
	int x, y;

	std::vector<Room*> rooms = section_admin->GetSwapedRoom();
	for (int i = 0; (signed int)rooms.size(); i++) {
		room = rooms[i];
		std::vector<int> rs = MyMethod::RandomSwap(0, room->GetSizeX()*room->GetSizeY() - 1);
		for (int j = 0; (signed int)rs.size(); j++) {
			x = room->GetX() + rs[j] / room->GetSizeX();
			y = room->GetY() + rs[j] % room->GetSizeY();
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

void MapAdmin::GetRespawnCellFarAway(int* m_x, int* m_y, const int u_x, const int u_y, const int distance) {
	Room* room;
	int x, y;

	std::vector<Room*> rooms = section_admin->GetSwapedRoom();
	for (int i = 0; (signed int)rooms.size(); i++) {
		room = rooms[i];
		std::vector<int> rs = MyMethod::RandomSwap(0, room->GetSizeX()*room->GetSizeY() - 1);
		for (int j = 0; (signed int)rs.size(); j++) {
			x = room->GetX() + rs[j] / room->GetSizeX();
			y = room->GetY() + rs[j] % room->GetSizeY();
			if (GetSpawnf_Conv(x, y) && IsFarAwayByMapPosition(x, y, u_x, u_y, distance)) {
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

bool MapAdmin::IsInCameraByMapPosition(const int _x, const int _y) {
	return camera->GetDrawf_ul(_x *CHIP_X_SIZE, _y *CHIP_Y_SIZE, CHIP_X_SIZE, CHIP_Y_SIZE);
}

bool MapAdmin::IsFarAwayByMapPosition(const int _x, const int _y, const int u_x, const int u_y, const int distance) {
	return (u_x - _x)*(u_x - _x) + (u_y - _y)*(u_y - _y) > distance*distance;
}

// *** トラップ関係 ***

bool MapAdmin::IsTrapFloor(const int _x, const int _y) { //その床はトラップがあるか
	if (map->GetCellAcsessf(_x, _y)) {
		return map->GetCell(_x, _y)->GetCellData()->GetTrapf();
	}
	else {
		return false;
	}
}

bool MapAdmin::ActivateTrapFloor(const int _x, const int _y) { //その床にトラップがあればトラップを露呈させる
	if (map->GetCellAcsessf(_x, _y)) {
		if (IsTrapFloor(_x, _y)) {
			map->GetCell(_x, _y)->SetTrapActive(true);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool MapAdmin::TrapEvent(const int _x, const int _y) {
	//その床がトラップならトラップの処理を実行する(プレイヤーと同位置の時)
	if (map->GetCellAcsessf(_x, _y)) {
		if (map->GetCell(_x, _y)->GetCellData()->GetTrapf()) {
			trapProcess->Process(map->GetCell(_x, _y)->GetTrapData()->GetTrapType());
			return true;
		}
	}
	else {
		return false;
	}
	return false;
}


Room* MapAdmin::GetRandomRoom() {
	return section_admin->GetRandomRoom();
};
Room* MapAdmin::GetRandomRoom_Square() {
	return section_admin->GetRandomRoom_Square();
};

bool MapAdmin::GetRoomFloor(Room* m_room, int* r_x, int* r_y) {
	return section_admin->GetRoomFloor(m_room, r_x, r_y);
};
bool MapAdmin::GetFloorInRoom(Room* m_room, int* r_x, int* r_y) {
	return section_admin->GetFloorInRoom(m_room, r_x, r_y);
}
bool MapAdmin::GetRandomRoomFloor(int* r_x, int* r_y) {
	return section_admin->GetRandomRoomFloor(r_x, r_y);
}

Room* MapAdmin::GetRoom(int i) {
	return section_admin->GetRoom(i);
}
Room* MapAdmin::GetRoom(int m_x, int m_y) {
	return section_admin->GetRoom(m_x, m_y);
}


SectionAdmin* MapAdmin::GetSectionAdmin() {
	return section_admin;
}


void MapAdmin::GraphLoad() {
	LoadDivGraph("image/map.png", NUM_MAPCHIP, NUM_MAPCHIP, 1, CHIP_X_SIZE, CHIP_Y_SIZE, graphic_handle);
}


void MapAdmin::Draw(Camera* m_camera,bool trapdrawmode) {
	map->Draw(m_camera, trapdrawmode);
}

//DEBUG
void MapAdmin::SetMiniMap(MiniMap* _minimap) {
	minimap = _minimap;
}


void MapAdmin::MakeMap(DungeonData* m_dungeondata,int step) {
	map->Clear();

	section_admin = new SectionAdmin(this, celldata_admin, trapdata_admin);

	//DEBUG
	section_admin->SetMiniMap(minimap);

	section_admin->SetDungeonData(m_dungeondata);
	section_admin->SetFloorData(step);

	section_admin->DungeonMake();

	/*
	make_map_graphic->MakeMapGraphicInit(map);
	make_map_graphic->MakeGraphic();
	*/
	make_tile_graphic->MakeGraphic(m_dungeondata->GetFloorData(step)->GetElement());

	//m_dungeondata->PrintDungeonData(step);
}
/*
void MapAdmin::MapInit() {


	//delete map;
	//delete section_admin;

	//map = new Map(MAP_X_MAX, MAP_Y_MAX);



	if (DEBUG_MODE_MAP) {
		map = new Map(MAP_X_MAX - EXPCHIPSIZE_X, MAP_Y_MAX - EXPCHIPSIZE_Y);
	}
	else {
		map = new Map(MAP_X_MAX, MAP_Y_MAX);
	}
	//expmap = new Map(EXPMAP_X_MAX, EXPMAP_Y_MAX);


	section_admin = new SectionAdmin(this, celldata_admin, trapdata_admin);


	if (DEBUG_MODE_MAP) {
		int buf_map[MAP_X_MAX][MAP_Y_MAX] = {
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,1,1,5,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,2,2,2,2,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,2,3,3,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,4,1,1,1,1,1,1,1,4,4,4,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,4,1,1,1,1,1,1,1,1,1,4,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,4,1,1,1,1,1,1,1,1,1,4,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,4,4,4,4,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,4,4,4,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,4,4,4,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
			{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		};
		for (int i = 0; i < MAP_X_MAX; i++) {
			for (int j = 0; j < MAP_Y_MAX; j++) {
					map->GetCell(i, j)->SetCellData(celldata_admin->GetCellData((CELLTYPE)buf_map[i][j]));
			}
		}
	}
	else {
		//SectionAdmin* section_admin = new SectionAdmin(map, celldata_admin, trapdata_admin);
		//SectionAdmin* section_admin = new SectionAdmin(map);
		//section_admin->SectionAdminClear();
		section_admin->DungeonMake();
	}


	make_map_graphic->MakeMapGraphicInit(map);



	make_map_graphic->MakeGraphic();



	for (int i = 0; i < MAP_X_MAX; i++) {
		for (int j = 0; j < MAP_Y_MAX; j++) {
			if (map->GetCell(i, j)->GetCellData() != NULL) {
				if (
					map->GetCell(i, j)->GetCellData()->GetMovef() &&
					map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					!map->GetCell(i, j)->GetCellData()->GetStepf() &&
					map->GetCell(i, j)->GetCellData()->GetRoomf()) {

					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[1], 0);
				}
				if (
					map->GetCell(i, j)->GetCellData()->GetMovef() &&
					map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					!map->GetCell(i, j)->GetCellData()->GetStepf() &&
					!map->GetCell(i, j)->GetCellData()->GetRoomf()) {
					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[1], 0);
				}

				if (
					!map->GetCell(i, j)->GetCellData()->GetMovef() &&
					!map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					!map->GetCell(i, j)->GetCellData()->GetStepf()) {
					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[2], 0);
				}
				if (
					!map->GetCell(i, j)->GetCellData()->GetMovef() &&
					map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					!map->GetCell(i, j)->GetCellData()->GetStepf()) {
					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[4], 0);
				}

				if (
					map->GetCell(i, j)->GetCellData()->GetMovef() &&
					map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					map->GetCell(i, j)->GetCellData()->GetStepf() &&
					!map->GetCell(i, j)->GetCellData()->GetRoomf()) {
					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[3], 0);
				}

				if (
					map->GetCell(i, j)->GetCellData()->GetMovef() &&
					map->GetCell(i, j)->GetCellData()->GetSlantMovef() &&
					map->GetCell(i, j)->GetCellData()->GetStepf() &&
					map->GetCell(i, j)->GetCellData()->GetRoomf()) {
					map->GetCell(i, j)->SetGraphicHandle(graphic_handle[3], 0);
				}
			}

		}
	}
	
	

	//printfDx("MapInit is completed.\n");
}
*/
