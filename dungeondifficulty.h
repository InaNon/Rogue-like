#ifndef DEF_DungeonDifficulty
#define DEF_DungeonDifficulty

#include "Dxlib.h"

#include <vector>


class DungeonDifficulty {
private:
	int base_floorsize;
	int base_room_num;
	double base_road_rate;
	int base_trap_amount;
	int base_item_amount;
	double base_monsterhouse_rate;
	int base_enemy_param;

	int max_floorsize;
	int max_room_num;
	double max_road_rate;
	int max_trap_amount;
	int max_item_amount;
	double max_monsterhouse_rate;
	int max_enemy_param;

	int max_param;

public:
	DungeonDifficulty();
	~DungeonDifficulty();
	void Init();

	double Param_convert(int);
	int FloorSize(int);
	int RoomNum(int);
	double RoadRate(int);
	int TrapAmount(int);
	int ItemAmount(int);
	double MonsterHouseRate(int);
	int EnemyParam(int);

	int GetParamNum();

};

#endif

