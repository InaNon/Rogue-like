#include "autocellimage.h"
#include "Dxlib.h"
#include "define.h"

AutoCellImage::AutoCellImage() {
};
AutoCellImage::~AutoCellImage() {
};

void AutoCellImage::LoadFile(std::string m_filename, int m_x, int m_y) {
	LoadDivGraph(m_filename.c_str(), AUTO_CELL_TYPE_NUM, 3, 5, CHIP_X_SIZE / 2, CHIP_Y_SIZE / 2, graphic_handle_auto);
}

int AutoCellImage::GetGraphicHandle(int i) {
	return graphic_handle_auto[i];
}