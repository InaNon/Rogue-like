#include "stagefloorobjectpropety.h"


//�K�w�ړ��̏��߂ɂ����Ƀ_���W�����ŏo��������A�C�e���ƃ����X�^�[��ۑ�
ObjectData* StageFloorObjectPropety::GetObjectData(){

	return object_data;
}

void StageFloorObjectPropety::SetObjectData(ObjectData* _object_data){

	object_data = _object_data;
}

int StageFloorObjectPropety::GetEpidemicity(){

	return epidemicity;
}

void StageFloorObjectPropety::SetEpidemicity(int _epidemicity){

	epidemicity = _epidemicity;
}



StageFloorObjectPropety::StageFloorObjectPropety(){}
StageFloorObjectPropety::~StageFloorObjectPropety(){}