#include "equipment.h"

ItemData* Equipment::GetEquipmentData() {

	return equipment_data;
}

void Equipment::SetEquipmentData(ItemData* m_equipment_data) {

	equipment_data = m_equipment_data;
}

Equipment::Equipment() {

	equipment_data = NULL;
}
Equipment::~Equipment() {}