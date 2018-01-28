#include "tileset.h"
#include "simpletileimage.h"
#include "autotileimage.h"
#include "DxLib.h"

#include "Windows.h"

const int TileSet::VAR_NUM = 4;
const std::string TileSet::DIR_NAME = "image\\tile\\";
const std::string TileSet::EXTENSION = "png";

TileSet::TileSet() {
	tile_image.resize(TILETYPE_NUM);
	for (int i = 0; i < (signed int)tile_image.size(); i++) {
		tile_image[i].resize(VAR_NUM);
	}

};
TileSet::~TileSet() {
	for (int i = 0; i < (signed int)tile_image.size(); i++) {
		for (int j = 0; j < (signed int)tile_image[i].size(); j++) {
			if (tile_image[i][j] != NULL) {
				delete tile_image[i][j];
			}
		}
	}
};
TileSet::TileSet(const TileSet &rhs) {
}

void TileSet::Init(std::string element_name) {
	//elementname = "lava" など

	//初期処理 4は最大アニメ枚数
	tile_image = std::vector<std::vector<TileImage*>>(TILETYPE_NUM, std::vector<TileImage*>(4));

	LoadTileImageAll(element_name);
};

std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& filename, const std::string& extension){
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> filenames;

	std::string search_name = dir_name +"\\" + filename + "." + extension;
	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	//該当ファイルがなかった場合
	if (hFind == INVALID_HANDLE_VALUE) {
		return filenames;
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		} else {
			filenames.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);
	return filenames;
}//https//qiita.com/tkymx/items/f9190c16be84d4a48f8a


TileImage* TileSet::GetTileImage(TileSet::TILETYPE _tiletype, int j) {
	return GetTileImage((int)_tiletype, j);
};


TileImage* TileSet::GetTileImage(int i, int j) {
	if ((i >= 0 && i < (signed int)tile_image.size()) && (j >= 0 && j < (signed int)tile_image[0].size())) {
		return tile_image[i][j];
	}
	else {
		return NULL;
	}
};

void TileSet::LoadTileImageAll(std::string element_name) {
	//ファイル検索用文字列
	std::string tiletype_name[TileSet::TILETYPE_NUM];
	tiletype_name[(int)TileSet::FLOOR] = "floor";
	tiletype_name[(int)TileSet::WALL] = "wall_s";
	tiletype_name[(int)TileSet::WALL_WRAPPER] = "wall_w";
	tiletype_name[(int)TileSet::WALL_FOUND] = "wall_f";
	tiletype_name[(int)TileSet::WALL_MINI] = "thing";
	tiletype_name[(int)TileSet::HOLE] = "hole_s";
	tiletype_name[(int)TileSet::HOLE_WRAPPER] = "hole_w";
	tiletype_name[(int)TileSet::HOLE_FOUND] = "hole_f";
	tiletype_name[(int)TileSet::HOLE_MINI] = "minihole";
	tiletype_name[(int)TileSet::STEP_FLOOR] = "step_f";
	tiletype_name[(int)TileSet::STEP_WALL] = "step_w";
	tiletype_name[(int)TileSet::SHOP_FLOOR] = "shop_floor";

	//該当ファイル名検索し、画像を読みこむ
	std::vector<std::string> filenames;
	std::string buf_element_name = element_name;//初期化を消さないこと
	for (unsigned int i = 0; i < TileSet::TILETYPE_NUM; i++) {
		filenames = GetFilePath(DIR_NAME + buf_element_name,"*"+tiletype_name[i]+"*", EXTENSION);
		if (filenames.size() == 0) {
			if (buf_element_name !="share") {
				if (i == (int)SHOP_FLOOR) {
					buf_element_name = "share";
					i--;
					continue;
				}
			}
		}
		for (unsigned int j = 0; j < filenames.size(); j++) {
			CompileTileImage(DIR_NAME + buf_element_name + "\\" + filenames[j], &tile_image[i][j]);
		}
		buf_element_name = element_name;
	}
	return;
};


bool TileSet::CompileTileImage(std::string _filename, TileImage** _tileimage) {
	//画像を読みこむ
	int handle = LoadGraph(_filename.c_str());
	if (handle == -1) {
		return false;
	}

	//画像サイズを獲得する
	int size_x, size_y;
	if (GetGraphSize(handle, &size_x, &size_y) == -1) {
		return false;
	}

	if ((size_x == CHIP_X_SIZE / ZOOM) && (size_y == CHIP_Y_SIZE / ZOOM)) {
		*_tileimage = new SimpleTileImage();
	} else if ((size_x % (CHIP_X_SIZE / ZOOM) == 0) && (size_y % (CHIP_Y_SIZE / ZOOM) == 0)) {
		*_tileimage = new AutoTileImage();
	}

	return (*_tileimage)->LoadHandle(handle);
}

bool TileSet::isWrapperWall() {
	return (tile_image[WALL_WRAPPER][0] != NULL && tile_image[WALL_FOUND][0] != NULL);
}
bool TileSet::isWrapperHole() {
	return (tile_image[HOLE_WRAPPER][0] != NULL && tile_image[HOLE_FOUND][0] != NULL);
}