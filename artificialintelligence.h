#ifndef DEF_ArtificialIntelligence
#define DEF_ArtificialIntelligence

#include "define.h"

class UnitAdmin;
class Unit;
class MapAdmin;

class ArtificialIntelligence {

private:
	UnitAdmin* unit_admin;
	MapAdmin* map_admin;

public:
	COMMAND EnemyAct(Unit*);
	//COMMAND ReSearchMove(COMMAND, Unit*);

	ArtificialIntelligence(UnitAdmin*, MapAdmin*);
	~ArtificialIntelligence();

};


#endif DEF_ArtificialIntelligence

