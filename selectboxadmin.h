#ifndef DEF_SelectBoxAdmin
#define DEF_SelectBoxAdmin

#include "DxLib.h"
#include "String"
#include "selectbox.h"
#include "listbox.h"
#include "define.h"
#include "modemanage.h"

class UnitAdmin;
class ItemAdmin;
class ItemStockAdmin;
class ItemDeal;
class EquipmentAdmin;

class SelectBoxAdmin {
private:
	UnitAdmin* unit_admin;
	ItemAdmin* item_admin;
	ItemStockAdmin* item_stock_admin;
	ListBox* list_box[LIST_BOX_MAX];
	ModeManage* mode_manage;
	ItemDeal* item_deal;
	EquipmentAdmin* equipment_admin;

	char* key;
	int count;
	bool draw_flag[LIST_BOX_MAX];
	bool active_flag[LIST_BOX_MAX];
	bool old_draw_flag[OLD_MAX][LIST_BOX_MAX];
	bool old_active_flag[OLD_MAX][LIST_BOX_MAX];
	BOXNUM next_box_num;
	int select_item_stock_num;

public:
	void Init(char*, UnitAdmin*,ItemAdmin*, EquipmentAdmin*, ModeManage*, ItemStockAdmin*);
	void Draw();
	void Update();

	SelectBoxAdmin();
	~SelectBoxAdmin();

};

#endif