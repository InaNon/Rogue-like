#include "sectionadmin.h"
#include "map.h"
#include <cstdlib>
#include "section.h"
#include "room.h"
#include "celldataadmin.h"
#include "trapdataadmin.h"
#include "mapadmin.h"
#include "road.h"
#include <algorithm>
#include "floordata.h"
#include "dungeondata.h"
#include "math.h"

static const int DEBUG_SA = false;

std::vector<int> RandomSwap(int m_min, int m_max) {
	std::vector<int> buf(m_max - m_min + 1, NULL);
	int rand, t;

	for (int i = 0; i < (signed int)buf.size(); i++) {
		buf[i] = i + m_min;
	}

	for (int i = 0; i < (signed int)buf.size() - 1; i++) {
		rand = GetRand(buf.size() - 1 - i - 1) + i;

		t = buf[rand];
		buf[rand] = buf[i];
		buf[i] = t;
	}

	/*
	printfDx("RandomSwap");
	for (int i = 0; i < (signed int)buf.size(); i++) {
		printfDx("%d", buf[i]);
	}
	WaitKey();
	*/


	return buf;
}

/*メモ*/
/*
ダンジョン生成において設定できるパラメータ

//Section割のアルゴリズムの選択<DUNGEON_MAKE_MODE>
DEPTH_FIRST_RAND　深さ優先形式。初めに大きな部屋が作られやすい。数値
DEPTH_FIRST_LARGER　深さ優先形式で、分割時もより大きい部屋が作られやすい
WIDTH_FIRST　幅優先形式で、

*/


SectionAdmin::SectionAdmin(MapAdmin* m_map_admin, CellDataAdmin* m_celldata_admin, TrapDataAdmin* m_trapdata_admin) {
	map_admin = m_map_admin;
	map = map_admin->GetMap();
	celldata_admin = m_celldata_admin;
	trapdata_admin = m_trapdata_admin;
}

SectionAdmin::~SectionAdmin() {
	//delete grand_section;
	for (int i = 0; i < (signed int)roads.size(); i++) {
		delete roads[i];
	}
	for (int i = 0; i < (signed int)sections.size(); i++) {
		delete sections[i];
	}
}

void SectionAdmin::Clear() {
	//delete grand_section;
	//grand_section = new Section();

	for (int i = 0; i < (signed int)roads.size(); i++) {
		delete roads[i];
	}
	for (int i = 0; i < (signed int)sections.size(); i++) {
		delete sections[i];
	}
}

void SectionAdmin::DungeonMake() {


	for (int i = 0; i < map->GetSizeX(); i++) {
		for (int j = 0; j < map->GetSizeY(); j++) {
			map->GetCell(i, j)->SetTemporaryCell(false);
		}
	}
	int all_map_x = map->GetSizeX();
	int all_map_y = map->GetSizeY();

	int map_x = floordata->GetFloorsizeX();
	int map_y = floordata->GetFloorsizeY();




	DUNGEON_MAKE_MODE make_mode = floordata->GetMakemode();

	MakeSection(0, (all_map_x - map_x) / 2, (all_map_y - map_y) / 2, map_x, map_y, NULL);
	MakeAllSection(make_mode);

	//最も最初のSectionの作成と、それに連なる全てのSectionの作成
	//grand_section->MakeSection(make_mode,5 , (all_map_x - map_x) / 2, (all_map_y - map_y) / 2, map_x, map_y, grand_section);


	//部屋を生成する
	//grand_section->MakeRoom();

	
	//全てsectionを、sectionsに格納する
	//grand_section->GetSection(&sections);
	int section_amount = (signed int) sections.size();


	//部屋のあるsectionについてexistを立てる
	std::vector<bool> exist_f(section_amount,false);
	for (int i = 0; i < section_amount; i++) {
		exist_f[i] = sections[i]->GetRoomf();
	}

	//roomのある場所をすべてTemp = trueにする処理
	SetRoomTempAll();

	//Temp = true に、「部屋の床」代入
	SetTempToCellDataAll(ROOM_FLOOR, true, false);//Temp = true の場所をすべて、CellData*にする。trueでCellDataを上書き

	/*
	for (int i = 0; i < (signed int)size(sections)-1; i++) {
		MakeRoadSectionToSection(sections[i], sections[i + 1]);
	}

	for (int i = 0; i < (signed int)size(sections); i++) {
		for (int j = 0; j < (signed int)size(sections); j++) {
			if (i - j >= 2) {
				MakeRoadSectionToSection(sections[i], sections[j]);
			}
		}
	}
	*/

	/*
	//深さ優先において、子と親を繋ぐ
	for (int i = 0; i < (signed int)size(sections) - 1; i++) {
		MakeRoadSectionToSection(sections[i], sections[i + 1]);
	}
	*/

	/*
	//全ての接続できる部屋同士をすべて繋ぐ
	for (int i = 0; i < section_amount; i++) {
		for (int j = 0; j < section_amount; j++) {
			if (i - j > 0) {
				if (sections[i]->GetRoomf() && sections[j]->GetRoomf()) {
					MakeRoadSectionToSection(sections[i], sections[j]);
				}
			}
		}
	}

	*/
	

	//全てのつなげられ得るセクション組を格納する。

	//std::vector<std::vector<bool>> section_connect_f(section_amount, std::vector<bool>(section_amount, false));
	//std::vector<Section*[2]> section_combination;
	//Section* buf_section_combination[2];

	std::vector<std::vector<int>> section_combination;
	std::vector<int> buf_section_combination(2, -1);
	for (int i = 0; i < section_amount; i++) {
		for (int j = 0; j < section_amount; j++) {
			if (i - j > 0) {
				if (sections[i]->GetRoomf() && sections[j]->GetRoomf()) {
					if (sections[i]->GetSectionDirecion(sections[j]) != NONE_DIRECTION) {
						buf_section_combination[0] = i;
						buf_section_combination[1] = j;
						//buf_section_combination[0] = sections[i];
						//buf_section_combination[1] = sections[j];
						section_combination.push_back(buf_section_combination);
					}
				}
			}
		}
	}

	double max_roads = (signed int)section_combination.size();

	//セクション組(道候補)を何本か消す処理
	std::vector<std::vector<int>> deleted_section_combination;
	deleted_section_combination = DeleteSectionCombination(section_combination, (int)(max_roads*(1.0 - floordata->GetMakeroadRate())), exist_f);
	//deleted_section_combination = section_combination;

	if (DEBUG_SA) {
		printfDx("DeleteSectionCombination end\n");
		WaitKey();
	}

	//道を生成する処理
	for (int i = 0; i < (signed int)size(deleted_section_combination); i++) {
		//printfDx("%d,%d\n", section_combination[i][0], section_combination[i][1]);
		MakeRoadSectionToSection(sections[deleted_section_combination[i][0]], sections[deleted_section_combination[i][1]]);
	}
	//WaitKey();

	/*
	std::vector<Room*> buf_cr;
	printfDx("---------\n");
	for (int i = 0; i < section_amount; i++) {
		printfDx("%d:", i);
		if (sections[i]->GetRoomf()) {
			buf_cr = sections[i]->GetRoom()->GetConnectionRoom();
			for (int j = 0; j < (signed int)sections[i]->GetRoom()->GetConnectionRoom().size(); j++) {
				printfDx("%d", buf_cr[j]->GetPSection()->GetNumber());
			}
		}
		else {
			printfDx("NULL");
		}
		printfDx("\n");
	}
	printfDx("---------\n");
	*/

	if (DEBUG_SA) {
		printfDx("MakeRoadSectionToSection end\n");
		WaitKey();
	}

	//部屋と部屋の接続の失敗などが原因で、部屋と部屋が繋がって居ない部屋群がある場合は、別途、ランダムに隣接するランダムなセクションと
	//接続を行う。
	//これを繰り返す。

	/*
	for (int i = 0; i < section_amount; i++) {
		if (sections[i]->GetRoomf()) {
			if (!sections[i]->GetRoom()->GetConnectionf()) {
				//接続を行う
				for (int j = 0; j < section_amount;j++) {
					if (i != j) {
						if (MakeRoadSectionToSection(sections[i], sections[j])) {
							//printfDx("t");
							break;
						}
					}
				}
			}
		}
	}
	//これだと解決しない。部屋群が孤立している場合対処できないので、最初に道を消す処理で使った検索方法を用いて判定が必要
	*/

	//繋がっていない部屋群を接続して、独立した部屋群をなくす処理
	std::vector<int> buf_group;
	std::vector<int> rs = RandomSwap(0, (signed int)section_combination.size() - 1);
	int group_num_max = 0, i = 0, sectosecf;
	bool b_f = false;

	
	/*
	for (int i = 0; i < (signed int)section_combination.size(); i++) {
		printfDx("[%d,%d]", section_combination[i][0], section_combination[i][1]);
	}
	printfDx("\nrs=%d\n",(signed int)rs.size());
	for (int i = 0; i < (signed int)rs.size(); i++) {
		printfDx("%d ",rs[i]);
	}
	printfDx("\n\n");
	*/

	while (1) {
		b_f = true;
		//printfDx("%d %d %d\n", i,group_num_max, rs.size());
		//WaitKey();

		//"実際に"接続されているセクション組を格納する
		std::vector<std::vector<int>> room_combination;
		std::vector<int> buf_room_combination(2, -1);
		std::vector<Room*> buf_connection_room;
		for (int k = 0; k < section_amount; k++) {
			if (sections[k]->GetRoomf()) {
				buf_connection_room = sections[k]->GetRoom()->GetConnectionRoom();
				for (int j = 0; j < (signed int)buf_connection_room.size(); j++) {
					if (buf_connection_room[j] != sections[k]->GetRoom()) {
						buf_room_combination[0] = k;
						buf_room_combination[1] = buf_connection_room[j]->GetPSection()->GetNumber();
						room_combination.push_back(buf_room_combination);
					}
				}
			}
		}

		//実際に接続されているセクション組のグループ番号をbuf_groupに格納する
		buf_group = GetConnectGroup(room_combination, (signed int)sections.size(), exist_f);
		
		int new_group_num_max = 0;
		for (int j = 0; j < (signed int)buf_group.size(); j++) {
			if (new_group_num_max < buf_group[j]) {
				new_group_num_max = buf_group[j];
			}
		}

		if (group_num_max != new_group_num_max) {
			i = 0;
		}
		group_num_max = new_group_num_max;


		//もしグループが二つ以上存在する場合は、各グループ間で接続を行う。
		if (group_num_max > 1) {
			while (i < (signed int)rs.size()) {
				//printfDx("'%d'",i);
				/*
				if (buf_group[section_combination[rs[i]][0]] == group_num_max && buf_group[section_combination[rs[i]][1]] != 0 && buf_group[section_combination[rs[i]][1]] != group_num_max) {
					if (MakeRoadSectionToSection(sections[section_combination[rs[i]][0]], sections[section_combination[rs[i]][1]])) {
						i++;
						break;
					}
				}
				if (buf_group[section_combination[rs[i]][1]] == group_num_max && buf_group[section_combination[rs[i]][0]] != 0 && buf_group[section_combination[rs[i]][0]] != group_num_max) {
					if (MakeRoadSectionToSection(sections[section_combination[rs[i]][1]], sections[section_combination[rs[i]][0]])) {
						i++;
						break;
					}
				}*/
				//printfDx("g<%d %d> ",buf_group[section_combination[rs[i]][0]], buf_group[section_combination[rs[i]][1]]);

				if (buf_group[section_combination[rs[i]][0]] != buf_group[section_combination[rs[i]][1]]) {
					sectosecf = MakeRoadSectionToSection(sections[section_combination[rs[i]][0]], sections[section_combination[rs[i]][1]]);
					if (sectosecf > 0) {
						i++;
						b_f = false;
						break;
					}
				}
			
				i++;
				if (i == (signed int)rs.size()) {
					printfDx("Cannot solve separated room problem\n");
					printfDx("%d %d\n",group_num_max, rs.size());
					//WaitKey();
					break;
				}
			}

		}
		else {
			break;
		}

		if (i >= (signed int)rs.size() && b_f) {
			break;
		}
	}

	//printfDx("%d", group_num_max);

	//Temp = true に、「通路の床」代入
	SetTempToCellDataAll(ROAD_FLOOR, true, false);

	//部屋と通路の境界に「部屋の床」代入
	for (int i = 0; i < section_amount; i++) {
		if (sections[i]->GetRoomf()) {
			for (int j = 0; j < (signed int) sections[i]->GetRoom()->GetEntranceCellSize(); j++) {
				map->GetCell(
					sections[i]->GetRoom()->GetEntranceCell_All()[j][0],
					sections[i]->GetRoom()->GetEntranceCell_All()[j][1]
					)->SetCellData(celldata_admin->GetCellData(ROOM_FLOOR));
			}
		}
	}

	//Temp = false に、「斜め移動できない壁」代入　これはダンジョン設定に依って、斜め移動できるかできないかを決定する必要がある
	if (floordata->GetWallSlant_f()) {
		SetTempToCellDataAll(SLANT_WALL, false, false);
	} else {
		SetTempToCellDataAll(BOX_WALL, false, false);
	}
	


	Room* shop_room = MakeShop(floordata->GetShopRate());


	//削っても問題ない場所をマーキングする。
	std::vector<std::vector<SHAVE_F>> buf_shavef;
	for (int k = 0; k < section_amount; k++) {
		if (sections[k]->GetRoomf() && shop_room != sections[k]->GetRoom()) {

			buf_shavef = RoomShaveMarking(sections[k]->GetRoom());
			
			ShaveEdge(sections[k]->GetRoom(), floordata->GetShaveRate(), buf_shavef, SHAVE_ALL_TRUE);

			/*
			for (int i = 0; i < sections[k]->GetRoom()->GetSizeX(); i++) {
				for (int j = 0; j < sections[k]->GetRoom()->GetSizeY(); j++) {
					if (buf_shavef[i][j] == SHAVE_SLANT_TRUE) {
						//map->GetCell(sections[k]->GetRoom()->GetX() + i, sections[k]->GetRoom()->GetY() + j)->SetCellData(celldata_admin->GetCellData(SLANT_WALL));
					}
					if (buf_shavef[i][j] == SHAVE_ALL_TRUE) {
						//map->GetCell(sections[k]->GetRoom()->GetX() + i, sections[k]->GetRoom()->GetY() + j)->SetCellData(celldata_admin->GetCellData(BOX_WALL));

					}
				}
			}
			*/
		}
	}

	//実際に削る処理

	//部屋の角を削る処理　封印中
	/*
	for (int i = 0; i < section_amount; i++) {
	if (sections[i]->GetRoomf()) {
	ShaveEdge(sections[i]->GetRoom(), 3.0);
	}
	}
	*/

	for (int i = 0; i < section_amount; i++) {
		if (sections[i]->GetRoomf()) {
			//MakeHole(sections[i]->GetRoom());
		}
	}

	//特殊タイルの設置
	MakeTrap(30); //罠レートを作ってねえ






	MakeStep(); //階段消滅の恐れがあるため、最後に設置

	
	//残りのマスを設定していない場所すべて(主にダンジョン外に)壁を設置
	SetTempToCellDataAll(BOX_WALL, false, false);


	return;
}

