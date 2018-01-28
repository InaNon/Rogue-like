#ifndef DEF_ItemStockAdmin
#define DEF_ItemStockAdmin

#include "define.h"

class ItemStock;
class ItemData;
class ItemInventory;

class ItemStockAdmin {
private:
	ItemStock* item_stock[ITEM_STOCK_MAX];


public:
	void Init();
	ItemStock* GetItemStock(int);
	void SetItemDataToItemStock(ItemData*, int);
	void LostItemStock(int);
	int GetItemNum();

	ItemStockAdmin();
	~ItemStockAdmin();

};


#endif