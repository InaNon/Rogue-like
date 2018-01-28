#ifndef DEF_ItemInventory
#define DEF_ItemInventory

#include "define.h"

#include "selectbox.h"

class ItemStockAdmin;

class ItemInventory: public SelectBox {
private:
	ItemStockAdmin* item_stock_admin;
	static const int ITEM_INVENTORY_MAX;
	int page;
	bool first_push_right_flag;
	bool first_push_left_flag;
	int right_count;
	int long_right_count;
	int left_count;
	int long_left_count;
	int page_max;
	string page_index;

public:
	BOXNUM NextBox();
	void SetText();
	void Update();
	void ResetCursor();
	void Draw();
	int GetCursor();

	ItemInventory(char*, ItemStockAdmin*);
	~ItemInventory();

};


#endif