void SectionAdmin::MakeHole(Room* m_Room) {
	
	int mx1 = m_Room->GetX() + GetRand(m_Room->GetSizeX() - 2) + 1;
	int my1 = m_Room->GetY() + GetRand(m_Room->GetSizeY() - 2) + 1;
	int mx2 = mx1 + 1 + GetRand(m_Room->GetSizeX() - (mx1 - m_Room->GetX()) - 2);
	int my2 = my1 + 1 + GetRand(m_Room->GetSizeY() - (my1 - m_Room->GetY()) - 2);
	//printfDx("%d %d %d %d  %d %d\n",mx1,my1,mx2,my2,map->GetSizeX(),map->GetSizeY());
	for (int i = 0; i < mx2 - mx1; i++) {
		for (int j = 0; j < my2 - my1; j++) {
			//printfDx("%d %d\n", mx1+i, my1+i);
			//WaitKey();
			map->GetCell(mx1 + i, my1 + j)->SetCellData(celldata_admin->GetCellData(SLANT_WALL));
		}
	}
	
}


void SectionAdmin::ShaveEdge(Room* m_Room, double m_shave_rate, std::vector<std::vector<SHAVE_F>> m_shavefvec,SHAVE_F m_shavef) {

	int mx = m_Room->GetX();
	int my = m_Room->GetY();
	int sizex = m_Room->GetSizeX();
	int sizey = m_Room->GetSizeY();

	std::vector<std::vector<bool>> shave_bool(sizex, std::vector<bool>(sizey, false));


	int shave_count = 0;
	int shave_count2 = 0;
	int shave_amount = int(double(sizex*sizey)*m_shave_rate);
	int rnd;
	int cnt;
	int bufx, bufy;

	bool breakf = false;

	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			if (m_shavefvec[i][j] == m_shavef && map->GetCell(mx,my)->GetMovef() == true) {
				/*
				if (i == 0 || j == 0 || i == sizex - 1 || j == sizey - 1) { shave_bool[i][j] = true; }
				if (i > 0) { if ( map->GetCell(mx + i - 1, my + j)->GetMovef() == false) { shave_bool[i][j] = true; } }
				if (j > 0) { if ( map->GetCell(mx + i, my + j - 1)->GetMovef() == false) { shave_bool[i][j] = true; } }
				if (i < sizex - 1) { if ( map->GetCell(mx + i + 1, my + j)->GetMovef() == false) { shave_bool[i][j] = true; } }
				if (j < sizey - 1) { if ( map->GetCell(mx + i, my + j + 1)->GetMovef() == false) { shave_bool[i][j] = true; } }
				*/
				cnt = 0;
				if (i == 0) { cnt++; }
				if (j == 0) { cnt++; }
				if (i == sizex - 1) { cnt++; }
				if (j == sizey - 1) { cnt++; }
				if (i > 0) { if (map->GetCell(mx + i - 1, my + j)->GetMovef() == false) { cnt++; } }
				if (j > 0) { if (map->GetCell(mx + i, my + j - 1)->GetMovef() == false) { cnt++; } }
				if (i < sizex - 1) { if (map->GetCell(mx + i + 1, my + j)->GetMovef() == false) { cnt++; } }
				if (j < sizey - 1) { if (map->GetCell(mx + i, my + j + 1)->GetMovef() == false) { cnt++; } }
				
				if (cnt > 1) { shave_bool[i][j] = true; }
				/*
				角削り方式に変更する
				*/

			}
			if (shave_bool[i][j]) {
				shave_count++;
			}
		}
	}


	for (int k = 0; k < shave_amount; k++) {
		rnd = GetRand(shave_count - 1);
		shave_count2 = 0;
		breakf = false;

		for (int i = 0; i < sizex; i++) {
			for (int j = 0; j < sizey; j++) {
				if (shave_bool[i][j]) {
					if (shave_count2 == rnd) {
						//壁にする
						map->GetCell(mx + i, my + j)->SetCellData(celldata_admin->GetCellData(BOX_WALL));

						//shave_boolを相対的に更新する
						shave_bool[i][j] = false;
						shave_count--;

						/*
						if (i > 0) { if (m_shavefvec[i - 1][j] == m_shavef && map->GetCell(mx + i - 1, my + j)->GetMovef() == true && shave_bool[i - 1][j] == false) { shave_bool[i - 1][j] = true; shave_count++; } }
						if (j > 0) { if (m_shavefvec[i][j - 1] == m_shavef && map->GetCell(mx + i, my + j - 1)->GetMovef() == true && shave_bool[i][j - 1] == false) { shave_bool[i][j - 1] = true; shave_count++; } }
						if (i < sizex - 1) { if (m_shavefvec[i + 1][j] == m_shavef && map->GetCell(mx + i + 1, my + j)->GetMovef() == true && shave_bool[i + 1][j] == false) { shave_bool[i + 1][j] = true; shave_count++; } }
						if (j < sizey - 1) { if (m_shavefvec[i][j + 1] == m_shavef && map->GetCell(mx + i, my + j + 1)->GetMovef() == true && shave_bool[i][j + 1] == false) { shave_bool[i][j + 1] = true; shave_count++; } }
						*/

						for (int l = 0; l < 4; l++) {
							if (l == 0) {
								if (i > 0) { bufx = i - 1; bufy = j; } else { continue; }
							}
							if (l == 1) {
								if (j > 0) { bufx = i; bufy = j - 1; } else { continue; }
							}
							if (l == 2) {
								if (i < sizex - 1) { bufx = i + 1; bufy = j; } else { continue; }
							}
							if (l == 3) {
								if (j < sizey - 1) { bufx = i; bufy = j + 1; } else { continue; }
							}

							cnt = 0;
							if (bufx == 0) { cnt++; }
							if (bufy == 0) { cnt++; }
							if (bufx == sizex - 1) { cnt++; }
							if (bufy == sizey - 1) { cnt++; }
							if (bufx > 0) { if (map->GetCell(mx + bufx - 1, my + bufy)->GetMovef() == false) { cnt++; } }
							if (bufy > 0) { if (map->GetCell(mx + bufx, my + bufy - 1)->GetMovef() == false) { cnt++; } }
							if (bufx < sizex - 1) { if (map->GetCell(mx + bufx + 1, my + bufy)->GetMovef() == false) { cnt++; } }
							if (bufy < sizey - 1) { if (map->GetCell(mx + bufx, my + bufy + 1)->GetMovef() == false) { cnt++; } }

							if (cnt > 1 && shave_bool[bufx][bufy] == false && map->GetCell(mx + bufx, my + bufy)->GetMovef() == true && m_shavefvec[bufx][bufy] == m_shavef) { shave_bool[bufx][bufy] = true; shave_count++; }
						}


						//ループを抜ける
						breakf = true;
						break;
					}
					shave_count2++;
				}
			}
			if (breakf) {
				break;
			}
		}
	}
}


