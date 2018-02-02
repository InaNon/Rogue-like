#ifndef DEF_ItemAdmin
#define DEF_ItemAdmin

#include "define.h"

class Item;
class ItemData;
class ObjectDataAdmin;
class Camera;
class UnitAdmin;
class MapAdmin;
class MessageAdmin;
class SelectBoxAdmin;

class ItemAdmin {
private:
	Item* item[ITEM_MAX];
	ObjectDataAdmin* object_data_admin;
	UnitAdmin* unit_admin;
	MapAdmin* map_admin;

	int item_num;


public:
	void Init(UnitAdmin*, ObjectDataAdmin*, MapAdmin*, MessageAdmin*, SelectBoxAdmin*);

	void Spawn();
	Item* ItemExistMap(int check_x, int check_y);

	void SubtractItemNum();
	Item* GetItem(int);
	void PutItem(int, int, ItemData*);
	int GetTotalSell();

	void SellItem();

	ItemAdmin();
	~ItemAdmin();

};


#endif DEF_ItemAdmin
