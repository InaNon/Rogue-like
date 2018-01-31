#include "makemapgraphic.h"
#include "cellimage.h"
#include "autocellimage.h"
#include "map.h"
#include "cell.h"
#include "celldata.h"

MakeMapGraphic::MakeMapGraphic() {
};
MakeMapGraphic::~MakeMapGraphic() {
};

void MakeMapGraphic::MakeMapGraphicInit(Map* m_map) {
	map = m_map;

	cell_image[(int)ROOM_FLOOR] = new CellImage();
	cell_image[(int)ROOM_FLOOR]->LoadFile("image/floor.png",0,0);
	//cell_image[(int)ROOM_FLOOR]->LoadFile("image/floor_cave.png", 0, 0);

	cell_image[(int)ROAD_FLOOR] = new CellImage();
	cell_image[(int)ROAD_FLOOR]->LoadFile("image/floor.png",0,0);
	//cell_image[(int)ROAD_FLOOR]->LoadFile("image/floor_cave.png", 0, 0);

	cell_image[(int)BOX_WALL] = new AutoCellImage();
	cell_image[(int)BOX_WALL]->LoadFile("image/box_wall.png",0,0);

	cell_image[(int)SLANT_WALL] = new AutoCellImage();
	cell_image[(int)SLANT_WALL]->LoadFile("image/slant_wall.png",0,0);
	//cell_image[(int)SLANT_WALL]->LoadFile("image/slant_wall_cave.png",0,0);

	cell_image[(int)ROOM_STEP] = new CellImage();
	cell_image[(int)ROOM_STEP]->LoadFile("image/floor.png",1,0);
	//cell_image[(int)ROOM_STEP]->LoadFile("image/floor_cave.png", 1, 0);

	cell_image[(int)ROAD_STEP] = new CellImage();
	cell_image[(int)ROAD_STEP]->LoadFile("image/floor.png",1,0);
	//cell_image[(int)ROAD_STEP]->LoadFile("image/floor_cave.png", 1, 0);

	cell_image[(int)TRAP_FLOOR] = new CellImage();
	cell_image[(int)TRAP_FLOOR]->LoadFile("image/floor.png", 0, 0);
	//cell_image[(int)TRAP_FLOOR]->LoadFile("image/floor_cave.png", 0, 0);

	cell_image[(int)SHOP_FLOOR] = new CellImage();
	cell_image[(int)SHOP_FLOOR]->LoadFile("image/floor.png", 2, 0);
}



void MakeMapGraphic::MakeGraphic() {
	for (int i = 0; i < map->GetSizeX(); i++) {
		for (int j = 0; j < map->GetSizeY(); j++) {

			switch ((int)map->GetCell(i, j)->GetCellData()->GetCellType()) {
			case((int)ROOM_FLOOR) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)ROAD_FLOOR) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)BOX_WALL) :
				SetAutoCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)SLANT_WALL) :
				SetAutoCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)ROOM_STEP) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)ROAD_STEP) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)TRAP_FLOOR) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			case((int)SHOP_FLOOR) :
				SetCellGrahic(i, j, map->GetCell(i, j)->GetCellData()->GetCellType());
				break;
			}

		}
	}
}

void MakeMapGraphic::SetCellGrahic(int m_x, int m_y, CELLTYPE m_celltype) {

	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(0), 0);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(1), 1);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(2), 2);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(3), 3);
}

void MakeMapGraphic::SetAutoCellGrahic(int m_x, int m_y, CELLTYPE m_celltype) {

	bool buf_flag[9];
	CELLTYPE buf_celltype = map->GetCell(m_x, m_y)->GetCellData()->GetCellType();

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


	/*周囲のCellType取得*/
	for (int i = 0; i < 9; i++) {
		if (
			m_x + buf_param[i][0] >= 0 &&
			m_y + buf_param[i][1] >= 0 &&
			m_x + buf_param[i][0] < map->GetSizeX() &&
			m_y + buf_param[i][1] < map->GetSizeY()) {
			if (buf_celltype == map->GetCell(m_x + buf_param[i][0], m_y + buf_param[i][1])->GetCellData()->GetCellType()) {
				buf_flag[i] = true;
			}
			else {
				buf_flag[i] = false;
			}
		}
		else {
			buf_flag[i] = true;
		}
	}

	/*セット開始*/

	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 0);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 1);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 2);
	map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 3);
	

	if (buf_flag[(int)UP_LEFT_CELL] && buf_flag[(int)UP_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL),0);
	}

	if (buf_flag[(int)UP_RIGHT_CELL] && buf_flag[(int)UP_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 1);
	}

	if (buf_flag[(int)DOWN_LEFT_CELL] && buf_flag[(int)DOWN_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 2);
	}

	if (buf_flag[(int)DOWN_RIGHT_CELL] && buf_flag[(int)DOWN_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(CENTER_CELL), 3);
	}


	if (!buf_flag[(int)UP_LEFT_CELL] && buf_flag[(int)UP_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_LEFT_EMPTY_CELL), 0);
	}

	if (!buf_flag[(int)UP_RIGHT_CELL] && buf_flag[(int)UP_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_RIGHT_EMPTY_CELL), 1);
	}

	if (!buf_flag[(int)DOWN_LEFT_CELL] && buf_flag[(int)DOWN_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_LEFT_EMPTY_CELL), 2);
	}

	if (!buf_flag[(int)DOWN_RIGHT_CELL] && buf_flag[(int)DOWN_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_RIGHT_EMPTY_CELL), 3);
	}


	if ( buf_flag[(int)UP_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(LEFT_CELL), 0);
	}

	if ( buf_flag[(int)UP_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(RIGHT_CELL), 1);
	}

	if ( buf_flag[(int)DOWN_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(LEFT_CELL), 2);
	}

	if ( buf_flag[(int)DOWN_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(RIGHT_CELL), 3);
	}


	if (!buf_flag[(int)UP_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_CELL), 0);
	}

	if (!buf_flag[(int)UP_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_CELL), 1);
	}

	if (!buf_flag[(int)DOWN_CELL] && buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_CELL), 2);
	}

	if (!buf_flag[(int)DOWN_CELL] && buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_CELL), 3);
	}
	

	
	if (!buf_flag[(int)UP_LEFT_CELL] && !buf_flag[(int)UP_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_LEFT_CELL), 0);
	}

	if (!buf_flag[(int)UP_RIGHT_CELL] && !buf_flag[(int)UP_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_RIGHT_CELL), 1);
	}

	if (!buf_flag[(int)DOWN_LEFT_CELL] && !buf_flag[(int)DOWN_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_LEFT_CELL), 2);
	}

	if (!buf_flag[(int)DOWN_RIGHT_CELL] && !buf_flag[(int)DOWN_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_RIGHT_CELL), 3);
	}
	

	if (buf_flag[(int)UP_LEFT_CELL] && !buf_flag[(int)UP_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_LEFT_CELL), 0);
	}

	if (buf_flag[(int)UP_RIGHT_CELL] && !buf_flag[(int)UP_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(UP_RIGHT_CELL), 1);
	}

	if (buf_flag[(int)DOWN_LEFT_CELL] && !buf_flag[(int)DOWN_CELL] && !buf_flag[(int)LEFT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_LEFT_CELL), 2);
	}

	if (buf_flag[(int)DOWN_RIGHT_CELL] && !buf_flag[(int)DOWN_CELL] && !buf_flag[(int)RIGHT_CELL]) {
		map->GetCell(m_x, m_y)->SetGraphicHandle(cell_image[(int)m_celltype]->GetGraphicHandle(DOWN_RIGHT_CELL), 3);
	}

}