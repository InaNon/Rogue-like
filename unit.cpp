#include "unit.h"

#include "unitadmin.h"
#include "camera.h"
#include "unitdata.h"

void Unit::Spawn(UnitData* spown_unit_data, int spawn_x, int spawn_y) {

	Object::Spawn(spawn_x, spawn_y);

	if (spown_unit_data != NULL) {
		unit_data = spown_unit_data;
		object_name = unit_data->GetName();
	}


	reservation_map_x = spawn_x;
	reservation_map_y = spawn_y;
	direction_flag = (COMMAND)(GetRand(7) + int(UP));
}

//行動内容関数、trueベース、行動が始まるとfalse、行動が終わった瞬間true
bool Unit::Move() {

	if (exist == false) { return false; }

	if (move_flag == UP){
		y -= 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}

	if (move_flag == UP_RIGHT){
		x += 2;
		y -= 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}

	if (move_flag == RIGHT){
		x += 2;

		if (x == stop) {
			move_flag = NOTHING;
			return true;
		}

	}


	if (move_flag == DOWN_RIGHT){
		x += 2;
		y += 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}


	if (move_flag == DOWN){
		y += 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}

	if (move_flag == DOWN_LEFT){
		x -= 2;
		y += 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}

	if (move_flag == LEFT){
		x -= 2;

		if (x == stop) {
			move_flag = NOTHING;
			return true;
		}

	}


	if (move_flag == UP_LEFT){
		x -= 2;
		y -= 2;

		if (y == stop) {
			move_flag = NOTHING;
			return true;
		}
	}

	if (move_flag == STOP){
		turn_count++;
		if (turn_count == 16) {
			move_flag = NOTHING;
			turn_count = 0;
			return true;

		}
	}

	if (move_flag == ATTACK){
		attack_motion();
		if (turn_count == 16) {
			unit_admin->UnitStateCheck(this, unit_admin->UnitExistMap(map_x + direction_x(direction_flag), map_y + direction_y(direction_flag)));
			move_flag = NOTHING;
			turn_count = 0;
			return true;

		}
	}


	if (move_flag == NOTHING)
		return true;

	return false;
}

void Unit::ReservationMapPosition(COMMAND move_direction){

	reservation_map_x = map_x + direction_x(move_direction);
	reservation_map_y = map_y + direction_y(move_direction);
}

void Unit::UpdateMapPosition(){

	map_x = reservation_map_x;
	map_y = reservation_map_y;
}

void Unit::LevelCheck(int add_exp) {

	exp += add_exp;

	while (exp >= (level + 1)* (level + 1) * 10) {
		//レベルアップメッセージ
		level++;
		atk += unit_data->GetStatus(UnitData::DELTA_ATK) + (GetRand(2) - 1);
		max_hp += unit_data->GetStatus(UnitData::DELTA_MAX_HP) + (GetRand(2) - 1);
		current_hp += unit_data->GetStatus(UnitData::DELTA_MAX_HP) + (GetRand(2) - 1);
		def += unit_data->GetStatus(UnitData::DELTA_DEF) + (GetRand(2) - 1);
		spead += unit_data->GetStatus(UnitData::DELTA_SPEED) + (GetRand(2) - 1);
		luk += unit_data->GetStatus(UnitData::DELTA_LUK) + (GetRand(2) - 1);
	}
}

void Unit::Initialization() {

	reservation_map_x = 0;
	reservation_map_y = 0;
	turn_count = 0;
	level = 0;
	max_hp = 0;
	current_hp = 0;
	atk = 0;
	def = 0;
	spead = 0;
	luk = 0;
	exp = 0;
	banned_direction = NONE_DIRECTION;
	ban_unit_num = 0;

	for (int i = 0; i < COMMAND_MAX; i++)
		reservation_command[i] = NOTHING;

	push = 0;
	pop = 0;

	last_command = NOTHING;
	first_load_command = NOTHING;
}




















int Unit::GetReservationMapX() {

	return reservation_map_x;
}

int Unit::GetReservationMapY() {

	return reservation_map_y;
}

COMMAND Unit::GetMoveFlag() {

	return move_flag;
}

int Unit::GetLevel() {

	return level;
}


int Unit::GetAtk() {

	return atk;
}

int Unit::GetDef() {

	return def;
}

int Unit::GetMaxHP() {

	return max_hp;
}

void Unit::SetMaxHP(int m_max_hp) {

	max_hp = m_max_hp;
}

int Unit::GetCurrentHP() {

	return current_hp;
}

void Unit::SetCurrentHP(int m_current_hp) {

	current_hp = m_current_hp;
}

int Unit::GetMaxStomach() {

	return max_stomach;
}

void Unit::SetMaxStomach(int m_max_stomach) {

	max_stomach = m_max_stomach;
}

int Unit::GetCurrentStomach() {

	return max_stomach;
}

void Unit::SetCurrentStomach(int m_current_stomach) {

	current_stomach = m_current_stomach;
}

int Unit::GetATK() {

	return atk;
}

void Unit::SetATK(int m_atk) {

	atk = m_atk;
}
int Unit::GetDEF() {

	return def;
}

void Unit::SetDEF(int m_def) {

	def = m_def;
}

int Unit::GetExp() {

	return exp;
}

COMMAND Unit::GetFirstLoadCommand() {

	return first_load_command;
}

void Unit::SetFirstLoadCommand(COMMAND m_first_load_command) {

	first_load_command = m_first_load_command;
}

COMMAND Unit::GetLastCommand() {

	return last_command;
}

void Unit::SetLastCommand(COMMAND m_last_command) {

	last_command = m_last_command;
}

