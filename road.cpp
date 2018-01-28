#include "road.h"
#include "DxLib.h"
Road::Road() {

};
Road::Road(const Road &rhs) {
}


Road::~Road() {
	
};

bool Road::CheckPoint(int m_x, int m_y) {
	//printfDx("@");
	for (int i = 0; i < (signed int)point.size() - 1; i++) {
		//printfDx("*%d %d %d %d %d %d*",point[i][0], m_x, point[i + 1][0], point[i][1], m_y, point[i + 1][1]);
		if (
			((point[i][0] <= m_x && m_x <= point[i + 1][0]) || (point[i + 1][0] <= m_x && m_x <= point[i][0]))
			&&
			((point[i][1] <= m_y && m_y <= point[i + 1][1]) || (point[i + 1][1] <= m_y && m_y <= point[i][1]))
			) {
			return true;
		}
	}
	return false;
}


int Road::GetPointX(int i) {
	return point[i][0];
};
int Road::GetPointY(int i) {
	return point[i][1];
};

std::vector<Room*> Road::GetConnectionRoom() {
	return connection_room;
}

Room* Road::GetConnectionRoom(int i) {
	if (i >= 0 && (signed int)connection_room.size() < i) {
		return connection_room[i];
	}
	else {
		return NULL;
	}
};


void Road::SetConnectionRoom(Room* m_room) {
	connection_room.push_back(m_room);
}
void Road::SetPoint(int* point) {
	SetPoint(point[0], point[1]);
}
void Road::SetPoint(int m_x, int m_y) {
	std::vector<int> buf_point(2);
	buf_point[0] = m_x;
	buf_point[1] = m_y;
	point.push_back(buf_point);
}