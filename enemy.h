#ifndef DEF_Enemy
#define	DEF_Enemy

#include "define.h"

#include "DxLib.h"
#include "unit.h"

class UnitAdmin;
class UnitData;

class Enemy : public Unit {

private:

public:
	void Spawn(UnitData*, int, int);
	int direction();
	void Update(int);
	int Update();
	void LevelCheck(int);

	int GetCurrentSatiety();

	Enemy(int, int, UnitAdmin*);
	~Enemy();

};

#endif