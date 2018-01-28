#ifndef DEF_TrapProcess
#define DEF_TrapProcess

#include "Dxlib.h"
#include "trapdata.h"

#include <vector>

class UnitAdmin;
class ItemAdmin;
class MessageAdmin;

class TrapProcess {
private:
	UnitAdmin* unitAdmin;
	MessageAdmin* messageAdmin;
	ItemAdmin* itemAdmin;

public:
	TrapProcess();
	~TrapProcess();

	void Init(UnitAdmin*, MessageAdmin*, ItemAdmin*);

	void Process(TrapData::TRAPTYPE);

	void Needle();
	void Warp();
	void Hunger();
	void Bomb();
	void WeaponWarp();

	void trapMessage(std::string, std::string);


};

#endif