#include "minimap.h"
#include "Dxlib.h"
#include "unitadmin.h"
#include "unit.h"
#include "mapadmin.h"
#include "sectionadmin.h"
#include "section.h"
#include "room.h"
#include "celldata.h"

MiniMap::MiniMap() {
}
MiniMap::~MiniMap() {
}
void MiniMap::Init(MapAdmin* m_map_admin, UnitAdmin* m_unit_admin) {
	map_admin = m_map_admin;
	unit_admin = m_unit_admin;
	MiniMapClear();

	GraphLoad("image/minimap_dot.png");
}


void MiniMap::GraphLoad(std::string m_filename) {
	LoadDivGraph(m_filename.c_str(), MINIMAP_NUM, MINIMAP_NUM, 1, MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE, graphic_handle);
}

void MiniMap::MiniMapClear() {

	for (int i = 0; i < map_admin->GetMap()->GetSizeX(); i++) {
		for (int j = 0; j < map_admin->GetMap()->GetSizeY(); j++) {
			minimap[i][j] = false;
		}
	}

}


void MiniMap::Update(int num) {

	int m_x = unit_admin->GetUnit(num)->GetMAPX();
	int m_y = unit_admin->GetUnit(num)->GetMAPY();
	
	if (DEBUG_MINI_MAP_FULL_OPEN) {
		for (int i = 0; i < map_admin->GetMap()->GetSizeX(); i++) {
			for (int j = 0; j < map_admin->GetMap()->GetSizeY(); j++) {
				minimap[i][j] = true;
			}
		}
	}


	//プレイヤーの周囲を開示
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			if (m_x + i - 1 >= 0 &&
				m_y + j - 1 >= 0 &&
				m_x + i - 1 < map_admin->GetMap()->GetSizeX() &&
				m_y + j - 1 < map_admin->GetMap()->GetSizeY()) {

				minimap[m_x + i - 1][m_y + j - 1] = true;
			}
		}
	}
	
	//プレイヤーのいる部屋について全て開示
	
	Room* buf_room = map_admin->GetSectionAdmin()->GetRoom(m_x, m_y);
	
	if (buf_room == NULL) {
		return;
	}
	int room_x = buf_room->GetX();
	int room_y = buf_room->GetY();
	int room_sizex = buf_room->GetSizeX();
	int room_sizey = buf_room->GetSizeY();

	for (int i = 0; i < room_sizex + 2; i++) {
		for (int j = 0; j < room_sizey + 2; j++) {
			if (room_x + i - 1 >= 0 &&
				room_y + j - 1 >= 0 &&
				room_x + i - 1 < map_admin->GetMap()->GetSizeX() &&
				room_y + j - 1 < map_admin->GetMap()->GetSizeY()) {

				minimap[room_x + i - 1][room_y + j - 1] = true;
			}
		}
	}
	
}
void MiniMap::Draw() {

	for (int i = 0; i < map_admin->GetMap()->GetSizeX(); i++) {
		for (int j = 0; j < map_admin->GetMap()->GetSizeY(); j++) {
			if (minimap[i][j]) {
				if (map_admin->GetMapCellData(i,j)->GetMovef()) {
					DrawGraph(ORIGIN_WINDOWSIZE_X / 2 + i*MINIMAP_CELL_SIZE, j*MINIMAP_CELL_SIZE, graphic_handle[0], false);
				} else {
					if (map_admin->GetMapCellData(i, j)->GetSlantMovef()) {
						DrawGraph(ORIGIN_WINDOWSIZE_X / 2 + i*MINIMAP_CELL_SIZE, j*MINIMAP_CELL_SIZE, graphic_handle[1], false);
					};
				}
			}
		}
	}

	Room* buf_room_p = map_admin->GetSectionAdmin()->GetRoom(unit_admin->GetUnit(0)->GetMAPX(), unit_admin->GetUnit(0)->GetMAPY());
	Room* buf_room_e;
	for (int i = 0; i < UNIT_MAX; i++) {
		if (unit_admin->GetUnit(i)->GetExist()) {
			if (i == 0) {
				DrawGraph(ORIGIN_WINDOWSIZE_X /2+ unit_admin->GetUnit(i)->GetMAPX()*MINIMAP_CELL_SIZE, unit_admin->GetUnit(i)->GetMAPY()*MINIMAP_CELL_SIZE, graphic_handle[2], false);
			}
			else {
				buf_room_e = map_admin->GetSectionAdmin()->GetRoom(unit_admin->GetUnit(i)->GetMAPX(), unit_admin->GetUnit(i)->GetMAPY());
				if (buf_room_p == buf_room_e && buf_room_p != NULL || DEBUG_MINI_MAP_FULL_OPEN) {
					DrawGraph(ORIGIN_WINDOWSIZE_X / 2 + unit_admin->GetUnit(i)->GetMAPX()*MINIMAP_CELL_SIZE, unit_admin->GetUnit(i)->GetMAPY()*MINIMAP_CELL_SIZE, graphic_handle[3], false);
				}
			}

		}
	}
	//debug

	for (int i = 0; i < 16; i++) {
		if (map_admin->GetSectionAdmin()->GetRoom(i) != NULL) {
			std::vector<std::vector<int >> ec_all = map_admin->GetSectionAdmin()->GetRoom(i)->GetEntranceCell_All();
			
			for (int j = 0; j < map_admin->GetSectionAdmin()->GetRoom(i)->GetEntranceCellSize(); j++) {
				DrawGraph(ORIGIN_WINDOWSIZE_X / 2 + ec_all[j][0] * MINIMAP_CELL_SIZE, ec_all[j][1] * MINIMAP_CELL_SIZE, graphic_handle[4], false);
			}
		}
	}




}