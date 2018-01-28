#include "itemdeal.h"

#include "unitadmin.h"
#include "unit.h"
#include "itemdata.h"
#include "equipmentadmin.h"

void ItemDeal::UseItem(ItemData* item_data) {

	unit_admin->GetUnit(0)->SetMaxHP(unit_admin->GetUnit(0)->GetMaxHP() + item_data->GetMaxHP());

	int new_hp = unit_admin->GetUnit(0)->GetCurrentHP() + item_data->GetCurrentHP();
	if (new_hp <= unit_admin->GetUnit(0)->GetMaxHP()) {
		unit_admin->GetUnit(0)->SetCurrentHP(new_hp);
	}

	else {
		unit_admin->GetUnit(0)->SetCurrentHP(unit_admin->GetUnit(0)->GetMaxHP());
	}

	unit_admin->GetUnit(0)->SetMaxStomach(unit_admin->GetUnit(0)->GetMaxStomach() + item_data->GetMaxStomach());

	int new_stomach = unit_admin->GetUnit(0)->GetCurrentStomach() + item_data->GetCurrentStomach();
	if (new_stomach <= unit_admin->GetUnit(0)->GetMaxStomach()) {
		unit_admin->GetUnit(0)->SetCurrentStomach(new_stomach);
	}

	else {
		unit_admin->GetUnit(0)->SetCurrentStomach(unit_admin->GetUnit(0)->GetMaxStomach());
	}

	unit_admin->GetUnit(0)->SetATK(unit_admin->GetUnit(0)->GetATK() + item_data->GetATK());
	unit_admin->GetUnit(0)->SetDEF(unit_admin->GetUnit(0)->GetDEF() + item_data->GetDEF());

}



void ItemDeal::Equip(ItemData* item_data) {

	equipment_admin->Equip(item_data);
}


ItemDeal::ItemDeal(UnitAdmin* m_unit_admin, EquipmentAdmin* m_equipment_admin) {

	unit_admin = m_unit_admin;
	equipment_admin = m_equipment_admin;

}

ItemDeal::~ItemDeal() {}
