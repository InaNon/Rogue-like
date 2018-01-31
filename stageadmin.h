#ifndef DEF_StageAdmin
#define DEF_StageAdmin

#include "define.h"

class MapAdmin;
class Unit;
class UnitAdmin;
class MessageAdmin;

class StageAdmin {
protected:

	int progress; //ŠK”

	int goal_progress;

	MapAdmin* map_admin;
	UnitAdmin* unit_admin;
	MessageAdmin* message_admin;

public:
	void StageInit();

	void Update(Unit*);

	void GoToNextProgress();

	void StageEnd();

	StageAdmin(MapAdmin*, UnitAdmin*, MessageAdmin*);
	~StageAdmin();
};

#endif
