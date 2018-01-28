#ifndef DEF_Explain
#define DEF_Explain

#include "DxLib.h"
#include "String"
#include "selectbox.h"
#include "define.h"
#include "unit.h"


class Explain : public ListBox {
private:
	Unit* player;
	ItemData* item_data;

public:
	BOXNUM NextBox();
	void RisetCursor();
	void SetItemData(ItemData*);
	void SetText();

	Explain();
	~Explain();

};

#endif