COMMAND Unit::GetReservationCommand() {

	COMMAND next_move;

	next_move = reservation_command[pop];
/*
	for (int i = pop; i < push; i++)
		printfDx("%d", reservation_command[i]);

	printfDx("\n");
*/
		pop++;

	if (pop == push)
		ResetReservationCommand();

	return next_move;
}

void Unit::SetReservationCommand(COMMAND move) {

	reservation_command[push] = move;
	push++;

}

COMMAND Unit::CheckReservationCommand() {

	return reservation_command[pop];
}

void Unit::ResetReservationCommand() {

	for (int i = 0; i < COMMAND_MAX; i++)
		reservation_command[i] = NOTHING;

	push = 0;
	pop = 0;
}

int Unit::GetUnitNum() {

	return unit_num;
}

COMMAND Unit::GetDirectionFlag() {

	return direction_flag;

}

void Unit::SetDirectionFlag(DIRECTION m_direction_flag) {

	direction_flag = (COMMAND)m_direction_flag;

}

DIRECTION Unit::GetBannedDirection() {

	return banned_direction;
}

void Unit::SetBannedDirection(DIRECTION m_banned_direction) {

	banned_direction = m_banned_direction;
}
int Unit::GetBanUnitNum() {

	return ban_unit_num;
}
void Unit::SetBannedUnitNum(int m_ban_unit_num) {

	ban_unit_num = m_ban_unit_num;
}

void Unit::SetForceCommand(COMMAND act) {
	//printfDx("a");
	move_flag = NOTHING;
	ReservationMapPosition(act);
	Update(act);
	SetLastCommand(act);
	/*
	if (ban_unit_num != 0) {

		if (unit_admin->GetUnit(ban_unit_num)->CheckReservationCommand() != NOTHING)
			unit_admin->GetUnit(ban_unit_num)->ResetReservationCommand();

		unit_admin->GetUnit(ban_unit_num)->SetForceCommand(STOP);
		unit_admin->GetUnit(ban_unit_num)->SetFirstLoadCommand(NOTHING);
	}
	*/
}

UnitData* Unit::GetUnitData() {

	return unit_data;
}

void Unit::SetUnitData(UnitData* m_unit_data) {

	unit_data = m_unit_data;
	object_name = unit_data->GetName();
}





int Unit::GetMoney() { return 0; }

void Unit::SetMoney(int) {}













void Unit::attack_motion() {

	if (turn_count<8 && direction_flag == UP) {
		y -= 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == UP) {
		y += 2;
		turn_count++;
	}

	if (turn_count<8 && direction_flag == UP_RIGHT) {
		x += 2;
		y -= 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == UP_RIGHT) {
		x -= 2;
		y += 2;
		turn_count++;
	}

	if (turn_count<8 && direction_flag == RIGHT) {
		x += 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == RIGHT) {
		x -= 2;
		turn_count++;
	}

	if (turn_count<8 && direction_flag == DOWN_RIGHT) {
		x += 2;
		y += 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == DOWN_RIGHT) {
		x -= 2;
		y -= 2;
		turn_count++;
	}

	if (turn_count<8 && direction_flag == DOWN) {
		y += 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == DOWN) {
		y -= 2;
		turn_count++;
	}

	if (turn_count<8 && direction_flag == DOWN_LEFT) {
		x -= 2;
		y += 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == DOWN_LEFT) {
		x += 2;
		y -= 2;
		turn_count++;
	}
	if (turn_count<8 && direction_flag == LEFT) {
		x -= 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == LEFT) {
		x += 2;
		turn_count++;
	}
	if (turn_count<8 && direction_flag == UP_LEFT) {
		x -= 2;
		y -= 2;
		turn_count++;
	}

	if (turn_count >= 8 && direction_flag == UP_LEFT) {
		x += 2;
		y += 2;
		turn_count++;
	}

}

int Unit::direction_x(COMMAND direction) {

	if (direction == UP)
		return 0;

	if (direction == UP_RIGHT)
		return 1;

	if (direction == RIGHT)
		return 1;

	if (direction == DOWN_RIGHT)
		return  1;

	if (direction == DOWN)
		return 0;

	if (direction == DOWN_LEFT)
		return -1;

	if (direction == LEFT)
		return -1;

	if (direction == UP_LEFT)
		return -1;

	if (direction == STOP)
		return 0;

	if (direction == ATTACK)
		return 0;

	return 0;
}

int Unit::direction_y(COMMAND direction) {

	if (direction == UP)
		return -1;

	if (direction == UP_RIGHT)
		return -1;

	if (direction == RIGHT)
		return 0;

	if (direction == DOWN_RIGHT)
		return 1;

	if (direction == DOWN)
		return 1;

	if (direction == DOWN_LEFT)
		return 1;

	if (direction == LEFT)
		return 0;

	if (direction == UP_LEFT)
		return -1;

	if (direction == STOP)
		return 0;

	if (direction == ATTACK)
		return 0;

	return 0;

}












Unit::Unit() {

	reservation_map_x = 0;
	reservation_map_y = 0;
	turn_count = 0;
	level = 0;
	max_hp = 0;
	current_hp = 0;
	atk = 0;
	def = 0;
	spead = 0;
	luk = 0;
	exp = 0;
	banned_direction = NONE_DIRECTION;
	ban_unit_num = 0;

	for (int i = 0; i < COMMAND_MAX; i++)
		reservation_command[i] = NOTHING;

	push = 0;
	pop = 0;

	last_command = NOTHING;
	first_load_command = NOTHING;
}



Unit::~Unit() {

}