//void SectionAdmin::ShaveEdge(Room* m_Room, double m_shave_rate) {
	/*
	int mx, my, c, cnt;

	//少し面を削る
	/*
	for (int i = 0; i < 2; i++) {
		c = 0;
		while (1) {
			if (c++ > 1000) { break; }
			cnt = 0;
			if (GetRand(1) == 0) {
				mx = m_Room->GetX() + GetRand(1)*(m_Room->GetSizeX() - 1);
				my = m_Room->GetY() + GetRand(m_Room->GetSizeY() - 1);
			}
			else {
				mx = m_Room->GetX() + GetRand(m_Room->GetSizeX() - 1);
				my = m_Room->GetY() + GetRand(1)*(m_Room->GetSizeY() - 1);
			}

			if (map->GetCell(mx - 1, my)->GetCellData()->GetMovef()) { cnt++; }
			if (map->GetCell(mx + 1, my)->GetCellData()->GetMovef()) { cnt++; }
			if (map->GetCell(mx, my - 1)->GetCellData()->GetMovef()) { cnt++; }
			if (map->GetCell(mx, my + 1)->GetCellData()->GetMovef()) { cnt++; }
			if (cnt == 3) {
				map->GetCell(mx, my)->SetCellData(celldata_admin->GetCellData(BOX_WALL));
				break;
			}
		}
	}
	

	for (int i = 0; i < (int)(m_shave_rate*sqrt(m_Room->GetSizeX()*m_Room->GetSizeY())); i++) {
		c = 0;
		while (1) {
			if (c++ > 1000) { break; }
			mx = m_Room->GetX() + GetRand(m_Room->GetSizeX() - 1);
			my = m_Room->GetY() + GetRand(m_Room->GetSizeY() - 1);
			if (map_admin->GetCellAcsessf(mx, my) &&
				map_admin->GetCellAcsessf(mx - 1, my) &&
				map_admin->GetCellAcsessf(mx + 1, my) &&
				map_admin->GetCellAcsessf(mx, my - 1) && 
				map_admin->GetCellAcsessf(mx, my + 1)) {
				
				if (map->GetCell(mx, my)->GetCellData()->GetMovef()) {
					cnt = 0;
					
					if ((
							!map->GetCell(mx - 1, my)->GetCellData()->GetMovef() &&
							!map->GetCell(mx, my - 1)->GetCellData()->GetMovef() &&
							map->GetCell(mx + 1, my + 1)->GetCellData()->GetMovef()
						) ||
						(
							!map->GetCell(mx + 1, my)->GetCellData()->GetMovef() &&
							!map->GetCell(mx, my - 1)->GetCellData()->GetMovef() &&
							map->GetCell(mx - 1, my + 1)->GetCellData()->GetMovef()
						) ||
						(
							!map->GetCell(mx + 1, my)->GetCellData()->GetMovef() &&
							!map->GetCell(mx, my + 1)->GetCellData()->GetMovef() &&
							map->GetCell(mx - 1, my - 1)->GetCellData()->GetMovef()
						) ||
						(
							!map->GetCell(mx - 1, my)->GetCellData()->GetMovef() &&
							!map->GetCell(mx, my + 1)->GetCellData()->GetMovef() &&
							map->GetCell(mx + 1, my - 1)->GetCellData()->GetMovef()
						)) {
						map->GetCell(mx, my)->SetCellData(celldata_admin->GetCellData(BOX_WALL));
						break;
					}
	
					if (map->GetCell(mx - 1, my)->GetCellData()->GetMovef()) { cnt++; }
					if (map->GetCell(mx + 1, my)->GetCellData()->GetMovef()) { cnt++; }
					if (map->GetCell(mx, my - 1)->GetCellData()->GetMovef()) { cnt++; }
					if (map->GetCell(mx, my + 1)->GetCellData()->GetMovef()) { cnt++; }

					if (cnt <= 3) {
						map->GetCell(mx, my)->SetCellData(celldata_admin->GetCellData(BOX_WALL));
						break;
					}
				}
			}
		}
	}*/


//
std::vector<int> SectionAdmin::GetConnectGroup(std::vector<std::vector<int>> m_combination, int size, std::vector<bool>& m_exist_f) {
	//返り値として、未使用0　グループ番号1~を格納したvectorを返す。
	std::vector<int> r_group(size,0);
	std::vector<bool> buf_connect_f(size);
	//std::vector<bool> buf_exist_f(size, 0);

	int num = 1;
	bool numplus_f = false;

	/*
	全てのSectionを未使用にする。
	未使用のSにあたったら、そのSとつながって居るSを全てtrueにして、
	trueすべてにSとおなじグループ番号を格納する。
	これを繰り返す。最終的にグループ番号最大値を返す。
	*/

	for (int i = 0; i < size; i++) {
		if (r_group[i] == 0 && m_exist_f[i]) {

			//printfDx("[%d]", m_combination.size());
			ConnectCheck(m_combination, size, m_exist_f, i, buf_connect_f);

			for (int j = 0; j < size; j++) {
				if (buf_connect_f[j] && m_exist_f[j]) {
					r_group[j] = num;
					numplus_f = true;
				}
			}
			if (numplus_f) {
				num++;
				numplus_f = false;
			}
		}
	}

	return r_group;
}

//
bool SectionAdmin::ConnectCheck(const std::vector<std::vector<int>> m_combination, const int size, std::vector<bool>& m_exist_f) {
	std::vector<bool> buf;
	return ConnectCheck(m_combination, size, m_exist_f, m_combination[0][0], buf);;
}
bool SectionAdmin::ConnectCheck(const std::vector<std::vector<int>> m_combination, const int size, std::vector<bool>& m_exist_f, int first_section_number, std::vector<bool>& r_connect_f) {
	
	//first_section_number = 接続について調べる時の親となるセクション番号

	//m_combination[i][2]


	
	std::vector<bool> m_connect_f(size, false);//その部屋は接続済みか
	std::vector<bool> m_check_f(size, false);//その番号から接続されている部屋を全て接続済みとしたか
	//std::vector<bool> m_exist_f(size, false);//その番号が使われているか

	r_connect_f = m_connect_f;
	//r_exist_f = m_exist_f;

	bool flag;

	/*
	printfDx("size %d, fsn %d ", size,first_section_number);
	for (int i = 0; i < (signed int)m_combination.size(); i++) {
		printfDx("(%d %d)", m_combination[i][0], m_combination[i][1]);
	}
	printfDx("\n");
	*/

	//m_combinationに入っている値が、size内に収まった値かを調べる。
	for (int i = 0; i < (signed int)m_combination.size() ; i++) {
		if (m_combination[i][0] >= 0 && m_combination[i][0] < size) {
			//m_exist_f[m_combination[i][0]] = true;
		}
		else {
			printfDx("ConnectCheck Error <m_combination>\n");
			WaitKey();
			return false;
		}
		if (m_combination[i][1] >= 0 && m_combination[i][1] < size) {
			//m_exist_f[m_combination[i][1]] = true;
		}
		else {
			printfDx("ConnectCheck Error <m_combination>\n");
			WaitKey();
			return false;
		}
	}

	//ある1部屋を接続済みにして開始
	//m_connect_f[m_combination[0][0]] = true;
	if (first_section_number >= 0 && first_section_number < size) {
		if (m_exist_f[first_section_number]) {
			m_connect_f[first_section_number] = true;
		}
		else {
			return false;
		}
	}
	else {
		printfDx("ConnectCheck Error <first_section_number>\n");
		WaitKey();
		return false;
	}

	/*
	for (int i = 0; i < size; i++) {
		printfDx("%d", (int)m_exist_f[i]);
	}
	printfDx("\n");
	*/

	int i = 0;
	while (i < size) {
		if (i == 0) {
			flag = false;
		}

		if (!m_check_f[i] && m_connect_f[i] && m_exist_f[i]) {
			for (int j = 0; j < (signed int)m_combination.size(); j++) {
				if (m_combination[j][0] == i) {
					m_connect_f[m_combination[j][1]] = true;
				}
				if (m_combination[j][1] == i) {
					m_connect_f[m_combination[j][0]] = true;
				}
			}
			m_check_f[i] = true;
			flag = true;
			
		}
		i++;
		if (i == size && flag) { i = 0; }

	}


	flag = true;
	for (int i = 0; i < size; i++) {
		if (!m_connect_f[i] && m_exist_f[i]) {
			flag = false;
		}
	}


	r_connect_f = m_connect_f;
	//r_exist_f = m_exist_f;
	return flag;
	
}

