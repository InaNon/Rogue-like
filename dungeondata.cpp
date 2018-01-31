#include "dungeondata.h"
#include "floordata.h"

DungeonData::DungeonData() {
}

DungeonData::~DungeonData() {
}

void DungeonData::Init(int floordata_num) {
	//インスタンス化
	for (int i = 0; i < floordata_num; i++) {
		floordata.push_back(new FloorData());
	}
}

int DungeonData::GetFloorNum() {
	return (signed int)floordata.size();
}

FloorData* DungeonData::GetFloorData(int i) {
	return floordata[i];
}

void DungeonData::EmplaceFloorData(int i) {
	while (1) {
		if ((signed int)floordata.size() >= i) {
			break;
		}
		floordata.emplace_back();
	}
}
