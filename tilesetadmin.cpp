#include "tilesetadmin.h"
#include "tileset.h"
#include "DxLib.h"

const int TileSetAdmin::TILE_SET_NUM = 5;


TileSetAdmin::TileSetAdmin() {
	for (int i = 0; i < TILE_SET_NUM; i++) {
		tile_set.push_back(new TileSet());
	}
}
TileSetAdmin::~TileSetAdmin() {
	for (int i = 0; i < (signed int)tile_set.size(); i++) {
		delete tile_set[i];
	}
};

void TileSetAdmin::Init() {
	GraphLoad();
}

void TileSetAdmin::GraphLoad() {
	std::string element_name;
	for (int i = 0; i < (signed int)tile_set.size(); i++) {

		if (i == 0) { element_name = "cave"; }
		if (i == 1) { element_name = "forest"; }
		if (i == 2) { element_name = "lava"; }
		if (i == 3) { element_name = "lake"; }
		if (i == 4) { element_name = "remains"; }

		tile_set[i]->LoadTileImageAll(element_name);
	}


}

TileSet* TileSetAdmin::GetTileSet(int element) {
	if (element >= 0 && element < (signed int)tile_set.size()) {
		return tile_set[element];
	}
	return NULL;
}