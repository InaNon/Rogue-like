#include "drawdungeon.h"
#include "unitadmin.h"
#include "unit.h"
#include "mapadmin.h"
#include "camera.h"
#include "sectionadmin.h"
#include "section.h"

#include "room.h"

DrawDungeon::DrawDungeon() {
}

void DrawDungeon::Init(MapAdmin* m_map_admin, UnitAdmin* m_unit_admin, Camera* m_camera) {
	map_admin = m_map_admin;
	unit_admin = m_unit_admin;
	camera = m_camera;

	CreateMaskScreen();

	MaskLoad("image/mask.png", "image/ring.png");
	GraphLoad("image/black.png");
}



void DrawDungeon::Draw1() {
	SetUseMaskScreenFlag(false);
	map_admin->Draw(camera, false);
	SetUseMaskScreenFlag(true);
	if (!DEBUG_MODE_DARK) {
		MakeDark(false);
	}
}
/*
map_admin->Draw(camera, true);
unit_admin->Draw(camera);
*/
void DrawDungeon::Draw3() {
	if (!DEBUG_MODE_DARK) {
		MakeDark(true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(0, 0, black_graphic_handle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	SetUseMaskScreenFlag(false);
}


void DrawDungeon::MakeDark(bool fill_mode_f) {

	int m_x = unit_admin->GetUnit(0)->GetMAPX();
	int m_y = unit_admin->GetUnit(0)->GetMAPY();
	Room* buf_room = map_admin->GetSectionAdmin()->GetRoom(m_x, m_y);

	//if (!DEBUG_MODE_DARK) {
		if (buf_room == NULL) {
			MakeDark_Road(fill_mode_f);
		}
		else {
			MakeDark_Room(fill_mode_f);
		}
	//}
}

void DrawDungeon::MakeDark_Road(bool fill_mode_f) {
	FillMaskScreen(!fill_mode_f);

	int m_x, m_y;
	GetMaskSize(&m_x, &m_y, ring_mask_handle[(int)fill_mode_f]);
	DrawMask(WINDOWSIZE_X / 2 - m_x / 2, WINDOWSIZE_Y / 2 - m_y / 2, ring_mask_handle[(int)fill_mode_f], DX_MASKTRANS_NONE);
}


void DrawDungeon::MakeDark_Room(bool fill_mode_f) { //部屋の中を見えるようにするならfalse、後で部屋の外を塗りつぶすマスクを作る時はtrue
	FillMaskScreen(!fill_mode_f);//false = brack true = white


	int m_x = unit_admin->GetUnit(0)->GetMAPX();
	int m_y = unit_admin->GetUnit(0)->GetMAPY();
	Room* buf_room = map_admin->GetSectionAdmin()->GetRoom(m_x, m_y);

	int room_x = buf_room->GetX();
	int room_y = buf_room->GetY();
	int room_sizex = buf_room->GetSizeX();
	int room_sizey = buf_room->GetSizeY();

	int mask_x1 = room_x * CHIP_X_SIZE - CHIP_X_SIZE / 2;
	int mask_x2 = (room_x + room_sizex) * CHIP_X_SIZE + CHIP_X_SIZE / 2;
	int mask_y1 = room_y * CHIP_Y_SIZE - CHIP_Y_SIZE / 2;
	int mask_y2 = (room_y + room_sizey) * CHIP_Y_SIZE + CHIP_Y_SIZE / 2;

	int c_mask_x1 = camera->GetDrawX(room_x * CHIP_X_SIZE - CHIP_X_SIZE / 2);
	int c_mask_x2 = camera->GetDrawX((room_x + room_sizex) * CHIP_X_SIZE + CHIP_X_SIZE / 2);
	int c_mask_y1 = camera->GetDrawY(room_y * CHIP_Y_SIZE - CHIP_Y_SIZE / 2);
	int c_mask_y2 = camera->GetDrawY((room_y + room_sizey) * CHIP_Y_SIZE + CHIP_Y_SIZE / 2);

	if (camera->GetDrawf_ul(mask_x1, mask_y1, mask_x2 - mask_x1, mask_y2 - mask_y1)) {
		DrawFillMask(c_mask_x1, c_mask_y1, c_mask_x2, c_mask_y2, mask_handle[(int)fill_mode_f]);
	}
}

void DrawDungeon::MaskLoad(std::string m_filename1, std::string m_filename2) {
	LoadDivMask(m_filename1.c_str(), 2, 2, 1, CHIP_X_SIZE/2, CHIP_Y_SIZE/2, mask_handle);
	LoadDivMask(m_filename2.c_str(), 2, 2, 1, 64, 64, ring_mask_handle);
}
void DrawDungeon::GraphLoad(std::string m_filename) {
	black_graphic_handle = LoadGraph(m_filename.c_str());
}

DrawDungeon::~DrawDungeon() {
}