#include "useitem.h"

#include "itemstockadmin.h"
#include "itemstock.h"
#include "itemdata.h"

BOXNUM UseItem::NextBox() {
	
	if (cursor == 3)
		return EXPLAIN;

	return NOBOX;
}

void UseItem::SetItemData(ItemData* m_item_data) {

	item_data = m_item_data;
}

void UseItem::SetText() {

	//content_num = item_data->GetAddContentNum() + 3;
	content_num = 1 + 3;

	for (int i = 0; i < content_num - 3; i++) {
		//content[0] = item_data->GetAddContentText(i);
		for (int j = 0; j < content_num; j++) {
			content[content_num - j] = content[content_num - j - 1];
		}
		content[0] = "Žg‚¤";
	}
}

void UseItem::ResetContent() {

	content_num = 3;
	content[0] = "‚È‚°‚é";
	content[1] = "‚¨‚­";
	content[2] = "‚¹‚Â‚ß‚¢";
}

UseItem::UseItem(char* m_key) {

	content[0] = "‚È‚°‚é";
	content[1] = "‚¨‚­";
	content[2] = "‚¹‚Â‚ß‚¢";

	box_up_left_x = 300;
	box_up_left_y = 200;
	box_down_right_x = 450;
	box_down_right_y = 350;
	content_num = 0;

	key = m_key;

}
UseItem::~UseItem() {}