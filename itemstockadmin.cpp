#include "itemstockadmin.h"

#include "itemstock.h"
#include "itemdata.h"



void ItemStockAdmin::Init(){

	for (int i = 0; i < ITEM_STOCK_MAX; i++)
		item_stock[i] = new ItemStock();
}

ItemStock* ItemStockAdmin::GetItemStock(int inventory_num){

	return item_stock[inventory_num];
}

void ItemStockAdmin::SetItemDataToItemStock(ItemData* item_data, int inventory_num){
	
	if (inventory_num == NO_ITEM_STOCK_NUM) {
		for (int i = 0; i < ITEM_STOCK_MAX; i++)
			if (item_stock[i]->GetExist() == false) {
				item_stock[i]->SetItemData(item_data);
				item_stock[i]->SetExist(true);
				break;
			}
	}


	if (inventory_num != NO_ITEM_STOCK_NUM) {
		item_stock[inventory_num]->SetItemData(item_data);
		item_stock[inventory_num]->SetExist(true);
	}
}

void ItemStockAdmin::LostItemStock(int inventory_num) {

	for (int i = inventory_num; i < ITEM_STOCK_MAX; i++) {

		if (item_stock[i + 1]->GetExist() == true) {
			item_stock[i]->SetItemData(item_stock[i + 1]->GetItemData());
		}

		if (item_stock[i + 1]->GetExist() == false){
			item_stock[i]->SetExist(false);
			break;
		}
	}
}

int ItemStockAdmin::GetItemNum() {

	int item_num = 0;

	for (int i = 0; i < ITEM_STOCK_MAX; i++) {
		if (item_stock[i]->GetExist() == true)
			item_num++;
	}

	return item_num;

}

int ItemStockAdmin::GetTotalBuy() {

	int total_buy = 0;

	for (int i = 0; i < ITEM_STOCK_MAX; i++) {
		if (item_stock[i]->GetExist() == true && item_stock[i]->GetBelong() == SHOP)
			total_buy += item_stock[i]->GetItemData()->GetBuy();
	}

	return total_buy;


}

void ItemStockAdmin::BuyItem() {

	for (int i = 0; i < ITEM_MAX; i++) {
		if (item_stock[i]->GetExist() == true && item_stock[i]->GetBelong() == PLAYER) {
			item_stock[i]->SetBelong(PLAYER);
		}
	}
}



ItemStockAdmin::ItemStockAdmin(){}

ItemStockAdmin::~ItemStockAdmin() {

	for (int i = 0; i < ITEM_STOCK_MAX; i++)
		delete item_stock[i];
}
