#include "dungeondifficulty.h"

DungeonDifficulty::DungeonDifficulty() {
}
DungeonDifficulty::~DungeonDifficulty() {
}
void DungeonDifficulty::Init() {
	base_floorsize = 32;
	base_room_num = 2;
	base_road_rate = 0.0;
	base_trap_amount = 0;
	base_item_amount = 20;
	base_monsterhouse_rate = 0.2;
	base_enemy_param = 0;

	max_floorsize = 64;
	max_room_num = 16;
	max_road_rate = 1.0;
	max_trap_amount = 50;
	max_item_amount = 5;
	max_monsterhouse_rate = 1.0;
	max_enemy_param = 100;

	max_param = 20;
}

double DungeonDifficulty::Param_convert(int param) {
	double i = double(param) / double(max_param);
	if (i > 1.0) {
		i = 1.0;
	}
	return i;
}

int DungeonDifficulty::FloorSize(int diff_param) {
	return (int)(base_floorsize + (double)(max_floorsize - base_floorsize) * Param_convert(diff_param));
}
int DungeonDifficulty::RoomNum(int diff_param){
	return (int)(base_room_num + (double)(max_room_num - base_room_num) * Param_convert(diff_param));
}
double DungeonDifficulty::DungeonDifficulty::RoadRate(int diff_param) {
	return (double)(base_road_rate + (double)(max_road_rate - base_road_rate) * Param_convert(diff_param));
}
int DungeonDifficulty::TrapAmount(int diff_param) {
	return (int)(base_trap_amount + (double)(max_trap_amount - base_trap_amount) * Param_convert(diff_param));
}
int DungeonDifficulty::ItemAmount(int diff_param) {
	return (int)(base_item_amount + (double)(max_item_amount - base_item_amount) * Param_convert(diff_param));
}
double DungeonDifficulty::MonsterHouseRate(int diff_param) {
	return (double)(base_monsterhouse_rate + (double)(max_monsterhouse_rate - base_monsterhouse_rate) * Param_convert(diff_param));
}
int DungeonDifficulty::EnemyParam(int diff_param) {
	return (int)(base_enemy_param + (double)(max_enemy_param - base_enemy_param) * Param_convert(diff_param));
}

int DungeonDifficulty::GetParamNum() {
	return 7;//floorsizeÇÕ2Ç¬ï™égÇ§ÇÃÇ≈íçà”ÅB
}

//int DungeonDifficulty::