#include "selectbox.h"

//描画部分
void SelectBox::Draw() {

	ListBox::Draw();

	if(content_num != 0)
		DrawTriangle(box_up_left_x + 2, box_up_left_y + MARGIN + 2 + CHAR_SIZE*cursor, box_up_left_x + 2, box_up_left_y + MARGIN + (CHAR_SIZE - 2) + CHAR_SIZE*cursor, box_up_left_x + 8, box_up_left_y + MARGIN + CHAR_SIZE / 2 + CHAR_SIZE*cursor, GetColor(255, 255, 255), TRUE);

}

//選択肢を選ぶ際のカーソルの処理
void SelectBox::Update() {

	//上が押されたとき
	if (key[KEY_INPUT_W] == 1 && key[KEY_INPUT_S] == 0 && cursor > 0 && first_push_up_flag == false) {
		first_push_up_flag = true;
		cursor--;
	}

	//ずっと上が押され続けたとき
	if (key[KEY_INPUT_W] == 1 && key[KEY_INPUT_S] == 0 && cursor > 0 && first_push_up_flag == true) {
		up_count++;
		if (up_count > 16) {
			long_up_count++;
			if (long_up_count == 3) {
				cursor--;
				long_up_count = 0;
			}
		}
	}


	//下が押されたとき
	if (key[KEY_INPUT_W] == 0 && key[KEY_INPUT_S] == 1 && cursor < content_num - 1 && first_push_down_flag == false) {
		first_push_down_flag = true;
		cursor++;
	}

	//下が押され続けたとき
	if (key[KEY_INPUT_W] == 0 && key[KEY_INPUT_S] == 1 && cursor < content_num - 1 && first_push_down_flag == true) {
		down_count++;
		if (down_count > 16) {
			long_down_count++;
			if (long_down_count == 3) {
				cursor++;
				long_down_count = 0;
			}
		}
	}



	//ボタンが押されていないとき、押し続けの判定を行うためのリセット
	if (key[KEY_INPUT_W] == 0) {
		first_push_up_flag = false;
		up_count = 0;
		long_up_count = 0;
	}

	if (key[KEY_INPUT_S] == 0) {
		first_push_down_flag = false;
		down_count = 0;
		long_down_count = 0;
	}
}

void SelectBox::ResetCursor() {

	cursor = 0;
}

int SelectBox::GetCursor() {

	return cursor;
}


SelectBox::SelectBox() {

	cursor = 0;
	first_push_up_flag = false;
	first_push_down_flag = false;
	up_count = 0;
	down_count = 0;
	long_up_count = 0;
	long_down_count = 0;
}

SelectBox::~SelectBox() {}