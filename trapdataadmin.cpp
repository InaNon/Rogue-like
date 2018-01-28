#include "trapdataadmin.h"
#include "trapdata.h"
#include "DxLib.h"
#include "mymethod.h"

TrapDataAdmin::TrapDataAdmin() {
};
TrapDataAdmin::~TrapDataAdmin() {
	for (unsigned int i = 0; i < trapdata.size(); i++) {
		delete trapdata[i];
	}
};

TrapData* TrapDataAdmin::GetTrapDataRand() {
	std::vector<int> rs = MyMethod::RandomSwap(0, trapdata.size() - 1);

	for (int i = 0; i < (signed int)rs.size(); i++) {
		if (trapdata[i] != NULL) {
			return trapdata[i];
		}
	}

	return NULL;
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
		exit(1);
	}
};


void TrapDataAdmin::Init() {
	//‰¼‚Æ‚µ‚ÄA‚±‚±‚Å‘ã“ü

	for (int i = 0; i < TrapData::TRAPTYPE_NUM; i++) {
		trapdata.push_back(new TrapData());
	}

	trapdata[(int)TrapData::BOMB]->TrapDataInit(TrapData::BOMB);
	trapdata[(int)TrapData::BOMB]->LoadFile("image/trap.png", 4, 0);
	trapdata[(int)TrapData::NEEDLE]->TrapDataInit(TrapData::NEEDLE);
	trapdata[(int)TrapData::NEEDLE]->LoadFile("image/trap.png", 1, 0);
	trapdata[(int)TrapData::WARP]->TrapDataInit(TrapData::WARP);
	trapdata[(int)TrapData::WARP]->LoadFile("image/trap.png", 8, 0);
	trapdata[(int)TrapData::HUNGER]->TrapDataInit(TrapData::HUNGER);
	trapdata[(int)TrapData::HUNGER]->LoadFile("image/trap.png", 6, 0);
	trapdata[(int)TrapData::WEAPON_WARP]->TrapDataInit(TrapData::WEAPON_WARP);
	trapdata[(int)TrapData::WEAPON_WARP]->LoadFile("image/trap.png", 2, 0);

}