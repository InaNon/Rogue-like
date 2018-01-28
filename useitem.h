#ifndef DEF_UseItem
#define DEF_UseItem

#include "define.h"

#include "selectbox.h"

class ItemData;

class UseItem : public SelectBox {
private:
	ItemData* item_data;

public:
	BOXNUM NextBox();
	void SetItemData(ItemData*);
	void SetText();
	void ResetContent();

	UseItem(char*);
	~UseItem();

};


#endif