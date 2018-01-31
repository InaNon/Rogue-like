#include "trapdataadmin.h"
#include "trapdata.h"
#include "DxLib.h"

TrapDataAdmin::TrapDataAdmin() {
};
TrapDataAdmin::~TrapDataAdmin() {
	for (unsigned int i = 0; i < trapdata.size(); i++) {
		delete trapdata[i];
	}
};

TrapData* TrapDataAdmin::GetTrapData(int i) {
	try {
		if (i < 0 || i >= (int)trapdata.size()) {
			throw i;
		}
		return trapdata[i];
	}
	catch (int i) {
		printfDx("GetTrapData Error %d", i);
		WaitKey();
		exit(1);
	}
};

void TrapDataAdmin::Init() {
	//‰¼‚Æ‚µ‚ÄA‚±‚±‚Å‘ã“ü

	for (int i = 0; i < TRAPTYPE_NUM; i++) {
		trapdata.push_back(new TrapData());
	}
	trapdata[(int)TRAP_BOMB]->TrapDataInit(TRAP_BOMB);
	trapdata[(int)TRAP_BOMB]->LoadFile("image/trap.png", 0, 0);
	trapdata[(int)TRAP_NEEDLE]->TrapDataInit(TRAP_NEEDLE);
	trapdata[(int)TRAP_NEEDLE]->LoadFile("image/trap.png", 1, 0);
	trapdata[(int)TRAP_ARROW]->TrapDataInit(TRAP_ARROW);
	trapdata[(int)TRAP_ARROW]->LoadFile("image/trap.png", 2, 0);
}