#include "sounddataadmin.h"

#include "sounddata.h"





//stringŒ^‚Åw’è•¶š‚Å•¶š—ñ•ªŠ„‚ğ‚·‚éŠÖ”
template <typename List>
void split(const std::string& s, const std::string& delim, List& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}



bool SoundDataAdmin::SplitLineSetSoundEffectData(string data_line) {

	vector<string> data;
	sound_effect_data[load_sound_effect_num] = new SoundData();

	split(data_line, ",", data);



	if (title_load_flag == true) {
		if (data[0] != "end") {
			string sound_effect_path = "sound/sound_effect/" + data[1];
			int sound_effect_handle = LoadSoundMem(sound_effect_path.c_str());

			vector<string> split_data;
			for (int i = 1; i < data.size(); i++) {
				split(data[i], "\\n", split_data);
				if (split_data.size() > 1) {
					data[i] = "";
					for (int j = 0; j < split_data.size(); j++) {
						data[i] += split_data[j] + "\n";
					}
				}
			}
			sound_effect_data[load_sound_effect_num]->SetData(data, sound_effect_handle, data_name);

			load_sound_effect_num++;
		}

		else {
			title_load_flag = false;
			load_sound_effect_num--;
			for (int i = load_sound_effect_num; i < UNIT_DATA_MAX; i++) {
				sound_effect_data[i] = NULL;
			}
			return false;
		}
	}

	else if (title_load_flag == false) {
		data_name = data;
		title_load_flag = true;
	}

	return true;
}

bool SoundDataAdmin::SplitLineSetMusicData(string data_line) {

	vector<string> data;
	music_data[load_music_num] = new SoundData();

	split(data_line, ",", data);



	if (title_load_flag == true) {
		if (data[0] != "end") {
			string music_path = "sound/music/" + data[1];
			int music_handle = LoadSoundMem(music_path.c_str());

			vector<string> split_data;
			for (int i = 1; i < data.size(); i++) {
				split(data[i], "\\n", split_data);
				if (split_data.size() > 1) {
					data[i] = "";
					for (int j = 0; j < split_data.size(); j++) {
						data[i] += split_data[j] + "\n";
					}
				}
			}
			music_data[load_music_num]->SetData(data, music_handle, data_name);

			load_music_num++;
		}

		else {
			title_load_flag = false;
			load_music_num--;
			for (int i = load_music_num; i < UNIT_DATA_MAX; i++) {
				music_data[i] = NULL;
			}
			return false;
		}
	}

	else if (title_load_flag == false) {
		data_name = data;
		title_load_flag = true;
	}

	return true;
}

SoundData* SoundDataAdmin::GetSoundEffectData(string unit_name) {

	for (int i = 0; i < load_sound_effect_num; i++) {
		if (sound_effect_data[i]->GetName() == unit_name) {
			return sound_effect_data[i];
		}
	}

	return NULL;
}


SoundData* SoundDataAdmin::GetSoundEffectData(int id) {

	if (id <= load_sound_effect_num)
		return sound_effect_data[id];

	return NULL;
}

SoundData* SoundDataAdmin::GetMusicData(string unit_name) {

	for (int i = 0; i < load_music_num; i++) {
		if (music_data[i]->GetName() == unit_name) {
			return music_data[i];
		}
	}

	return NULL;
}


SoundData* SoundDataAdmin::GetMusicData(int id) {

	if (id <= load_music_num)
		return music_data[id];

	return NULL;
}


SoundDataAdmin::SoundDataAdmin() {

	load_sound_effect_num = 0;
	load_music_num = 0;
	title_load_flag = false;
}



SoundDataAdmin::~SoundDataAdmin() {}