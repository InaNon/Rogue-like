#ifndef DEF_EquipBox
#define DEF_EquipBox

#include "define.h"

#include "selectbox.h"

class EquipmentAdmin;

class EquipBox : public SelectBox {
private:
	EquipmentAdmin* equipment_admin;

public:
	BOXNUM NextBox();
	void SetText();

	EquipBox(char*, EquipmentAdmin*);
	~EquipBox();

};


#endif