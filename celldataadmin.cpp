#include "celldataadmin.h"
#include "celldata.h"

CellDataAdmin::CellDataAdmin() {
};
CellDataAdmin::~CellDataAdmin() {
	for (unsigned int i = 0; i < celldata.size(); i++) {
		delete celldata[i];
	}
};

CellData* CellDataAdmin::GetCellData(int i) {
	try {
		if (i < 0 || i >= (int)celldata.size()) {
			throw i;
		}
		return celldata[i];
	}
	catch(int i) {
		printfDx("GetCellData Error %d", i);
		WaitKey();
		exit(1);
	}
};


void CellDataAdmin::SetCellData(CellData* m_celldata) {
	/*celldata.push_back(new CellData());
	*(celldata.end()-1) = &m_celldata;
	celldata_count++;
	*/
};

void CellDataAdmin::Init() {
	//âºÇ∆ÇµÇƒÅAÇ±Ç±Ç≈ë„ì¸

	for (int i = 0; i < CELLTYPE_NUM; i++) {
		celldata.push_back(new CellData());
	}
	celldata[(int)ROOM_FLOOR]->CellDataInit(ROOM_FLOOR,true, true, false, true,false);//ïîâÆÇÃè∞
	celldata[(int)ROAD_FLOOR]->CellDataInit(ROAD_FLOOR,true, true, false, false, false);//í òHÇÃè∞
	celldata[(int)BOX_WALL]->CellDataInit(BOX_WALL,false, false, false, false);//éŒÇﬂÇ≈Ç´Ç»Ç¢ï«
	celldata[(int)SLANT_WALL]->CellDataInit(SLANT_WALL,false, true, false, false);//éŒÇﬂÇ≈Ç´ÇÈï«
	celldata[(int)ROOM_STEP]->CellDataInit(ROOM_STEP,true, true, true, true, false);//ïîâÆÇÃäKíi
	celldata[(int)ROAD_STEP]->CellDataInit(ROAD_STEP,true, true, true, false, false);//í òHÇÃäKíi
	celldata[(int)TRAP_FLOOR]->CellDataInit(TRAP_FLOOR, true, true, false, true, true);//ïîâÆÇÃè∞ÅAÉgÉâÉbÉvÇ†ÇË
	celldata[(int)SHOP_FLOOR]->CellDataInit(SHOP_FLOOR, true, true, false, true, false);//ìXÇÃè∞
	celldata[(int)SHOP_FLOOR]->SetShopf(true);
}