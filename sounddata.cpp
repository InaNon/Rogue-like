#include "sounddata.h"


void SoundData::SetData(vector<string> data, int _sound_handle, vector<string> data_name){

	sound_handle = _sound_handle;

	for (unsigned int j = 0; j < size(data_name); j++) {
		if (data_name[j] == "name")
			name = data[j];
	}
}

string SoundData::GetName(){

	return name;
}

int SoundData::GetSoundHandle(){

	return sound_handle;
}



SoundData::SoundData(){}
SoundData::~SoundData() {}