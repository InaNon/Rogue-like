#include "artificialintelligence.h"

#include <cstdlib>

#include "Dxlib.h"

#include "unit.h"
#include "unitadmin.h"
#include "mapadmin.h"
#include "sectionadmin.h"
#include "celldata.h"
#include "room.h"

DIRECTION AdjacentCheck(Unit*, int, int);



COMMAND ArtificialIntelligence::EnemyAct(Unit* enemy) {

	COMMAND move = NOTHING;
	int enemy_map_x = enemy->GetMAPX();
	int enemy_map_y = enemy->GetMAPY();
	int player_map_x = unit_admin->GetUnit(0)->GetMAPX();
	int player_map_y = unit_admin->GetUnit(0)->GetMAPY();
	bool doublebookingflag = false;
	DIRECTION adjacent_direction = AdjacentCheck(enemy, player_map_x, player_map_y);



	if (enemy->GetExist() == true) {

		Room* enemy_room = map_admin->GetSectionAdmin()->GetRoom(enemy_map_x, enemy_map_y);
		Room* player_room = map_admin->GetSectionAdmin()->GetRoom(player_map_x, player_map_y);

		//プレイヤーと敵が隣り合っているとき
		if (adjacent_direction != NONE_DIRECTION) {

			if (enemy->CheckReservationCommand() != NOTHING)
				enemy->ResetReservationCommand();

			enemy->SetFirstLoadCommand(NOTHING);

			enemy->SetDirectionFlag(adjacent_direction);
			move = ATTACK;
		}

		//プレイヤーと敵が同じ部屋にいる場合
		else if (enemy_room != NULL && player_room != NULL && enemy_room == player_room) {

			if (enemy->CheckReservationCommand() != NOTHING)
				enemy->ResetReservationCommand();

			enemy->SetFirstLoadCommand(NOTHING);

			int x_cost = enemy_map_x - player_map_x;
			int y_cost = enemy_map_y - player_map_y;
			DIRECTION direction = NONE_DIRECTION;

			//進む方向を求めている
			if (x_cost == 0) {
				if (y_cost > 0)
					direction = DIR_UP;
				if (y_cost < 0)
					direction = DIR_DOWN;
			}

			if (y_cost == 0) {
				if (x_cost > 0)
					direction = DIR_LEFT;
				if (x_cost < 0)
					direction = DIR_RIGHT;
			}


			if (x_cost > 0 && y_cost > 0)
				direction = DIR_UP_LEFT;

			if (x_cost > 0 && y_cost < 0)
				direction = DIR_DOWN_LEFT;

			if (x_cost < 0 && y_cost > 0)
				direction = DIR_UP_RIGHT;

			if (x_cost < 0 && y_cost < 0)
				direction = DIR_DOWN_RIGHT;

			move = (COMMAND)direction;

			if (map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false) {
				int n = 1;
				int m = 1;

				do {
					move = (COMMAND)(move + m);

					if (move > UP_LEFT)
						move = (COMMAND)(move - UP_LEFT);
					else if (move < UP)
						move = (COMMAND)(move + UP_LEFT);

					n++;
					if (n % 2 == 0) {
						m = -n;
					}
					else {
						m = n;
					}

				} while (map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false && n < 8);

				if (map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false)
					move = STOP;

			}

		}

		//予約コマンドがない場合
		else if (enemy->CheckReservationCommand() == NOTHING) {

			if (enemy_room != NULL) {
				//道からエントランスまたは部屋の中(生成されたばかりか道を譲った場合)で予約コマンドがない場合(行き止まりの部屋の場合を除く)
				if (/*enemy_room->GetEntranceCell_Number(enemy_map_x, enemy_map_y) != -1 || */enemy->GetFirstLoadCommand() == NOTHING && !(enemy_room->GetEntranceCellSize() == 1 && enemy_room->GetEntranceCell_Number(enemy_map_x, enemy_map_y) != -1)) {
					static int next_entrance_point_x = -1;
					static int next_entrance_point_y = -1;
					static DIRECTION load_direction;
					bool slant_start;
					bool slant_goal;
					int x_cost;
					int y_cost;
					int slant_cost;
					DIRECTION direction = NONE_DIRECTION;
					COMMAND x_move = NOTHING;
					COMMAND y_move = NOTHING;
					COMMAND slant_move = NOTHING;

					if (next_entrance_point_x == -1 && next_entrance_point_y == -1)
						enemy_room->GetEntranceCell_Rand(enemy_map_x, enemy_map_y, next_entrance_point_x, next_entrance_point_y, load_direction);

					map_admin->GetSectionAdmin()->GetEntranceSlantMovef(enemy_map_x, enemy_map_y, next_entrance_point_x, next_entrance_point_y, slant_start, slant_goal);

					//斜め移動で部屋に侵入できない場合、何も考えずまっすぐに移動
					if (slant_start == false) {
						move = enemy->GetLastCommand();
						if (move == ATTACK) {
							DIRECTION adjacent_direction = AdjacentCheck(enemy, player_map_x, player_map_y);
							if (adjacent_direction == NONE_DIRECTION) {
								move = enemy->GetDirectionFlag();
							}
							else
								enemy->SetDirectionFlag(adjacent_direction);
						}

						//printfDx("%d", move);
						return move;
					}

					//斜め移動で通路に侵入できない場合は、ゴール地点を一つ分部屋に移動させて考える
					if (slant_goal == false) {
						next_entrance_point_x = next_entrance_point_x - enemy->direction_x((COMMAND)load_direction);
						next_entrance_point_y = next_entrance_point_y - enemy->direction_y((COMMAND)load_direction);
					}

					enemy->SetFirstLoadCommand((COMMAND)load_direction);

					//ここでx,y方向に何回進めばよいかがわかる
					x_cost = enemy_map_x - next_entrance_point_x;
					y_cost = enemy_map_y - next_entrance_point_y;

					//進む方向を求めている
					if (x_cost == 0) {
						if (y_cost > 0)
							direction = DIR_UP;
						if (y_cost < 0)
							direction = DIR_DOWN;
					}

					if (y_cost == 0) {
						if (x_cost > 0)
							direction = DIR_LEFT;
						if (x_cost < 0)
							direction = DIR_RIGHT;
					}


					if (x_cost > 0 && y_cost > 0)
						direction = DIR_UP_LEFT;

					if (x_cost > 0 && y_cost < 0)
						direction = DIR_DOWN_LEFT;

					if (x_cost < 0 && y_cost > 0)
						direction = DIR_UP_RIGHT;

					if (x_cost < 0 && y_cost < 0)
						direction = DIR_DOWN_RIGHT;

					//回数としてちゃんと正に戻している
					x_cost = abs(x_cost);
					y_cost = abs(y_cost);

					//斜めに進む回数(コスト)を求める
					if (x_cost <= y_cost) {
						slant_cost = x_cost;
						y_cost = y_cost - slant_cost;
						x_cost = 0;
					}

					else {
						slant_cost = y_cost;
						x_cost = x_cost - slant_cost;
						y_cost = 0;
					}


					if (direction == DIR_UP || direction == DIR_RIGHT || direction == DIR_DOWN || direction == DIR_LEFT) {
						if (x_cost != 0) {
							while (x_cost > 0) {
								enemy->SetReservationCommand((COMMAND)direction);
								x_cost--;
							}
						}

						if (y_cost != 0) {
							while (y_cost > 0) {
								enemy->SetReservationCommand((COMMAND)direction);
								y_cost--;
							}
						}
					}

					//ここまでx_moveはNOTHINGでここから先で定義され、場合分けされる

					else if (direction == DIR_UP_RIGHT) {
						x_move = RIGHT;
						y_move = UP;
						slant_move = UP_RIGHT;
					}

					else if (direction == DIR_DOWN_RIGHT) {
						x_move = RIGHT;
						y_move = DOWN;
						slant_move = DOWN_RIGHT;
					}

					else if (direction == DIR_DOWN_LEFT) {
						x_move = LEFT;
						y_move = DOWN;
						slant_move = DOWN_LEFT;
					}

					else if (direction == DIR_UP_LEFT) {
						x_move = LEFT;
						y_move = UP;
						slant_move = UP_LEFT;
					}

					//この場合に入るのは斜め移動が含まれる場合のみ
					if (x_move != NOTHING && y_move != NOTHING && slant_move != NOTHING) {
						//次のゴールへは、斜め移動で侵入できない(ゴールが部屋側に移動しているので、コストをすべて使い切る)かゴールに斜め侵入可能かつ直進移動が道の初めの一歩と一致している場合
						if (slant_goal == false || (slant_goal == true && ((x_cost != 0 && x_move == (COMMAND)direction) || (y_cost != 0 && y_move == (COMMAND)direction)))) {
							while (x_cost + y_cost > 0 || slant_cost > 0) {

								switch (GetRand(2)) {
								case 0:
									if (x_cost > 0) {
										enemy->SetReservationCommand(x_move);
										x_cost--;
									}
									break;
								case 1:
									if (y_cost > 0) {
										enemy->SetReservationCommand(y_move);
										y_cost--;
									}
									break;
								case 2:
									if (slant_cost > 0) {
										enemy->SetReservationCommand(slant_move);
										slant_cost--;
									}
									break;
								}
							}
							//斜め移動で侵入できるゴールでかつゴールへは直進移動で侵入が不可能、つまり必ず斜めで侵入する
						}
						else {
							while (x_cost + y_cost > 0 || slant_cost > 1) {

								switch (GetRand(2)) {
								case 0:
									if (x_cost > 0) {
										enemy->SetReservationCommand(x_move);
										x_cost--;
									}
									break;
								case 1:
									if (y_cost > 0) {
										enemy->SetReservationCommand(y_move);
										y_cost--;
									}
									break;
								case 2:
									if (slant_cost > 1) {
										enemy->SetReservationCommand(slant_move);
										slant_cost--;
									}
									break;
								}
							}
							enemy->SetReservationCommand(slant_move);
							slant_cost--;
						}


						/*
							//次のゴールへは、斜め移動で侵入できない→xかyの移動を1回は残していないといけない
							else {
								while (x_cost > 1 || y_cost > 1) {

									switch (GetRand(2)) {
									case 0:
										if (x_cost > 0) {
											enemy->SetReservationCommand(x_move);
											x_cost--;
										}
										break;
									case 1:
										if (y_cost > 0) {
											enemy->SetReservationCommand(y_move);
											y_cost--;
										}
										break;
									case 2:
										if (slant_cost > 0) {
											enemy->SetReservationCommand(slant_move);
											slant_cost--;
										}
										break;
									}
								}

								while (slant_cost > 0) {
									enemy->SetReservationCommand(slant_move);
									slant_cost--;
								}



								if (x_cost == 1) {
									enemy->SetReservationCommand(x_move);
									x_cost--;
								}

								else if (y_cost == 1) {
									enemy->SetReservationCommand(y_move);
									y_cost--;
								}
							}
							*/
					}

					if (slant_goal == false)
						enemy->SetReservationCommand((COMMAND)load_direction);


					move = enemy->GetReservationCommand();

					next_entrance_point_x = -1;
					next_entrance_point_y = -1;

				}

				//エントランスの上におり、道に入って初めての移動方向がさたまっている場合(部屋から通路の侵入した場合 ファーストコマンドによって判定)
				//if (enemy_room != NULL) {
				else if (enemy_room->GetEntranceCell_Number(enemy_map_x, enemy_map_y) != -1 && enemy->GetFirstLoadCommand() != NOTHING) {
					move = enemy->GetFirstLoadCommand();
					enemy->SetFirstLoadCommand(NOTHING);
				}


				//たどり着いた部屋が行き止まりだった場合、来た方向に戻る。
				//if (enemy_room != NULL) {
				else if (enemy_room->GetEntranceCellSize() == 1 && enemy_room->GetEntranceCell_Number(enemy_map_x, enemy_map_y) != -1) {
					move = (COMMAND)(((UP_LEFT / 2) + enemy->GetLastCommand()) % 8);
				}
			}
			//通路を踏んでいた場合
			else if (map_admin->GetMapCellData(enemy_map_x, enemy_map_y)->GetRoomf() == false) {
				do {
					move = (COMMAND)(GetRand(UP_LEFT - UP) + 1);
				} while ((enemy_map_x + enemy->direction_x(move) == enemy_map_x - enemy->direction_x(enemy->GetLastCommand())) && (enemy_map_y + enemy->direction_y(move) == enemy_map_y - enemy->direction_y(enemy->GetLastCommand())) || map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false);
			}
		}

		//予約コマンドがある場合
		else {
			move = enemy->GetReservationCommand();
		}
	}


	/*
		//すれ違いチェック
		if (move == (COMMAND)enemy->GetForcesMovementDirection()) {

			int n = 1;
			int m = 1;
			do {
				move = (COMMAND)(move + m);

				if (move > UP_LEFT)
					move = (COMMAND)(move - UP_LEFT);
				else if (move < UP)
					move = (COMMAND)(move + UP_LEFT);

				n++;
				if (n % 2 == 0) {
					m = -n;
				}
				else {
					m = n;
				}

			} while (map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false && n < 8);

			//袋小路
			if (n == 8 && map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false) {
				move = STOP;

				if (unit_admin->GetUnit(enemy->GetForcesMovementUnitNum())->CheckReservationCommand() != NOTHING)
					unit_admin->GetUnit(enemy->GetForcesMovementUnitNum())->ResetReservationCommand();

				unit_admin->GetUnit(enemy->GetForcesMovementUnitNum())->SetFirstLoadCommand(NOTHING);
			}
		}

		//重なりチェック
		if (move != STOP) {
			for (int i = 1; i < enemy->GetUnitNum(); i++) {
				if (enemy_map_x + enemy->direction_x(move) == unit_admin->GetUnit(i)->GetReservationMapX() && enemy_map_y + enemy->direction_y(move) == unit_admin->GetUnit(i)->GetReservationMapY()) {
					doublebookingflag = true;

					if (enemy->CheckReservationCommand() != NOTHING)
						enemy->ResetReservationCommand();

					enemy->SetFirstLoadCommand(NOTHING);

					break;
				}
			}

			if (doublebookingflag == true) {
				int n = 1;
				int m = 1;
				do {
					doublebookingflag = false;
					move = (COMMAND)(move + m);

					if (move > UP_LEFT)
						move = (COMMAND)(move - UP_LEFT);
					else if (move < UP)
						move = (COMMAND)(move + UP_LEFT);

					for (int i = 1; i < enemy->GetUnitNum(); i++) {
						if ((enemy_map_x + enemy->direction_x(move) == unit_admin->GetUnit(i)->GetReservationMapX() && enemy_map_y + enemy->direction_y(move) == unit_admin->GetUnit(i)->GetReservationMapY()) || map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false)
							doublebookingflag = true;//処理追加、すれ違い、なかった場合は二つともストップ
					}

					n++;
					if (n % 2 == 0) {
						m = -n;
					}
					else {
						m = n;
					}

				} while (doublebookingflag == true && n < 8);

				if (doublebookingflag == true)
					move = STOP;

			}
		}
		*/


	for (int i = 1; i < enemy->GetUnitNum(); i++) {
		if (enemy_map_x + enemy->direction_x(move) == unit_admin->GetUnit(i)->GetReservationMapX() && enemy_map_y + enemy->direction_y(move) == unit_admin->GetUnit(i)->GetReservationMapY()) {
			doublebookingflag = true;
			break;
		}
	}



	if (doublebookingflag == true || move == (COMMAND)enemy->GetBannedDirection()) {
		int n = 1;
		int m = 1;
		bool allowed_move_flag = false;

		if (enemy->CheckReservationCommand() != NOTHING)
			enemy->ResetReservationCommand();

		enemy->SetFirstLoadCommand(NOTHING);

		while (allowed_move_flag == false && n < 8) {
			allowed_move_flag = true;

			move = (COMMAND)(move + m);

			if (move > UP_LEFT)
				move = (COMMAND)(move - UP_LEFT);
			else if (move < UP)
				move = (COMMAND)(move + UP_LEFT);

			//重なりチェック
			for (int i = 1; i < enemy->GetUnitNum(); i++) {
				if ((enemy_map_x + enemy->direction_x(move) == unit_admin->GetUnit(i)->GetReservationMapX() && enemy_map_y + enemy->direction_y(move) == unit_admin->GetUnit(i)->GetReservationMapY()) || map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, move) == false || move == (COMMAND)enemy->GetBannedDirection()) {
					allowed_move_flag = false;
					break;
				}
			}

			n++;
			if (n % 2 == 0) {
				m = -n;
			}
			else {
				m = n;
			}

		}


		if (n == 8 && allowed_move_flag == false) {
			move = STOP;
			if (enemy->GetBannedDirection() != NONE_DIRECTION) {
				if (unit_admin->GetUnit(enemy->GetBanUnitNum())->CheckReservationCommand() != NOTHING)
					unit_admin->GetUnit(enemy->GetBanUnitNum())->ResetReservationCommand();

				unit_admin->GetUnit(enemy->GetBanUnitNum())->SetFirstLoadCommand(NOTHING);
				unit_admin->GetUnit(enemy->GetBanUnitNum())->SetForceCommand(STOP);
			}
		}

		enemy->SetBannedDirection(NONE_DIRECTION);
		enemy->SetBannedUnitNum(0);
	}


	for (int i = enemy->GetUnitNum() + 1; i < UNIT_MAX; i++) {
		if ((enemy_map_x + enemy->direction_x(move) == unit_admin->GetUnit(i)->GetMAPX() && enemy_map_y + enemy->direction_y(move) == unit_admin->GetUnit(i)->GetMAPY())) {
			DIRECTION ban_direction = (DIRECTION)((move + 4) % 8);

			if (ban_direction == NONE_DIRECTION)
				ban_direction = DIR_UP_LEFT;

			unit_admin->GetUnit(i)->SetBannedDirection(ban_direction);
			unit_admin->GetUnit(i)->SetBannedUnitNum(enemy->GetUnitNum());
			break;
		}
	}

	return move;

}



	/*COMMAND move = NOTHING;

		if (enemy->GetExist() == true) {
			int enemy_map_x = enemy->GetMAPX();
			int enemy_map_y = enemy->GetMAPY();

			while (1)
			{

				move = (COMMAND)(GetRand(ATTACK - UP) + (int)UP);
				if ((move == UP) && (unit_admin->GetMovef(enemy_map_x, enemy_map_y - 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x, enemy_map_y - 1) == false)
					break;
				if ((move == UP_RIGHT) && (unit_admin->GetMovef(enemy_map_x + 1, enemy_map_y - 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x + 1, enemy_map_y - 1) == false)
					break;
				if ((move == RIGHT) && (unit_admin->GetMovef(enemy_map_x + 1, enemy_map_y) == true) && unit_admin->UnitReservationMapExist(enemy_map_x + 1, enemy_map_y) == false)
					break;
				if ((move == DOWN_RIGHT) && (unit_admin->GetMovef(enemy_map_x + 1, enemy_map_y + 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x + 1, enemy_map_y + 1) == false)
					break;
				if ((move == DOWN) && (unit_admin->GetMovef(enemy_map_x, enemy_map_y + 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x, enemy_map_y + 1) == false)
					break;
				if ((move == DOWN_LEFT) && (unit_admin->GetMovef(enemy_map_x - 1, enemy_map_y + 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x - 1, enemy_map_y + 1) == false)
					break;
				if ((move == LEFT) && (unit_admin->GetMovef(enemy_map_x - 1, enemy_map_y) == true) && unit_admin->UnitReservationMapExist(enemy_map_x - 1, enemy_map_y) == false)
					break;
				if ((move == UP_LEFT) && (unit_admin->GetMovef(enemy_map_x - 1, enemy_map_y - 1) == true) && unit_admin->UnitReservationMapExist(enemy_map_x - 1, enemy_map_y - 1) == false)
					break;
				if (move == STOP)
					break;
				if (move == ATTACK)
					break;
			}
			/*
			if (check_unit_num == 1)
			move = RIGHT;

			if (check_unit_num == 2)
			move = ATTACK;
			*/

