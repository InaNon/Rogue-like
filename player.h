#ifndef DEF_Player
#define	DEF_Player

#include "DxLib.h"
#include "unit.h"

class UnitAdmin;

class Player : public Unit {
private:
	char* key;
	bool direction_mode;
	bool control_flag;
	int max_satiety;
	int current_satiety;
	int satiety_count;

public:
	void Spawn(int, int);
	int direction();
	int Update();
	void Update(int k);
	int GetMoney();
	void SetMoney(int);
	int GetFloor();
	void SetFloor(int);

	int GetCurrentSatiety();

	Player(int , int, char*, UnitAdmin*);
	~Player();

};

#endif