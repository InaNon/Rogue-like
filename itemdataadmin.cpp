#include "itemdataadmin.h"

#include "unitdata.h"
#include "statusitemdata.h"
#include "equipitemdata.h"





//string型で指定文字で文字列分割をする関数
template <typename List>
void split(const std::string& s, const std::string& delim, List& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}








void ItemDataAdmin::Init(){

	load_item_num = 0;
	load_unit_num = 0;
	title_load_flag = false;

	LoadDivGraph("image/item.png", ALL_IMAGE_CHIP_X * ALL_IMAGE_CHIP_Y, ALL_IMAGE_CHIP_X, ALL_IMAGE_CHIP_Y, IMAGE_CHIP_SIZE_X, IMAGE_CHIP_SIZE_Y, item_graph_handle);
}















void ItemDataAdmin::SplitLineSetUnitData(string data_line) {

	vector<string> data;
	unit_data[load_unit_num] = new UnitData();

	split(data_line, ",", data);

	if (title_load_flag == true) {
		if (data[0] != "end") {
			string graph_path = "image/unit/" + data[2];
			int unit_graph_handle = LoadGraph(graph_path.c_str());

			unit_data[load_unit_num]->SetData(data, unit_graph_handle, data_name);

			load_unit_num++;
		}

		else {
			title_load_flag = false;
		}
	}

	else if (title_load_flag == false) {
		data_name = data;
		title_load_flag = true;
	}
}


void ItemDataAdmin::SplitLineSetEquipItemData(string data_line) {

	vector<string> data;
	item_data[load_item_num] = new EquipItemData();

	split(data_line, ",", data);

	if (title_load_flag == true) {
		if (data[0] != "end") {
			int graph_num = stoi(data[2]) + stoi(data[3]) * ALL_IMAGE_CHIP_X;

			item_data[load_item_num]->SetData(data, item_graph_handle[graph_num], data_name);

			load_item_num++;
		}

		else {
			title_load_flag = false;
		}
	}

	else if (title_load_flag == false) {
			data_name = data;
			title_load_flag = true;
	}
}



//loaddatabaseによって実行され、excelファイルの文字列を分割しアイテムのデータを取り込む部分、ここでアイテムのインスタンス化も行う
void ItemDataAdmin::SplitLineSetStatusItemData(string data_line) {

	vector<string> data;
	item_data[load_item_num] = new StatusItemData();

	split(data_line, ",", data);

	if (title_load_flag == true) {
		if (data[0] != "end") {
			int graph_num = stoi(data[2]) + stoi(data[3]) * ALL_IMAGE_CHIP_X;

			item_data[load_item_num]->SetData(data, item_graph_handle[graph_num], data_name);

			load_item_num++;
		}

		else {
			title_load_flag = false;
		}
	}

	else if (data[0] != "") {
		data_name = data;
		title_load_flag = true;
	}
}





ItemData* ItemDataAdmin::GetItemData(int item_data_num) {
	/*
	for (int i = 0; i < ITEM_DATA_MAX; i++) {
		if (item_data[i]->GetName() == item_name) {
			return item_data[i];
		}
	}
	*/
	return item_data[item_data_num];
}

UnitData* ItemDataAdmin::GetUnitData(string unit_name) {

	for (int i = 0; i < ITEM_DATA_MAX; i++) {
		//printfDx("%d", i);
		//WaitKey();
		if (unit_data[i]->GetName() == unit_name) {
			//printfDx("入った");
			//WaitKey();
			return unit_data[i];
		}
	}

	return NULL;
}





ItemDataAdmin::ItemDataAdmin() {}


ItemDataAdmin::~ItemDataAdmin() {}