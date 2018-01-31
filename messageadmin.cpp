#include "messageadmin.h"
#include "message.h"


void MessageAdmin::Init(char* m_key, ModeManage* m_mode_manage) {
	wait_check_flag = false;
	key = m_key;
	count = 0;
	last_count = 0;
	push = 0;
	pop = 0;

	for (int i = 0; i < MESSAGE_MAX; i++)
		message[i] = new Message();

	mode_manage = m_mode_manage;
}

void MessageAdmin::Draw() {

	if (pop != push) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//ブレンドモードをα(128/255)に設定
		DrawBoxAA(50, WINDOWSIZE_Y-100, WINDOWSIZE_X - 50, WINDOWSIZE_Y - 20, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
		DrawFormatString(55, WINDOWSIZE_Y - 90, GetColor(255, 0, 0), "%s", active_text.c_str());
	}
}

void MessageAdmin::Update() {

	count++;

	active_text = message[pop]->GetText();

	if (pop != push && wait_check_flag == false) {
		wait_check_flag = true;
		mode_manage->SetMessageMode(message[pop + 1]->GetWaitMode());
		if (mode_manage->GetMessageMode() == true)
			message[pop]->AddEnter();
	}

	if (count >= 16 && mode_manage->GetMessageMode() == true) {
		if (key[KEY_INPUT_RETURN] == 1) {
			mode_manage->SetMessageMode(false);
			wait_check_flag = false;
			count = 0;
			wait_check_flag = 0;
			message[pop]->SetText("");
			message[pop]->SetWaitMode(false);
			pop++;
			pop = pop % 64;
			mode_manage->SetMessageMode(message[pop]->GetWaitMode());
		}
	}


	if (count >=16 && mode_manage->GetMessageMode() == false && message[pop]->GetText()!="") {
		if (pop == (push - 1) || (pop==63 && push==0))
			last_count++;

		if (!(pop == (push - 1) || (pop == 63 && push == 0)) || last_count == 70) {
			count = 0;
			last_count = 0;
			wait_check_flag = false;
			message[pop]->SetText("");
			message[pop]->SetWaitMode(false);
			pop++;
			pop = pop % 64;
			mode_manage->SetMessageMode(message[pop + 1]->GetWaitMode());
		}
	}
}

void MessageAdmin::AnyMessage(string text, bool wait_mode) {

	message[push]->SetText(text);
	message[push]->SetWaitMode(wait_mode);
	push++;
	push = push % 64;
	count = 0;

}

void MessageAdmin::AttackMessage(string attack_unit_name, string target_unit_name, int damage) {

	string text;
	text = attack_unit_name + "は" + target_unit_name + "に" + to_string(damage) + "ダメージあえた";

	message[push]->SetText(text);
	message[push]->SetWaitMode(false);
	push++;
	push = push % 64;
	count = 0;

}

void MessageAdmin::CrushMessage(string attack_unit_name, string target_unit_name) {

	string text;
	text = attack_unit_name + "は" + target_unit_name + "をたおした";
	message[push]->SetText(text);
	message[push]->SetWaitMode(true);
	push++;
	push = push % 64;
	count = 0;

}

void MessageAdmin::ExpMessage(string attack_unit_name, int exp) {

	string text;
	text = attack_unit_name + "は" + to_string(exp) + "のけいけんちをえた";
	message[push]->SetText(text);
	message[push]->SetWaitMode(true);
	push++;
	push = push % 64;
	count = 0;

}





MessageAdmin::MessageAdmin(){}

MessageAdmin::~MessageAdmin(){
	for (int i = 0; i < MESSAGE_MAX; i++)
		delete message[i];
}
