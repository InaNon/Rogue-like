#ifndef DEF_StatusItemData
#define DEF_StatusItemData

#include "Dxlib.h"
#include <string>
#include <vector>


using namespace std;



#include "itemdata.h"

class StatusItemData :public ItemData {

private:
	int max_hp;
	int current_hp;
	int max_stomach;
	int current_stomach;
	int atk;
	int def;

public:
	void SetData(vector<string>, int, vector<string>);

	ITEM_KIND GetItemKind();
	int GetMaxHP();
	int GetCurrentHP();
	int GetMaxStomach();
	int GetCurrentStomach();
	int GetATK();
	int GetDEF();

	StatusItemData();
	~StatusItemData();
};


#endif
