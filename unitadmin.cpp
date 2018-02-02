#include "unitadmin.h"

#include "DxLib.h"

#include "unit.h"
#include "player.h"
#include "enemy.h"
#include "itemstockadmin.h"
#include "itemadmin.h"
#include "item.h"
#include "mapadmin.h"
#include "messageadmin.h"
#include "selectboxadmin.h"
#include "modemanage.h"
#include "artificialintelligence.h"
#include "celldata.h"
#include "objectdataadmin.h"
#include "unitdata.h"
#include "dungeondataadmin.h"
#include "objectgenerator.h"
#include "room.h"


void UnitAdmin::Init(char* m_key, ItemStockAdmin* m_item_stock_admin, ItemAdmin* m_item_admin, MapAdmin* m_map_admin, MessageAdmin* m_message_admin, SelectBoxAdmin* m_select_box_admin, ModeManage* m_mode_manage, ObjectDataAdmin* m_object_data_admin, DungeonDataAdmin* m_dungeon_data_admin) {

	player_request = NOTHING;
	enemy_request = NOTHING;
	wait_count = 0;
	flag = 1;
	unit_member = 3;
	enemy_attack_end_check = 1;
	wait_command = true;
	floor_num = 0;

	for (int i = 0; i < UNIT_MAX; i++)
		enemy_attack_flag[i] = 0;

	enemy_attack = 0;

	item_stock_admin = m_item_stock_admin;
	item_admin = m_item_admin;
	map_admin = m_map_admin;			//�}�b�v�C���X�^���X�̃|�C���^����荞��
	message_admin = m_message_admin;
	select_box_admin = m_select_box_admin;
	mode_manage = m_mode_manage;
	object_data_admin = m_object_data_admin;
	dungeon_data_admin = m_dungeon_data_admin;


	artificial_intelligence = new ArtificialIntelligence(this, map_admin);
	object_generator = new ObjectGenerator();
	object_generator->Init(this, map_admin, object_data_admin);
	unit[0]->SetUnitData(object_data_admin->GetUnitData("�t�F�A���["));

}

//���j�b�g��`�悷��
void UnitAdmin::Draw(Camera* camera) {

	//for (int i = 0; i< UNIT_MAX; i++) 
		//unit[i]->Draw(unit[i]->direction(),camera);

}


void UnitAdmin::AdvanceInit() {

	floor_num++;

	for (int i = 1; i < UNIT_MAX; i++) {
		unit[i]->ResetReservationCommand();
		unit[i]->SetFirstLoadCommand(NOTHING);
	}

	map_admin->MakeMap(dungeon_data_admin->GetDungeonData(0), 0);
	item_admin->Spawn();
	object_generator->AdvanceInit(30, CAVE, 100);

	for (int i = 0; i < UNIT_MAX; i++) {
		unit[i]->SetExist(false);
	}

	int spawn_x = -100;
	int spawn_y = -100;

	map_admin->GetRespawnCell(&spawn_x, &spawn_y);

	unit[0]->Spawn(NULL, spawn_x, spawn_y);


	//�K�w�ړ����̃��j�b�g�����A100�^�[���o�߂Ɠ��`�A100�Ƃ��������̓|�C���g����U��ɂ���Ă����ꂽ�ق����ǂ�
	for (int i = 0; i < 3; i++) {
		UnitData* spown_unit_data = object_generator->SpownCheck();
		if (spown_unit_data != NULL) {
			Spawn(spown_unit_data);
		}
	}
	return;
}


Unit* UnitAdmin::UnitExistMap(int check_x, int check_y) {

	for (int i = 0; i < UNIT_MAX; i++) {
		if (unit[i]->GetExist() == true) {
			if (check_x == unit[i]->GetMAPX() && check_y == unit[i]->GetMAPY()) {
				return unit[i];
			}
		}
	}

	return NULL;

}


