#ifndef DEF_Equipment
#define DEF_Equipment

#include "Dxlib.h"
#include <string>
#include <vector>
#include <iostream>
#include "define.h"

class ItemData;


class Equipment {

private:
	ItemData* equipment_data;

public:
	ItemData* GetEquipmentData();
	void SetEquipmentData(ItemData*);

	Equipment();
	~Equipment();

};

#endif