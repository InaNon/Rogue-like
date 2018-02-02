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

void DungeonData::PrintDungeonData(int i) {
	printfDx("FloorsizeX %d\nFloorsizeY %d\nMakeroomNum[0] %d\nMakeroomNum[1] %d\nMakeroadRate %f\nTrapNum %d\nItemNum %d\nMonsterhouseRate %f\n",
		GetFloorData(i)->GetFloorsizeX(),
		GetFloorData(i)->GetFloorsizeY(),
		GetFloorData(i)->GetMakeroomNum(0),
		GetFloorData(i)->GetMakeroomNum(1),
		GetFloorData(i)->GetMakeroadRate(),
		GetFloorData(i)->GetTrapNum(),
		GetFloorData(i)->GetItemNum(),
		GetFloorData(i)->GetMonsterhouseRate());
}
