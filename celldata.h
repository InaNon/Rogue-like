#ifndef DEF_Celldata
#define DEF_Celldata
#include "define.h"


class CellData {
protected:
	CELLTYPE celltype;

	bool movef; //移動可能か
	bool slantmovef; //斜め移動できるか

	bool stepf; //階段であるならTRUE
	bool roomf; //部屋の床であるならTRUE　壁ならとりあえずfalseにしておく。

	bool trapf; //トラップであるならtrue

	bool shopf;//店であるならtrue

	//床と壁をそれぞれ継承させるべきかも

public:

	CellData();
	CellData(const CellData &rhs);

	~CellData();

	void CellDataInit(CELLTYPE, bool, bool, bool, bool, bool);
	void CellDataInit(CELLTYPE, bool, bool, bool, bool);

	CELLTYPE GetCellType();
	bool GetMovef();
	bool GetSlantMovef();
	bool GetStepf();
	bool GetRoomf();
	bool GetTrapf();
	bool GetShopf();

	bool GetSpawnf();


	void SetCellType(CELLTYPE);
	void SetMovef(bool);
	void SetSlantMovef(bool);
	void SetStepf(bool);
	void SetRoomf(bool);
	void SetTrapf(bool);
	void SetShopf(bool);
};



#endif
