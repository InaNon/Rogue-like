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
		graphic_handle[i] = DerivationGraph(m_x*CHIP_X_SIZE + (CHIP_X_SIZE / 2)*(i % 2), m_y*CHIP_Y_SIZE + (CHIP_Y_SIZE / 2)*(i / 2), CHIP_X_SIZE / 2, CHIP_Y_SIZE / 2, handle);
	}
}


int CellImage::GetGraphicHandle(int i) {
	return graphic_handle[i];
}