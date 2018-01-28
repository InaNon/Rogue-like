#include "autotileimage.h"
#include "Dxlib.h"
#include "define.h"

AutoTileImage::AutoTileImage() {
	is_auto = true;
	is_simple = false;
};
AutoTileImage::~AutoTileImage() {
};

//@Override
bool AutoTileImage::LoadHandle(int handle) {
	//画像サイズを獲得する
	int size_x, size_y;
	if (GetGraphSize(handle, &size_x, &size_y) == -1) {
		return false;
	}

	//チップ単位に変換
	int original_x = CHIP_X_SIZE / ZOOM;
	int original_y = CHIP_Y_SIZE / ZOOM;

	size_x /= original_x;
	size_y /= original_y;

	anime = size_x;

	if (size_y != 5) {
		return false;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < anime; k++) {
				gh[i][j][k] = DerivationGraph(
					k * original_x + (j % 2) * (original_x / 2),
					i * original_y + (j / 2) * (original_y / 2),
					original_x / 2, original_y / 2,
					handle);

				if (gh[i][j][k] == -1) {
					return false;
				}
			}
		}
	}

	return true;
}


//@Override
int AutoTileImage::GetGraphicHandle(int i, int j, int k) {
	if (i < 0 || i >5) {
		return -1;
	}
	if (j < 0 || j >4) {
		return -1;
	}
	return gh[i][j][k];
}

//@Override
int AutoTileImage::GetGraphicHandle(int j) {
	if (j < 0 || j >4) {
		return -1;
	}
	return gh[0][j][0];
}

//@Override
int AutoTileImage::GetAnime() {
	return anime;
}