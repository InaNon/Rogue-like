#include "enemy.h"
#include "unitadmin.h"
#include "unitdata.h"

void Enemy::Spawn(UnitData* spown_unit_data, int spawn_x, int spawn_y) {

	Unit::Spawn(spown_unit_data, spawn_x, spawn_y);

	level = unit_admin->GetFloorNum();
	max_hp = unit_data->GetStatus(UnitData::MAX_HP) + level*unit_data->GetStatus(UnitData::DELTA_MAX_HP);
	current_hp = max_hp;
	atk = unit_data->GetStatus(UnitData::ATK) + level*unit_data->GetStatus(UnitData::DELTA_ATK);
	def = unit_data->GetStatus(UnitData::DEF) + level*unit_data->GetStatus(UnitData::DELTA_DEF);
	spead = unit_data->GetStatus(UnitData::SPEED) + level*unit_data->GetStatus(UnitData::DELTA_SPEED);
	luk = unit_data->GetStatus(UnitData::LUK) + level*unit_data->GetStatus(UnitData::DELTA_LUK);
	exp = unit_data->GetStatus(UnitData::EXP) + level*unit_data->GetStatus(UnitData::DELTA_EXP);


	max_stomach = 100;
	current_stomach = 100;
	money;//値決めないとな
}

int Enemy::direction(){
		return direction_flag;
}

//プレイヤー移動のキー判定と位置更新、更新されたx,yはunit.cppのx,yで使われる
void Enemy::Update(int move) {

	if (exist == false) { return; }

	if (move == UP && move_flag == NOTHING) {
		move_flag = UP;
		direction_flag = UP;
		stop = y - 32;
	}

	if (move == UP_RIGHT && move_flag == NOTHING) {
		move_flag = UP_RIGHT;
		direction_flag = UP_RIGHT;
		stop = y - 32;
	}

	if (move == RIGHT && move_flag == NOTHING) {
		move_flag = RIGHT;
		direction_flag = RIGHT;
		stop = x + 32;
	}

	if (move == DOWN_RIGHT && move_flag == NOTHING) {
		move_flag = DOWN_RIGHT;
		direction_flag = DOWN_RIGHT;
		stop = y + 32;
	}

	if (move == DOWN && move_flag == NOTHING) {
		move_flag = DOWN;
		direction_flag = DOWN;
		stop = y + 32;
	}

	if (move == DOWN_LEFT && move_flag == NOTHING) {
		move_flag = DOWN_LEFT;
		direction_flag = DOWN_LEFT;
		stop = y + 32;
	}


	if (move == LEFT && move_flag == NOTHING) {
		move_flag = LEFT;
		direction_flag = LEFT;
		stop = x - 32;
	}

	if (move == UP_LEFT && move_flag == NOTHING) {
		move_flag = UP_LEFT;
		direction_flag = UP_LEFT;
		stop = y - 32;
	}

	if (move == STOP && move_flag == NOTHING)
		move_flag = STOP;

	if (move == ATTACK && move_flag == NOTHING) {
		//direction_flag = (COMMAND)(GetRand(7) + (int)UP);
		move_flag = ATTACK;
	}

}

int Enemy::Update() { return 0; }

void Enemy::LevelCheck(int add_exp) {}

int Enemy::GetCurrentSatiety() { return -1; }

Enemy::Enemy(int m_unit_num, int enemy_graphic_handle, UnitAdmin* m_unit_admin) {

	unit_num = m_unit_num;
	gphandle = enemy_graphic_handle;
	unit_admin = m_unit_admin;
	direction_flag = (COMMAND)(GetRand(7) + (int)UP);
	move_flag = NOTHING;

}



Enemy::~Enemy() {

}
