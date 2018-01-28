#ifndef DEF_SimpleTileImage
#define DEF_SimpleTileImage

#include "define.h"
#include "tileimage.h"
#include <string>

class SimpleTileImage : public TileImage {
protected:
	int graphic_handle[4];
public:
	SimpleTileImage();
	~SimpleTileImage();

	bool LoadHandle(int);
	int GetGraphicHandle(int);
	int GetGraphicHandle(int,int,int);

	int GetAnime();
};


#endif
