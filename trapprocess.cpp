#include "trapprocess.h"
#include "trapdata.h"
#include "unitadmin.h"
#include "unit.h"
#include "messageadmin.h"
#include "unitdata.h"
#include "itemadmin.h"
#include "item.h"

//minimap iti tyousei

TrapProcess::TrapProcess() {
}

TrapProcess::~TrapProcess() {
}

void TrapProcess::Init(UnitAdmin* _unitAdmin, MessageAdmin* _messageAdmin, ItemAdmin* _itemAdmin) {
	unitAdmin = _unitAdmin;
	messageAdmin = _messageAdmin;
	itemAdmin = _itemAdmin;

}


void TrapProcess::Process(TrapData::TRAPTYPE trapType) {
	if (trapType == TrapData::TRAPTYPE::NEEDLE) {
		Needle();
	}
	if (trapType == TrapData::TRAPTYPE::BOMB) {
		Bomb();
	}
	if (trapType == TrapData::TRAPTYPE::WARP) {
		Warp();
	}
	if (trapType == TrapData::TRAPTYPE::HUNGER) {
		Hunger();
	}
	if (trapType == TrapData::TRAPTYPE::WEAPON_WARP) {
		WeaponWarp();
	}

}

void TrapProcess::Needle() {
	Unit* unit = unitAdmin->GetUnit(0);

	trapMessage(unit->GetUnitData()->GetName(), "�g�Q�g�Q��");

	//�v���C���[�̓_���[�W���󂯂�
	int damage = (int)(unit->GetMaxHP() * 0.10 + 1);
	int resultHP = unit->GetCurrentHP() - damage;
	unit->SetCurrentHP(resultHP);

	messageAdmin->AnyMessage(unit->GetUnitData()->GetName() + "��" + to_string(damage) + "�_���[�W���󂯂�", false);

	if (resultHP <= 0) {
		unit->SetExist(false);
		unit->Initialization();
	}

}

void TrapProcess::Hunger() {
	Unit* unit = unitAdmin->GetUnit(0);

	trapMessage(unit->GetUnitData()->GetName(), "����������X�C�b�`");

	//�v���C���[�͂���������
	int damage = 50;
	int currentStomach = unit->GetCurrentStomach() - damage;
	if (currentStomach < 0) {
		currentStomach = 0;
	}
	unit->SetCurrentStomach(currentStomach);

	messageAdmin->AnyMessage(unit->GetUnitData()->GetName() + "�̂������肾����", false);

}

void TrapProcess::Warp() {
	Unit* unit = unitAdmin->GetUnit(0);
	trapMessage(unit->GetUnitData()->GetName(), "���[�v�X�C�b�`");

	//�v���C���[�̈ړ��ʒu������
	//TODO

	messageAdmin->AnyMessage(unit->GetUnitData()->GetName() + "�̓��[�v���Ă��܂���", false);
}


void TrapProcess::Bomb() {
	trapMessage(unitAdmin->GetUnit(0)->GetUnitData()->GetName(), "�����X�C�b�`");

	int buf_param[9][2] = {
		{ -1,-1 },
		{ 0,-1 },
		{ 1,-1 },
		{ -1,0 },
		{ 0,0 },
		{ 1,0 },
		{ -1,1 },
		{ 0,1 },
		{ 1,1 },
	};


	Unit* unit;
	Item* item;

	for (int i = 0; i < 9; i++) {
		buf_param[i][1] += unitAdmin->GetUnit(0)->GetX();
		buf_param[i][2] += unitAdmin->GetUnit(0)->GetY();

		if ((unit = unitAdmin->UnitExistMap(buf_param[i][1], buf_param[i][2])) != NULL) {
			//UNIT�̓_���[�W���󂯂�
			int damage = (int)(unit->GetMaxHP() * 0.10 + 1);
			int resultHP = unit->GetCurrentHP() - damage;
			unit->SetCurrentHP(resultHP);
			messageAdmin->AnyMessage(unit->GetUnitData()->GetName() + "��" + to_string(damage) + "�_���[�W���󂯂�", false);
			if (resultHP <= 0) {
				unit->SetExist(false);
				unit->Initialization();
			}
		}

		if ((item = itemAdmin->ItemExistMap(buf_param[i][1], buf_param[i][2])) != NULL) {
			itemAdmin->ItemExistMap(buf_param[i][1], buf_param[i][2])->SetExist(false);
			itemAdmin->SubtractItemNum();
		}

	}

}

void TrapProcess::WeaponWarp() {
	//by ina
}

void TrapProcess::trapMessage(std::string unitName, std::string trapName) {
	std::string text = "" + unitName + "��" + trapName + "�𓥂�ł��܂����I";
	messageAdmin->AnyMessage(text, true);
	return;
}