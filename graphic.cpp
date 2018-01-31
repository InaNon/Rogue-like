#include "graphic.h"

#include "itemadmin.h"
#include "item.h"
#include "itemdata.h"
#include "unitadmin.h"
#include "unit.h"
#include "unitdata.h"
#include "camera.h"

const float Graphic::MAX_BAR_LENGTH_X = 270;
const float Graphic::BAR_LENGTH_Y = 20;
const float Graphic::BAR_START_X = 30;
const float Graphic::BAR_START_Y = 30;
const int Graphic::HP_FONT_SIZE = 13;
const int Graphic::MONEY_FONT_SIZE = 20;


void Graphic::Init(ItemAdmin* m_item_admin, UnitAdmin* m_unit_admin, Camera* m_camera) {

	order_element = 0;

	pose_order[0] = 0;
	pose_order[1] = 1;
	pose_order[2] = 2;
	pose_order[3] = 1;

	item_admin = m_item_admin;
	unit_admin = m_unit_admin;
	camera = m_camera;

    hp_font = CreateFontToHandle(NULL, HP_FONT_SIZE, 3, DX_FONTTYPE_EDGE);
	money_font = CreateFontToHandle(NULL, 10, 3, DX_FONTTYPE_EDGE);
	advance_dungeon_font = CreateFontToHandle(NULL, 40, 3);

}




void Graphic::DrawItem() {

	for (int i = 0; i < ITEM_MAX; i++) {
		if (item_admin->GetItem(i)->GetExist() == true) {
			int plane_x = item_admin->GetItem(i)->GetX();
			int plane_y = item_admin->GetItem(i)->GetY();

			if (camera->GetDrawf(plane_x, plane_y, CHIP_X_SIZE, CHIP_Y_SIZE) == true) {
				int draw_x = camera->GetDrawX(plane_x);
				int draw_y = camera->GetDrawY(plane_y);

				if (item_admin->GetItem(i)->GetItemData() != NULL) {
					int graph_handle = item_admin->GetItem(i)->GetItemData()->GetGraphHandle();
					DrawRotaGraph(draw_x, draw_y, 1.0, 0, graph_handle, TRUE);
				}

				else {
					//printfDx("%d:NULL",i);
				}
			}
		}
	}
}


void Graphic::DrawUnit(){

	change_pose_frame++;
	if (change_pose_frame == 10) {
		order_element++;
		order_element %= 4;
		change_pose_frame = 0;
	}

	for (int i = 0; i < UNIT_MAX; i++) {
		if (unit_admin->GetUnit(i)->GetExist() == true) {
			int plane_x = unit_admin->GetUnit(i)->GetX();
			int plane_y = unit_admin->GetUnit(i)->GetY();

			if (camera->GetDrawf(plane_x, plane_y, CHIP_X_SIZE, CHIP_Y_SIZE) == true) {
				int draw_x = camera->GetDrawX(plane_x);
				int draw_y = camera->GetDrawY(plane_y);
				DIRECTION draw_direction = (DIRECTION)(unit_admin->GetUnit(i)->GetDirectionFlag());

				int graph_handle = unit_admin->GetUnit(i)->GetUnitData()->GetDrawGraphHandle(draw_direction, pose_order[order_element]);

				DrawRotaGraph(draw_x, draw_y, 1.0, 0, graph_handle, TRUE);
			}
		}
	}
}

void Graphic::DrawStatus(){

	float current_hp = unit_admin->GetUnit(0)->GetCurrentHP();
	float max_hp = unit_admin->GetUnit(0)->GetMaxHP();
	int money = unit_admin->GetUnit(0)->GetMoney();
	int floor = unit_admin->GetFloorNum();
	int level = unit_admin->GetUnit(0)->GetLevel();

	float hp_parsentage = current_hp/max_hp;
	float bar_length = MAX_BAR_LENGTH_X*hp_parsentage;

	float green = 255 * hp_parsentage;
	float red = 255 * (1 - hp_parsentage);

	DrawBoxAA(BAR_START_X-1, BAR_START_Y-1, BAR_START_X+MAX_BAR_LENGTH_X+1, BAR_START_Y+BAR_LENGTH_Y+1, GetColor(0,0,0), false);
	DrawBoxAA(BAR_START_X, BAR_START_Y, BAR_START_X+bar_length, BAR_START_Y+BAR_LENGTH_Y, GetColor(red,green,0), true);

	DrawFormatStringToHandle(BAR_START_X+1, BAR_START_Y+BAR_LENGTH_Y-HP_FONT_SIZE-1, GetColor(255,255,255), hp_font,"%d/%d", (int)current_hp, (int)max_hp);
	DrawFormatStringToHandle(330, BAR_START_Y+3, GetColor(255, 255, 255), hp_font, "%dLv", level);
	DrawFormatStringToHandle(430, BAR_START_Y+3, GetColor(255, 255, 255), hp_font, "‚¨‚©‚Ë:%d", money);
	DrawFormatStringToHandle(600, BAR_START_Y+3, GetColor(255, 255, 255), hp_font, "%d‚©‚¢", floor);

}


void Graphic::DrawAdvanceDungeon() {

	DrawFormatStringToHandle(200, 250, GetColor(255, 255, 255), advance_dungeon_font, "%d‚©‚¢", unit_admin->GetFloorNum());
}


Graphic::Graphic() {}
Graphic::~Graphic() {}
