#ifndef DEF_MiniMap
#define DEF_MiniMap

#include "define.h"
#include <string>

class MapAdmin;
class UnitAdmin;
class MiniMap {
protected:
	MapAdmin* map_admin;
	UnitAdmin* unit_admin;
	bool minimap[EXPMAP_X_MAX][EXPMAP_Y_MAX];

	int graphic_handle[MINIMAP_NUM];
public:

	MiniMap();
	~MiniMap();
	void Init(MapAdmin*, UnitAdmin*);

	void MiniMapClear();

	void GraphLoad(std::string);

	void Update(int);
	void Draw();
};

#endif
