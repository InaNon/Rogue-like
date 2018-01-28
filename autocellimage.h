#ifndef DEF_AutoCellImage
#define DEF_AutoCellImage

#include "define.h"
#include <string>
#include "cellimage.h"

class AutoCellImage : public CellImage {
protected:
	int graphic_handle_auto[];
public:
	AutoCellImage();
	~AutoCellImage();

	void LoadFile(std::string, int, int);
	int GetGraphicHandle(int);
};


#endif
