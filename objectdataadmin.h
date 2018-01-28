#ifndef DEF_ObjectDataAdmin
#define DEF_ObjectDataAdmin

#include "Dxlib.h"
#include <string>
#include <vector>
#include <iostream>
#include "define.h"

using namespace std;

class UnitData;
class ItemData;

class ObjectDataAdmin {

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
	bool SplitLineSetUnitData(string);
	bool SplitLineSetEquipItemData(string);
	bool SplitLineSetStatusItemData(string);

	ItemData* GetItemData(int);
	UnitData* GetUnitData(string);
	UnitData* GetUnitData(int);

	ObjectDataAdmin();
	~ObjectDataAdmin();

};

#endif