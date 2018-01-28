#ifndef DEF_ItemData
#define DEF_ItemData

#include "Dxlib.h"
#include "define.h"
#include <string>
#include <vector>

using namespace std;

#include "objectdata.h"

class ItemData :public ObjectData {

protected:
	int graph_handle;
	int buy;
	int sell;
	ITEM_KIND item_kind;


public:
	virtual void SetData(vector<string>, int, vector<string>) = 0;

	int GetBuy();
	int GetSell();
	int GetGraphHandle();

	virtual ITEM_KIND GetItemKind();
	virtual int GetMaxHP();
	virtual int GetCurrentHP();
	virtual int GetMaxStomach();
	virtual int GetCurrentStomach();
	virtual int GetATK();
	virtual int GetDEF();
	virtual EQUIPMENT_KIND GetEquipmentKind();

	ItemData();
	~ItemData();

};



#endif
