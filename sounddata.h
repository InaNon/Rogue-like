#ifndef DEF_SoundData
#define DEF_SoundData

#include "Dxlib.h"
#include "define.h"
#include <string>
#include <vector>

using namespace std;

#include "objectdata.h"

class SoundData {

private:
	string name;
	int sound_handle;

public:

	void SetData(vector<string>, int, vector<string>);
	string GetName();
	int GetSoundHandle();

	SoundData();
	~SoundData();

};



#endif
