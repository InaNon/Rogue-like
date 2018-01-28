#ifndef DEF_ObjectGenerator
#define DEF_ObjectGenerator

#include "define.h"

class UnitAdmin;
class MapAdmin;
class ObjectDataAdmin;
class UnitData;
class StageFloorObjectPropety;

class ObjectGenerator {

private:
	UnitAdmin* unit_admin;
	MapAdmin* map_admin;
	ObjectDataAdmin* object_data_admin;

	UnitData* unit_data_list[REMAINS+1][UNIT_DATA_MAX];
	StageFloorObjectPropety* stage_floor_unit_propety[UNIT_DATA_MAX];
	StageFloorObjectPropety* stage_floor_item_propety[UNIT_DATA_MAX];

	int total_epidemicity;
	int spown_check_param;
	int spown_frequency_point;

public:
	void Init(UnitAdmin*, MapAdmin*, ObjectDataAdmin*);
	void AdvanceInit(int, DUNGEON_KIND,int);
	UnitData* SpownCheck();



	ObjectGenerator();
	~ObjectGenerator();

};


#endif DEF_ArtificialIntelligence