//
std::vector<std::vector<int>> SectionAdmin::DeleteSectionCombination(std::vector<std::vector<int>> m_section_combination, int m_delete_road_num, std::vector<bool>& m_exist_f) {
//bool SectionAdmin::DeleteSectionConbination(std::vector<Section*[2]> m_section_combination, int m_delete_road_num) {

	//std::vector<Section*[2]> buf_section_combination = m_section_combination;
	//std::vector<int[2]> buf_section_combination = m_section_combination;
	//std::vector<bool> buf_section_connect_f(size(sections));
	//std::vector<bool> buf_section_connect_f(size(sections),false);
	//bool flag = true;

	if (m_delete_road_num == 0) {
		return m_section_combination;
	}

	int cnt = 0;
	std::vector<int> rs = RandomSwap(0, (signed int)size(m_section_combination) - 1);

	for (int i = 0; i < (signed int)rs.size(); i++) {
		//printfDx("loop start\n");
		/*cnt++;
		if (cnt > 10000) {
			if (DEBUG_SA) {
				printfDx("DeleteSectionCombination cnt = 10000 %d\n", m_delete_road_num);
				WaitKey();
			}
			break;
		}
		*/


		std::vector<std::vector<int>> buf_section_combination = m_section_combination;
		//std::vector<bool> buf_section_connect_f(size(sections), false);

		/*
		buf_section_combination.erase(
			buf_section_combination.begin()
			+ GetRand((signed int)size(buf_section_combination) - 1)
			);
		*/
		buf_section_combination.erase(buf_section_combination.begin() + rs[i]);



		/*
		*(buf_section_connect_f.begin() + buf_section_combination[0][0]) = true;


		//printfDx("%d %d\n", *(buf_section_connect_f.begin()), buf_section_connect_f[0]);

		int i = 0;
		while (1) {
			//printfDx("%d %d %d %d\n", buf_section_combination[i][0], buf_section_combination[i][1], *(buf_section_connect_f.begin() + buf_section_combination[i][0]), *(buf_section_connect_f.begin() + buf_section_combination[i][1]));
			if ((
				*(buf_section_connect_f.begin() + buf_section_combination[i][0]) == true ||
				*(buf_section_connect_f.begin() + buf_section_combination[i][1]) == true
				) &&
				!(
				*(buf_section_connect_f.begin() + buf_section_combination[i][0]) == true &&
				*(buf_section_connect_f.begin() + buf_section_combination[i][1]) == true
				)){

				*(buf_section_connect_f.begin() + buf_section_combination[i][0]) = true;
				*(buf_section_connect_f.begin() + buf_section_combination[i][1]) = true;
				i = 0;
			}
			else {
				i++;
				//if (i >= (signed int)size(buf_section_combination)) {
				if (i >= (signed int)buf_section_combination.size()) {
					break;
				}
			}
		}

		flag = true;
		//for (int i = 0; i < (signed int)size(buf_section_connect_f); i++) {
		for (int i = 0; i < (signed int)buf_section_connect_f.size(); i++) {
			if (!buf_section_connect_f[i] && sections[i]->GetRoomf()) {
				flag = false;
			}
		}
		*/

		if (ConnectCheck(buf_section_combination,(signed int)sections.size(), m_exist_f)) {
			/*
			for (int i = 0; i < (signed int)buf_section_combination.size(); i++) {
				printfDx("%d %d\n", buf_section_combination[i][0], buf_section_combination[i][1]);
			}
			printfDx("\n");
			WaitKey();
			*/
			m_delete_road_num--;


			if (m_delete_road_num > 0) {
				return DeleteSectionCombination(buf_section_combination, m_delete_road_num, m_exist_f);
			}
			else {
				return buf_section_combination;
			}
		}
	}
	return m_section_combination;
}

Room* SectionAdmin::MakeShop(double percentage) {
	Room* buf_room = NULL;

	std::vector<int> rs = RandomSwap(0, (signed int)sections.size() - 1);

	for (int i = 0; i < (signed int)rs.size(); i++) {
		int j = rs[i];
		if (sections[j]->GetRoomf()) {
			buf_room = sections[j]->GetRoom();
			if ((buf_room->GetSizeX() >= floordata->GetShopsizeMin() && buf_room->GetSizeY() >= floordata->GetShopsizeMin()) && buf_room->GetSizeX() <= floordata->GetShopsizeMax() && buf_room->GetSizeY() <= floordata->GetShopsizeMax()) {
				break;
			}
		}
		buf_room = NULL;
	}
	if (buf_room == NULL) {
		return buf_room;
	}

	int m_x = buf_room->GetX();
	int m_y = buf_room->GetY();
	int m_sizex = buf_room->GetSizeX();
	int m_sizey = buf_room->GetSizeY();

	if ((double)GetRand(99) + 1.0 <= percentage*100.0) {
		for (int i = 0 + 1; i < m_sizex - 1; i++) {
			for (int j = 0 + 1; j < m_sizey - 1; j++) {
				map->GetCell(m_x + i, m_y + j)->SetCellData(celldata_admin->GetCellData(SHOP_FLOOR));
			}
		}
	}
	return buf_room;
}


void SectionAdmin::MakeTrap(int traps) {
	int m_x, m_y;
	for (int i = 0; i < traps; i++) {
		if (GetRandomRoomFloor(&m_x, &m_y)) {
			map->GetCell(m_x, m_y)->SetCellData(celldata_admin->GetCellData(TRAP_FLOOR));
			map->GetCell(m_x, m_y)->SetTrapData(trapdata_admin->GetTrapData((TRAPTYPE)GetRand((int)TRAPTYPE_NUM - 2) + 1));
		}
		else {
			printfDx("MakeTrap is failed\n");
		}
	}
}

void SectionAdmin::MakeStep() {
	int m_x, m_y;
	if (GetRandomRoomFloor(&m_x, &m_y)) {
		map->GetCell(m_x, m_y)->SetCellData(celldata_admin->GetCellData(ROOM_STEP));
	}
	else {
		printfDx("MakeStep is failed\n");
	}
}


Room* SectionAdmin::GetRandomRoom() {
	Section* buf_section;
	int cnt = 0;
	while (1) {
		cnt++;
		if (cnt > 10000) {
			return NULL;
		}
		buf_section = sections[GetRand(size(sections) - 1)];
		if (buf_section->GetRoomf()) {
			return buf_section->GetRoom();
		}
	};
}

Room* SectionAdmin::GetRandomRoom_Square() {

	int square_all = 0;
	for (int i = 0; i < (signed int)size(sections); i++) {
		if (sections[i]->GetRoomf()) {
			square_all += sections[i]->GetRoom()->GetSizeX() * sections[i]->GetRoom()->GetSizeY();
		}
	}
	int rand = GetRand(square_all - 1);

	for (int i = 0; i < (signed int)size(sections); i++) {
		if (sections[i]->GetRoomf()) {
			rand -= sections[i]->GetRoom()->GetSizeX() * sections[i]->GetRoom()->GetSizeY();
			if (rand < 0) {
				return sections[i]->GetRoom();
			}
		}
	}

	return NULL;
}


bool SectionAdmin::GetFloorInRoom(Room* m_room, int* r_x, int* r_y) {
	return GetRoomFloor(m_room, r_x, r_y);
}

bool SectionAdmin::GetRandomRoomFloor(int* r_x,int* r_y) {
	//ランダムな部屋の、通路につながる床でない、かつ階段でも店でもないある地点を選ぶ関数。
	Room* buf_room = GetRandomRoom();
	if (buf_room == NULL) {
		return false;
	}
	return GetRoomFloor(buf_room, r_x, r_y);
}

bool SectionAdmin::GetRoomFloor(Room* buf_room, int* r_x, int* r_y) {
	
	/*
	Section* buf_section;
	int cnt = 0;
	while (1) {
		cnt++;
		if (cnt > 10000) {
			return false;
		}
		buf_section = sections[GetRand(size(sections) - 1)];
		if (buf_section->GetRoomf()) {
			break;
		}
	};

	int m_x = buf_section->GetRoom()->GetX();
	int m_y = buf_section->GetRoom()->GetY();
	int m_sizex = buf_section->GetRoom()->GetSizeX();
	int m_sizey = buf_section->GetRoom()->GetSizeY();
	*/



	int m_x = buf_room->GetX();
	int m_y = buf_room->GetY();
	int m_sizex = buf_room->GetSizeX();
	int m_sizey = buf_room->GetSizeY();

	int room_floor_x;
	int room_floor_y;

	int cnt = 0;

	std::vector<int> rs = RandomSwap(0, m_sizex*m_sizey - 1);

	for (int i = 0; i < (signed int)rs.size(); i++) {
//	while (1) {
		/*
		cnt++;
		if (cnt > 10000) {

			return false;
		}
		*/
		/*
		room_floor_x = m_x + GetRand(m_sizex - 1);
		room_floor_y = m_y + GetRand(m_sizey - 1);
		*/
		room_floor_x = m_x + rs[i] % m_sizex;
		room_floor_y = m_y + rs[i] / m_sizex;

		if (map->GetCell(room_floor_x - 1, room_floor_y)->GetCellData()->GetCellType() != ROAD_FLOOR &&
			map->GetCell(room_floor_x, room_floor_y - 1)->GetCellData()->GetCellType() != ROAD_FLOOR &&
			map->GetCell(room_floor_x, room_floor_y + 1)->GetCellData()->GetCellType() != ROAD_FLOOR &&
			map->GetCell(room_floor_x + 1, room_floor_y)->GetCellData()->GetCellType() != ROAD_FLOOR
			) {
			if (
				map->GetCell(room_floor_x, room_floor_y)->GetCellData()->GetMovef() &&
				!map->GetCell(room_floor_x, room_floor_y)->GetCellData()->GetShopf() &&
				!map->GetCell(room_floor_x, room_floor_y)->GetCellData()->GetStepf()
				) {
				*r_x = room_floor_x;
				*r_y = room_floor_y;
				break;
			}
		}

	}

	return true;
}

