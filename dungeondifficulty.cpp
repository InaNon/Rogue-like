#include "dungeondifficulty.h"

DungeonDifficulty::DungeonDifficulty() {
}
DungeonDifficulty::~DungeonDifficulty() {
}
void DungeonDifficulty::Init() {
	base_floorsize = 20;
	base_room_num = 2;
	base_road_rate = 0.0;
	base_trap_amount = 0;
	base_item_amount = 20;
	base_monsterhouse_rate = 0.0;
	base_enemy_param = 0;

	half_floorsize = 100;
	half_room_num = 20;
	half_road_rate = 0.8;
	half_trap_amount = 30;
	half_item_amount = 5;
	half_monsterhouse_rate = 0.8;
	half_enemy_param = 100;

	max_param = 50;
}

double DungeonDifficulty::Param_convert(int param) {
	return double(max_param - param) / double(max_param);
}

int DungeonDifficulty::FloorSize(int diff_param) {
	return (int)(base_floorsize + 2.0 * (double)(half_floorsize - base_floorsize) * Param_convert(diff_param));
}
int DungeonDifficulty::RoomNum(int diff_param){
	return (int)(base_room_num + 2.0 * (double)(half_room_num - base_room_num) * Param_convert(diff_param));
}
double DungeonDifficulty::DungeonDifficulty::RoadRate(int diff_param) {
	return (double)(base_road_rate + 2.0 * (double)(half_road_rate - base_road_rate) * Param_convert(diff_param));
}
int DungeonDifficulty::TrapAmount(int diff_param) {
	return (int)(base_trap_amount + 2.0 * (double)(half_trap_amount - base_trap_amount) * Param_convert(diff_param));
}
int DungeonDifficulty::ItemAmount(int diff_param) {
	return (int)(base_item_amount + 2.0 * (double)(half_item_amount - base_item_amount) * Param_convert(diff_param));
}
double DungeonDifficulty::MonsterHouseRate(int diff_param) {
	return (double)(base_monsterhouse_rate + 2.0 * (double)(half_monsterhouse_rate - base_monsterhouse_rate) * Param_convert(diff_param));
}
int DungeonDifficulty::EnemyParam(int diff_param) {
	return (int)(base_enemy_param + 2.0 * (double)(half_enemy_param - base_enemy_param) * Param_convert(diff_param));
}

int DungeonDifficulty::GetParamNum() {
	return 7;//floorsizeÇÕ2Ç¬ï™égÇ§ÇÃÇ≈íçà”ÅB
}