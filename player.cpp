#include "player.h"

#include "unitadmin.h"
#include "ObjectDataAdmin.h"
#include "unitdata.h"


//プレイヤーの向きを決める関数
int Player::direction(){

	//通常モード
	if (key[KEY_INPUT_RSHIFT] == 1)
		direction_mode = true;

	if (key[KEY_INPUT_RSHIFT] == 0)
		direction_mode = false;


/*トグルモード
	if (control_flag == false && key[KEY_INPUT_RSHIFT] == 1){
		direction_mode = !direction_mode;
		control_flag = true;
	}

	if (control_flag == true && key[KEY_INPUT_RSHIFT] == 0)
		control_flag = false;
*/

	if (move_flag == NOTHING && direction_mode == true)
	{
		if (key[KEY_INPUT_W] == 1 && key[KEY_INPUT_D] == 1) 
			return direction_flag = UP_RIGHT;

		if (key[KEY_INPUT_D] == 1 && key[KEY_INPUT_S] == 1) 
			return	direction_flag = DOWN_RIGHT;

		if (key[KEY_INPUT_S] == 1 && key[KEY_INPUT_A] == 1) 
			return	direction_flag = DOWN_LEFT;

		if (key[KEY_INPUT_A] == 1 && key[KEY_INPUT_W] == 1) 
			return	direction_flag = UP_LEFT;

		if (key[KEY_INPUT_W] == 1) 
			return direction_flag = UP;

		if (key[KEY_INPUT_D] == 1) 
			return direction_flag = RIGHT;

		if (key[KEY_INPUT_S] == 1) 
			return	direction_flag = DOWN;

		if (key[KEY_INPUT_A] == 1) 
			return	direction_flag = LEFT;
	}

	return direction_flag;

}

//プレイヤー移動のキー判定と位置更新、更新されたx,yはunit.cppのx,yで使われる
int Player::Update() {

	if (exist == false) { return NOTHING; }

	if (direction_mode == false && key[KEY_INPUT_W] == 1 && key[KEY_INPUT_D] == 1) {
		direction_flag = UP_RIGHT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x + 1, map_y - 1) == true && unit_admin->UnitExistMap(map_x + 1, map_y - 1) == NULL)
		{
			move_flag = UP_RIGHT;
			stop = y - 32;
			ReservationMapPosition(UP_RIGHT);
			UpdateMapPosition();
			satiety_count++;
			return UP_RIGHT;
		}
	}

	if (direction_mode == false && key[KEY_INPUT_D] == 1 && key[KEY_INPUT_S] == 1) {
		direction_flag = DOWN_RIGHT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x + 1, map_y + 1) == true && unit_admin->UnitExistMap(map_x + 1, map_y + 1) == NULL)
		{
			move_flag = DOWN_RIGHT;
			stop = y + 32;
			ReservationMapPosition(DOWN_RIGHT);
			UpdateMapPosition();
			satiety_count++;
			return DOWN_RIGHT;
		}
	}


	if (direction_mode == false && key[KEY_INPUT_S] == 1 && key[KEY_INPUT_A] == 1) {
		direction_flag = DOWN_LEFT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x - 1, map_y + 1) == true && unit_admin->UnitExistMap(map_x - 1, map_y + 1) == NULL)
		{
			move_flag = DOWN_LEFT;
			stop = y + 32;
			ReservationMapPosition(DOWN_LEFT);
			UpdateMapPosition();
			satiety_count++;
			return DOWN_LEFT;
		}
	}


	if (direction_mode == false && key[KEY_INPUT_A] == 1 && key[KEY_INPUT_W] == 1) {
		direction_flag = UP_LEFT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x - 1, map_y - 1) == true && unit_admin->UnitExistMap(map_x - 1, map_y - 1) == NULL)
		{
			move_flag = UP_LEFT;
			stop = y - 32;
			ReservationMapPosition(UP_LEFT);
			UpdateMapPosition();
			satiety_count++;
			return UP_LEFT;
		}
	}

	if (direction_mode == false && key[KEY_INPUT_W] == 1) {
		direction_flag = UP;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x, map_y - 1) == true && unit_admin->UnitExistMap(map_x, map_y - 1) == NULL)
		{
			move_flag = UP;
			stop = y - 32;
			ReservationMapPosition(UP);
			UpdateMapPosition();
			satiety_count++;
			return UP;
		}
	}

	if (direction_mode == false && key[KEY_INPUT_S] == 1) {
		direction_flag = DOWN;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x, map_y + 1) == true && unit_admin->UnitExistMap(map_x, map_y + 1) == NULL)
		{
			move_flag = DOWN;
			stop = y + 32;
			ReservationMapPosition(DOWN);
			UpdateMapPosition();
			satiety_count++;
			return DOWN;
		}
	}

	if (direction_mode == false && key[KEY_INPUT_A] == 1) {
		direction_flag = LEFT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x - 1, map_y) == true && unit_admin->UnitExistMap(map_x - 1, map_y) == NULL)
		{
			move_flag = LEFT;
			stop = x - 32;
			ReservationMapPosition(LEFT);
			UpdateMapPosition();
			satiety_count++;
			return LEFT;
		}
	}

	if (direction_mode == false && key[KEY_INPUT_D] == 1) {
		direction_flag = RIGHT;
		if (move_flag == NOTHING && unit_admin->GetMovef(map_x + 1, map_y) == true && unit_admin->UnitExistMap(map_x + 1, map_y) == NULL)
		{
			move_flag = RIGHT;
			stop = x + 32;
			ReservationMapPosition(RIGHT);
			UpdateMapPosition();
			satiety_count++;
			return RIGHT;
		}
	}


	if (key[KEY_INPUT_SPACE] == 1) {
		move_flag = STOP;
		satiety_count++;
		return STOP;
	}

	if (key[KEY_INPUT_RETURN] == 1) {
		move_flag = ATTACK;
		satiety_count++;
		return ATTACK;
	}

	if (satiety_count == 16) {
		satiety_count = 0;
		current_satiety--;
	}

	return NOTHING;

}

void Player::Update(int k) {}

int Player::GetCurrentSatiety(){

	return current_satiety;
}

int Player::GetMoney() {
	
	return money; 
}

void Player::SetMoney(int m_money) {

	money = m_money;
}






Player::Player(int m_unit_num, int player_graphic_handle, char* m_key, UnitAdmin* m_unit_admin) {

	unit_num = m_unit_num;
	key = m_key;
	gphandle = player_graphic_handle;
	unit_admin = m_unit_admin;

	move_flag = NOTHING;
	direction_flag = (COMMAND)(GetRand(7) + (int)UP);
	direction_mode = false;
	control_flag = false;

	max_satiety = 100;
	current_satiety = 100;
	level = 1;
	max_hp = 30;
	current_hp = 30;
	atk = 2;
	def = 2;
	spead = 3;
	luk = 3;
	exp = 0;
	money = 10000;

}

Player::~Player() {}