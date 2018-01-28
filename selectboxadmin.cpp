#include "selectboxadmin.h"

#include "unitadmin.h"
#include "itemadmin.h"
#include "itemstockadmin.h"
#include "itemstock.h"
#include "menu.h"
#include "status.h"
#include "iteminventory.h"
#include "useitem.h"
#include "itemdeal.h"
#include "itemdata.h"
#include "equipbox.h"
#include "equipmentadmin.h"
#include "putoff.h"
#include "equipment.h"
#include "explain.h"


void SelectBoxAdmin::Init(char* m_key, UnitAdmin* m_unit_admin, ItemAdmin* m_item_admin, EquipmentAdmin* m_equipment_admin, ModeManage* m_mode_manage, ItemStockAdmin* m_item_stock_admin) {

	unit_admin = m_unit_admin;
	item_admin = m_item_admin;
	equipment_admin = m_equipment_admin;

	key = m_key;

	list_box[STATUS] = new Status(m_key, unit_admin->GetUnit(0));
	item_deal = new ItemDeal(unit_admin, m_equipment_admin);
	list_box[EQUIP] = new EquipBox(m_key, m_equipment_admin);
	list_box[ITEM] = new ItemInventory(m_key, m_item_stock_admin);
	list_box[MENU] = new Menu(m_key);
	list_box[USE_ITEM] = new UseItem(m_key);
	list_box[PUT_OFF] = new PutOff(m_key);
	list_box[EXPLAIN] = new Explain();

	item_stock_admin = m_item_stock_admin;
	mode_manage = m_mode_manage;

	count = 0;

	for (int i = 0; i < LIST_BOX_MAX; i++) {
		draw_flag[i] = false;
		active_flag[i] = false;

		for (int j = 0; j < OLD_MAX; j++) {
			old_draw_flag[j][i] = false;
			old_active_flag[j][i] = false;
		}
	}

	active_flag[NOBOX] = true;
}

//draw_flag��true�̃{�b�N�X��`��
void SelectBoxAdmin::Draw() {

	for (int i = 0; i < LIST_BOX_MAX; i++) {
		if (draw_flag[i] == true)
			list_box[i]->Draw();
	}
}


