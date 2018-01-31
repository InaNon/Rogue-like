#ifndef DEF_DungeonData
#define DEF_DungeonData

#include "define.h"
#include "Dxlib.h"

#include <vector>


class FloorData;

class DungeonData {
protected:
	std::vector<FloorData*> floordata;

public:
	DungeonData();
	~DungeonData();

	void Init(int);

	int GetFloorNum();
	FloorData* GetFloorData(int);

	void EmplaceFloorData(int);

};

#endif


/*
メモ　Mapinit

・必要引数

生成部屋数

道生成割合(double)　引くことのできる道の本数に対する、実際の道の本数の割合

部屋の辺最小値
部屋の辺最大値

生成方式
　幅優先
 　深さ優先
  　深さ優先-大きい部屋分割優先
   　外周道式

	削りフラグ
	対部屋削り割合　1部屋のマス数のうち何割を削るか

	画像セットポインタ

	壁種類　実質、斜めの是非

	出現するトラップリスト
	トラップの割合

	店の生成確率




	メモ　ダンジョンデータ

	ダンジョンデータは、各フロアのフロアデータポインタを持つ。
	ダンジョンデータから、すべてのフロアにセットしたり、特定のフロアにだけセットしたりする。

	・各ダンジョンデータ
	各フロアデータポインタ
	(階層数)




	・ 各フロアデータ

	出現する敵リスト
	敵の割合

	出現するアイテムリスト
	アイテムの割合

	店に出現するアイテムリスト
	アイテムの割合

	Mapinitに必要な引数の全て(ランダムなら、ランダムであることが分かるようなパラメータ)


	*/