void UnitAdmin::Spawn(UnitData* spown_unit) {

	int spown_unit_num = 1;
	while (spown_unit_num < UNIT_DATA_MAX) {
		if (unit[spown_unit_num]->GetExist() == false) {
			break;
		}
		spown_unit_num++;
	}

	if (spown_unit_num < UNIT_DATA_MAX) {

		int spawn_x = -100;
		int spawn_y = -100;

		map_admin->GetRespawnCell(&spawn_x, &spawn_y);

		unit[spown_unit_num]->Spawn(spown_unit, spawn_x, spawn_y);
	}
}


bool UnitAdmin::UnitReservationMapExist(int check_x, int check_y) {

	for (int i = 0; i < UNIT_MAX; i++) {
		if (unit[i]->GetExist() == true) {
			if (check_x == unit[i]->GetReservationMapX() && check_y == unit[i]->GetReservationMapY()) {
				return true;
			}
		}
	}

	return false;

}

void UnitAdmin::UnitStateCheck(Unit* attack_unit , Unit* target_unit) {
	int old_hp;
	int result_hp;

	if (target_unit != NULL) {
		old_hp = target_unit->GetCurrentHP();
		result_hp = old_hp - attack_unit->GetAtk() - GetRand(2);
		target_unit->SetCurrentHP(result_hp);

		message_admin->AttackMessage(attack_unit->GetObjectName(), target_unit->GetObjectName(), old_hp - result_hp );

		if (result_hp <= 0) {
			target_unit->SetExist(false);
			target_unit->Initialization();
			message_admin->CrushMessage(attack_unit->GetObjectName(), target_unit->GetObjectName());
			message_admin->ExpMessage(attack_unit->GetObjectName(), target_unit->GetExp());
			attack_unit->LevelCheck(target_unit->GetExp());
		}
	}
}



