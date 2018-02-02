#ifndef DEF_ModeManage
#define DEF_ModeManage

#include "Dxlib.h"


class ModeManage {

private:
	bool unit_mode;
	bool player_command_mode;
	bool message_mode;
	bool select_mode;
	bool advance_dungeon_mode;
	bool shop_mode;

public:
	void Init();
	bool GetUnitMode();
	void SetUnitMode(bool);
	bool GetPlayerCommandMode();
	void SetPlayerCommandMode(bool);
	bool GetMessageMode();
	void SetMessageMode(bool);
	bool GetSelectMode();
	void SetSelectMode(bool);
	bool GetAdvanceDungeonMode();
	void SetAdvanceDungeonMode(bool);
	bool GetShopMode();
	void SetShopMode(bool);

	ModeManage();
	~ModeManage();
};


#endif