#include "map.h"
#include "cell.h"
#include "celldata.h"


Map::Map(int m_sizex,int m_sizey) {
	sizex = m_sizex+ EXPCHIPSIZE_X;
	sizey = m_sizey+ EXPCHIPSIZE_Y;
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			cell[i][j] = new Cell(i,j);
		}
	}
};

Map::~Map() {
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			delete cell[i][j];
		}
	}
};

void Map::Clear() { //Cell‚ð‚·‚×‚Ä‰Šú‰»‚·‚é
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			cell[i][j]->Clear();
		}
	}
}

Cell* Map::GetCell(int m_x, int m_y) {
	if (GetCellAcsessf(m_x, m_y)) {
		return cell[m_x][m_y];
	}
	else {

		printfDx("GetCellAcsessf NULL %d %d", m_x, m_y);
		WaitKey();

		return NULL;
	}
}

bool Map::GetMovef(int m_x, int m_y) {
		return GetCell(m_x, m_y)->GetMovef();
}

bool Map::GetCellAcsessf(int m_x, int m_y) {
	return (m_x >= 0 && m_y >= 0 && m_x < sizex && m_y < sizey);
}

bool Map::GetMovef_Conv(int m_x, int m_y, int m_move_x, int m_move_y) {
	if (!(GetCellAcsessf(m_x, m_y) && GetCellAcsessf(m_x + m_move_x, m_y + m_move_y))) {
		return false;
	}
	if (m_move_x <= 1 && m_move_x >= -1 && m_move_y <= 1 && m_move_y >= -1) {
		if (m_move_x * m_move_y == 0) {
			return cell[m_x + m_move_x][m_y + m_move_y]->GetMovef();
		}
		else {
			if (cell[m_x][m_y + m_move_y]->GetCellData()->GetSlantMovef() &&
				cell[m_x + m_move_x][m_y]->GetCellData()->GetSlantMovef() &&
				cell[m_x + m_move_x][m_y + m_move_y]->GetMovef()
				) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

void Map::Draw(Camera* m_camera,bool trapdrawmode) {
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			cell[i][j]->Draw(m_camera,trapdrawmode);
		}
	}
}

int Map::GetSizeX() {
	return sizex;
}

int Map::GetSizeY() {
	return sizey;
}