//���j�b�g�̍s���X�V
void UnitAdmin::Update() {

	Room* room = map_admin->GetRoom(unit[0]->GetMAPX(), unit[0]->GetMAPY());
	unit[0]->direction();

	if (mode_manage->GetMessageMode() == true || mode_manage->GetSelectMode() == true) {
		mode_manage->SetUnitMode(false);
		return;
	}

	if ((mode_manage->GetMessageMode() == false || mode_manage->GetSelectMode() == false) && mode_manage->GetUnitMode() == false && wait_count < 16) {
		wait_count++;
		return;
	}

	if ((mode_manage->GetMessageMode() == false || mode_manage->GetSelectMode() == false) && mode_manage->GetUnitMode() == false && wait_count == 16) {
		wait_count = 0;
		mode_manage->SetUnitMode(true);
		mode_manage->SetPlayerCommandMode(true);
	}


	int i;
	COMMAND act;

	//�v���C���[���G�����N�G�X�g���Ȃ��ꍇ�A�v���C���[�̃��N�G�X�g����t�A�ړ����U���ɂ���ĈႤ�t���O�����Ă�
	if (player_request == NOTHING && enemy_request == NOTHING) 
		player_request = unit[0]->Update();

	//�v���C���[���U������ꍇ�A�U�������s���I�������Ƃ��Ƀ��N�G�X�g��attack�t���O��߂�
	if (player_request == ATTACK) {
		wait_command = false;
		mode_manage->SetPlayerCommandMode(false);
		if (unit[0]->Move() == 1) {
			player_request = NOTHING;
		}

		//���߂ăv���C���[���N�G�X�g�������ɖ߂������A�G�̃��N�G�X�g����t�A�U���̏ꍇ��attack�z��ŋL�^
		if (player_request == NOTHING) {
			if (enemy_request == NOTHING) {
				enemy_request = 1;
				for (i = 1; i < UNIT_MAX; i++) {
					if (unit[i]->GetExist() == true) {
						act = artificial_intelligence->EnemyAct(unit[i]);
						unit[i]->ReservationMapPosition(act);
						unit[i]->Update(act);
						unit[i]->SetLastCommand(act);

						if (act == ATTACK) {
							enemy_attack_flag[i] = 1;
							enemy_attack = 1;
						}
					}
				}
			}
		}
	}


	//�v���C���[���ړ�����ꍇ�A�ړ������s����O�ɓG�̃��N�G�X�g����t�A�U���̗L���ƓG�ԍ����L�^
	if (player_request >= UP && player_request <= STOP) {
		wait_command = false;
		mode_manage->SetPlayerCommandMode(false);
		if (enemy_request == NOTHING) {
			enemy_request = 1;
			for (i = 1; i < UNIT_MAX; i++) {
				if (unit[i]->GetExist() == true) {
					act = artificial_intelligence->EnemyAct(unit[i]);
					unit[i]->ReservationMapPosition(act);
					unit[i]->Update(act);
					unit[i]->SetLastCommand(act);

					if (act == ATTACK) {
						enemy_attack_flag[i] = 1;
						enemy_attack = 1;
					}
				}
			}
		}
	}



	//�v���C���[���ړ������G�̍U��������ꍇ�̓v���C���[�̈ړ��ƃA�C�e���̃`�F�b�N���s�����N�G�X�g�ƃt���O��߂�
	if (enemy_attack == 1 && player_request >= UP && player_request <= STOP) {
		if (unit[0]->Move() == 1) {

			//shop����
			if (room != NULL) {
				if (room->IsShopRoom() == true) {
					if (mode_manage->GetShopMode() == false) {
						message_admin->AnyMessage("��������Ⴂ�܂�", true);
						mode_manage->SetShopMode(true);
					}
				}else {
					if (room->IsShopRoom() == false) {
						if (mode_manage->GetShopMode() == true) {
							int total_sell = item_admin->GetTotalSell();
							int total_buy = item_stock_admin->GetTotalBuy();
							if (total_sell*total_buy != 0) {
								if (total_sell > 0) {
									message_admin->AnyMessage("���l�͍��v1000�ɂȂ�܂��A����܂���?", true);
									if (list_box_admin->yes_or_no() == true) {
										unit[0]->SetMoney(unit[0]->GetMoney() + total_sell);
										item_admin->SellItem();
										mode_manage->SetShopMode(true);
									}else {
										unit[0]->ippomodoru();
									}
								}
								if (total_buy > 0) {
									message_admin->AnyMessage("���l�͍��v1000�ɂȂ�܂��A�����܂���?", true);
									if (list_box_admin->yes_or_no() == true) {
										unit[0]->SetMoney(unit[0]->GetMoney() - total_buy);
										item_stock_admin->BuyItem();
										mode_manage->SetShopMode(true);
									}else {
										unit[0]->ippomodoru();
									}
								}
							}
						}
					}
				}
			}
			if (map_admin->GetMapCellData(unit[0]->GetMAPX(), unit[0]->GetMAPY())->GetStepf() == true) {
				mode_manage->SetAdvanceDungeonMode(true);
			}else if (item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY()) != NULL) {
				item_stock_admin->SetItemDataToItemStock(item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY())->GetItemData(), NO_ITEM_STOCK_NUM);
				item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY())->SetExist(false);
				item_admin->SubtractItemNum();
			}

			player_request = NOTHING;
		}
	}
	

	//��ɓG�̍s�������A���������ׂẴ��j�b�g�i�v���C���[����ѓG�j���U�������ړ��������Ȃ��ꍇ�̃v���C���[�̍s���͂��̒��ŏ��������
	if (wait_command == false && (player_request == NOTHING || (player_request >= UP && player_request <= STOP && enemy_attack == 0))) {
		//�����œG�̍U��������ꍇ�ɂ��ď����A�G�ԍ������������ɏ������s���U�����I���Ƃ��̔ԍ��̃t���O��߂�
		for (i = 1; i < UNIT_MAX; i++) {
			if (enemy_attack_flag[i] == 1) {
				if (unit[i]->Move() == true) {
					enemy_attack_flag[i] = 0;
				}
				break;
			}
		}

		//�G�S���̍U�����I�����������m�F�A�I�����Ă����ꍇ�c���Ă��郆�j�b�g�̍s�������ׂčs��(��ɓG�̈ړ��A���ׂẴ��j�b�g���ړ�����ꍇ�̃v���C���[�̈ړ����܂�)�A���ׂẴ��j�b�g���ړ�����ꍇ�̓A�C�e���̃`�F�b�N���s��
		enemy_attack_end_check = 1;
		for (i = 1; i < UNIT_MAX; i++) {
			enemy_attack_end_check = enemy_attack_end_check * !enemy_attack_flag[i];
		}

		if (enemy_attack_end_check == 1) {
			flag = 1;
			for (i = 0; i < UNIT_MAX; i++) {
				if (unit[i]->GetExist() == true)
					flag = flag * unit[i]->Move();
			}

			if (flag == 1) {

				for (i = 0; i < UNIT_MAX; i++) 
					unit[i]->UpdateMapPosition();

				if (enemy_attack == 0) {

					//shop����
					if (room != NULL) {
						if (room->IsShopRoom() == true) {
							if (mode_manage->GetShopMode() == false) {
								message_admin->AnyMessage("��������Ⴂ�܂�", true);
								mode_manage->SetShopMode(true);
							}
						}else {
							if (room->IsShopRoom() == false) {
								if (mode_manage->GetShopMode() == true) {
									int total_sell = item_admin->GetTotalSell();
									int total_buy = item_stock_admin->GetTotalBuy();
									if (total_sell*total_buy != 0) {
										if (total_sell > 0) {
											message_admin->AnyMessage("���l�͍��v1000�ɂȂ�܂��A����܂���?", true);
											if (list_box_admin->yes_or_no() == true) {
												unit[0]->SetMoney(unit[0]->GetMoney() + total_sell);
												item_admin->SellItem();
												mode_manage->SetShopMode(true);
											}else {
												unit[0]->ippomodoru();
											}
										}
										if (total_buy > 0) {
											message_admin->AnyMessage("���l�͍��v1000�ɂȂ�܂��A�����܂���?", true);
											if (list_box_admin->yes_or_no() == true) {
												unit[0]->SetMoney(unit[0]->GetMoney() - total_buy);
												item_stock_admin->BuyItem();
												mode_manage->SetShopMode(true);
											}else {
												unit[0]->ippomodoru();
											}
										}
									}
								}
							}
						}
					}
					if (map_admin->GetMapCellData(unit[0]->GetMAPX(), unit[0]->GetMAPY())->GetStepf() == true) {
						mode_manage->SetAdvanceDungeonMode(true);
					}else if (item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY()) != NULL) {
						item_stock_admin->SetItemDataToItemStock(item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY())->GetItemData(), NO_ITEM_STOCK_NUM);
						item_admin->ItemExistMap(unit[0]->GetMAPX(), unit[0]->GetMAPY())->SetExist(false);
					}
				}
				mode_manage->SetPlayerCommandMode(true);
				enemy_attack_end_check = 1;
				player_request = NOTHING;
				enemy_request = NOTHING;
				enemy_attack = 0;
				wait_command = true;
			}
		}
	}
}

//�}�b�v�̕ǔ���
bool UnitAdmin::GetMovef(int x, int y, COMMAND move_command) {

	if (map_admin->GetMapCell(x, y) == NULL) {
		return false;
	}

	return map_admin->GetMovef_Conv(x,y, move_command);

}

Unit* UnitAdmin::GetUnit(int i) {
	return unit[i];
}

int UnitAdmin::GetFloorNum() {

	return floor_num;
}

void UnitAdmin::SetFloorNum(int _floor_num){

	floor_num = _floor_num;
}


UnitAdmin::UnitAdmin(char* m_key) {

	unit[0] = new Player(0, phandle, m_key, this);		//���j�b�g�z��Ƀv���C���[�̃C���X�^���X��ۑ�
	for (int i = 1; i < UNIT_MAX; i++) {			//���j�b�g�z��ɓG�̃C���X�^���X��ۑ�
		unit[i] = new Enemy(i, ehandle, this);
	}
}

UnitAdmin::~UnitAdmin() {

	for (int i = 0; i < UNIT_MAX; i++) 
		delete unit[i];

	delete object_generator;

}
