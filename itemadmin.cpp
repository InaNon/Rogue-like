#include "itemadmin.h"

#include <string>

#include "Dxlib.h"

#include "define.h"
#include "item.h"
#include "ObjectDataAdmin.h"
#include "unitadmin.h"
#include "mapadmin.h"

using namespace std;


void ItemAdmin::Init(UnitAdmin* m_unit_admin, ObjectDataAdmin* m_object_data_admin, MapAdmin* m_map_admin, MessageAdmin* m_message_admin, SelectBoxAdmin* m_select_box_admin) {

	unit_admin = m_unit_admin;
	object_data_admin = m_object_data_admin;
	map_admin = m_map_admin;
}

void ItemAdmin::Spawn() {

	item_num = 100;

	int spawn_x = -100;
	int spawn_y = -100;
	int spawn_check = 0;
	string item_name;

	for (int i = 0; i < ITEM_MAX; i++)
		item[i]->SetExist(false);

	for (int i = 0; i < item_num; i++) {
		while (1) {
			spawn_x = GetRand(MAP_X_MAX - 1);
			spawn_y = GetRand(MAP_Y_MAX - 1);

			if ((map_admin->GetMapCell(spawn_x, spawn_y)->GetMovef()) == true && unit_admin->UnitExistMap(spawn_x, spawn_y) == NULL && ItemExistMap(spawn_x, spawn_y) == NULL) {
				item[i]->Spawn(spawn_x, spawn_y);

				int k = GetRand(33);

				item[i]->SetItemData(object_data_admin->GetItemData(k));
				break;
			}
		}
	}
}

Item* ItemAdmin::ItemExistMap(int check_x, int check_y) {

	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i]->GetExist() == true) {
			if (check_x == item[i]->GetMAPX() && check_y == item[i]->GetMAPY()) {
				return item[i];
			}
		}
	}

	return NULL;

}


void ItemAdmin::SubtractItemNum() {

	item_num--;
}


Item* ItemAdmin::GetItem(int m_item_num) {

	return item[m_item_num];
}

void ItemAdmin::PutItem(int map_x, int map_y, ItemData* m_item_data) {

	item_num++;

	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i]->GetExist() == false) {
			item[i]->SetExist(true);
			item[i]->Spawn(map_x, map_y);
			item[i]->SetItemData(m_item_data);
			break;
		}
	}
}



ItemAdmin::ItemAdmin() {
	for (int i = 0; i < ITEM_MAX; i++)
		item[i] = new Item();
}

ItemAdmin::~ItemAdmin() {}