#ifndef DEF_DrawDungeon
#define DEF_DrawDungeon
#include "define.h"
#include <string>
class MapAdmin;
class UnitAdmin;
//class ItemAdmin;
class Camera;

class DrawDungeon {
protected:
	MapAdmin* map_admin;
	UnitAdmin* unit_admin;
	//ItemAdmin* item_admin;

	Camera* camera;

	int mask_handle[2];
	int ring_mask_handle[2];


	int black_graphic_handle;

public:

	DrawDungeon();
	void Init(MapAdmin*, UnitAdmin*, Camera*);

	void Draw1();
	//void Draw2();
	void Draw3();

	void MakeDark(bool);
	void MakeDark_Room(bool);
	void MakeDark_Road(bool);

	void MaskLoad(std::string, std::string);
	void GraphLoad(std::string);



	~DrawDungeon();

};



#endif
