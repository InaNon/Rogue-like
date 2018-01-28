#include "autocellimage.h"
#include "Dxlib.h"
#include "define.h"

AutoCellImage::AutoCellImage() {
};
AutoCellImage::~AutoCellImage() {
};

void AutoCellImage::LoadFile(std::string m_filename, int m_x, int m_y) {
	LoadDivGraph(m_filename.c_str(), 15, 3, 5, CHIP_X_SIZE / 2 / ZOOM, CHIP_Y_SIZE / 2 / ZOOM, graphic_handle_auto);
}

int AutoCellImage::GetGraphicHandle(int i) {
	return graphic_handle_auto[i];
}