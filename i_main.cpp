#include "DxLib.h"
#include "define.h"
#include "unitadmin.h"
#include "mapadmin.h"
#include "messageadmin.h"
#include "selectboxadmin.h"
#include "sectionadmin.h"
#include "celldataadmin.h"
#include "camera.h"
#include "loaddatabase.h"
#include "ObjectDataAdmin.h"
#include "trapdataadmin.h"
#include "minimap.h"
#include "modemanage.h"
#include "itemadmin.h"
#include "itemstockadmin.h"
#include "drawdungeon.h"
#include "graphic.h"
#include "equipmentadmin.h"
#include "dungeondifficulty.h"
#include "dungeondataadmin.h"

bool Process(char key[256]) {
	if (ScreenFlip() != 0)return false;
	if (ProcessMessage() != 0)return false;
	if (ClearDrawScreen() != 0)return false;
	if (GetHitKeyStateAll(key) != 0)return false;
	return true;
}




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(true);
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);//ウィンドウサイズとカラービット

	if (DxLib_Init() == -1) 
		return -1;

//	int SCREEN_ORIGIN = MakeScreen(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y, true); //標準サイズ用
	//SetDrawScreen(DX_SCREEN_BACK);

	SetDrawMode(DX_DRAWMODE_NEAREST);//アンチとかかけるやつ

	SetWindowText("Rogue-like");


	char key[256];
	int mode_count = 0;
	//printfDx("%s", key);

	CellDataAdmin* cell_data_admin = new CellDataAdmin();
	TrapDataAdmin* trapdata_admin = new TrapDataAdmin();
	MapAdmin* map_admin = new MapAdmin();
	ModeManage* mode_manage = new ModeManage();
	ItemStockAdmin* item_stock_admin = new ItemStockAdmin();
	MessageAdmin* message_admin = new MessageAdmin();
	Camera* camera = new Camera();
	ObjectDataAdmin* object_data_admin = new ObjectDataAdmin();
	LoadDataBase* load_data_base = new LoadDataBase();
	EquipmentAdmin* equipment_admin = new EquipmentAdmin();
	SelectBoxAdmin* select_box_admin = new SelectBoxAdmin();
	ItemAdmin* item_admin = new ItemAdmin();
	UnitAdmin* unit_admin = new UnitAdmin(key);
	MiniMap* minimap = new MiniMap();
	DrawDungeon* drawdungeon = new DrawDungeon();
	Graphic* graphic = new Graphic();
	DungeonDifficulty* dungeon_difficulty = new DungeonDifficulty();
	DungeonDataAdmin* dungeon_data_admin = new DungeonDataAdmin();

		
	dungeon_difficulty->Init();
	cell_data_admin->Init();
	trapdata_admin->Init();
	dungeon_data_admin->Init(1, dungeon_difficulty);
	map_admin->Init(cell_data_admin, trapdata_admin);
	camera->Init(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y);
	minimap->Init(map_admin, unit_admin);
	drawdungeon->Init(map_admin, unit_admin, camera);
	mode_manage->Init();
	item_stock_admin->Init();
	message_admin->Init(key, mode_manage);
	object_data_admin->Init();
	load_data_base->Init(object_data_admin);
	equipment_admin->Init();
	select_box_admin->Init(key, unit_admin, item_admin, equipment_admin, mode_manage, item_stock_admin);
	item_admin->Init(unit_admin, object_data_admin, map_admin, message_admin, select_box_admin);
	graphic->Init(item_admin, unit_admin, camera);
	unit_admin->Init(key, item_stock_admin, item_admin, map_admin, message_admin, select_box_admin, mode_manage, object_data_admin, dungeon_data_admin);
	


	bool stage_flag = false;
	int title = LoadGraph("image/title/title.bmp");

	while(Process(key)){

		DrawGraph(0, 0, title, false);

		for(int i = 0; i < 256; i++){
			if (key[i] == 1) {
				stage_flag = true;
				break;
			}
		}

		if (stage_flag == true) {
			mode_manage->SetAdvanceDungeonMode(true);
			break;
		}
	}
	
	DeleteGraph(title);
	
	dungeon_data_admin->SetDungeonData(0);
	map_admin->MakeMap(dungeon_data_admin->GetDungeonData(0), 0);

	while (Process(key)) {		//キー情報の取得

		if (mode_manage->GetAdvanceDungeonMode() == true) {

			graphic->DrawAdvanceDungeon();

			if (mode_count == 0) {
				unit_admin->AdvanceInit();
			}

			mode_count++;

			if (mode_count == 100) {
				mode_manage->SetAdvanceDungeonMode(false);
				mode_count = 0;
			}
		}

		else if (mode_manage->GetAdvanceDungeonMode() == false) {
			unit_admin->Update();		//ユニット位置の更新
			select_box_admin->Update();
			message_admin->Update();
			minimap->Update(0);
			camera->UpdatePlayerCenter(unit_admin->GetUnit(0));
			//SetDrawScreen(SCREEN_ORIGIN);
			drawdungeon->Draw1();
			map_admin->Draw(camera, true);
			graphic->DrawItem();
			graphic->DrawUnit();
			drawdungeon->Draw3();
			minimap->Draw();
			message_admin->Draw();
			select_box_admin->Draw();
			graphic->DrawStatus();
			//SetDrawScreen(DX_SCREEN_BACK);//裏画面にセット
			//DrawExtendGraph(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, SCREEN_ORIGIN, false);

			//printfDx("test\n");
		}
	}

	DxLib_End();
	return 0;

}