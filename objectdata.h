#ifndef DEF_ObjectData
#define DEF_ObjectData

#include "Dxlib.h"
#include "define.h"
#include <string>
#include <vector>

using namespace std;


class ObjectData {

protected:
	string name;
	string explain;
	DUNGEON_KIND dungeon_kind;
	int growth_floor;
	int peak_floor;
	int decay_floor;
	int growth_epidemicity;
	int peak_epidemicity;
	int decay_epidemicity;


public:
	virtual void SetData(vector<string>, int, vector<string>) = 0;

	string GetName();
	string GetExplain();
	DUNGEON_KIND GetDungeonKind();
	int CheckEpidemicity(int);

	ObjectData();
	~ObjectData();

};



#endif
