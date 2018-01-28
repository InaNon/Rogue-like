#ifndef DEF_TileImage
#define DEF_TileImage

#include "define.h"
#include <string>
#include <vector>

class TileImage {
protected :
	bool is_auto;
	bool is_simple;
public:
	TileImage();
	TileImage(const TileImage &rhs);
	~TileImage();

	virtual bool LoadHandle(int) = 0;
	virtual int GetGraphicHandle(int, int, int) = 0;
	virtual int GetGraphicHandle(int) = 0;
	virtual int GetAnime();

	bool IsAuto();
	bool IsSimple();
};


#endif