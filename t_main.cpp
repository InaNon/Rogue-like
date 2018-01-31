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
	if (ScreenFlip() != 0) return false; //����ʂ�\�ɕ\��
	if (ProcessMessage() != 0) return false; //Windows�Ƃ̐����m�F��
	if (ClearDrawScreen() != 0) return false; //����ʃ��Z�b�g
	if (GetHitKeyStateAll(key) != 0) return false;//�L�[�m�F
	return true;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);//�E�B���h�E���[�h

	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);//�E�B���h�E�T�C�Y�ƃJ���[�r�b�g
	if (DxLib_Init() == -1) return -1;

	int SCREEN_ORIGIN = MakeScreen(ORIGIN_WINDOWSIZE_X, ORIGIN_WINDOWSIZE_Y, true); //�W���T�C�Y�p

	/*3�̕\���X�N���[��������
	SCREEN_ORIGIN�@�摜�t�@�C�����̂܂܂̑傫���ŕ`�悵�����́B
	DX_SCREEN_FRONT�@ORIGIN�̓��e��WINDOW_ZOOM�{�����A���ۂ̃Q�[�����
	DX_SCREEN_BACK�@FRONT�̗����
	*/

	//SetDrawScreen(DX_SCREEN_BACK);//����ʕ`��
	SetDrawMode(DX_DRAWMODE_NEAREST);//�A���`�Ƃ���������
	SetTransColor(100, 100, 100);

	SetWindowText("�_�E�_�E�_�E�_���W����");//�E�B���h�E�^�C�g��

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

	UnitAdmin* unit_admin = new UnitAdmin(key, item_stock_admin, item_admin, map_admin, message_admin, select_box_admin, mode_manage);		//UnitAdmin�̃C���X�^���X���쐬�Akey�̃|�C���^��mapadmin�̃|�C���^�𑗂��Ă���
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
		unit_admin->Update();		//���j�b�g�ʒu�̍X�V
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

		SetDrawScreen(DX_SCREEN_BACK);//����ʂɃZ�b�g
		DrawExtendGraph(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, SCREEN_ORIGIN, false);//����ʂɁAORIGIN��WINDOW_ZOOM�{��\��
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