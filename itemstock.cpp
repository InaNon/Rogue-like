#include "itemstock.h"

#include "itemdata.h"

ItemData* ItemStock::GetItemData() {

	return item_data;
}

void ItemStock::SetItemData(ItemData* m_item_data) {

	item_data = m_item_data;
}

bool ItemStock::GetExist() {

	return exist;
}

void ItemStock::SetExist(bool m_exist) {

	exist = m_exist;
}


bool ItemStock::GetEquiped() {

	return equiped;
}

void ItemStock::SetEquiped(bool m_equiped) {

	equiped = m_equiped;
}





ItemStock::ItemStock() {

	exist = false;
}
ItemStock::~ItemStock() {}