#include "cell.h"
#include "DxLib.h"
#include "define.h"
#include "celldata.h"
#include "camera.h"
#include "trapdata.h"
#include "tileimage.h"

/*
cellimageä÷åWçÏê¨íÜ
cellÇ™handleÇ4Ç¬éùÇ¬ÇÃÇ™Ç‚Ç‚ãCÇ…Ç»ÇÈÇ™
Ç±Ç±Ç…autocellimageÇ…ÇÊÇÈåãâ Çäiî[ÅAà»ç~ÇÃåvéZÇè»ó™Ç∑ÇÈó\íË

*/

const int Cell::ANIME_TIME = 30;


Cell::Cell() {
	celldata = NULL;
	//celltype = NONE_CELLTYPE;

}

Cell::Cell(int m_cx, int m_cy) {
	cx = m_cx;
	cy = m_cy;
	celldata = NULL;
}

Cell::Cell(int m_cx,int m_cy,int m_graphic_handle) {
	cx = m_cx;
	cy = m_cy;
	celldata = NULL;
	//graphic_handle[0] = m_graphic_handle;
}

Cell::~Cell() {
}

void Cell::Clear() {
	temporary_cell = false;

	celldata = NULL;
	trapdata = NULL;

	/*
	for (int i = 0; i < 4; i++) {
		graphic_handle[i] = 0;
	}
	*/

	//tile_image = NULL;
}

void Cell::Draw(Camera* m_camera, bool trapdrawmode, int time) {
	if (celldata == NULL) {
		return;
	}
	int zoom = ZOOM;//ÉZÉãÇÃägëÂó¶

	int m_x = m_camera->GetDrawX(cx*CHIP_X_SIZE);
	int m_y = m_camera->GetDrawY(cy*CHIP_Y_SIZE);

	int buf_graphic_handle[4];

	for (int i = 0; i < 4; i++) {
		buf_graphic_handle[i] = graphic_handle[i][time % (ANIME_TIME * anime) / ANIME_TIME];
	}


	if (!m_camera->GetDrawf(cx*CHIP_X_SIZE + CHIP_X_SIZE / 2, cy*CHIP_Y_SIZE + CHIP_Y_SIZE / 2, CHIP_X_SIZE, CHIP_Y_SIZE)) {
		return;
	}

	if (trapdrawmode) {
		if (isTrapActive && celldata->GetTrapf()) {
			GetTrapData()->Draw(m_camera, cx, cy);
		}
	}
	else {
		DrawExtendGraph(m_x, m_y, m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE / 2, buf_graphic_handle[0], false);
		DrawExtendGraph(m_x + CHIP_X_SIZE / 2 , m_y, m_x + CHIP_X_SIZE, m_y + CHIP_Y_SIZE / 2, buf_graphic_handle[1], false);
		DrawExtendGraph(m_x, m_y + CHIP_Y_SIZE / 2, m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE, buf_graphic_handle[2], false);
		DrawExtendGraph(m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE / 2, m_x + CHIP_X_SIZE, m_y + CHIP_Y_SIZE, buf_graphic_handle[3], false);
	}

}

/* Setter */
void Cell::SetCx(int m_cx) {
	cx = m_cx;
};
void Cell::SetCy(int m_cy) {
	cy = m_cy;
};

void Cell::SetCellData(CellData* m_celldata) {
	celldata = m_celldata;
}
void Cell::SetTrapData(TrapData* m_trapdata) {
	trapdata = m_trapdata;
}
void Cell::SetTemporaryCell(bool m_temporary_cell) {
	temporary_cell = m_temporary_cell;
}

void Cell::SetTrapActive(bool _isTrapActive) {
	isTrapActive =_isTrapActive;
}

/*
void Cell::SetGraphicHandle(int m_graphic_handle,int i) {
	graphic_handle[i] = m_graphic_handle;
};
*/

void Cell::SetGraphicHandle(int m_graphic_handle, int i, int j) {
	graphic_handle[i][j] = m_graphic_handle;
};

void Cell::SetAnime(int _anime) {
	anime = _anime;
};



/*
void Cell::SetGraphicHandle(int* m_graphic_handle) {
	for (int i = 0; i < (signed int)graphic_handle.size(); i++) {
		graphic_handle[i].push_back(m_graphic_handle[i]);
	}
};
*/
/*
void Cell::SetTileImage(TileImage* _tile_image) {
	tile_image = _tile_image;
}
*/


/*
void Cell::SetCellType(CELLTYPE m_celltype) {
	celltype = m_celltype;
}
void Cell::SetTemporaryCell(bool m_temporary_cell) {
	temporary_cell = m_temporary_cell;
}

void Cell::SetCellTypeConverter(CellTypeConverter* m_celltype_converter) {
	celltype_converter = m_celltype_converter;
}

CELLTYPE Cell::GetCellType() {
	return celltype;
}
*/

/* Getter */

bool Cell::GetMovef() {
	return celldata->GetMovef();
}
/*

bool Cell::GetMovef() {
	return celltype_converter->GetMovef(celltype);
}
*/

CellData* Cell::GetCellData() {
	return celldata;
}

TrapData* Cell::GetTrapData() {
	return trapdata;
}

bool Cell::GetTemporaryCell() {
	return temporary_cell;
}

bool Cell::IsTrapActive() {
	return isTrapActive;
}

/*
TileImage* Cell::GetTileImage() {
	return tile_image;
}
*/





