#include "menu.h"

//メニュー画面のカーソルの位置と、選択内容
BOXNUM Menu::NextBox() {
	if (cursor == 0)
		return ITEM;
	else if (cursor == 1)
		return EQUIP;
	else if (cursor == 2)
		return STATUS;
	else if (cursor == 3)
		return FOOT;	
	else if (cursor == 4)
		return SAVE;

	return NOBOX;
}



Menu::Menu(char* m_key) {
	box_up_left_x = 10;
	box_up_left_y = 10;
	box_down_right_x = 120;
	box_down_right_y = 110;
	content_num = 5;
	key = m_key;

	content[0] = "アイテム";
	content[1] = "そうび";
	content[2] = "ステータス";
	content[3] = "あしもと";
	content[4] = "セーブ";
}

Menu::~Menu() {}
