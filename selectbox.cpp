#include "selectbox.h"

//�`�敔��
void SelectBox::Draw() {

	ListBox::Draw();

	if(content_num != 0)
		DrawTriangle(box_up_left_x + 2, box_up_left_y + MARGIN + 2 + CHAR_SIZE*cursor, box_up_left_x + 2, box_up_left_y + MARGIN + (CHAR_SIZE - 2) + CHAR_SIZE*cursor, box_up_left_x + 8, box_up_left_y + MARGIN + CHAR_SIZE / 2 + CHAR_SIZE*cursor, GetColor(255, 255, 255), TRUE);

}

//�I������I�ԍۂ̃J�[�\���̏���
void SelectBox::Update() {

	//�オ�����ꂽ�Ƃ�
	if (key[KEY_INPUT_W] == 1 && key[KEY_INPUT_S] == 0 && cursor > 0 && first_push_up_flag == false) {
		first_push_up_flag = true;
		cursor--;
	}

	//�����Əオ�����ꑱ�����Ƃ�
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


	//���������ꂽ�Ƃ�
	if (key[KEY_INPUT_W] == 0 && key[KEY_INPUT_S] == 1 && cursor < content_num - 1 && first_push_down_flag == false) {
		first_push_down_flag = true;
		cursor++;
	}

	//���������ꑱ�����Ƃ�
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



	//�{�^����������Ă��Ȃ��Ƃ��A���������̔�����s�����߂̃��Z�b�g
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