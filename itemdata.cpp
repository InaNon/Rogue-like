#include "itemdata.h"


int ItemData::GetGraphHandle() {

	return graph_handle;//たまにここで突然エラーになるらしい(ItemDataがNullらしい・・・)
}

int ItemData::GetBuy() {

	return buy;
}

int ItemData::GetSell() {

	return sell;
}



ITEM_KIND ItemData::GetItemKind() { return STATUS_ITEM;}
int ItemData::GetMaxHP() { return 0; }
int ItemData::GetCurrentHP() { return 0; }
int ItemData::GetMaxStomach() { return 0; }
int ItemData::GetCurrentStomach() { return 0; }
int ItemData::GetATK() { return 0; }
int ItemData::GetDEF() { return 0; }
EQUIPMENT_KIND ItemData::GetEquipmentKind() { return SWORD; }


ItemData::ItemData(){}
ItemData::~ItemData() {}
