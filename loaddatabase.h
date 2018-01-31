#ifndef DEF_LoadDataBase
#define DEF_LoadDataBase

#include "DxLib.h"
#include <string>
#include <fstream>
#include "define.h"

using namespace std;

class ObjectDataAdmin;
class SoundDataAdmin;

class LoadDataBase {

private:
	ObjectDataAdmin* object_data_admin;
	SoundDataAdmin* sound_data_admin;

public:
	void Init(ObjectDataAdmin*, SoundDataAdmin*);
	void LoadData();

	LoadDataBase();
	~LoadDataBase();

};

#endif