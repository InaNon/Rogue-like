#include "loaddatabase.h"

#include "ObjectDataAdmin.h"
#include "sounddataadmin.h"

void LoadDataBase::Init(ObjectDataAdmin* _object_data_admin, SoundDataAdmin* _sound_data_admin) {

	object_data_admin = _object_data_admin;
	sound_data_admin = _sound_data_admin;
	LoadData();
}

//アイテムの名前などの様々なデータが保存された.csvファイルを読み込む
void LoadDataBase::LoadData() {
	
	string data_line;
	ifstream unit_ifs("data_base/unit.csv");
	if (unit_ifs.fail()) {
		printfDx("fail loading database.");
	}



	getline(unit_ifs, data_line);
	while (object_data_admin->SplitLineSetUnitData(data_line)) {
		getline(unit_ifs, data_line);
	}





	ifstream equip_item_ifs("data_base/equip_item.csv");
	if (equip_item_ifs.fail()) {
		printfDx("fail loading database.");
	}

	getline(equip_item_ifs, data_line);
	while (object_data_admin->SplitLineSetEquipItemData(data_line)) {
		getline(equip_item_ifs, data_line);
	}





	ifstream status_item_ifs("data_base/status_item.csv");
	if (status_item_ifs.fail()){
		printfDx("fail loading database.");
	}


	getline(status_item_ifs, data_line);
	while (object_data_admin->SplitLineSetStatusItemData(data_line)){
		getline(status_item_ifs, data_line);
	}









	/*
	ifstream music_ifs("data_base/music.csv");
	if (music_ifs.fail()) {
		printfDx("fail loading database.");
	}


	getline(music_ifs, data_line);
	while (object_data_admin->SplitLineSetStatusItemData(data_line)) {
		getline(status_item_ifs, data_line);
	}
	*/


	ifstream sound_effect_ifs("data_base/sound_effect.csv");
	if (sound_effect_ifs.fail()) {
		printfDx("fail loading database.");
	}


	getline(sound_effect_ifs, data_line);
	while (sound_data_admin->SplitLineSetSoundEffectData(data_line)) {
		getline(sound_effect_ifs, data_line);
	}


}

LoadDataBase::LoadDataBase() {}
LoadDataBase::~LoadDataBase(){}



