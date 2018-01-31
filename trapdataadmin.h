#ifndef DEF_TrapdataAdmin
#define DEF_TrapDataAdmin

#include "define.h"
#include "Dxlib.h"

#include <vector>

class TrapData;
class TrapDataAdmin {
protected:
	std::vector<TrapData*> trapdata;

public:
	TrapDataAdmin();
	~TrapDataAdmin();

	void Init();

	TrapData* GetTrapData(int);
};

#endif
