#include "simpletileimage.h"
#include "Dxlib.h"
#include <string>

//SimpleTile‚ÍƒAƒjƒ‚µ‚È‚¢‚Æ‚·‚é

SimpleTileImage::SimpleTileImage() {
	is_auto = false;
	is_simple = true;
};
SimpleTileImage::~SimpleTileImage() {
};

//@Override
bool SimpleTileImage::LoadHandle(int handle) {
	for (int i = 0; i < 4; i++) {
		graphic_handle[i] = DerivationGraph((CHIP_X_SIZE / 2 / ZOOM)*(i % 2), (CHIP_Y_SIZE / 2 / ZOOM)*(i / 2), CHIP_X_SIZE / 2 / ZOOM, CHIP_Y_SIZE / 2 / ZOOM, handle);
		if (graphic_handle[i] == -1) {
			return false;
		}
	}
	return true;
}

//@Override
int SimpleTileImage::GetGraphicHandle(int i) {
	return graphic_handle[i];
}

//@Override
int SimpleTileImage::GetGraphicHandle(int i, int j, int k) {
	return graphic_handle[j];
}

//@Override
int SimpleTileImage::GetAnime() {
	return 1;
}