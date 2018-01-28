#include "listbox.h"

//項目を羅列するメッセージボックス、ボックスの枠組みと項目の羅列を行っている
void ListBox::Draw() {

	DrawBox(box_up_left_x, box_up_left_y, box_down_right_x, box_down_right_y, GetColor(0, 0, 0), TRUE);

	for (int i = 0; i < content_num; i++)
		DrawString(box_up_left_x + MARGIN, box_up_left_y + CHAR_SIZE * i + MARGIN, content[i].c_str(), GetColor(255, 255, 255));

}

void ListBox::SetItemData(ItemData* ){}
void ListBox::ResetCursor() {}
int ListBox::GetCursor() { return 0; }
void ListBox:: SetText(){}
void ListBox::Update(){}
void ListBox::ResetContent(){}

ListBox::ListBox() {}

ListBox::~ListBox() {}