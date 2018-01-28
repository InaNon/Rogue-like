#ifndef DEF_Unit
#define	DEF_Unit

#include "DxLib.h"
#include "define.h"
#include <String>

using namespace std;

#include "object.h"

class UnitAdmin;
class Cmaera;
class UnitData;


class Unit :public Object {
protected:
	int stop;
	UnitData* unit_data;
	UnitAdmin* unit_admin;
	int rapid;
	int gphandle;
	COMMAND direction_flag;
	COMMAND move_flag;
	int turn_count;
	int unit_num;
	int spawn_check;
	int level;
	int max_hp;
	int current_hp;
	int max_stomach;
	int atk;
	int def;
	int current_stomach;
	int spead;
	int luk;
	int exp;
	int money;
	int reservation_map_x;
	int reservation_map_y;
	int push;
	int pop;
	COMMAND reservation_command[COMMAND_MAX];
	COMMAND first_load_command;
	COMMAND last_command;
	DIRECTION banned_direction;
	int ban_unit_num;

public:
	virtual void Spawn(UnitData*, int, int);
	void ReservationMapPosition(COMMAND);
	void UpdateMapPosition();
	bool Move();
	void Initialization();

	COMMAND GetMoveFlag();
	int GetReservationMapX();
	int GetReservationMapY();
	int GetLevel();
	int GetAtk();
	int GetDef();
	int GetMaxHP();
	void SetMaxHP(int);
	int GetCurrentHP();
	void SetCurrentHP(int);

	int Unit::GetMaxStomach();
	void SetMaxStomach(int);
	int GetCurrentStomach();
	void SetCurrentStomach(int);
	int GetATK();
	void SetATK(int);
	int GetDEF();
	void SetDEF(int);
	int GetExp();
	COMMAND GetLastCommand();
	void SetLastCommand(COMMAND);
	COMMAND GetFirstLoadCommand();
	void SetFirstLoadCommand(COMMAND);
	COMMAND GetReservationCommand();
	void SetReservationCommand(COMMAND);
	COMMAND CheckReservationCommand();
	void ResetReservationCommand();
	void LevelCheck(int);
	COMMAND GetDirectionFlag();
	void SetDirectionFlag(DIRECTION);
	DIRECTION GetBannedDirection();
	void SetBannedDirection(DIRECTION);
	int GetBanUnitNum();
	void SetBannedUnitNum(int);
	void SetForceCommand(COMMAND);
	UnitData* GetUnitData();
	void SetUnitData(UnitData*);

	int direction_x(COMMAND direction);
	int direction_y(COMMAND direction);
	int GetUnitNum();

	void attack_motion();

	virtual int Update() = 0;
	virtual void Update(int) = 0;
	virtual int direction() = 0;
	virtual int GetCurrentSatiety() = 0;
	virtual int GetMoney();
	virtual void SetMoney(int);

	Unit();
	~Unit();

};

#endif