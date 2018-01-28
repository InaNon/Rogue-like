#include "statusitemdata.h"

void StatusItemData::SetData(vector<string> data, int m_graph_handle, vector<string> data_name) {

	graph_handle = m_graph_handle;

	for (unsigned int i = 0; i < size(data_name); i++) {
		if (data_name[i] == "name")
			name = data[i];
		else if (data_name[i] == "explain")
			explain = data[i];
		else if (data_name[i] == "buy")
			buy = stoi(data[i]);
		else if (data_name[i] == "sell")
			sell = stoi(data[i]);
		else if (data_name[i] == "max_hp")
			max_hp = stoi(data[i]);
		else if (data_name[i] == "current_hp")
			current_hp = stoi(data[i]);
		else if (data_name[i] == "max_stomach")
			max_stomach = stoi(data[i]);
		else if (data_name[i] == "current_stomach")
			current_stomach = stoi(data[i]);
		else if (data_name[i] == "offense")
			atk = stoi(data[i]);
		else if (data_name[i] == "defense")
			def = stoi(data[i]);
	}

}

ITEM_KIND StatusItemData::GetItemKind() {

	return STATUS_ITEM;
}

int StatusItemData::GetMaxHP() {

	return max_hp;
}

int StatusItemData::GetCurrentHP() {

	return current_hp;
}

int StatusItemData::GetMaxStomach() {

	return max_stomach;
}

int StatusItemData::GetCurrentStomach() {

	return current_stomach;
}

int StatusItemData::GetATK() {

	return atk;
}

int StatusItemData::GetDEF() {

	return def;
}



StatusItemData::StatusItemData() {
	buy = -999;
	sell = -999;
	max_hp = -999;
	current_hp = -999;
	max_stomach = -999;
	current_stomach = -999;
	atk = -999;

}

StatusItemData::~StatusItemData() {}