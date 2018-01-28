#ifndef DEF_AutoTileImage
#define DEF_AutoTileImage

#include "define.h"
#include "tileimage.h"
#include <string>

#include <vector>

class AutoTileImage : public TileImage {
public:
	static const enum TILE_PIECE {
		HOLD, LENG, SIDE, DENT, ALL,
	} tile_piece;
protected:

	int gh[5][4][6];
	//縦、四隅、アニメ
	int anime;

public:
	AutoTileImage();
	~AutoTileImage();

	//@Override
	bool LoadHandle(int);
	int GetGraphicHandle(int);
	int GetGraphicHandle(int, int, int);
	int GetAnime();
};


#endif
