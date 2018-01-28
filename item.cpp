#include "item.h"

#include "DxLib.h"

#include "itemdata.h"
#include "camera.h"


ItemData* Item::GetItemData() {

	return item_data;
}

void Item::SetItemData(ItemData* m_item_data){

	item_data = m_item_data;
}

Item::Item() {}
Item:: ~Item() {}
