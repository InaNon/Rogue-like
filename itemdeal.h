#ifndef DEF_ItemDeal
#define	DEF_ItemDeal

#include "DxLib.h"
#include "define.h"


class ItemData;
class UnitAdmin;
class EquipmentAdmin;

class ItemDeal {

private:
	UnitAdmin *unit_admin;
	EquipmentAdmin *equipment_admin;

public:
	void UseItem(ItemData*);
	void Equip(ItemData*);

	ItemDeal(UnitAdmin*, EquipmentAdmin*);
	~ItemDeal();

};

#endif