#ifndef DEF_TileSet
#define DEF_TileSet

#include "define.h"
#include <string>
#include <vector>

class TileImage;

class TileSet {
public:
	static const enum TILETYPE {
		FLOOR,
		WALL,
		WALL_WRAPPER,
		WALL_FOUND,
		WALL_MINI,
		HOLE,
		HOLE_WRAPPER,
		HOLE_FOUND,
		HOLE_MINI,
		STEP_FLOOR,
		STEP_WALL,
		SHOP_FLOOR,
		TILETYPE_NUM,
	} tile_type; //tile_imageの第一次元指定用

	static const int VAR_NUM;

	static const std::string DIR_NAME;
	static const std::string EXTENSION;
	
private:

	std::vector<std::vector<TileImage*>> tile_image;
	//第一要素 = TileType,第二要素 = 種類

public:

	TileSet();
	TileSet(const TileSet &rhs);
	~TileSet();

	void Init(std::string);

	TileImage* GetTileImage(TileSet::TILETYPE, int);
	TileImage* GetTileImage(int, int);

	//タイル画像を読みこむ。
	void LoadTileImageAll(std::string);

	bool isWrapperWall();
	bool isWrapperHole();

protected:
	bool CompileTileImage(std::string, TileImage**);
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