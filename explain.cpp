#include "explain.h"

#include "itemstockadmin.h"
#include "itemstock.h"
#include "itemdata.h"

//�G���^�[���������ꍇ���̃{�b�N�X�͑��݂��Ȃ�
BOXNUM Explain::NextBox() {

	return NOBOX;
}

void Explain::SetItemData(ItemData* m_item_data) {

	item_data = m_item_data;
}

void Explain::SetText() {
	content[0] = item_data->GetExplain();
}

void Explain::RisetCursor() {}












Explain::Explain() {
	box_up_left_x = 170;
	box_up_left_y = 370;
	box_down_right_x = 400;
	box_down_right_y = 517;
	content_num = 1;
}

Explain::~Explain() {}