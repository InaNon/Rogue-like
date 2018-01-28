#ifndef DEF_EquipItemData
#define DEF_EquipItemData

#include "Dxlib.h"
#include <string>
#include <vector>


using namespace std;

#include "itemdata.h"

class EquipItemData :public ItemData {

private:
	int max_hp;
	int atk;
	int def;
	int speed;
	int luk;
	EQUIPMENT_KIND equipment_kind;


public:
	void SetData(vector<string>, int, vector<string>);

	ITEM_KIND GetItemKind();
	EQUIPMENT_KIND GetEquipmentKind();



	EquipItemData();
	~EquipItemData();
};


#endif
