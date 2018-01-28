#ifndef DEF_CellImage
#define DEF_CellImage

#include "define.h"
#include <string>

class CellImage {
protected:
	int graphic_handle[4];
public:
	CellImage();
	~CellImage();

	virtual void LoadFile(std::string,int,int);
	virtual int GetGraphicHandle(int);
};


#endif
