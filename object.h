#ifndef DEF_Object
#define DEF_Object

#include "define.h"
#include <string>

using namespace std;

class Camera;

class Object {
protected:
	int x, y;
	int map_x, map_y;
	bool exist;
	string object_name;


public:
	void Spawn(int, int);
	bool GetExist();
	void SetExist(bool);
	string GetObjectName();
	void SetObjectName(string);
	int GetX();
	int GetY();
	int GetMAPX();
	int GetMAPY();


	Object();
	~Object();

};

#endif DEF_Object