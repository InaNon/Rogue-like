#ifndef DEF_EquipmentAdmin
#define DEF_EquipmentAdmin

#include "Dxlib.h"
#include <string>
#include <vector>
#include <iostream>
#include "define.h"


class ItemData;
class Equipment;


class EquipmentAdmin {

private:
	Equipment* equipment[RING + 1];

public:
	void Init();

	void Equip(ItemData*);
	Equipment* GetEquipment(EQUIPMENT_KIND);
	//ItemData* GetEquipmentData(EQUIPMENT_KIND);

	EquipmentAdmin();
	~EquipmentAdmin();

};

#endif