void SectionAdmin::SetRoomTempAll() {
	for (int i = 0; i < (signed int)size(sections); i++) {
		if (sections[i]->GetRoomf()) {
			int m_x = sections[i]->GetRoom()->GetX();
			int m_y = sections[i]->GetRoom()->GetY();
			int m_sizex = sections[i]->GetRoom()->GetSizeX();
			int m_sizey = sections[i]->GetRoom()->GetSizeY();

			for (int i = m_x; i < m_x + m_sizex; i++) {
				for (int j = m_y; j < m_y + m_sizey; j++) {
					map->GetCell(i, j)->SetTemporaryCell(true);
				}
			}
		}
	}
}

void SectionAdmin::SetTempToCellDataAll(CELLTYPE m_celltype, bool m_temporarycell, bool overwritef) {
	for (int i = 0; i < map->GetSizeX(); i++) {
		for (int j = 0; j < map->GetSizeY(); j++) {
			if (map->GetCell(i, j)->GetTemporaryCell() == m_temporarycell) {
				if ((map->GetCell(i, j)->GetCellData() == NULL && !overwritef) || overwritef) {
					map->GetCell(i, j)->SetCellData(celldata_admin->GetCellData(m_celltype));
				}
			}
		}
	}
}

Room* SectionAdmin::GetRoom(int i) {
	if (i >= (signed int)size(sections)) {
		return NULL;
	}
	if (sections[i]->GetRoomf()) {
		return sections[i]->GetRoom();
	}
	else {
		return NULL;
	}
}

Room* SectionAdmin::GetRoom(int m_x, int m_y) {

	int room_x;
	int room_y;
	int room_sizex;
	int room_sizey;

	for (int i = 0; i < (signed int)size(sections); i++) {
		if (sections[i]->GetRoomf()) {
			room_x = sections[i]->GetRoom()->GetX();
			room_y = sections[i]->GetRoom()->GetY();
			room_sizex = sections[i]->GetRoom()->GetSizeX();
			room_sizey = sections[i]->GetRoom()->GetSizeY();

			//部屋の中、を定義しなおしたので直す。壁のそれとか
			if (room_x - 1 <= m_x &&
				room_y - 1 <= m_y &&
				room_x + room_sizex + 1 > m_x &&
				room_y + room_sizey + 1 > m_y) {
				if (map->GetCell(m_x,m_y)->GetCellData()->GetRoomf()) {
					return sections[i]->GetRoom();
				}
			}
		}
	}
	return NULL;
}
/*
std::vector<std::vector<SHAVE_F>> SectionAdmin::RoomShaveMarking(Room* m_room) {
	std::vector<std::vector<SHAVE_F>> mark(m_room->GetSizeX(), std::vector<SHAVE_F>(m_room->GetSizeY(), SHAVE_FALSE));
	int m_x, m_y, dx, dy, sdx, ecx, ecy;
	bool breakf;
	int sides_min = m_room->GetSizeY();
	if (m_room->GetSizeY() > m_room->GetSizeX()) {
		sides_min = m_room->GetSizeX();
	}

	//printfDx("size : %d,%d ", m_room->GetSizeX(), m_room->GetSizeY());

	for (int i = 0; i < 4; i++) {
		m_x = 0;
		m_y = 0;
		breakf = false;

		switch(i) {
		case(0) :
			sdx = 1;
			dx = -1;
			dy = 1;
			break;
		case(1) :
			sdx = -1;
			dx = 1;
			dy = 1;
			m_x += m_room->GetSizeX() - 1;
			break;
		case(2) :
			sdx = -1;
			dx = 1;
			dy = -1;
			m_x += m_room->GetSizeX() - 1;
			m_y += m_room->GetSizeY() - 1;
			break;
		case(3) :
			sdx = 1;
			dx = -1;
			dy = -1;
			m_y += m_room->GetSizeY() - 1;
			break;
		}


		for (int j = 0; j < m_room->GetSizeX() + m_room->GetSizeY(); j++) {
			//printfDx("j=%d ", j);
			
			for (int m = 0; m < m_room->GetEntranceCellSize(); m++) {
				ecx = m_room->GetEntranceCell_OneX(m) - m_room->GetX();
				ecy = m_room->GetEntranceCell_OneY(m) - m_room->GetY();
				if (m_room->GetEntranceCell_OneDirection(m) == (int)DIR_DOWN) {
					ecy++;
				}
				if (m_room->GetEntranceCell_OneDirection(m) == (int)DIR_UP) {
					ecy--;
				}
				if (m_room->GetEntranceCell_OneDirection(m) == (int)DIR_RIGHT) {
					ecx--;
				}
				if (m_room->GetEntranceCell_OneDirection(m) == (int)DIR_LEFT) {
					ecx++;
				}
				printfDx("%d %d %d %d %d %d\n",ecx, ecy, m_x, m_y, m_x + dx*j, m_y + dy*j);

				if (
					(ecx == m_x &&
					 ecy == m_y)
					 || 
					(ecx == m_x + dx*j &&
					 ecy == m_y + dy*j)
					) {
					breakf = true;
					printfDx("a");
					break;
				}
				
			}
			if (breakf) {
				break;
			}

			for (int k = 0; k < j + 1; k++) {
				//printfDx("%d,%d ",m_x + dx*k, m_y + dy*k);
				//WaitKey();
				mark[m_x + dx*k][m_y + dy*k] = SHAVE_ALL_TRUE;
			}

			m_x += sdx;
			

		}
	}

	return mark;
}
*/

void SectionAdmin::SetDungeonData(DungeonData* m_dungeondata) { dungeondata = m_dungeondata; }
void SectionAdmin::SetFloorData(int i) { floordata = dungeondata->GetFloorData(i); };
void SectionAdmin::SetFloorData(FloorData* m_floordata) { floordata = m_floordata; };