/*
COMMAND ArtificialIntelligence::ReSearchMove(COMMAND old_move, Unit* enemy) {

	bool re_search_flag;
	int n = 1;
	int m = 1;
	int enemy_map_x = enemy->GetMAPX();
	int enemy_map_y = enemy->GetMAPY();

	COMMAND newer_move = old_move;

	do {
		re_search_flag = false;
		newer_move = (COMMAND)(newer_move + m);

		if (newer_move > UP_LEFT)
			newer_move = (COMMAND)(newer_move - UP_LEFT);
		else if (newer_move < UP)
			newer_move = (COMMAND)(newer_move + UP_LEFT);

		for (int i = 1; i < enemy->GetUnitNum(); i++) {
			if ((enemy_map_x + enemy->direction_x(newer_move) == unit_admin->GetUnit(i)->GetReservationMapX() && enemy_map_y + enemy->direction_y(newer_move) == unit_admin->GetUnit(i)->GetReservationMapY()) || map_admin->GetMovef_Conv(enemy_map_x, enemy_map_y, newer_move) == false)
				re_search_flag = true;
		}

		n++;
		if (n % 2 == 0) {
			m = -n;
		}
		else {
			m = n;
		}

	} while (re_search_flag == true && n < 8);

	if (re_search_flag == true)
		newer_move = STOP;

	return newer_move;
}
*/


