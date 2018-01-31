#include "DxLib.h"
#include "define.h"
#include "unitadmin.h"
#include "mapadmin.h"
#include "messageadmin.h"
#include "selectboxadmin.h"
#include "sectionadmin.h"
#include "celldataadmin.h"
#include "stageadmin.h"
#include "camera.h"
#include "loaddatabase.h"
#include "itemdataadmin.h"
#include "trapdataadmin.h"
#include "minimap.h"
#include "modemanage.h"
#include "itemadmin.h"
#include "itemstockadmin.h"
#include "drawdungeon.h"
#include <string>

#include "dungeondifficulty.h"
#include "dungeondataadmin.h"

int Process(char key[256]) {
	if (ScreenFlip() != 0) return false; //裏画面を表に表示
	if (ProcessMessage() != 0) return false; //Windowsとの生存確認報告
	if (ClearDrawScreen() != 0) return false; //裏画面リセット
	if (GetHitKeyStateAll(key) != 0) return false;//キー確認
	return true;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);//ウィンドウモード

	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);//ウィンドウサイズとカラービット
	if (DxLib_Init() == -1) return -1;

	int SCREEN_ORIGIN = MakeScreen(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y, true); //標準サイズ用

	/*3つの表示スクリーンがある
	SCREEN_ORIGIN　画像ファイルそのままの大きさで描画したもの。
	DX_SCREEN_FRONT　ORIGINの内容をWINDOW_ZOOM倍した、実際のゲーム画面
	DX_SCREEN_BACK　FRONTの裏画面
	*/

	//SetDrawScreen(DX_SCREEN_BACK);//裏画面描画
	SetDrawMode(DX_DRAWMODE_NEAREST);//アンチとかかけるやつ
	SetTransColor(100, 100, 100);

	SetWindowText("ダ・ダ・ダ・ダンジョン");//ウィンドウタイトル

	char key[256];

	DungeonDifficulty* dungeon_difficulty = new DungeonDifficulty();
	dungeon_difficulty->Init();


	CellDataAdmin* cell_data_admin = new CellDataAdmin();
	cell_data_admin->Init();

	TrapDataAdmin* trapdata_admin = new TrapDataAdmin();
	trapdata_admin->Init();

	DungeonDataAdmin* dungeondata_admin = new DungeonDataAdmin();
	dungeondata_admin->Init(1, dungeon_difficulty);
	dungeondata_admin->SetDungeonData(0);

	MapAdmin* map_admin = new MapAdmin();
	map_admin->Init(cell_data_admin, trapdata_admin);

	map_admin->MakeMap(dungeondata_admin->GetDungeonData(0),0);

	ModeManage* mode_manage = new ModeManage();

	ItemStockAdmin* item_stock_admin = new ItemStockAdmin();

	MessageAdmin* message_admin = new MessageAdmin(key, mode_manage);

	SelectBoxAdmin* select_box_admin = new SelectBoxAdmin(key, mode_manage, item_stock_admin);

	Camera* camera = new Camera();
	camera->Init(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y);

	ItemDataAdmin* item_data_admin = new ItemDataAdmin();

	LoadDataBase* load_data_base = new LoadDataBase(item_data_admin);
	load_data_base->LoadDataBaseInit();

	ItemAdmin* item_admin = new ItemAdmin(item_data_admin, map_admin, message_admin, select_box_admin);

	UnitAdmin* unit_admin = new UnitAdmin(key, item_stock_admin, item_admin, map_admin, message_admin, select_box_admin, mode_manage);		//UnitAdminのインスタンスを作成、keyのポインタとmapadminのポインタを送っている
	select_box_admin->SelectBoxAdminInit(unit_admin->GetUnit(0));

	/*
	StageAdmin* stage_admin = new StageAdmin(map_admin, unit_admin, message_admin);
	stage_admin->StageInit();
	*/

	MiniMap* minimap = new MiniMap();
	minimap->Init(map_admin, unit_admin);

	item_admin->ItemAdminInit(unit_admin);

	

	DrawDungeon* drawdungeon = new DrawDungeon();
	drawdungeon->Init(map_admin, unit_admin, camera);
	

	while (Process(key)) {
		unit_admin->Update();		//ユニット位置の更新
		select_box_admin->Update();
		message_admin->Update();
		minimap->Update(0);
		camera->UpdatePlayerCenter(unit_admin->GetUnit(0));
		//stage_admin->Update(unit_admin->GetUnit(0));

		SetDrawScreen(SCREEN_ORIGIN);

		drawdungeon->Draw1();
		map_admin->Draw(camera, true);
		item_admin->Draw(camera);
		unit_admin->Draw(camera);
		drawdungeon->Draw3();

		minimap->Draw();
		message_admin->Draw();
		select_box_admin->Draw();

		SetDrawScreen(DX_SCREEN_BACK);//裏画面にセット
		DrawExtendGraph(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, SCREEN_ORIGIN, false);//裏画面に、ORIGINのWINDOW_ZOOM倍を表示
		//DrawRotaGraph(WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2, WINDOW_ZOOM, 0.0, SCREEN_ORIGIN, false, false);

		//DEBUG
		
		//WaitKey();
		//clsDx();
		//ScreenFlip();
		//map_admin->MapInit();
		//map_admin->MakeMap(dungeondata_admin->GetDungeonData(0),0);
		//minimap->Draw();
		//ScreenFlip();
		//WaitKey();
	}

	DxLib_End();
	return 0;
}