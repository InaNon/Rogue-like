#include "room.h"
#include "DxLib.h"
#include "define.h"
//#include "map.h"
#include "section.h"

Room::Room(Section* m_p_section) {
	p_section = m_p_section;
	//connectionf = false;
}

Room::~Room() {
}
/*
void Room::MakeRoom(int m_x,int m_y,int m_sizex,int m_sizey,int min_x,int min_y) { 
	sizex = min_x + GetRand(m_sizex - min_x - 4);
	sizey = min_y + GetRand(m_sizey - min_y - 4);

	x = m_x + 2 +GetRand(m_sizex - sizex - 4);
	y = m_y + 2 +GetRand(m_sizey - sizey - 4);
	*/
	/*
	if (DEBUG_F) {
		DrawBox(160 + x, y, 160+ x + sizex + 1, y + sizey + 1, GetColor(255, 0, 0), false);
	}
	*/
/*

};
*/


void Room::MakeRoom(int m_x,int m_y,int m_sizex,int m_sizey,int min,int max) {
	if (m_sizex < min + 4 || m_sizey < min + 4) {
		printfDx("MakeRoom is cancelled. sectionsizex = %d, sectionsizey = %d, min = %d", m_sizex, m_sizey, min);
		//WaitKey();
		return;
	}


	/*
	        
	        
	  œœœœ  
	  œœœœ  
	  œœœœ  
	        
	        

	*/

	if (min + m_sizex - min - 4 < max) {
		sizex = min + GetRand(m_sizex - min - 4);
	}
	else {
		sizex = min + GetRand(max - min);
	}
	if (min + m_sizey - min - 4 < max) {
		sizey = min + GetRand(m_sizey - min - 4);
	}
	else {
		sizey = min + GetRand(max - min);
	}

	x = m_x + 2 +GetRand(m_sizex - sizex - 4);
	y = m_y + 2 +GetRand(m_sizey - sizey - 4);
};


bool Room::MakeFirstRoad(DIRECTION m_direction, int* start_point, int* goal_point) {
	int headx;
	int heady;

	switch (m_direction) {
	case(DIR_LEFT) :
		headx = x - 1;
		heady = y + 1 + GetRand(sizey - 3);
		start_point[0] = headx;
		start_point[1] = heady;

		while (p_section->GetX() < headx) {
			headx--;
		}
		break;
	case(DIR_RIGHT) :
		headx = x + sizex;
		heady = y + 1 + GetRand(sizey - 3);
		start_point[0] = headx;
		start_point[1] = heady;

		while (p_section->GetX() + p_section->GetSizeX() > headx) {
			headx++;
		}
		break;
	case(DIR_UP) :
		headx = x + 1 + GetRand(sizex - 3);
		heady = y - 1;
		start_point[0] = headx;
		start_point[1] = heady;

		while (p_section->GetY() < heady) {
			heady--;
		}
		break;
	case(DIR_DOWN) :
		headx = x + 1 + GetRand(sizex - 3);
		heady = y + sizey;
		start_point[0] = headx;
		start_point[1] = heady;

		while (p_section->GetY() + p_section->GetSizeY() > heady) {
			heady++;
		}
		break;
	default:
		break;
	}

	goal_point[0] = headx;
	goal_point[1] = heady;
	return true;
}

/*
void Room::Output(Map* m_map) {
	
	for (int i = x; i < x+sizex; i++) {
		for (int j = y; j < y + sizey; j++) {
			m_map->GetCell(i, j)->SetMovef(true);
		}
	}
};
*/

/* Getter */
int Room::GetX() { return x; };
int Room::GetY() { return y; };

int Room::GetSizeX() { return sizex; };
int Room::GetSizeY() { return sizey; };

bool Room::IsMonsterhouse() { return is_monsterhouse; }

//bool Room::GetConnectionf() { return connectionf; };


Section* Room::GetPSection() { return p_section; };

void Room::GetEntranceCell_One(int* rv, int i) {
	rv[0] = entrance_cell[i][0];
	rv[1] = entrance_cell[i][1];
	rv[2] = entrance_cell[i][2];
}

