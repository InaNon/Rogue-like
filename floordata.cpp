#include "floordata.h"
#include "define.h"

FloorData::FloorData() {
	makeroom_num.reserve(5);
	makeroad_rate = 1.0;
	roomsize_min = 3;
	roomsize_max = 10;
	makemode = DEPTH_FIRST_RAND;
	shave_rate = 0;
	wallslant_f = false;
	shop_rate = 0.0;
}

FloorData::FloorData(const FloorData &rhs) {
}

FloorData::~FloorData() {

}


/* ゲッター */
int FloorData::GetMakeroomNum(int i) {
	if (i >= 0 && (signed int)makeroom_num.size() > i) {
		return makeroom_num[i];
	}
	return NULL;
}; //生成部屋数値
double FloorData::GetMakeroadRate() { return makeroad_rate; }; //生成道割合

int FloorData::GetFloorsizeX() { return floorsizex; };
int FloorData::GetFloorsizeY() { return floorsizey; };

int FloorData::GetRoomsizeMin() { return roomsize_min; }; //部屋幅最小値
int FloorData::GetRoomsizeMax() { return roomsize_max; }; //部屋高さ最大値

int FloorData::GetShopsizeMin() { return shopsize_min; };
int FloorData::GetShopsizeMax() { return shopsize_max; };

int FloorData::GetElement() { return element; };

int FloorData::GetEnemyParam() { return enemy_param; };

DUNGEON_MAKE_MODE FloorData::GetMakemode() { return makemode; }; //ダンジョン生成方式

double FloorData::GetShaveRate() { return shave_rate; }; //削り率

int FloorData::GetTrapNum() { return trap_num; }
int FloorData::GetItemNum() { return item_num; }

bool FloorData::GetWallSlant_f() { return wallslant_f; }; //壁斜め

double FloorData::GetShopRate() { return shop_rate; }; //部屋生成率

double FloorData::GetMonsterhouseRate() { return monsterhouse_rate; };
int FloorData::GetMonsterhouseNum() { return MONSTER_HOUSE_NUM; }


/* セッター */
void FloorData::SetMakeroomNum(int m_makeroom_num) {
	makeroom_num.push_back(m_makeroom_num);
}; //生成部屋数値

void FloorData::SetMakeroadRate(double m_makeroad_rate) { makeroad_rate = m_makeroad_rate; }; //生成道割合

void FloorData::SetFloorsizeX(int m_floorsizex) {
	if (m_floorsizex > MAP_X_MAX) {
		floorsizex = MAP_X_MAX;
	}
	else {
		floorsizex = m_floorsizex;
	}
};
void FloorData::SetFloorsizeY(int m_floorsizey) {
	if (m_floorsizey > MAP_Y_MAX) {
		floorsizey = MAP_Y_MAX;
	}
	else {
		floorsizey = m_floorsizey;
	}
};

void FloorData::SetShopsizeMin(int m_shopsize_min) { shopsize_min = m_shopsize_min; }
void FloorData::SetShopsizeMax(int m_shopsize_max) { shopsize_max = m_shopsize_max; }

void FloorData::SetRoomsizeMin(int m_roomsize_min) { roomsize_min = m_roomsize_min; }; //部屋最小値
void FloorData::SetRoomsizeMax(int m_roomsize_max) { roomsize_max = m_roomsize_max; }; //部屋最大値

void FloorData::SetElement(int m_element) { element = m_element; }

void FloorData::SetEnemyParam(int m_enemy_param) { enemy_param = m_enemy_param; }



void FloorData::SetMakemode(DUNGEON_MAKE_MODE m_makemode) { makemode = m_makemode; }; //ダンジョン生成方式

void FloorData::SetShaveRate(double m_shave_rate) { shave_rate = m_shave_rate; }; //削り率

void FloorData::SetWallSlant_f(bool m_wallslant_f) { wallslant_f = m_wallslant_f; }; //壁斜め

void FloorData::SetTrapNum(int m_trap_num) { trap_num = m_trap_num; };
void FloorData::SetItemNum(int m_item_num) { item_num = m_item_num; };

void FloorData::SetShopRate(double m_shop_rate) { shop_rate = m_shop_rate; }; //部屋生成率

void FloorData::SetMonsterhouseRate(double m_monsterhouse_rate) { monsterhouse_rate = m_monsterhouse_rate; };