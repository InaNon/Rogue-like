#include "equipbox.h"

#include "equipmentadmin.h"
#include "equipment.h"
#include "itemdata.h"

BOXNUM EquipBox::NextBox() {

	if (equipment_admin->GetEquipment(EQUIPMENT_KIND(cursor))->GetEquipmentData() != NULL)
		return PUT_OFF;
	
	return NOBOX; 
}


void EquipBox::SetText() {

	content_num = 3;
	for (int i = 0; i < content_num; i++) {
		if (equipment_admin->GetEquipment((EQUIPMENT_KIND)i)->GetEquipmentData() != NULL) {
			content[i] = equipment_admin->GetEquipment((EQUIPMENT_KIND)i)->GetEquipmentData()->GetName();
		}

		else
			content[i] = "";
	}

}












EquipBox::EquipBox(char* m_key, EquipmentAdmin* m_equipment_admin) {
	box_up_left_x = 70;
	box_up_left_y = 70;
	box_down_right_x = 244;
	box_down_right_y = 196;
	content_num = 0;

	key = m_key;
	equipment_admin = m_equipment_admin;

}

EquipBox::~EquipBox() {}