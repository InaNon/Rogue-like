#include "section.h"
#include "DxLib.h"

#include "room.h"
//#include "map.h"

Section::Section() {
}

Section::Section(const Section &rhs) {
}

Section::~Section() {
	if (room != NULL) { delete room; }
}

void Section::MakeRoom(int min_room_size,int max_room_size) {
	//•”‰®‚ðì‚é
	room = new Room(this);
	room->MakeRoom(x, y, sizex, sizey, min_room_size, max_room_size);//’ù³•K—v
}

DIRECTION Section::GetSectionDirecion(Section* m_section) {
	//ˆø‚«”‚ÌSection‚ªA‚Ç‚Ì•ûŒü‚É‚ ‚é‚©‚ð•Ô‚·ŠÖ”

	int m_x = m_section->GetX();
	int m_y = m_section->GetY();
	int m_sizex = m_section->GetSizeX();
	int m_sizey = m_section->GetSizeY();

	//if (DEBUG_F) {
		//printfDx("x=%d,y=%d,sizex=%d,sizey=%d,m_x=%d,m_y=%d,m_sizex=%d,m_sizey=%d\n",x,y,sizex,sizey,m_x,m_y,m_sizex,m_sizey);
	//}

	if (x + sizex == m_x) {
		if (
			(y <= m_y && m_y <= y + sizey) ||
			(y <= m_y + m_sizex && m_y + m_sizey <= y + sizey) ||
			(m_y <= y && y <= m_y + m_sizey) ||
			(m_y <= y + sizex && y + sizey <= m_y + m_sizey)
			) {
			return DIR_RIGHT;
		}
	}
	if (x == m_x + m_sizex) {
		if (
			(y <= m_y && m_y <= y + sizey) ||
			(y <= m_y + m_sizex && m_y + m_sizey <= y + sizey) ||
			(m_y <= y && y <= m_y + m_sizey) ||
			(m_y <= y + sizex && y + sizey <= m_y + m_sizey)
			) {
			return DIR_LEFT;
		}
	}
	if (y + sizey == m_y) {
		if (
			(x <= m_x && m_x <= x + sizex) ||
			(x <= m_x + m_sizex && m_x + m_sizex <= x + sizex) ||
			(m_x <= x && x <= m_x + m_sizex) ||
			(m_x <= x + sizex && x + sizex <= m_x + m_sizex)
			) {
			return DIR_DOWN;
		}
	}
	if (y == m_y + m_sizey) {
		if (
			(x <= m_x && m_x <= x + sizex) ||
			(x <= m_x + m_sizex && m_x + m_sizex <= x + sizex) ||
			(m_x <= x && x <= m_x + m_sizex) ||
			(m_x <= x + sizex && x + sizex <= m_x + m_sizex)
			) {
			return DIR_UP;
		}
	}

	//printfDx("NONE\n");
	return NONE_DIRECTION;
	
}

bool Section::MakeFirstRoad(DIRECTION m_direction,int* start_point, int* goal_point) {
	if (room != NULL) {
		return room->MakeFirstRoad(m_direction, start_point,goal_point);
	}
	return false;
}

/* Getter */
int Section::GetNumber() { return number; };
int Section::GetDepth() { return depth; };
//int Section::GetDevide() { return devide; };
//bool Section::GetDevideWH() { return devide_wh; }
DIRECTION Section::GetCDirection() { return c_direction; };
DIRECTION Section::GetPDirection() { return p_direction; };

int Section::GetX() { return x; };
int Section::GetY() { return y; };

int Section::GetSizeX() { return sizex; };
int Section::GetSizeY() { return sizey; };

bool Section::GetChildf() { return child_f; };

bool Section::GetRoomf() {
	if (room == NULL) {
		return false;
	}
	return true;
};

bool Section::GetRoomMakef() { return room_make_f; };

//Section* Section::GetCSection(int i) { return c_section[i]; };
Section* Section::GetPSection() { return p_section; };

Room* Section::GetRoom() { return room; };


/* Setter */

void Section::SetNumber(int m_number) { number = m_number; };
void Section::SetDepth(int m_depth) { depth = m_depth; };
//void Section::SetDevide(int m_devide) { devide = m_devide; };
//void Section::SetDevideWH(bool m_devide_wh) { devide_wh = m_devide_wh; }
void Section::SetCDirection(DIRECTION m_direction) { c_direction = m_direction; };
void Section::SetPDirection(DIRECTION m_direction) { p_direction = m_direction; };

void Section::SetX(int m_x) { x = m_x; };
void Section::SetY(int m_y) { y = m_y; };

void Section::SetSizeX(int m_sizex) { sizex = m_sizex; };
void Section::SetSizeY(int m_sizey) { sizey = m_sizey; };

void Section::SetChildf(bool m_child_f) { child_f = m_child_f; };
void Section::SetRoomMakef(bool m_room_make_f) { room_make_f = m_room_make_f; }

//void Section::SetCSection(Section* m_c_section) { c_section = m_c_section; };
void Section::SetPSection(Section* m_p_section) { p_section = m_p_section; };