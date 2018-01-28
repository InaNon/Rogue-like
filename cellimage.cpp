#include "cellimage.h"
#include "Dxlib.h"
#include <string>

CellImage::CellImage() {
};
CellImage::~CellImage() {
};

void CellImage::LoadFile(std::string m_filename, int m_x, int m_y) {
	int handle = LoadGraph(m_filename.c_str());

	for (int i = 0; i < 4; i++) {
		graphic_handle[i] = DerivationGraph(m_x*CHIP_X_SIZE / ZOOM + (CHIP_X_SIZE / 2 / ZOOM)*(i % 2), m_y*CHIP_Y_SIZE / ZOOM + (CHIP_Y_SIZE / 2 / ZOOM)*(i / 2), CHIP_X_SIZE / 2 / ZOOM, CHIP_Y_SIZE / 2 / ZOOM, handle);
	}
}

int CellImage::GetGraphicHandle(int i) {
	return graphic_handle[i];
}