#ifndef DEF_Cell
#define DEF_Cell

#include "define.h"
#include <vector>

class CellData;
class TrapData;
class Camera;
//class TileImage;

class Cell {
protected:

	int cx;
	int cy;

	bool temporary_cell; //ダンジョンの最初の生成時(壁か床かだけを生成する部分)において使用する。

	bool isTrapActive; //=true でトラップ露呈

	CellData* celldata;
	TrapData* trapdata;

	//CELLTYPE celltype;
	//CellTypeConverter* celltype_converter;

	//int graphic_handle[4];
	
	//std::vector<std::vector<int>> graphic_handle;
	int graphic_handle[4][6];
	int anime;

public:

	static const int ANIME_TIME;

	Cell();
	Cell(int,int);
	Cell(int,int,int);
	~Cell();

	void Clear();

	void SetCx(int);
	void SetCy(int);
	void SetTemporaryCell(bool);
	//void SetGraphicHandle(int,int);
	void SetCellData(CellData*);
	void SetTrapData(TrapData*);
	void SetTrapActive(bool);
	//void SetTileImage(TileImage*);
	//void SetCellTypeConverter(CellTypeConverter*);
	void SetGraphicHandle(int, int, int);
	void SetAnime(int);
	//void SetGraphicHandle(int*);

	//void SetCellType(CELLTYPE);

	bool GetMovef();
	bool GetTemporaryCell();
	CellData* GetCellData();
	TrapData* GetTrapData();
	bool IsTrapActive();
	//CELLTYPE GetCellType();
	//TileImage* GetTileImage();


	void Draw(Camera*, bool, int);
};


#endif
