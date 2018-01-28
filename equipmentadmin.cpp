#include "equipmentadmin.h"

#include "itemdata.h"
#include "equipment.h"

void EquipmentAdmin::Init() {

	for (int i = 0; i < 3; i++)
		equipment[i] = new Equipment();
}

void EquipmentAdmin::Equip(ItemData* item_data) {
	
	if (item_data->GetEquipmentKind() == SWORD) {
		equipment[SWORD]->SetEquipmentData(item_data);
	}

	else if (item_data->GetEquipmentKind() == SHIELD) {
		equipment[SHIELD]->SetEquipmentData(item_data);
	}

	else if (item_data->GetEquipmentKind() == RING) {
		equipment[RING]->SetEquipmentData(item_data);
	}
}

Equipment* EquipmentAdmin::GetEquipment(EQUIPMENT_KIND m_equipment_kind) {

	return	equipment[m_equipment_kind];
}

EquipmentAdmin::EquipmentAdmin() {}

EquipmentAdmin::~EquipmentAdmin() {}