#ifndef DEF_Cell
#define DEF_Cell

#include "define.h"
#include <vector>

class CellData;
class TrapData;
class Camera;
class Cell {
protected:
	int cx;
	int cy;

	bool temporary_cell; //�_���W�����̍ŏ��̐�����(�ǂ����������𐶐����镔��)�ɂ����Ďg�p����B

	bool trapf; //=true �Ńg���b�v�I��

	CellData* celldata;
	TrapData* trapdata;

	//CELLTYPE celltype;
	//CellTypeConverter* celltype_converter;

	int graphic_handle[4];

public:

	Cell();
	Cell(int,int);
	Cell(int,int,int);
	~Cell();

	void Clear();

	void SetCx(int);
	void SetCy(int);
	void SetTemporaryCell(bool);
	void SetGraphicHandle(int,int);
	void SetCellData(CellData*);
	void SetTrapData(TrapData*);
	void SetTrapf(bool);
	//void SetCellTypeConverter(CellTypeConverter*);

	//void SetCellType(CELLTYPE);

	bool GetMovef();
	bool GetTemporaryCell();
	CellData* GetCellData();
	TrapData* GetTrapData();
	bool GetTrapf();
	//CELLTYPE GetCellType();


	void Draw(Camera*,bool);
};


#endif
