#ifndef DEF_UnitData
#define DEF_UnitData

#include "Dxlib.h"
#include "define.h"
#include <string>
#include <vector>

using namespace std;

#include "objectdata.h"

class UnitData :public ObjectData {

private:
	int graph_handle[DIR_UP_LEFT - DIR_UP + 1][3];
	int max_hp;
	int atk;
	int def;
	int speed;
	int luk;
	int exp;
	int delta_max_hp;
	int delta_atk;
	int delta_def;
	int delta_speed;
	int delta_luk;
	int delta_exp;

public:
	enum STATUS {
		MAX_HP,
		DELTA_MAX_HP,
		ATK,
		DELTA_ATK,
		DEF,
		DELTA_DEF,
		SPEED,
		DELTA_SPEED,
		LUK,
		DELTA_LUK,
		EXP,
		DELTA_EXP,
	};

	void SetData(vector<string>, int, vector<string>);
	int GetDrawGraphHandle(DIRECTION, int);
	void PrintUnitData();
	int GetStatus(STATUS);


	UnitData();
	~UnitData();

};



#endif
