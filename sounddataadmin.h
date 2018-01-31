#ifndef DEF_SoundDataAdmin
#define DEF_SoundDataAdmin

#include "Dxlib.h"
#include <string>
#include <vector>
#include <iostream>
#include "define.h"

using namespace std;

class SoundData;

class SoundDataAdmin {

private:
	SoundData* sound_effect_data[SOUND_DATA_MAX];
	SoundData* music_data[SOUND_DATA_MAX];

	string data_line;
	vector<string> data_name;
	bool title_load_flag;
	int load_sound_effect_num;
	int load_music_num;

public:
	bool SplitLineSetSoundEffectData(string);
	bool SplitLineSetMusicData(string);

	SoundData* GetSoundEffectData(string);
	SoundData* GetSoundEffectData(int);
	SoundData* GetMusicData(string);
	SoundData* GetMusicData(int);

	SoundDataAdmin();
	~SoundDataAdmin();

};

#endif