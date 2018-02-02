#include "dungeondataadmin.h"
#include "dungeondata.h"
#include "floordata.h"
#include "dungeondifficulty.h"
#include <vector>


DungeonDataAdmin::DungeonDataAdmin() {

}
DungeonDataAdmin::~DungeonDataAdmin() {
}


void DungeonDataAdmin::Init(int dungeon_num, DungeonDifficulty* m_dungeon_difficulty) {
	//インスタンス化
	for (int i = 0; i < dungeon_num; i++) {
		dungeondata.push_back(new DungeonData());
	}

	dungeon_difficulty = m_dungeon_difficulty;
}



void DungeonDataAdmin::SetDungeonData(int dungeon_id) {
	int enemy_param, dungeon_param;

	dungeondata[0]->Init(100);//ポイント自体はいなが生成するので、残りを貰う
	for (int i = 0; i < 1; i++) {

		

		//ポイントの配布
		enemy_param = i / 2; //ここはいなと相談する。ダンジョンとモンスターへのポイント配布割合
		dungeon_param = i - enemy_param;

		dungeon_param = 50;


		int param_amount = dungeon_difficulty->GetParamNum();
		std::vector<int> distri_param(param_amount, 0);
		for (int j = 0; j < dungeon_param; j++) {
			distri_param[GetRand(distri_param.size() - 1)]++;
		}

		GetDungeonData(0)->GetFloorData(i)->SetMakemode(WIDTH_FIRST);

		GetDungeonData(0)->GetFloorData(i)->SetFloorsizeX(dungeon_difficulty->FloorSize(distri_param[0]));
		GetDungeonData(0)->GetFloorData(i)->SetFloorsizeY(dungeon_difficulty->FloorSize(distri_param[1]));
		GetDungeonData(0)->GetFloorData(i)->SetMakeroomNum(dungeon_difficulty->RoomNum(distri_param[2]));
		GetDungeonData(0)->GetFloorData(i)->SetMakeroadRate(dungeon_difficulty->RoadRate(distri_param[3]));
		GetDungeonData(0)->GetFloorData(i)->SetTrapNum(dungeon_difficulty->TrapAmount(distri_param[4]));
		GetDungeonData(0)->GetFloorData(i)->SetItemNum(dungeon_difficulty->ItemAmount(distri_param[5]));
		GetDungeonData(0)->GetFloorData(i)->SetMonsterhouseRate(dungeon_difficulty->MonsterHouseRate(distri_param[6]));

		GetDungeonData(0)->GetFloorData(i)->SetRoomsizeMin(3);
		GetDungeonData(0)->GetFloorData(i)->SetRoomsizeMax(15);
		GetDungeonData(0)->GetFloorData(i)->SetShopsizeMin(3);
		GetDungeonData(0)->GetFloorData(i)->SetShopsizeMax(7);
		GetDungeonData(0)->GetFloorData(i)->SetElement(0); //cave固定
		GetDungeonData(0)->GetFloorData(i)->SetShaveRate(0.4);
		GetDungeonData(0)->GetFloorData(i)->SetShopRate(1.0);

		GetDungeonData(0)->GetFloorData(i)->SetWallSlant_f(false);

	}

	//本来はデータベースから読み込むが適当に
	/*
	dungeondata[0]->Init(12);
	for (int i = 0; i < 12; i++) {
		GetDungeonData(0)->GetFloorData(i)->SetMakeroomNum(4);

		GetDungeonData(0)->GetFloorData(i)->SetMakeroadRate(0.6 + (double)GetRand(40) / 100.0);

		GetDungeonData(0)->GetFloorData(i)->SetRoomsizeMin(3);
		GetDungeonData(0)->GetFloorData(i)->SetRoomsizeMax(10);

		GetDungeonData(0)->GetFloorData(i)->SetFloorsizeX(60);
		GetDungeonData(0)->GetFloorData(i)->SetFloorsizeY(40);

		GetDungeonData(0)->GetFloorData(i)->SetShopsizeMin(3);
		GetDungeonData(0)->GetFloorData(i)->SetShopsizeMax(7);

		GetDungeonData(0)->GetFloorData(i)->SetElement(0);

		GetDungeonData(0)->GetFloorData(i)->SetShaveRate(0.2);

		GetDungeonData(0)->GetFloorData(i)->SetMakemode(DEPTH_FIRST_RAND);

		GetDungeonData(0)->GetFloorData(i)->SetShopRate(1.0);

		if (GetRand(1) == 0) {
			GetDungeonData(0)->GetFloorData(i)->SetWallSlant_f(false);
		}
		else {
			GetDungeonData(0)->GetFloorData(i)->SetWallSlant_f(true);
		}
	}
	*/

}

DungeonData* DungeonDataAdmin::GetDungeonData(int i) {
	return dungeondata[i];
}