std::vector<std::vector<SHAVE_F>> SectionAdmin::RoomShaveMarking(Room* m_room) {
	std::vector<std::vector<SHAVE_F>> mark(m_room->GetSizeX(), std::vector<SHAVE_F>(m_room->GetSizeY(), SHAVE_FALSE));

	int m_x, m_y, min_i_param[8], buf_param, d_param;
	bool entrance_slant_higher, entrance_slant_lower;
	DIRECTION m_d;

	int min_i[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
	//
	//確認ラインはこんな配置になっている。

	//／0　4　1＼
	//	7	  5
	//＼3　6　2／
	

	for (int i = 0; i < m_room->GetEntranceCellSize(); i++) {
		m_x = m_room->GetEntranceCell_OneX(i) - m_room->GetX();
		m_y = m_room->GetEntranceCell_OneY(i) - m_room->GetY();
		m_d = (DIRECTION)m_room->GetEntranceCell_OneDirection(i);
		for (int j = 0; j < 8; j++) {
			if (m_d == DIR_UP) {
				switch (j) {
				case(0) : buf_param = m_x; break;
				case(1) : buf_param = m_room->GetSizeX() - m_x - 1; break;
				case(2) : buf_param = m_room->GetSizeX() - m_x - 1 + m_room->GetSizeY() - 1; break;
				case(3) : buf_param = m_x + m_room->GetSizeY() - 1; break;

				case(4) : buf_param = 0; break;
				case(5) : buf_param = m_room->GetSizeX() - m_x - 1; break;
				case(6) : buf_param = m_room->GetSizeY() - 1; break;
				case(7) : buf_param = m_x; break;
				}
			}
			if (m_d == DIR_RIGHT) {
				switch (j) {
				case(1) : buf_param = m_y; break;
				case(2) : buf_param = m_room->GetSizeY() - m_y - 1; break;
				case(3) : buf_param = m_room->GetSizeY() - m_y - 1 + m_room->GetSizeX() - 1; break;
				case(0) : buf_param = m_y + m_room->GetSizeX() - 1; break;

				case(4) : buf_param = m_y; break;
				case(5) : buf_param = 0; break;
				case(6) : buf_param = m_room->GetSizeY() - m_y - 1; break;
				case(7) : buf_param = m_room->GetSizeX() - 1; break;
				}
			}
			if (m_d == DIR_DOWN) {
				switch (j) {
				case(3) : buf_param = m_x; break;
				case(2) : buf_param = m_room->GetSizeX() - m_x - 1; break;
				case(1) : buf_param = m_room->GetSizeX() - m_x - 1 + m_room->GetSizeY() - 1; break;
				case(0) : buf_param = m_x + m_room->GetSizeY() - 1; break;

				case(4) : buf_param = m_room->GetSizeY() - 1; break;
				case(5) : buf_param = m_room->GetSizeX() - m_x - 1; break;
				case(6) : buf_param = 0; break;
				case(7) : buf_param = m_x; break;
				}
			}
			if (m_d == DIR_LEFT) {
				switch (j) {
				case(0) : buf_param = m_y; break;
				case(3) : buf_param = m_room->GetSizeY() - m_y - 1; break;
				case(2) : buf_param = m_room->GetSizeY() - m_y - 1 + m_room->GetSizeX() - 1; break;
				case(1) : buf_param = m_y + m_room->GetSizeX() - 1; break;

				case(4) : buf_param = m_y; break;
				case(5) : buf_param = m_room->GetSizeX() - 1; break;
				case(6) : buf_param = m_room->GetSizeY() - m_y - 1; break;
				case(7) : buf_param = 0; break;
				}
			}

			if (min_i[j] == -1) {
				min_i[j] = i;
				min_i_param[j] = buf_param;
			}
			else {
				if (buf_param < min_i_param[j]) {
					min_i[j] = i;
					min_i_param[j] = buf_param;
					//printfDx("ov");
				}
			}
		}
	}


	for (int l = 0; l < 8; l++) {
		//printfDx("%d", min_i[l]);
		//WaitKey();
		if (min_i[l] >= 0) {
			if (l < 4) {
				m_x = m_room->GetEntranceCell_OneX(min_i[l]);
				m_y = m_room->GetEntranceCell_OneY(min_i[l]);
				m_d = (DIRECTION)m_room->GetEntranceCell_OneDirection(min_i[l]);

				if (m_d == DIR_UP || m_d == DIR_DOWN) {
					entrance_slant_lower = map->GetCell(m_x - 1, m_y)->GetCellData()->GetSlantMovef();
					entrance_slant_higher = map->GetCell(m_x + 1, m_y)->GetCellData()->GetSlantMovef();
				}

				if (m_d == DIR_LEFT || m_d == DIR_RIGHT) {
					entrance_slant_lower = map->GetCell(m_x, m_y - 1)->GetCellData()->GetSlantMovef();
					entrance_slant_higher = map->GetCell(m_x, m_y + 1)->GetCellData()->GetSlantMovef();
				}
				entrance_slant_lower = true;
				entrance_slant_higher = true;
				//printfDx("%d%d ",entrance_slant_lower, entrance_slant_higher);

				d_param = 0;
				if (l==0) {
					if (m_d == DIR_UP) {
						d_param = -1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_RIGHT) {
						d_param = 1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_DOWN) {
						d_param = 1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_LEFT) {
						d_param = -1 * (int)entrance_slant_lower;
					}
				}
				if (l == 1) {
					if (m_d == DIR_UP) {
						d_param = -1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_RIGHT) {
						d_param = -1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_DOWN) {
						d_param = 1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_LEFT) {
						d_param = 1 * (int)entrance_slant_lower;
					}
				}
				if (l == 2) {
					if (m_d == DIR_UP) {
						d_param = 1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_RIGHT) {
						d_param = -1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_DOWN) {
						d_param = -1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_LEFT) {
						d_param = 1 * (int)entrance_slant_higher;
					}
				}
				if (l == 3) {
					if (m_d == DIR_UP) {
						d_param = 1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_RIGHT) {
						d_param = 1 * (int)entrance_slant_higher;
					}
					if (m_d == DIR_DOWN) {
						d_param = -1 * (int)entrance_slant_lower;
					}
					if (m_d == DIR_LEFT) {
						d_param = -1 * (int)entrance_slant_higher;
					}
				}
				
			}
		}
		m_x -= m_room->GetX();
		m_y -= m_room->GetY();
		for (int j = 0; j < m_room->GetSizeX(); j++) {
			for (int k = 0; k < m_room->GetSizeY(); k++) {
				if (
					(l == 0 && j + k < min_i_param[l] + d_param) ||
					(l == 1 && m_room->GetSizeX() - 1 - j + k < min_i_param[l] + d_param) ||
					(l == 2 && m_room->GetSizeX() - 1 - j + m_room->GetSizeY() - 1 - k < min_i_param[l] + d_param) ||
					(l == 3 && j + m_room->GetSizeY() - 1 - k < min_i_param[l] + d_param) ||
					
					(l == 4 && k < min_i_param[l]) ||
					(l == 5 && m_room->GetSizeX() - 1 - j < min_i_param[l]) ||
					(l == 6 && m_room->GetSizeY() - 1 - k < min_i_param[l]) ||
					(l == 7 && j < min_i_param[l])
						
					){
					 mark[j][k] = SHAVE_ALL_TRUE;
				}
				if (
					(l == 0 && 1 + j + k == min_i_param[l] + d_param) ||
					(l == 1 && 1 + m_room->GetSizeX() - 1 - j + k == min_i_param[l] + d_param) ||
					(l == 2 && 1 + m_room->GetSizeX() - 1 - j + m_room->GetSizeY() - 1 - k == min_i_param[l] + d_param) ||
					(l == 3 && 1 + j + m_room->GetSizeY() - 1 - k == min_i_param[l] + d_param)
					) {
					mark[j][k] = SHAVE_SLANT_TRUE;
				}
			}
		}
	}

	return mark;
}


/*
std::vector<std::vector<bool>> SectionAdmin::RoomShaveMarking(Room* m_room) {
	std::vector<std::vector<bool>> mark(m_room->GetSizeX(), std::vector<bool>(m_room->GetSizeY(), false));
	//まずすべての場所が削れると仮定して、削れない部分をSHAVE_SLANT_TRUE,SHAVE_FALSEにしていく

	//int buf_point[3];
	int m_x, m_y, entrance_slant_higher = 0, entrance_slant_lower = 0;
	DIRECTION m_d;

	for (int i = 0; i < m_room->GetEntranceCellSize(); i++) {
		//m_room->GetEntranceCell_One(buf_point, i);
		m_x = m_room->GetEntranceCell_OneX(i);//buf_point[0] - m_room->GetX();
		m_y = m_room->GetEntranceCell_OneY(i);//buf_point[1] - m_room->GetY();
		m_d = (DIRECTION)m_room->GetEntranceCell_OneDirection(i);//(DIRECTION)buf_point[2];

		if (m_d == DIR_UP || m_d == DIR_DOWN) {
			if (map->GetCell(m_x - 1 , m_y)->GetCellData()->GetSlantMovef()) {
				entrance_slant_lower = 0;
			}
			else {
				entrance_slant_lower = 1;
			}
			if (map->GetCell(m_x + 1, m_y)->GetCellData()->GetSlantMovef()) {
				entrance_slant_higher = 0;
			}
			else {
				entrance_slant_higher = 1;
			}

			m_x -= m_room->GetX();
			m_y -= m_room->GetY();
			for (int j = 0; j < m_room->GetSizeX(); j++) {
				for (int k = 0; k < m_room->GetSizeY(); k++) {
					if (j == m_x + abs( 0 - (m_y - k) - 1 + entrance_slant_lower) || j == m_x - abs(0 - (m_y - k) - 1 + entrance_slant_higher)) {
						mark[j][k] = SHAVE_SLANT_TRUE;
					}

					if (j < m_x + abs(0 - (m_y - k) - 1 + entrance_slant_lower) && j > m_x - abs(0 - (m_y - k) - 1 + entrance_slant_higher)) {
						mark[j][k] = SHAVE_FALSE;
					}
				}
			}
		}

		if (m_d == DIR_LEFT || m_d == DIR_RIGHT) {
			if (map->GetCell(m_x, m_y - 1)->GetCellData()->GetSlantMovef()) {
				entrance_slant_lower = 0;
			}
			else {
				entrance_slant_lower = 1;
			}
			if (map->GetCell(m_x, m_y + 1)->GetCellData()->GetSlantMovef()) {
				entrance_slant_higher = 0;
			}
			else {
				entrance_slant_higher = 1;
			}

			m_x -= m_room->GetX();
			m_y -= m_room->GetY();
			for (int j = 0; j < m_room->GetSizeX(); j++) {
				for (int k = 0; k < m_room->GetSizeY(); k++) {
					//if (k == m_x - (m_y - j) - 1 + entrance_slant_lower || k == m_x + (m_y - j) + 1 - entrance_slant_higher) {
					if (k == m_y + abs(0 - (m_x - j) - 1 + entrance_slant_lower) || k == m_y - abs(0 - (m_x - j) - 1 + entrance_slant_higher)) {

						mark[j][k] = SHAVE_SLANT_TRUE;
					}

					//if (k > m_x - (m_y - j) - 1 + entrance_slant_lower && k < m_x + (m_y - j) + 1 - entrance_slant_higher) {
					if (k < m_y + abs(0 - (m_x - j) - 1 + entrance_slant_lower) && k > m_y - abs(0 - (m_x - j) - 1 + entrance_slant_higher)) {

						mark[j][k] = SHAVE_FALSE;
					}
				}
			}
		}
		

	}
	return mark;

}
*/

/*

bool SectionAdmin::GetEntranceSlantMovef(int start_mx, int start_my, int end_mx, int end_my, bool* rbool) {
	Room* m_room = GetRoom(start_mx, start_my);
	if (!(m_room == GetRoom(end_mx, end_my))) {
		return false;
	}
	int num_s = m_room->GetEntranceCell_Number(start_mx, start_my);
	int num_e = m_room->GetEntranceCell_Number(end_mx, end_my);

	if (num_s == -1 || num_e == -1) {
		return false;
	}
	return GetEntranceSlantMovef(m_room, num_s, num_e, rbool);
}

bool SectionAdmin::GetEntranceSlantMovef(int start_mx, int start_my, int end_mx, int end_my, bool* rbool) {
	bool buf[2];
	GetEntranceSlantMovef(start_mx, start_my, end_mx, end_my, buf);
	return buf[1];
}

bool SectionAdmin::GetEntranceSlantMovef(Room* m_room, int start, int end, bool* rbool) {
	std::vector<std::vector<int>> buf_entrance_cell = m_room->GetEntranceCell_All();

	
	if (!(start < (signed int)buf_entrance_cell.size() && end < (signed int)buf_entrance_cell.size())) {
		return false;
	}
	

	int start_x = buf_entrance_cell[start][0];
	int start_y = buf_entrance_cell[start][1];
	DIRECTION start_d = (DIRECTION)buf_entrance_cell[start][2];
	int end_x = buf_entrance_cell[end][0];
	int end_y = buf_entrance_cell[end][1];
	DIRECTION end_d = (DIRECTION)buf_entrance_cell[end][2];
	

	if (start_d == DIR_UP || start_d == DIR_DOWN) {
		if (start_x > end_x) { rbool[0] = map->GetCell(start_x - 1, start_y)->GetCellData()->GetSlantMovef(); }
		if (start_x < end_x) { rbool[0] = map->GetCell(start_x + 1, start_y)->GetCellData()->GetSlantMovef(); }
		if (start_x == end_x) { rbool[0] = false; }
	}

	if (start_d == DIR_LEFT || start_d == DIR_RIGHT) {
		if (start_y > end_y) { rbool[0] = map->GetCell(start_x, start_y - 1)->GetCellData()->GetSlantMovef(); }
		if (start_y < end_y) { rbool[0] = map->GetCell(start_x, start_y + 1)->GetCellData()->GetSlantMovef(); }
		if (start_y == end_y) { rbool[0] = false; }
	}
*/

std::vector<Road*> SectionAdmin::GetRoad(int m_x, int m_y) {
	std::vector<Road*> r_road;
	if (map_admin->GetCellAcsessf(m_x, m_y)) {
		for (int i = 0; i < (signed int)roads.size(); i++) {
			if (roads[i]->CheckPoint(m_x, m_y)) {
				r_road.push_back(roads[i]);
			}
		}
	}
	else {
		return r_road;
	}
	return r_road;
}


void SectionAdmin::GetEntranceSlantMovef(int start_x, int start_y, int end_x, int end_y, bool& start_f,bool& goal_f) {
	goal_f = GetEntranceSlantMovef(start_x, start_y, end_x, end_y);
	start_f = GetEntranceSlantMovef(end_x, end_y, start_x, start_y);
}


bool SectionAdmin::GetEntranceSlantMovef(int start_x, int start_y, int end_x, int end_y) {
	Room* m_room = GetRoom(end_x, end_y);
	if (!(m_room == GetRoom(start_x, start_y))) {
		return false;
	}

	int num_e = m_room->GetEntranceCell_Number(end_x, end_y);
	if (num_e == -1) {
		return true;
	}

	DIRECTION end_d = (DIRECTION)m_room->GetEntranceCell_OneDirection(num_e);

	if (end_d == DIR_UP || end_d == DIR_DOWN) {
		if (start_x > end_x) { return map->GetCell(end_x + 1, end_y)->GetCellData()->GetSlantMovef(); }
		if (start_x < end_x) { return  map->GetCell(end_x - 1, end_y)->GetCellData()->GetSlantMovef(); }
		if (start_x == end_x) { return false; }
	}

	if (end_d == DIR_LEFT || end_d == DIR_RIGHT) {
		if (start_x > end_x) { return map->GetCell(end_x, end_y + 1)->GetCellData()->GetSlantMovef(); }
		if (start_x < end_x) { return map->GetCell(end_x, end_y - 1)->GetCellData()->GetSlantMovef(); }
		if (start_x == end_x) { return false; }
	}
	return true;
}


int SectionAdmin::MakeRoadSectionToSection(Section* section1, Section* section2) {

	DIRECTION direction1 = section1->GetSectionDirecion(section2);
	DIRECTION direction2 = section2->GetSectionDirecion(section1);

	int point1s[2];
	int point1e[2];
	int point2s[2];
	int point2e[2];

	int point_end[2];
	int point_break[2];

	if (direction1 && direction2) {
		int cnt = 0;
		while (1) {
			cnt++;//そもそもMakeFirstRoad内で被り処理すべき
			if (cnt > 10000) {
				return -1;
			}
			if (section1->MakeFirstRoad(direction1, point1s, point1e)) {
				if (direction1 == DIR_LEFT || direction1 == DIR_RIGHT) {
					//他の同じ方向から出ている通路に隣接しているかどうかをチェック
					if (!map->GetCell(point1s[0], point1s[1] - 1)->GetTemporaryCell() &&
						!map->GetCell(point1s[0], point1s[1] + 1)->GetTemporaryCell()) {
						break;
					}
				}
				if (direction1 == DIR_UP || direction1 == DIR_DOWN) {
					if (!map->GetCell(point1s[0] - 1, point1s[1])->GetTemporaryCell() &&
						!map->GetCell(point1s[0] + 1, point1s[1])->GetTemporaryCell()) {
						break;
					}
				}
			}
		}
		cnt = 0;
		while (1) {
			cnt++;//そもそもMakeFirstRoad内で被り処理すべき
			if (cnt > 10000) {
				return -1;
			}
			if (section2->MakeFirstRoad(direction2, point2s, point2e)) {
				if (direction2 == DIR_LEFT || direction2 == DIR_RIGHT) {
					if (!map->GetCell(point2s[0], point2s[1] - 1)->GetTemporaryCell() &&
						!map->GetCell(point2s[0], point2s[1] + 1)->GetTemporaryCell()) {
						break;
					}
				}
				if (direction2 == DIR_UP || direction2 == DIR_DOWN) {
					if (!map->GetCell(point2s[0] - 1, point2s[1])->GetTemporaryCell() &&
						!map->GetCell(point2s[0] + 1, point2s[1])->GetTemporaryCell()) {
						break;
					}
				}
			}
		}


		//Roadをインスタンス化して準備
		roads.push_back(new Road());
		Road* buf_roads = roads.back();
		buf_roads->SetConnectionRoom(section1->GetRoom());
		bool flag1,flag2,flag3;


		flag1 = MakeRoadPointToPoint(point1s[0], point1s[1], point1e[0], point1e[1], true, point_end, point_break);
		buf_roads->SetConnectionRoom(section1->GetRoom());
		buf_roads->SetPoint(point1s);
		buf_roads->SetPoint(point_end);

		section1->GetRoom()->SetEntranceCell(point1s[0], point1s[1], direction1);
		if (flag1) {
			//この時点で、1側の部屋の通路入り口は確定
			if (point1e[0] == point2e[0] && point1e[1] == point2e[1]) { //各部屋から出た道を繋げると、曲がり角が無くなる場合
				flag2 = true;
			}
			else {
				flag2 = MakeRoadPointToPoint(point1e[0], point1e[1], point2e[0], point2e[1], true, point_end, point_break);
				buf_roads->SetPoint(point_end);
			}

			if (flag2) {
				flag3 = MakeRoadPointToPoint(point2e[0], point2e[1], point2s[0], point2s[1], true, point_end, point_break);
				buf_roads->SetPoint(point_end);

				if (flag3) {
					//この時点で、2側の部屋の通路入り口は確定
					section2->GetRoom()->SetEntranceCell(point2s[0], point2s[1], direction2);
					section2->GetRoom()->SetConnectionRoom(section1->GetRoom());
					section1->GetRoom()->SetConnectionRoom(section2->GetRoom());
					buf_roads->SetConnectionRoom(section2->GetRoom());

					/*
					printfDx("%d %d\n", buf_roads->GetPointX(0), buf_roads->GetPointY(0));
					printfDx("%d %d\n", buf_roads->GetPointX(1), buf_roads->GetPointY(1));
					printfDx("%d %d\n", buf_roads->GetPointX(2), buf_roads->GetPointY(2));
					WaitKey();
					*/

					return 1;
				}
				else {
					//部屋間接続失敗
				}
			}
			else {
				//部屋間接続失敗
			}
		}
		else {
			//部屋間接続失敗
		}

		//部屋間接続に失敗した場合
		if (!flag1 || !flag2 || !flag3) {
			std::vector<Road*> candidated_road = GetRoad(point_break[0], point_break[1]);
			//printfDx("<%d>", candidated_road.size());
			for (int j = 0; j < (signed int)candidated_road.size(); j++) {
				Road* connect_road = candidated_road[j];
				if (connect_road != NULL && connect_road != buf_roads) {
					std::vector<Room*> buf_rooms = connect_road->GetConnectionRoom();
					for (int i = 0; i < (signed int)buf_rooms.size(); i++) {
						buf_roads->SetConnectionRoom(buf_rooms[i]);

						section1->GetRoom()->SetConnectionRoom(buf_rooms[i]);
						buf_rooms[i]->SetConnectionRoom(section1->GetRoom());
						//printfDx(" %d^%d ", section1->GetNumber(), buf_rooms[i]->GetPSection()->GetNumber());
					}
				}
			}
	
		}
		return 2;

	}
	return 0;
}

bool SectionAdmin::MakeRoadPointToPoint(int m_x1, int m_y1, int m_x2, int m_y2, bool flag, int* point_end, int* point_break) {
	
	// flag = true の時、壁に当たった場合は即終了する
	// 最初の1マス目は、仮に床であっても続行させている。



	point_end[0] = -1;
	point_end[1] = -1;

	if (
		map->GetSizeX() <= m_x1 ||
		map->GetSizeX() <= m_x2 ||
		map->GetSizeY() <= m_y1 ||
		map->GetSizeY() <= m_y2 ||
		0 > m_x1 ||
		0 > m_x2 ||
		0 > m_y1 ||
		0 > m_y2) {

		printfDx("MakeRoadPointToPoint error");
		WaitKey();
		return false;
	}

	int i = 0;
	int dir = 0;
	bool break_flag = false;
	if (m_x1 == m_x2 && m_y1 != m_y2) {
		dir = (m_y2 - m_y1) / abs(m_y2 - m_y1);
		while (1) {
			if (i == (m_y2 - m_y1)) {
				map->GetCell(m_x1, m_y1 + i)->SetTemporaryCell(true);

				point_end[0] = m_x1;
				point_end[1] = m_y1 + i;

				break;
			} //ゴールに到達したなら強制終了
			if (flag && i != 0) {
				// 何かの道と隣り合わせで繋がったら終了
				if (map->GetCell(m_x1, m_y1 + i + dir)->GetTemporaryCell()) {
					point_break[0] = m_x1;
					point_break[1] = m_y1 + i + dir;
					break_flag = true;
				}
				if (map->GetCell(m_x1 + 1, m_y1 + i)->GetTemporaryCell()) {
					point_break[0] = m_x1 + 1;
					point_break[1] = m_y1 + i;
					break_flag = true;
				}
				if (map->GetCell(m_x1 + 1, m_y1 + i)->GetTemporaryCell()) {
					point_break[0] = m_x1 - 1;
					point_break[1] = m_y1 + i;
					break_flag = true;
				}
				if (break_flag) {
					map->GetCell(m_x1, m_y1 + i)->SetTemporaryCell(true);
					point_end[0] = m_x1;
					point_end[1] = m_y1 + i;
					return false;
				}

				// 何かの道に当たったら終了
				if (map->GetCell(m_x1, m_y1 + i)->GetTemporaryCell()) {
					point_end[0] = m_x1;
					point_end[1] = m_y1 + i;
					point_break[0] = m_x1;
					point_break[1] = m_y1 + i;
					return false;
				}
			}

			map->GetCell(m_x1, m_y1 + i)->SetTemporaryCell(true);
			i = i + dir;
		}
		return true;
	}
	if(m_x1 != m_x2 && m_y1 == m_y2) {
		dir = (m_x2 - m_x1) / abs(m_x2 - m_x1);
		while (1) {
			if (i == (m_x2 - m_x1)) {
				map->GetCell(m_x1 + i, m_y1)->SetTemporaryCell(true);
				point_end[0] = m_x1 + i;
				point_end[1] = m_y1;
				break;
			}//ゴールに到達したなら強制終了
			if (flag && i != 0) {
				// 何かの道と隣り合わせで繋がったら終了

				if (map->GetCell(m_x1 + i + dir, m_y1)->GetTemporaryCell()) {
					point_break[0] = m_x1 + i + dir;
					point_break[1] = m_y1;
					break_flag = true;
				}
				if (map->GetCell(m_x1 + i, m_y1 + 1)->GetTemporaryCell()) {
					point_break[0] = m_x1 + i;
					point_break[1] = m_y1 + 1;
					break_flag = true;
				}
				if (map->GetCell(m_x1 + i, m_y1 - 1)->GetTemporaryCell()) {
					point_break[0] = m_x1 + i;
					point_break[1] = m_y1 - 1;
					break_flag = true;
				}
				if (break_flag) {
					map->GetCell(m_x1 + i, m_y1)->SetTemporaryCell(true);
					point_end[0] = m_x1 + i;
					point_end[1] = m_y1;
					return false;
				}

				// 何かの道に当たったら終了
				if (map->GetCell(m_x1 + i, m_y1)->GetTemporaryCell()) {
					point_end[0] = m_x1 + i;
					point_end[1] = m_y1;
					point_break[0] = m_x1 + i;
					point_break[1] = m_y1;
					return false;
				}
			}
			map->GetCell(m_x1 + i, m_y1)->SetTemporaryCell(true);
			i = i + dir;
		}
		return true;
	}
	return false;
}


Section* SectionAdmin::MakeSection(int m_depth, int m_x, int m_y, int m_size_x, int m_size_y, Section* m_p_section) {
	sections.push_back(new Section());
	Section* this_section = sections.back();
	int number = (signed int)sections.size() - 1;

	this_section->SetNumber(number);
	this_section->SetX(m_x);
	this_section->SetY(m_y);
	this_section->SetSizeX(m_size_x);
	this_section->SetSizeY(m_size_y);
	this_section->SetDepth(m_depth);
	this_section->SetPSection(m_p_section);
	if (m_p_section != NULL) {
		m_p_section->SetChildf(true);
	}

	//DrawBox(160 + m_x, m_y, 160 + m_x + m_size_x + 1, m_y + m_size_y + 1, GetColor(255, 255, 255), false);
	//WaitKey();

	return this_section;
}

bool SectionAdmin::DevideSection(Section* m_section,int m_devide, int m_num_section, int section_min, int section_max, std::vector<Section*>& new_sections) {
	//m_devide 0=横線　1=縦線
	int x = m_section->GetX();
	int y = m_section->GetY();
	int size_x = m_section->GetSizeX();
	int size_y = m_section->GetSizeY();

	if ((m_devide == 1 && size_x >= m_num_section*section_max) || (m_devide == 0 && size_y >= m_num_section*section_max)) {
		printfDx("DevideSection Error 1\n");
		//WaitKey();
		return false; //親の空間が大きすぎる
	}

	if ((m_devide == 1 && size_x < m_num_section*section_min) || (m_devide == 0 && size_y < m_num_section*section_min)) {
		//printfDx("DevideSection Error 2 : %d,%d,%d,%d %d\n", m_devide,size_x, size_y, m_num_section, section_min);
		//WaitKey();
		return false; //親に十分な空間が無い
	}

	std::vector<int> size_devide(m_num_section, section_min);//各部屋の広さを宣言しつつ、最低領域分を格納

	int size;

	if (m_devide == 0) {
		size = size_y;
	}
	else {
		size = size_x;
	}

	//最低領域分以外の残り部分を配分
	int stick = m_num_section - 1;
	int loop = size - section_min*m_num_section + stick;
	int cnt = 0;

	for (int i = 0; i < loop ; i++) {
		if ((GetRand(loop - i - 1) < stick) || (cnt >= section_max)) {
			stick--;
			cnt = 0;
		}
		else {
			cnt++;
			size_devide[m_num_section - stick - 1] += 1;
		}
	}

	int point;
	if (m_devide == 0) {
		point = y;
	}
	else {
		point = x;
	}
	


	//子section作成
	for (int i = 0; i < m_num_section; i++) {
		if (m_devide == 0) {
			new_sections.push_back(MakeSection(m_section->GetDepth() + 1, x, point, size_x, size_devide[i], m_section));
		}
		else {
			new_sections.push_back(MakeSection(m_section->GetDepth() + 1, point, y, size_devide[i], size_y, m_section));
		}
		point += size_devide[i];
	}

	

	return true;
}

void SectionAdmin::MakeAllSection(DUNGEON_MAKE_MODE make_mode) {
	std::vector<Section*> buf_sections;
	std::vector<Section*> next_psection;
	next_psection.push_back(sections.back());

	int max, devide = 0;
	if (floordata->GetFloorsizeX() > floordata->GetFloorsizeY()) {
		max = floordata->GetFloorsizeX();
	}
	else {
		max = floordata->GetFloorsizeY();
	}

	if (make_mode == DEPTH_FIRST_RAND || make_mode == DEPTH_FIRST_LARGER || make_mode == DEPTH_FIRST_DEVIDE_LARGER) {
		for (int i = 0; i < floordata->GetMakeroomNum(0)- 1; i++) {
			if (!DevideSection(sections.back(),devide, 2, (floordata->GetRoomsizeMin() + 2) * 2, max, buf_sections)) {
				break;
			}
			if (make_mode == DEPTH_FIRST_RAND) {
				next_psection[0] = buf_sections[GetRand((signed int)buf_sections.size() - 1)];
				devide = (i + 1) % 2;
			}
			if (make_mode == DEPTH_FIRST_LARGER) {
				if (buf_sections[0]->GetSizeX() * buf_sections[0]->GetSizeY() > buf_sections[1]->GetSizeX() * buf_sections[1]->GetSizeY()) {
					next_psection[0] = buf_sections[0];
				}
				else {
					next_psection[0] = buf_sections[1];
				}
				devide = (i + 1) % 2;
			}
			if (make_mode == DEPTH_FIRST_DEVIDE_LARGER) {
				if (buf_sections[0]->GetSizeX() * buf_sections[0]->GetSizeY() > buf_sections[1]->GetSizeX() * buf_sections[1]->GetSizeY()) {
					next_psection[0] = buf_sections[0];
				}
				else {
					next_psection[0] = buf_sections[1];
				}
				if (next_psection[0]->GetSizeX() > next_psection[0]->GetSizeY()) {
					devide = 1;
				}
				else {
					devide = 0;
				}
				
			}
		}

		for (int i = 0; i < (signed int)sections.size(); i++) {
			if (!sections[i]->GetChildf()) {
				sections[i]->SetRoomMakef(true);
			}
		}

	}

	if (make_mode == WIDTH_FIRST) {
		for (int i = 0; i*i <= floordata->GetMakeroomNum(0); i++) {
			if (!DevideSection(sections.back(), i % 2, 2, (floordata->GetRoomsizeMin() + 2) * 2, max, buf_sections)) {
				break;
			}
			next_psection.clear();
			for (int j = 0; j < (signed int)buf_sections.size(); j++) {
				next_psection.push_back(buf_sections[j]);
			}
		}
		for (int i = 0; i < (signed int)sections.size(); i++) {
			if (!sections[i]->GetChildf()) {
				sections[i]->SetRoomMakef(true);
			}
		}
	}

	if (make_mode == EVEN_DEVIDE) {
		devide = 1;
		DevideSection(sections.back(), devide, floordata->GetMakeroomNum(0), (floordata->GetRoomsizeMin() + 2) * 2, max, buf_sections);
		devide = 0;
		for (int i = 0; i < floordata->GetMakeroomNum(0); i++) {
			DevideSection(buf_sections[i], devide, floordata->GetMakeroomNum(1), (floordata->GetRoomsizeMin() + 2) * 2, max, buf_sections);
		}
	}

	for (int i = 0; i < (signed int)sections.size(); i++) {
		if (sections[i]->GetRoomMakef()) {
			sections[i]->MakeRoom(floordata->GetRoomsizeMin(), floordata->GetRoomsizeMax());
		}
	}

}

