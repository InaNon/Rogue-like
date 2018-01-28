#ifndef DEF_Road
#define DEF_Road

#include <vector>
#include "define.h"

class Room;

class Road {
protected:
	std::vector<std::vector<int>> point;
	std::vector<Room*> connection_room;
	
public:

	Road();
	Road(const Road &rhs);
	~Road();

	int GetPointX(int);
	int GetPointY(int);

	bool CheckPoint(int, int);

	std::vector<Room*> Road::GetConnectionRoom();
	Room* GetConnectionRoom(int);


	void SetConnectionRoom(Room*);
	void SetPoint(int* point);
	void SetPoint(int,int);

};

#endif