#ifndef DEF_Item
#define DEF_Item

#include "object.h"

class ItemData;
class Camera;

class Item :public Object {
private:
	ItemData* item_data;

public:

	ItemData* GetItemData();
	void SetItemData(ItemData*);

	Item();
	~Item();
};


#endif DEF_Item

