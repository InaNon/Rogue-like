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
#include "itemdataadmin.h"
#include "trapdataadmin.h"
#include "minimap.h"
#include "modemanage.h"
#include "itemadmin.h"
#include "itemstockadmin.h"
#include "drawdungeon.h"
#include "dungeondifficulty.h"
#include "dungeondataadmin.h"
#include "graphic.h"
#include "equipmentadmin.h"

#include "ObjectDataAdmin.h"
#include "tilesetadmin.h"
#include "trapprocess.h"




#include <string>

int Process(char key[256]) {
	if (ScreenFlip() != 0) return false; //裏画面を表に表示
	if (ProcessMessage() != 0) return false; //Windowsとの生存確認報告
	if (ClearDrawScreen() != 0) return false; //裏画面リセット
	if (GetHitKeyStateAll(key) != 0) return false;//キー確認
	return true;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//

	ChangeWindowMode(true);//ウィンドウモード

	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);//ウィンドウサイズとカラービット
	if (DxLib_Init() == -1) return -1;

	//int SCREEN_ORIGIN = MakeScreen(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y, true); //標準サイズ用



	/*3つの表示スクリーンがある
	SCREEN_ORIGIN　画像ファイルそのままの大きさで描画したもの。
	DX_SCREEN_FRONT　ORIGINの内容をWINDOW_ZOOM倍した、実際のゲーム画面
	DX_SCREEN_BACK　FRONTの裏画面
	*/

	//SetDrawScreen(DX_SCREEN_BACK);//裏画面描画
	SetDrawMode(DX_DRAWMODE_NEAREST);//アンチとかかけるやつ
	SetTransColor(100, 100, 100);

	SetWindowText("Rouge-like");//ウィンドウタイトル

	

	char key[256];
	int mode_count = 0;//ina

	//printfDx("%s",key);

	//WaitKey();

	//TileSet* test_tile_set = new TileSet();
	//test_tile_set->Init("cave");


	ModeManage* mode_manage = new ModeManage();
	DungeonDifficulty* dungeon_difficulty = new DungeonDifficulty();
	CellDataAdmin* cell_data_admin = new CellDataAdmin();
	TrapDataAdmin* trapdata_admin = new TrapDataAdmin();
	DungeonDataAdmin* dungeon_data_admin = new DungeonDataAdmin();
	MapAdmin* map_admin = new MapAdmin();
	ItemStockAdmin* item_stock_admin = new ItemStockAdmin();
	MessageAdmin* message_admin = new MessageAdmin();
	EquipmentAdmin* equipment_admin = new EquipmentAdmin();
	SelectBoxAdmin* select_box_admin = new SelectBoxAdmin();
	Camera* camera = new Camera();
	ItemDataAdmin* item_data_admin = new ItemDataAdmin();
	LoadDataBase* load_data_base = new LoadDataBase();
	ItemAdmin* item_admin = new ItemAdmin();
	UnitAdmin* unit_admin = new UnitAdmin(key);
	Graphic* graphic = new Graphic();
	MiniMap* minimap = new MiniMap();
	DrawDungeon* drawdungeon = new DrawDungeon();
	ObjectDataAdmin* object_data_admin = new ObjectDataAdmin();
	
	
	//鷹野追加
	TileSetAdmin* tile_set_admin = new TileSetAdmin();
	TrapProcess* trap_process = new TrapProcess();
	
	//鷹野追加
	tile_set_admin->Init();
	trap_process->Init(unit_admin, message_admin, item_admin);

	dungeon_data_admin->Init(1, dungeon_difficulty);
	dungeon_difficulty->Init();
	cell_data_admin->Init();
	trapdata_admin->Init();
	map_admin->Init(cell_data_admin, trapdata_admin, tile_set_admin, camera, trap_process);//引数追加
	camera->Init(WINDOWSIZE_X, WINDOWSIZE_Y);
	minimap->Init(map_admin, unit_admin);
	drawdungeon->Init(map_admin, unit_admin, camera);
	mode_manage->Init();
	item_stock_admin->Init();
	message_admin->Init(key, mode_manage);
	item_data_admin->Init();
	object_data_admin->Init();//ina

	load_data_base->Init(object_data_admin);
	equipment_admin->Init();//ina
	select_box_admin->Init(key, unit_admin, item_admin, equipment_admin, mode_manage, item_stock_admin);
	item_admin->Init(unit_admin, object_data_admin, map_admin, message_admin, select_box_admin);//ina
	graphic->Init(item_admin, unit_admin, camera);
	unit_admin->Init(key, item_stock_admin, item_admin, map_admin, message_admin, select_box_admin, mode_manage, object_data_admin, dungeon_data_admin);

	//DEBUG
	//map_admin->SetMiniMap(minimap);

	//dungeon_data_admin->SetDungeonData(0);
	//map_admin->MakeMap(dungeon_data_admin->GetDungeonData(0), 0);
	//unit_admin->Spawn();
	//item_admin->Spawn();

	//int step = 0;

	//ina
	bool stage_flag = false;
	int title = LoadGraph("image/title/title.bmp");
	
	//ina
	while (Process(key)) {

		DrawGraph(0, 0, title, false);

		for (int i = 0; i < 256; i++) {
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
			//DrawExtendGraph(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, SCREEN_ORIGIN, false);//裏画面に、ORIGINのWINDOW_ZOOM倍を表示

			//DEBUG

			//WaitKey();
			//clsDx();
			//ScreenFlip();
			//map_admin->MakeMap(dungeon_data_admin->GetDungeonData(0),step++);
			//minimap->Draw();
			//ScreenFlip();
			//WaitKey();

			/*
			if (key[KEY_INPUT_Y]) {
				clsDx();
				step++;
				if (step >= 100) {
					return 0;
				}
				map_admin->MakeMap(dungeon_data_admin->GetDungeonData(0), step);
			}
			*/
		}
	}

	DxLib_End();
	return 0;
}