DIRECTION AdjacentCheck(Unit* enemy, int player_map_x, int player_map_y) {

	if (enemy->GetMAPX() + enemy->direction_x(UP) == player_map_x && enemy->GetMAPY() + enemy->direction_y(UP) == player_map_y)
		return DIR_UP;

	if (enemy->GetMAPX() + enemy->direction_x(UP_RIGHT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(UP_RIGHT) == player_map_y)
		return DIR_UP_RIGHT;

	if (enemy->GetMAPX() + enemy->direction_x(RIGHT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(RIGHT) == player_map_y)
		return DIR_RIGHT;

	if (enemy->GetMAPX() + enemy->direction_x(DOWN_RIGHT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(DOWN_RIGHT) == player_map_y)
		return DIR_DOWN_RIGHT;

	if (enemy->GetMAPX() + enemy->direction_x(DOWN) == player_map_x && enemy->GetMAPY() + enemy->direction_y(DOWN) == player_map_y)
		return DIR_DOWN;

	if (enemy->GetMAPX() + enemy->direction_x(DOWN_LEFT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(DOWN_LEFT) == player_map_y)
		return DIR_DOWN_LEFT;

	if (enemy->GetMAPX() + enemy->direction_x(LEFT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(LEFT) == player_map_y)
		return DIR_LEFT;

	if (enemy->GetMAPX() + enemy->direction_x(UP_LEFT) == player_map_x && enemy->GetMAPY() + enemy->direction_y(UP_LEFT) == player_map_y)
		return DIR_UP_LEFT;

	return NONE_DIRECTION;

}









ArtificialIntelligence::ArtificialIntelligence(UnitAdmin *m_unit_admin, MapAdmin* m_map_admin){

	unit_admin = m_unit_admin;
	map_admin = m_map_admin;

}
ArtificialIntelligence::~ArtificialIntelligence(){}