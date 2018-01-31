#ifndef DEF_UnitAdmin
#define DEF_UnitAdmin

#include "define.h"

class ItemStockAdmin;
class ItemAdmin;
class Camera;
class MapAdmin;
class MessageAdmin;
class SelectBoxAdmin;
class Unit;
class UnitData;
class ModeManage;
class ArtificialIntelligence;
class ObjectDataAdmin;
class ItemData;
class DungeonDataAdmin;
class ObjectGenerator;

class UnitAdmin {
private:
	ItemStockAdmin* item_stock_admin;
	ItemAdmin* item_admin;
	MapAdmin* map_admin;
	MessageAdmin* message_admin;
	SelectBoxAdmin* select_box_admin;
	Unit* unit[UNIT_MAX];
	ModeManage* mode_manage;
	ArtificialIntelligence*	artificial_intelligence;
	ObjectDataAdmin* object_data_admin;
	DungeonDataAdmin* dungeon_data_admin;
	ObjectGenerator* object_generator;

	int phandle;
	int ehandle;
	int unit_num;
	int	player_request;
	int enemy_attack_flag[UNIT_MAX];
	int	enemy_attack_end_check;
	int enemy_attack;
	int enemy_request;
	int flag;
	int unit_member;
	int wait_count;
	int floor_num;
	bool wait_command;

public:
	void Init(char*, ItemStockAdmin*, ItemAdmin*, MapAdmin*, MessageAdmin*, SelectBoxAdmin*, ModeManage*, ObjectDataAdmin*, DungeonDataAdmin*);
	void Spawn(UnitData*);
	void AdvanceInit();
	void Draw(Camera*);
	void Update();
	bool GetMovef(int, int, COMMAND);
	Unit* GetUnit(int);
	Unit* UnitExistMap(int, int);
	bool UnitReservationMapExist(int, int);
	void UnitStateCheck(Unit*, Unit*);
	int GetFloorNum();
	void SetFloorNum(int);

	UnitAdmin(char*);
	~UnitAdmin();

};

#endif