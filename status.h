#ifndef DEF_Status
#define DEF_Status

#include "DxLib.h"
#include "String"
#include "selectbox.h"
#include "define.h"
#include "unit.h"

class Status : public ListBox {
private:
	Unit* player;

public:
	BOXNUM NextBox();
	void RisetCursor();
	void SetText();

	Status(char*,Unit*);
	~Status();

};

#endif