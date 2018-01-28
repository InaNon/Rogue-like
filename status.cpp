#include "status.h"

//エンターを押した場合次のボックスは存在しない
BOXNUM Status::NextBox() {

	return NOBOX;
}

void Status::SetText() {

	content[0] = "レベル　" + to_string(player->GetLevel());
	content[1] = "たいりょく  " + to_string(player->GetCurrentHP());
	content[2] = "こうげき  " + to_string(player->GetAtk());
	content[3] = "ぼうぎょ　" + to_string(player->GetDef());
	content[4] = "くうふく　" + to_string(player->GetCurrentSatiety());
	content[5] = "トータルけいけんち　52" + to_string(player->GetExp());
	content[6] = "おかね" + to_string(player->GetMoney());
}

void Status::RisetCursor() {}












Status::Status(char* m_key, Unit* m_player){
	box_up_left_x = 70;
	box_up_left_y = 70;
	box_down_right_x = 300;
	box_down_right_y = 217;
	content_num = 7;
	key = m_key;

	player = m_player;

	content[0] = "レベル　";
	content[1] = "たいりょく  ";
	content[2] = "こうげき  ";
	content[3] = "ぼうぎょ　";
	content[4] = "くうふく　";
	content[5] = "トータルけいけんち　";
	content[6] = "おかね";
}
Status::~Status(){}