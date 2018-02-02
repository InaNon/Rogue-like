#ifndef DEF_SectionAdmin
#define DEF_SectionAdmin

#include <vector>
#include "define.h"



class MapAdmin;
class Section;
class CellDataAdmin;
class TrapDataAdmin;
class Room;
class Map;
class Road;
class DungeonData;
class FloorData;
class MiniMap;
class SectionAdmin {
protected:
	
	//Section* grand_section;
	std::vector<Section*> sections;
	std::vector<Road*> roads;

	CellDataAdmin* celldata_admin;
	TrapDataAdmin* trapdata_admin;
	MapAdmin* map_admin;
	Map* map;
	DungeonData* dungeondata;
	FloorData* floordata;

	//DEBUG
	MiniMap* minimap;

public:

	SectionAdmin(MapAdmin* map_admin, CellDataAdmin* m_celldata_admin, TrapDataAdmin* trapdata_admin);
	//SectionAdmin(Map* map);
	~SectionAdmin();

	void Clear();

	void DungeonMake(DUNGEON_MAKE_MODE,int);
	void DungeonMake();

	void MakeStep();
	Room* MakeShop(double);
	void MakeTrap(int);

	
	Room* GetRandomRoom();
	Room* GetRandomRoom_Square();
	
	bool GetRoomFloor(Room*, int*, int*);
	bool GetFloorInRoom(Room*, int*, int*);
	bool GetRandomRoomFloor(int*, int*);


	std::vector<Room*> GetRoomAll();
	Room* GetRoom(int);
	Room* GetRoom(int, int);

	std::vector<std::vector<SHAVE_F>> SectionAdmin::RoomShaveMarking(Room*);

	/*
	bool GetEntranceSlantMovef(int, int, int, int);
	bool GetEntranceSlantMovef(int, int, int, int, bool*);
	bool GetEntranceSlantMovef(Room*, int, int, bool*);
	*/

	std::vector<Road*> GetRoad(int, int);



	bool GetEntranceSlantMovef(int, int, int, int);
	void GetEntranceSlantMovef(int, int, int, int, bool& ,bool&);

	void SetDungeonData(DungeonData*);
	void SetFloorData(int);
	void SetFloorData(FloorData*);

	void MakeHole(Room*);

	void ShaveEdge(Room*, double, std::vector<std::vector<SHAVE_F>>, SHAVE_F, CELLTYPE);

	std::vector<int> GetConnectGroup(std::vector<std::vector<int>>, int, std::vector<bool>&);

	bool ConnectCheck(const std::vector<std::vector<int>>, const int, std::vector<bool>&);
	bool ConnectCheck(const std::vector<std::vector<int>>, const int, std::vector<bool>&, int, std::vector<bool>&);

	void MakeMonsterhouse();
	std::vector<Room*> GetMonsterhouseRooms();

	std::vector<Room*> GetSwapedRoom();

	void SetRoomTempAll();
	void SetTempToCellDataAll(CELLTYPE, bool, bool);
	int MakeRoadSectionToSection(Section*, Section*);
	bool MakeRoadPointToPoint(int, int, int, int, bool, int*, int*);

	std::vector<std::vector<int>> DeleteSectionCombination(std::vector<std::vector<int>>, int, std::vector<bool>&);
	//bool DeleteSectionConbination(std::vector<Section*[2]>, int);

	Section* MakeSection(int, int, int, int, int, Section*);
	bool DevideSection(Section* m_section, int, int, int, int, std::vector<Section*>&);

	void MakeAllSection(DUNGEON_MAKE_MODE);
	void MakeRooms(std::vector<Section*>, FloorData*);

	//Section* MakeSection(DUNGEON_MAKE_MODE, int, int, int, int, int, int);


	//DEBUG
	void SetMiniMap(MiniMap*);
};

#endif
