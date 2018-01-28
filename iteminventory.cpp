#include "iteminventory.h"

#include "itemstockadmin.h"
#include "itemstock.h"
#include "itemdata.h"

const int ItemInventory::ITEM_INVENTORY_MAX = 7;

BOXNUM ItemInventory::NextBox() { return USE_ITEM; }

void ItemInventory::Draw() {

	SelectBox::Draw();

	DrawString(box_down_right_x - 5*MARGIN, box_down_right_y -2*MARGIN, page_index.c_str(), GetColor(255, 255, 255));

}



void ItemInventory::Update() {

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
	if (key[KEY_INPUT_W] == 0 && key[KEY_INPUT_S] == 1 && cursor < ITEM_INVENTORY_MAX-1 && cursor+ITEM_INVENTORY_MAX*page < content_num-1 && first_push_down_flag == false) {
		first_push_down_flag = true;
		cursor++;
	}

	//下が押され続けたとき
	if (key[KEY_INPUT_W] == 0 && key[KEY_INPUT_S] == 1 && cursor < ITEM_INVENTORY_MAX - 1 && cursor+ITEM_INVENTORY_MAX*page < content_num-1 && first_push_down_flag == true) {
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


	if (key[KEY_INPUT_D] == 1 && key[KEY_INPUT_A] == 0 && first_push_right_flag == false) {
		first_push_right_flag = true;
		if ((page + 1) * ITEM_INVENTORY_MAX < content_num) {
			page++;
			for (int i = 0; i < ITEM_INVENTORY_MAX; i++) {
				content[i] = "";
			}
			SetText();
		}
	}


	if (key[KEY_INPUT_D] == 1 && key[KEY_INPUT_A] == 0 && first_push_right_flag == true) {
		right_count++;
		if (right_count > 16) {
			long_right_count++;
			if (long_right_count == 3) {
				  if ((page + 1) * ITEM_INVENTORY_MAX < content_num) {
					  page++;
					  for (int i = 0; i < ITEM_INVENTORY_MAX; i++) {
						  content[i] = "";
					  }
					  SetText();
				  }
				long_right_count = 0;
			}
		}
	}


	if (key[KEY_INPUT_D] == 0 && key[KEY_INPUT_A] == 1 && first_push_left_flag == false) {
		first_push_left_flag = true;
		if ((page - 1) >= 0) {
			page--;
			for (int i = 0; i < ITEM_INVENTORY_MAX; i++) {
				content[i] = "";
			}
			SetText();
		}
	}


	if (key[KEY_INPUT_D] == 0 && key[KEY_INPUT_A] == 1 && first_push_left_flag == true) {
		left_count++;
		if (left_count > 16) {
			long_left_count++;
			if (long_left_count == 3) {
				if ((page - 1) >= 0) {
					page--;
					for (int i = 0; i < ITEM_INVENTORY_MAX; i++) {
						content[i] = "";
					}
					SetText();
				}
				long_left_count = 0;
			}
		}
	}



	if (key[KEY_INPUT_D] == 0) {
		first_push_right_flag = false;
		right_count = 0;
		long_right_count = 0;
	}

	if (key[KEY_INPUT_A] == 0) {
		first_push_left_flag = false;
		left_count = 0;
		long_left_count = 0;
	}


}

void ItemInventory::SetText() {

	content_num = item_stock_admin->GetItemNum();

	page_max = (content_num-1) / ITEM_INVENTORY_MAX;
	page_index = to_string(page+1) + "/" + to_string(page_max+1);

	for (int i = 0; i < ITEM_INVENTORY_MAX; i++) {
		if (i + page*ITEM_INVENTORY_MAX < content_num) {
			if (item_stock_admin->GetItemStock(i+page*ITEM_INVENTORY_MAX)->GetEquiped() == true) {
				content[i] = item_stock_admin->GetItemStock(i+ page*ITEM_INVENTORY_MAX)->GetItemData()->GetName() + "E";
			}else {
				content[i] = item_stock_admin->GetItemStock(i+ page*ITEM_INVENTORY_MAX)->GetItemData()->GetName();
			}
		}
	}
}


void ItemInventory::ResetCursor() {

	cursor = 0;
	page = 0;
}

int ItemInventory::GetCursor(){

	return page*ITEM_INVENTORY_MAX + cursor;
}







ItemInventory::ItemInventory(char* m_key, ItemStockAdmin* m_item_stock_admin) {
	box_up_left_x = 70;
	box_up_left_y = 70;
	box_down_right_x = 260;
	box_down_right_y = 212;
	content_num = 0;

	key = m_key;
	item_stock_admin = m_item_stock_admin;

	page = 0;

	first_push_right_flag = false;
	first_push_left_flag = false;
	right_count = 0;
	left_count = 0;
	long_right_count = 0;
	long_left_count = 0;

}

ItemInventory::~ItemInventory() {}