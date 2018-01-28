#include "cellgraphic.h"
#include "DxLib.h"
#include "define.h"
#include "celldata.h"
#include "camera.h"
#include "trapdata.h"
#include "tileimage.h"


const int CellGraphic::ANIME_TIME = 30;
const int CellGraphic::CELL_GRAPHIC_X = 32 * 2;
const int CellGraphic::CELL_GRAPHIC_Y = 32 * 2;


CellGraphic::CellGraphic() {
}

CellGraphic::CellGraphic(int m_cx, int m_cy) {
	cx = m_cx;
	cy = m_cy;
}

CellGraphic::CellGraphic(int m_cx, int m_cy, Cell* _cell) {
	cx = m_cx;
	cy = m_cy;
	cell = _cell;
}

CellGraphic::~CellGraphic() {
}

void CellGraphic::Clear() {
}

void CellGraphic::Draw(Camera* m_camera, bool trapdrawmode, int time) {
	int zoom = 1;

	int m_x = m_camera->GetDrawX(cx*CELL_GRAPHIC_X);
	int m_y = m_camera->GetDrawY(cy*CELL_GRAPHIC_Y);

	int buf_graphic_handle[4];

	for (int i = 0; i < 4; i++) {
		buf_graphic_handle[i] = graphic_handle[i][time % (ANIME_TIME * anime) / ANIME_TIME];
	}


	if (!m_camera->GetDrawf(cx*CELL_GRAPHIC_X + CELL_GRAPHIC_X / 2, cy*CELL_GRAPHIC_Y + CELL_GRAPHIC_Y / 2, CELL_GRAPHIC_X, CELL_GRAPHIC_Y)) {
		return;
	}

	DrawExtendGraph(m_x, m_y, m_x + CELL_GRAPHIC_X / 2, m_y + CELL_GRAPHIC_Y / 2, buf_graphic_handle[0], false);
	DrawExtendGraph(m_x + CELL_GRAPHIC_X / 2, m_y, m_x + CELL_GRAPHIC_X, m_y + CELL_GRAPHIC_Y / 2, buf_graphic_handle[1], false);
	DrawExtendGraph(m_x, m_y + CELL_GRAPHIC_Y / 2, m_x + CELL_GRAPHIC_X / 2, m_y + CELL_GRAPHIC_Y, buf_graphic_handle[2], false);
	DrawExtendGraph(m_x + CELL_GRAPHIC_X / 2, m_y + CELL_GRAPHIC_Y / 2, m_x + CELL_GRAPHIC_X, m_y + CELL_GRAPHIC_Y, buf_graphic_handle[3], false);

}

/* Setter */
void CellGraphic::SetCx(int m_cx) {
	cx = m_cx;
};
void CellGraphic::SetCy(int m_cy) {
	cy = m_cy;
};
void CellGraphic::SetCell(Cell* _cell) {
	cell = _cell;
};

void CellGraphic::SetGraphicHandle(int m_graphic_handle, int i, int j) {
	graphic_handle[i][j] = m_graphic_handle;
};

void CellGraphic::SetAnime(int _anime) {
	anime = _anime;
};

/* Getter */
Cell* CellGraphic::GetCell() {
	return cell;
}


