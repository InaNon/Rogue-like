#ifndef DEF_FloorData
#define DEF_FloorData

#include "define.h"
#include "Dxlib.h"
#include <vector>

class FloorData {
protected:
	std::vector<int> makeroom_num; //生成部屋数値
	double makeroad_rate; //生成道割合

	int floorsizex; //フロアx
	int floorsizey; //フロアy

	int roomsize_min; //部屋最小値
	int roomsize_max; //部屋最小値

	int shopsize_min; //ショップ最小値
	int shopsize_max; //ショップ最小値

	int enemy_param;

	DUNGEON_MAKE_MODE makemode; //ダンジョン生成方式
	/*
	DEPTH_FIRST_RAND, 幅優先
	DEPTH_FIRST_LARGER, 深さ優先
	WIDTH_FIRST, 深さ優先-大きい部屋分割優先
	線引き部屋割り
	外周方式
	*/

	double shave_rate; //削り率
	double road_rate; //作られ得る道に対する実際の道の割合


	//画像セットポインタ

	bool wallslant_f; //壁斜め

	//トラップリスト
	int trap_num;//トラップ数

	double shop_rate; //部屋生成率

	int element;//ダンジョンの属性

	//出現する敵リスト
	//敵の割合

	//出現するアイテムリスト
	int item_num;//アイテムの数

	//店に出現するアイテムリスト
	//アイテムの割合

	double monsterhouse_rate;//モンスターハウス出現確率


public:
	FloorData();
	FloorData(const FloorData &rhs);
	~FloorData();

	void Init();


	/* ゲッター */
	int GetMakeroomNum(int); //生成部屋数値
	double GetMakeroadRate(); //生成道割合

	int GetFloorsizeX();
	int GetFloorsizeY();

	int GetRoomsizeMin(); //部屋最小値
	int GetRoomsizeMax(); //部屋最大値

	int GetShopsizeMin();
	int GetShopsizeMax();

	int GetElement();

	int GetEnemyParam();

	DUNGEON_MAKE_MODE GetMakemode(); //ダンジョン生成方式

	double GetShaveRate(); //削り率

	bool GetWallSlant_f(); //壁斜め

	int GetTrapNum();
	int GetItemNum();

	double GetShopRate(); //店生成率

	double GetMonsterhouseRate();

	/* セッター */
	void SetMakeroomNum(int); //生成部屋数値
	void SetMakeroadRate(double); //生成道割合

	void SetFloorsizeX(int);
	void SetFloorsizeY(int);

	void SetShopsizeMin(int);
	void SetShopsizeMax(int);

	void SetRoomsizeMin(int); //部屋幅最小値
	void SetRoomsizeMax(int); //部屋高さ最大値

	void SetElement(int);

	void SetEnemyParam(int);

	void SetMakemode(DUNGEON_MAKE_MODE); //ダンジョン生成方式

	void SetShaveRate(double); //削り率

	void SetWallSlant_f(bool); //壁斜め

	void SetTrapNum(int);
	void SetItemNum(int);

	void SetShopRate(double); //店生成率

	void SetMonsterhouseRate(double);

};

#endif

/*
メモ　Mapinit

・必要引数

フロアの大きさx
フロアの大きさy

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









	データベース

	部屋の






	*/