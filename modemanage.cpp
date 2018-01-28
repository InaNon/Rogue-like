#include "modemanage.h"

void ModeManage::Init() {

	unit_mode = true;
	player_command_mode = true;
	message_mode = false;
	select_mode = false;
	advance_dungeon_mode = false;
}
bool ModeManage::GetUnitMode() {return unit_mode;}
void ModeManage::SetUnitMode(bool m_unit_mode) {unit_mode = m_unit_mode;}
bool ModeManage::GetPlayerCommandMode() { return player_command_mode; }
void ModeManage::SetPlayerCommandMode(bool m_player_command_mode) {player_command_mode = m_player_command_mode;}
bool ModeManage::GetMessageMode() {return message_mode;}
void ModeManage::SetMessageMode(bool m_message_mode) { message_mode = m_message_mode; }
bool ModeManage::GetSelectMode() { return select_mode; }
void ModeManage::SetSelectMode(bool m_select_mode) { select_mode = m_select_mode; }
bool ModeManage::GetAdvanceDungeonMode() { return advance_dungeon_mode; }
void ModeManage::SetAdvanceDungeonMode(bool _advance_dungeon_mode) { advance_dungeon_mode = _advance_dungeon_mode; }

ModeManage::ModeManage(){}
ModeManage::~ModeManage(){}