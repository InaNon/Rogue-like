#include "equipitemdata.h"

void EquipItemData::SetData(vector<string> data, int m_graph_handle, vector<string> data_name) {

	graph_handle = m_graph_handle;

	for (unsigned int i = 0; i < size(data_name); i++) {
		if (data_name[i] == "name")
			name = data[i];
		else if (data_name[i] == "explain") {

			explain = data[i];
		}
		else if (data_name[i] == "buy")
			buy = stoi(data[i]);
		else if (data_name[i] == "sell")
			sell = stoi(data[i]);
		else if (data_name[i] == "atk")
			atk = stoi(data[i]);
		else if (data_name[i] == "def")
			def = stoi(data[i]);
		else if (data_name[i] == "speed")
			speed = stoi(data[i]);
		else if (data_name[i] == "luk")
			luk = stoi(data[i]);
		else if (data_name[i] == "kind") {
			if (data[i] == "sword")
				equipment_kind = SWORD;
			else if (data[i] == "shield")
				equipment_kind = SHIELD;
			else if (data[i] == "ring")
				equipment_kind = RING;
		}
	}
}

ITEM_KIND EquipItemData::GetItemKind() {

	return EQUIP_ITEM;
}


EQUIPMENT_KIND EquipItemData::GetEquipmentKind() {

	return equipment_kind;
}


EquipItemData::EquipItemData() {
	buy = -999;
	sell = -999;
	max_hp = -999;
	atk = -999;
	def = -999;
	speed = -999;
	luk = -999;
	equipment_kind = RING;
}

EquipItemData::~EquipItemData() {}