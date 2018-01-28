#ifndef DEF_TileSetAdmin
#define DEF_TileSetAdmin

#include "define.h"
#include "Dxlib.h"
#include <vector>

class TileSet;
class TileSetAdmin {
public:
	static const int TILE_SET_NUM;

private:
	std::vector<TileSet*> tile_set;
	//第一要素は属性
public:

	TileSetAdmin();
	~TileSetAdmin();

	void Init();

	void GraphLoad();

	//tottyuu
	//void MakeGraphic();
	//void SetAutoCellGrahic(int, int, CELLTYPE);
	//void SetCellGrahic(int, int, CELLTYPE);

	TileSet* GetTileSet(int);
};

#endif


/*
タイルの種類

・属性毎
床

壁のラッパー
壁の土台
1マス用壁

穴のラッパー
穴の土台
1マス用穴

床階段
壁階段

・共通
店の床

ラッパーと土台のセットなのか、ただ一種類の画像しかないかのどちらなのかは分からない。
後者の場合は１マス用のやつが無くても構わない
上記のものをセットにして格納しておくクラスが欲しい。

オートタイルかどうかは分からない。
継承によって管理することにし、フラグで判別したり、共通名メソッドなどを使う

*/