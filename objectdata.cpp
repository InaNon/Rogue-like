#include "objectdata.h"

string ObjectData::GetName() {

	return name;
}

string ObjectData::GetExplain() {

	return explain;
}

DUNGEON_KIND ObjectData::GetDungeonKind(){

	return dungeon_kind;
}

int ObjectData::CheckEpidemicity(int stage_floor) {

	if (stage_floor <= growth_floor) {
		return growth_epidemicity;
	}
	else if (stage_floor < peak_floor){
		return growth_epidemicity + stage_floor * ((peak_epidemicity - growth_epidemicity) / (peak_epidemicity - growth_floor));
	}
	else if (stage_floor < decay_floor){
		return peak_epidemicity + stage_floor * ((decay_epidemicity - peak_epidemicity) / (decay_epidemicity - peak_floor));
	}else if (stage_floor >= decay_floor) {
		return decay_epidemicity;
	}

	return decay_epidemicity;


/*
	if (stage < growth_peak) {
		return GROWTH;
	}else if (stage < growth_peak) {
		return PEAK;
	}else{
		return DECAY;
	}

	return DECAY;
*/
}

ObjectData::ObjectData() {}
ObjectData::~ObjectData() {}