bool Room::GetEntranceCell_Rand(int* rv) {
	int random = GetRand(entrance_cell.size() - 1);
	rv[0] = entrance_cell[random][0];
	rv[1] = entrance_cell[random][1];
	rv[2] = entrance_cell[random][2];
	return true;
}

bool Room::GetEntranceCell_Rand(int* rv, int m_x, int m_y) {
	int random;
	int c = 0;
	while (1) {
		if (c++ > 10000) { break; }
		random = GetRand(entrance_cell.size() - 1);
		if (entrance_cell[random][0] != m_x || entrance_cell[random][1] != m_y) {
			rv[0] = entrance_cell[random][0];
			rv[1] = entrance_cell[random][1];
			rv[2] = entrance_cell[random][2];
			return true;
		}
	}
	return false;
}


void Room::GetEntranceCell_One(int i,int&rx ,int&ry ,DIRECTION& rcommand) {
	int point[3];
	GetEntranceCell_One(point, i);

	rx = point[0];
	ry = point[1];
	rcommand = (DIRECTION)point[2];
}

bool Room::GetEntranceCell_Rand(int&rx, int&ry, DIRECTION& rcommand) {
	int point[3];
	bool f = GetEntranceCell_Rand(point);

	rx = point[0];
	ry = point[1];
	rcommand = (DIRECTION)point[2];
	return f;
}

bool Room::GetEntranceCell_Rand(int mx, int my, int&rx, int&ry, DIRECTION& rcommand) {
	int point[3];
	bool f = GetEntranceCell_Rand(point, mx, my);

	rx = point[0];
	ry = point[1];
	rcommand = (DIRECTION)point[2];

	return f;
}



std::vector<std::vector<int>> Room::GetEntranceCell_All() {
	return entrance_cell;
}

int Room::GetEntranceCellSize() {
	return entrance_cell.size();
}

int Room::GetEntranceCell_Number(int m_x, int m_y) {
	for (int i = 0; i < (signed int)entrance_cell.size(); i++) {
		if (entrance_cell[i][0] == m_x && entrance_cell[i][1] == m_y) {
			return i;
		}
	}
	return -1;
}

int Room::GetEntranceCell_OneX(int i) {
	return entrance_cell[i][0];
}
int Room::GetEntranceCell_OneY(int i) {
	return entrance_cell[i][1];
}
int Room::GetEntranceCell_OneDirection(int i) {
	return entrance_cell[i][2];
}

std::vector<Room*> Room::GetConnectionRoom() {
	return connection_room;
}
Room* Room::GetConnectionRoom(int i) {
	if (i >= (signed int)connection_room.size() || i < 0) {
		return NULL;
	}
	return connection_room[i];
}

bool Room::SearchConnectionRoom(Room* m_room) {
	printfDx("(%d)", connection_room.size());
	for (int i = 0; i < (signed int)connection_room.size(); i++) {
		if (m_room == connection_room[i]) {
			return true;
		}
	}
	
	return false;
}



/* Setter */
void Room::SetX(int m_x) { x = m_x; };
void Room::SetY(int m_y) { y = m_y; };

void Room::SetSizeX(int m_sizex) { sizex = m_sizex; };
void Room::SetSizeY(int m_sizey) { sizey = m_sizey; };

void Room::SetIsMonsterhouse(bool _is_monsterhouse) {
	is_monsterhouse = _is_monsterhouse;
}

/*
void Room::SetConnectionf(bool m_connectionf) {
	connectionf = m_connectionf;
}
*/

void Room::SetPSection(Section* m_p_section) { p_section = m_p_section; };

void Room::SetEntranceCell(int m_x, int m_y, DIRECTION m_direction) {
	//”í‚Á‚½ê‡‚Í“ü‚ê‚È‚¢
	for (int i = 0; i < (signed int)entrance_cell.size(); i++) {
		if (entrance_cell[i][0] == m_x && entrance_cell[i][1] == m_y) {
			break;
		}
	}
	std::vector<int> buf(3);
	buf[0] = m_x;
	buf[1] = m_y;
	buf[2] = (int)m_direction;

	entrance_cell.push_back(buf);
}

void Room::SetConnectionRoom(Room* m_room) {
	connection_room.push_back(m_room);
}