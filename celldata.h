#ifndef DEF_Celldata
#define DEF_Celldata
#include "define.h"


class CellData {
protected:
	CELLTYPE celltype;

	bool movef; //�ړ��\��
	bool slantmovef; //�΂߈ړ��ł��邩

	bool stepf; //�K�i�ł���Ȃ�TRUE
	bool roomf; //�����̏��ł���Ȃ�TRUE�@�ǂȂ�Ƃ肠����false�ɂ��Ă����B

	bool trapf; //�g���b�v�ł���Ȃ�true

	bool shopf;//�X�ł���Ȃ�true

	//���ƕǂ����ꂼ��p��������ׂ�����

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
