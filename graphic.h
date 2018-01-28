#ifndef DEF_Graphic
#define	DEF_Graphic

#include "DxLib.h"
#include "define.h"


class ItemAdmin;
class UnitAdmin;
class Camera;

class Graphic {

protected:
	ItemAdmin* item_admin;
	UnitAdmin* unit_admin;
	Camera* camera;
	int pose_order[4];
	int order_element;
	int change_pose_frame;
	int money_font;
	int hp_font;
	int advance_dungeon_font;


public:
	void Init(ItemAdmin*, UnitAdmin*, Camera*);
	void DrawItem();
	void DrawUnit();
	void DrawStatus();
	void DrawAdvanceDungeon();

	static const float Graphic::MAX_BAR_LENGTH_X;
	static const float Graphic::BAR_LENGTH_Y;
	static const float Graphic::BAR_START_X;
	static const float Graphic::BAR_START_Y;
	static const int Graphic::HP_FONT_SIZE;
	static const int Graphic::MONEY_FONT_SIZE;

	Graphic();
	~Graphic();

};

#endif