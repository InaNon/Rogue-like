#ifndef DEF_LoadDataBase
#define DEF_LoadDataBase

#include "DxLib.h"
#include <string>
#include <fstream>
#include "define.h"

using namespace std;

class ObjectDataAdmin;

class LoadDataBase {

private:
	ObjectDataAdmin* object_data_admin;

public:
	void Init(ObjectDataAdmin*);
	void LoadData();

	LoadDataBase();
	~LoadDataBase();

};

#endif