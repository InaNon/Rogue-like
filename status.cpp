#include "status.h"

//�G���^�[���������ꍇ���̃{�b�N�X�͑��݂��Ȃ�
BOXNUM Status::NextBox() {

	return NOBOX;
}

void Status::SetText() {

	content[0] = "���x���@" + to_string(player->GetLevel());
	content[1] = "������傭  " + to_string(player->GetCurrentHP());
	content[2] = "��������  " + to_string(player->GetAtk());
	content[3] = "�ڂ�����@" + to_string(player->GetDef());
	content[4] = "�����ӂ��@" + to_string(player->GetCurrentSatiety());
	content[5] = "�g�[�^���������񂿁@52" + to_string(player->GetExp());
	content[6] = "������" + to_string(player->GetMoney());
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

	content[0] = "���x���@";
	content[1] = "������傭  ";
	content[2] = "��������  ";
	content[3] = "�ڂ�����@";
	content[4] = "�����ӂ��@";
	content[5] = "�g�[�^���������񂿁@";
	content[6] = "������";
}
Status::~Status(){}