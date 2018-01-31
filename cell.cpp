#include "cell.h"
#include "DxLib.h"
#include "define.h"
#include "celldata.h"
#include "camera.h"
#include "trapdata.h"

/*
cellimageŠÖŒWì¬’†
cell‚ªhandle‚ğ4‚Â‚Â‚Ì‚ª‚â‚â‹C‚É‚È‚é‚ª
‚±‚±‚Éautocellimage‚É‚æ‚éŒ‹‰Ê‚ğŠi”[AˆÈ~‚ÌŒvZ‚ğÈ—ª‚·‚é—\’è

*/


Cell::Cell() {
	celldata = NULL;
	//celltype = NONE_CELLTYPE;
}

Cell::Cell(int m_cx, int m_cy) {
	cx = m_cx;
	cy = m_cy;
}

Cell::Cell(int m_cx,int m_cy,int m_graphic_handle) {
	cx = m_cx;
	cy = m_cy;
	graphic_handle[0] = m_graphic_handle;
}

Cell::~Cell() {
}

void Cell::Clear() {
	temporary_cell = false;
	trapf = false;

	celldata = NULL;
	trapdata = NULL;

	for (int i = 0; i < 4; i++) {
		graphic_handle[i] = 0;
	}
}

void Cell::Draw(Camera* m_camera, bool trapdrawmode) {
	if (celldata == NULL) {
		return;
	}

	int m_x = m_camera->GetDrawX(cx*CHIP_X_SIZE);
	int m_y = m_camera->GetDrawY(cy*CHIP_Y_SIZE);


	if (!m_camera->GetDrawf(cx*CHIP_X_SIZE + CHIP_X_SIZE / 2, cy*CHIP_Y_SIZE + CHIP_Y_SIZE / 2, CHIP_X_SIZE, CHIP_Y_SIZE)) {
		return;
	}

	if (trapdrawmode) {
		if (trapf && celldata->GetTrapf()) {
			GetTrapData()->Draw(m_camera, cx, cy);
		}
	}
	else {
		DrawExtendGraph(m_x, m_y, m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE / 2, graphic_handle[0], false);
		DrawExtendGraph(m_x + CHIP_X_SIZE / 2, m_y, m_x + CHIP_X_SIZE, m_y + CHIP_Y_SIZE / 2, graphic_handle[1], false);
		DrawExtendGraph(m_x, m_y + CHIP_Y_SIZE / 2, m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE, graphic_handle[2], false);
		DrawExtendGraph(m_x + CHIP_X_SIZE / 2, m_y + CHIP_Y_SIZE / 2, m_x + CHIP_X_SIZE, m_y + CHIP_Y_SIZE, graphic_handle[3], false);
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

void Cell::SetTrapf(bool m_trapf) {
	trapf = m_trapf;
}

void Cell::SetGraphicHandle(int m_graphic_handle,int i) {
	graphic_handle[i] = m_graphic_handle;
};
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

bool Cell::GetTrapf() {
	return trapf;
}




