#ifndef DEF_Room
#define DEF_Room

#include <vector>
#include "define.h"

class Section;
//class Map;

class Room {
protected:
	Section* p_section;

	int x;
	int y;
	int sizex;
	int sizey;

	std::vector<std::vector<int>> entrance_cell;
	/*
	Å°Å°Å†Å°Å°Å°Å°
	Å°Å°ÅôÅ°Å°Å°Å°
	Å†Å†Å†Å†Å°Å°Å°
	Å†Å†Å†Å†ÅôÅ†Å†
	Å†Å†Å†Å†Å°Å°Å°
	*/


	std::vector<Room*> connection_room;



	//bool connectionf;

public:

	Room(Section*);
	~Room();

	void MakeRoom(int,int,int,int,int,int);

	bool MakeFirstRoad(DIRECTION,int*,int*);

	//void Output(Map*);

	/* Getter */
	int GetX();
	int GetY();

	int GetSizeX();
	int GetSizeY();

	//bool GetConnectionf();

	Section* GetPSection();

	void GetEntranceCell_One(int*, int);
	bool GetEntranceCell_Rand(int*);
	bool GetEntranceCell_Rand(int*, int, int);
	std::vector<std::vector<int>> GetEntranceCell_All();

	void GetEntranceCell_One(int, int&, int&, DIRECTION&);
	bool GetEntranceCell_Rand(int&, int&, DIRECTION&);
	bool GetEntranceCell_Rand(int, int, int&, int&, DIRECTION&);


	int GetEntranceCell_OneX(int);
	int GetEntranceCell_OneY(int);
	int GetEntranceCell_OneDirection(int);

	int GetEntranceCell_Number(int, int);

	int GetEntranceCellSize();


	std::vector<Room*> GetConnectionRoom();
	Room* GetConnectionRoom(int);
	bool SearchConnectionRoom(Room*);


	/* Setter */
	void SetX(int);
	void SetY(int);

	void SetSizeX(int);
	void SetSizeY(int);

	//void SetConnectionf(bool);

	void SetPSection(Section*);

	void SetEntranceCell(int, int, DIRECTION);

	void SetConnectionRoom(Room*);
};

#endif
