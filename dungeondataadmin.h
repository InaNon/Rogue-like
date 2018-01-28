#ifndef DEF_DungeonDataAdmin
#define DEF_DungeonDataAdmin

#include "define.h"
#include "Dxlib.h"

#include <vector>


class DungeonData;
class DungeonDifficulty;

class DungeonDataAdmin {
protected:
	std::vector<DungeonData*> dungeondata;
	DungeonDifficulty* dungeon_difficulty;

public:
	DungeonDataAdmin();
	~DungeonDataAdmin();

	void Init(int, DungeonDifficulty*);

	void SetDungeonData(int);

	DungeonData* GetDungeonData(int);

};

#endif