//�{�b�N�X�S�ʂ̍X�V�Acount�͘A���ł̃L�[���͂�����邽�߂̂���
void SelectBoxAdmin::Update() {

	if (count != COUNT_MARGIN)
		count++;

	//M�Ń��j���[��ʂ��J����
	if (key[KEY_INPUT_M] == 1 && mode_manage->GetPlayerCommandMode() && count == COUNT_MARGIN && (active_flag[MENU] == true || active_flag[NOBOX] == true)) {
		count = 0;
		list_box[MENU]->ResetCursor();
		draw_flag[MENU] = !draw_flag[MENU];
		active_flag[MENU] = !active_flag[MENU];
		active_flag[NOBOX] = !active_flag[NOBOX];
		mode_manage->SetSelectMode(!mode_manage->GetSelectMode());
	}










	//�G���^�[���������ꍇ�A�I�����̂���{�b�N�X�Ȃ�΁A���̏����i�����Ɏ��̃{�b�N�X���ĂыN�����j���s��
	if (key[KEY_INPUT_RETURN] == 1 && count == COUNT_MARGIN) {

		count = 0;
		//���̃{�b�N�X���J������
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			if (active_flag[i] == true) {

				if (i == ITEM) {
					if (item_stock_admin->GetItemNum() == 0)
						break;
				}

				next_box_num = list_box[i]->NextBox();
				break;
			}
		}











		//�A�C�e���̎g�p��ʂ��J���Ă����ꍇ�̏���
		if (active_flag[USE_ITEM] == true) {
			if (0 <= list_box[USE_ITEM]->GetCursor() && list_box[USE_ITEM]->GetCursor() <= 2) {
				mode_manage->SetSelectMode(false);

				//�g��(�������O��)
				if (list_box[USE_ITEM]->GetCursor() == 0) {

					if (item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetItemKind() == STATUS_ITEM) {
						item_deal->UseItem(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
						item_stock_admin->LostItemStock(select_item_stock_num);

					}


					else if (item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetItemKind() == EQUIP_ITEM) {
						//�I�������A�C�e�����������̃A�C�e���������ꍇ
						if (item_stock_admin->GetItemStock(select_item_stock_num)->GetEquiped() == true) {
							equipment_admin->GetEquipment(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetEquipmentKind())->SetEquipmentData(NULL);
							item_stock_admin->GetItemStock(select_item_stock_num)->SetEquiped(false);
						}

						//�������łȂ��A�C�e����I�������ꍇ
						else {

							//�I�������C���x���g���̑����̎�ނ̑������܂��������Ă��Ȃ��ꍇ
							if (equipment_admin->GetEquipment(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetEquipmentKind())->GetEquipmentData() == NULL) {
								item_deal->Equip(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
								item_stock_admin->GetItemStock(select_item_stock_num)->SetEquiped(true);

							}

							//�w�ւ�I�������Ƃ��Ɏw�ւ����łɑ������Ă���ꍇ�Ȃ�
							else {
								for (int i = 0; i < ITEM_STOCK_MAX; i++) {
									//�C���x���g���̒��̑������̃A�C�e�����I�����Ă��鑕���A�C�e���Ɠ������ʂɑ�������A�C�e���ł���ꍇ
									if (item_stock_admin->GetItemStock(i)->GetEquiped() == true && item_stock_admin->GetItemStock(i)->GetItemData()->GetEquipmentKind() == item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetEquipmentKind())
										item_stock_admin->GetItemStock(i)->SetEquiped(false);
								}

								item_deal->Equip(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
								item_stock_admin->GetItemStock(select_item_stock_num)->SetEquiped(true);
							}
						}
					}

					for (int i = 0; i < LIST_BOX_MAX; i++) {
						draw_flag[i] = false;
						active_flag[i] = false;
						for (int j = 0; j < OLD_MAX; j++) {
							old_draw_flag[j][i] = false;
							old_active_flag[j][i] = false;
						}
					}
					active_flag[NOBOX] = true;
					list_box[ITEM]->ResetCursor();
					list_box[MENU]->ResetCursor();
					list_box[USE_ITEM]->ResetCursor();
				}

				//������
				else if (list_box[USE_ITEM]->GetCursor() == 1) {
					item_stock_admin->LostItemStock(select_item_stock_num);
					for (int i = 0; i < LIST_BOX_MAX; i++) {
						draw_flag[i] = false;
						active_flag[i] = false;
						for (int j = 0; j < OLD_MAX; j++) {
							old_draw_flag[j][i] = false;
							old_active_flag[j][i] = false;
						}
					}
					active_flag[NOBOX] = true;
					list_box[ITEM]->ResetCursor();
					list_box[MENU]->ResetCursor();
					list_box[USE_ITEM]->ResetCursor();
				}

				//�u��
				else if (list_box[USE_ITEM]->GetCursor() == 2) {
					if (item_stock_admin->GetItemStock(select_item_stock_num)->GetEquiped() == true) {
						equipment_admin->GetEquipment(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData()->GetEquipmentKind())->SetEquipmentData(NULL);
						item_stock_admin->GetItemStock(select_item_stock_num)->SetEquiped(false);
					}
					item_admin->PutItem(unit_admin->GetUnit(0)->GetMAPX(), unit_admin->GetUnit(0)->GetMAPY(), item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
					item_stock_admin->LostItemStock(select_item_stock_num);
					for (int i = 0; i < LIST_BOX_MAX; i++) {
						draw_flag[i] = false;
						active_flag[i] = false;
						for (int j = 0; j < OLD_MAX; j++) {
							old_draw_flag[j][i] = false;
							old_active_flag[j][i] = false;
						}
					}
					active_flag[NOBOX] = true;
					list_box[ITEM]->ResetCursor();
					list_box[MENU]->ResetCursor();
					list_box[USE_ITEM]->ResetCursor();
				}
			}
		}

		//�������O���{�b�N�X���o�Ă����ꍇ
		if (active_flag[PUT_OFF] == true) {
			mode_manage->SetSelectMode(false);

			//�O��
			if (list_box[PUT_OFF]->GetCursor() == 0) {
				equipment_admin->GetEquipment(EQUIPMENT_KIND(list_box[EQUIP]->GetCursor()))->SetEquipmentData(NULL);
				item_stock_admin->GetItemStock(select_item_stock_num)->SetEquiped(false);

				for (int i = 0; i < LIST_BOX_MAX; i++) {
					draw_flag[i] = false;
					active_flag[i] = false;
					for (int j = 0; j < OLD_MAX; j++) {
						old_draw_flag[j][i] = false;
						old_active_flag[j][i] = false;
					}
				}
				active_flag[NOBOX] = true;
				list_box[MENU]->ResetCursor();
				list_box[USE_ITEM]->ResetCursor();
			}


			//����
			else if (list_box[PUT_OFF]->GetCursor() == 1) {
				item_stock_admin->LostItemStock(select_item_stock_num);
				for (int i = 0; i < LIST_BOX_MAX; i++) {
					draw_flag[i] = false;
					active_flag[i] = false;
					for (int j = 0; j < OLD_MAX; j++) {
						old_draw_flag[j][i] = false;
						old_active_flag[j][i] = false;
					}
				}
				active_flag[NOBOX] = true;
				list_box[MENU]->ResetCursor();
				list_box[USE_ITEM]->ResetCursor();
			}
		}
	}



	//]���������ꍇ�A�ЂƂO�ɖ߂�(B�{�^���̂悤�Ȃ���)
	if (key[KEY_INPUT_RBRACKET] == 1 && count == COUNT_MARGIN) {
		count = 0;

		if (active_flag[MENU] == true) {
			mode_manage->SetSelectMode(false);
			list_box[MENU]->ResetCursor();
			active_flag[NOBOX] = true;
		}

		else if (active_flag[USE_ITEM] == true) {
			list_box[USE_ITEM]->ResetContent();
		}

		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			draw_flag[i] = old_draw_flag[0][i];
			active_flag[i] = old_active_flag[0][i];
			for (int j = 1; j < OLD_MAX; j++) {
				old_draw_flag[j - 1][i] = old_draw_flag[j][i];
				old_active_flag[j - 1][i] = old_active_flag[j][i];
			}
			old_draw_flag[15][i] = false;
			old_active_flag[15][i] = false;
		}
	}










	//�I�����Ŏ��̃{�b�N�X���X�e�[�^�X�{�b�N�X�������ꍇ�A��Ԃ�ۑ����X�e�[�^�X��ʂ��Ăяo��
	if (next_box_num == STATUS) {
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[STATUS] = true;
		active_flag[STATUS] = true;
		next_box_num = NOBOX;
		list_box[STATUS]->SetText();
	}


	//�I�����Ŏ��̃{�b�N�X���A�C�e���{�b�N�X�������ꍇ�A��Ԃ�ۑ����A�C�e����ʂ��Ăяo��
	else if (next_box_num == ITEM) {
		list_box[ITEM]->ResetCursor();
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[ITEM] = true;
		active_flag[ITEM] = true;
		next_box_num = NOBOX;
		list_box[ITEM]->SetText();
	}

	//�I�����Ŏ��̃{�b�N�X���A�C�e���{�b�N�X�������ꍇ�A��Ԃ�ۑ����A�C�e����ʂ��Ăяo��
	else if (next_box_num == USE_ITEM) {
		list_box[USE_ITEM]->ResetContent();
		list_box[USE_ITEM]->ResetCursor();
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[USE_ITEM] = true;
		active_flag[USE_ITEM] = true;
		next_box_num = NOBOX;
		select_item_stock_num = list_box[ITEM]->GetCursor();
		list_box[USE_ITEM]->SetItemData(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
		list_box[USE_ITEM]->SetText();
	}

	//�I�����Ŏ��̃{�b�N�X���A�C�e���{�b�N�X�������ꍇ�A��Ԃ�ۑ����A�C�e����ʂ��Ăяo��
	else if (next_box_num == EQUIP) {
		list_box[EQUIP]->ResetContent();
		list_box[EQUIP]->ResetCursor();
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[EQUIP] = true;
		active_flag[EQUIP] = true;
		next_box_num = NOBOX;
		list_box[EQUIP]->SetText();
	}


	else if (next_box_num == PUT_OFF) {

		list_box[PUT_OFF]->ResetCursor();
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[PUT_OFF] = true;
		active_flag[PUT_OFF] = true;
		next_box_num = NOBOX;
	}

	else if (next_box_num == EXPLAIN) {

		list_box[EXPLAIN]->ResetCursor();
		for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
			for (int j = OLD_MAX - 1; j > 0; j--) {
				old_draw_flag[j][i] = old_draw_flag[j - 1][i];
				old_active_flag[j][i] = old_active_flag[j - 1][i];
			}
			old_draw_flag[0][i] = draw_flag[i];
			old_active_flag[0][i] = active_flag[i];
			active_flag[i] = false;
		}
		draw_flag[EXPLAIN] = true;
		active_flag[EXPLAIN] = true;
		next_box_num = NOBOX;
		list_box[EXPLAIN]->SetItemData(item_stock_admin->GetItemStock(select_item_stock_num)->GetItemData());
		list_box[EXPLAIN]->SetText();
	}








	for (int i = 0; i < LIST_BOX_MAX - 1; i++) {
		if (active_flag[i] == true)
			list_box[i]->Update();
	}

}






SelectBoxAdmin::SelectBoxAdmin() {}

SelectBoxAdmin::~SelectBoxAdmin() {

	for (int i = 0; i < LIST_BOX_MAX; i++)
		delete list_box[i];
}
