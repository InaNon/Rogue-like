#ifndef DEF_ItemDataAdmin
#define DEF_ItemDataAdmin

#include "Dxlib.h"
#include <string>
#include <vector>
#include <iostream>
#include "define.h"

using namespace std;

class UnitData;
class ItemData;

class ItemDataAdmin {

private:
	UnitData* unit_data[UNIT_DATA_MAX];
	ItemData* item_data[ITEM_DATA_MAX];



	string data_line;
	vector<string> data_name;
	bool title_load_flag;
	int load_item_num;
	int load_unit_num;
	int item_graph_handle[ALL_IMAGE_CHIP_X * ALL_IMAGE_CHIP_Y];

public:
	void Init();
	void SplitLineSetUnitData(string);
	void SplitLineSetEquipItemData(string);
	void SplitLineSetStatusItemData(string);

	ItemData* GetItemData(int);
	UnitData* GetUnitData(string);

	ItemDataAdmin();
	~ItemDataAdmin();

};

#endif