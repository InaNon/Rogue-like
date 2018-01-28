#include "tileimage.h"

TileImage::TileImage() {
};
TileImage::~TileImage() {
};
TileImage::TileImage(const TileImage &rhs) {
}

int TileImage::GetAnime() {
	return -1;
}

bool TileImage::IsAuto() {
	return is_auto;
}
bool TileImage::IsSimple() {
	return is_simple;
}