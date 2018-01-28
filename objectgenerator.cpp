#include "objectgenerator.h"

#include "Dxlib.h"


#include "unitadmin.h"
#include "mapadmin.h"
#include "unitdata.h"
#include "objectdataadmin.h"
#include "stagefloorobjectpropety.h"


void ObjectGenerator::Init(UnitAdmin* _unit_admin, MapAdmin* _map_admin, ObjectDataAdmin* _object_data_admin){

	unit_admin = _unit_admin;
	map_admin = _map_admin;
	object_data_admin = _object_data_admin;


	for (int i = 0; i < REMAINS + 1; i++) {
		for (int j = 0; j < UNIT_DATA_MAX; j++) {
			if (object_data_admin->GetUnitData(j) != NULL) {
				if (i == (int)object_data_admin->GetUnitData(j)->GetDungeonKind()) {
					unit_data_list[i][j] = object_data_admin->GetUnitData(j);
				}
			}else {
				unit_data_list[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < UNIT_DATA_MAX; i++) {
		stage_floor_unit_propety[i] = new StageFloorObjectPropety();
	}

	for (int i = 0; i < ITEM_DATA_MAX; i++) {
		stage_floor_item_propety[i] = new StageFloorObjectPropety();
	}

	total_epidemicity = 0;

}

//階層移動時の初めに行う
void ObjectGenerator::AdvanceInit(int stage_floor, DUNGEON_KIND dungeon_kind, int _spown_frequency_point) {

	spown_frequency_point = _spown_frequency_point;
	total_epidemicity = 0;

	for (int i = 0; i < UNIT_DATA_MAX; i++) {
		if (unit_data_list[dungeon_kind][i] != NULL) {
			stage_floor_unit_propety[i]->SetObjectData(unit_data_list[dungeon_kind][i]);
			stage_floor_unit_propety[i]->SetEpidemicity(unit_data_list[dungeon_kind][i]->CheckEpidemicity(stage_floor));
			total_epidemicity += unit_data_list[dungeon_kind][i]->CheckEpidemicity(stage_floor);
		}
	}

	printfDx("%d",total_epidemicity);

	//初めの敵の放出、100は何らかのランダムできたらよい
	//for (int i = 0; i < 100; i++) {}

}


//一ターン経過ごとにチェックする
UnitData* ObjectGenerator::SpownCheck() {
	
	int spown_check = GetRand(100);

	if (spown_check < spown_frequency_point) {

		int spown_index = GetRand(total_epidemicity);
		int storage_epidemicity = 0;

		//レア出現
		if (spown_index == 0) {}

		for (int i = 0; i < UNIT_DATA_MAX; i++) {
			storage_epidemicity += stage_floor_unit_propety[i]->GetEpidemicity();
			if (storage_epidemicity > spown_index)
				return (UnitData*)stage_floor_unit_propety[i]->GetObjectData();
		}

	}

	return NULL;
	
}


ObjectGenerator::ObjectGenerator() {}

ObjectGenerator::~ObjectGenerator() {

	delete[] stage_floor_unit_propety;
	delete[] stage_floor_item_propety;

}
