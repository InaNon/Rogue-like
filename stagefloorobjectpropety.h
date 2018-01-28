#ifndef DEF_StageFloorObjectPropety
#define DEF_StageFloorOjectPropety

#include "define.h"

class ObjectData;

class StageFloorObjectPropety {

private:
	ObjectData* object_data;
	int epidemicity;

public:
	ObjectData* GetObjectData();
	void SetObjectData(ObjectData*);
	int GetEpidemicity();
	void SetEpidemicity(int);

	StageFloorObjectPropety();
	~StageFloorObjectPropety();

};

#endif