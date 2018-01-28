#ifndef DEF_MapAdmin
#define DEF_MapAdmin

#include "define.h"
#include "Dxlib.h"

#include "map.h"

/*

MapAdmin
Map�֌W���Ǘ�����N���X

*/

enum MAPCHIP {
	NON_MAPCHIP,
	FLOOR,
	WALL,
	STEP,
	NUM_MAPCHIP
};

class CellDataAdmin;
class TrapDataAdmin;
class Camera;
//class MakeMapGraphic;
class SectionAdmin;
class DungeonData;
class Room;
class MakeTileGraphic;
class TileSetAdmin;
class MiniMap;
class TrapProcess;

class MapAdmin {
protected:
	Map* map;
	//Map* expmap;
	int graphic_handle[NUM_MAPCHIP];
	CellDataAdmin* celldata_admin;
	TrapDataAdmin* trapdata_admin;
	//MakeMapGraphic* make_map_graphic;
	SectionAdmin* section_admin;
	MakeTileGraphic* make_tile_graphic;
	Camera* camera;

	TrapProcess* trapProcess;

	//DEBUG
	MiniMap* minimap;

public:

	MapAdmin();
	//MapAdmin();
	~MapAdmin();
	void Init(CellDataAdmin*, TrapDataAdmin*, TileSetAdmin*, Camera*, TrapProcess*);

	Map* GetMap();
	//Map* GetExpMap();

	Cell* GetMapCell(int, int);
	CellData* GetMapCellData(int, int);
	CELLTYPE GetMapCellType(int, int);

	bool GetSpawnf_Conv(int, int);
	bool GetMovef_Conv(int, int, COMMAND);
	bool GetMovef_Conv(int, int, int, int);
	bool GetCellAcsessf(int, int);

	void GetRespawnCell(int*, int*);
	void GetRespawnCellFarAway(int*, int*, int, int, int);

	bool IsInCameraByMapPosition(int, int);
	bool IsFarAwayByMapPosition(int, int, int, int, int);
	bool IsTrapFloor(const int, const int);

	bool ActivateTrapFloor(const int, const int);

	bool TrapEvent(const int, const int);

	Room* GetRandomRoom();
	Room* GetRandomRoom_Square();

	bool GetRoomFloor(Room*, int*, int*);
	bool GetFloorInRoom(Room*, int*, int*);
	bool GetRandomRoomFloor(int*, int*);

	Room* GetRoom(int);
	Room* GetRoom(int, int);

	SectionAdmin* GetSectionAdmin();

	void GraphLoad(); // Main�ŁA��x�����Ăяo���B

	void MakeMap(DungeonData*, int);

	void MapInit(); // Map�������쐬

	void Draw(Camera*,bool);

	//DEBUG
	void MapAdmin::SetMiniMap(MiniMap*);
};

#endif

/*
�����@Mapinit

�E�K�v����

����������

����������(double)�@�������Ƃ̂ł��铹�̖{���ɑ΂���A���ۂ̓��̖{���̊���

�����̕Ӎŏ��l
�����̕Ӎő�l

��������
�@���D��
�@�[���D��
�@�[���D��-�傫�����������D��
�@�O������

 ���t���O
 �Ε�����芄���@1�����̃}�X���̂�����������邩

 �摜�Z�b�g�|�C���^

 �ǎ�ށ@�����A�΂߂̐���

 �o������g���b�v���X�g
 �g���b�v�̊���

 �X�̐����m��




 �����@�_���W�����f�[�^

 �_���W�����f�[�^�́A�e�t���A�̃t���A�f�[�^�|�C���^�����B
 �_���W�����f�[�^����A���ׂẴt���A�ɃZ�b�g������A����̃t���A�ɂ����Z�b�g�����肷��B

 �E�e�_���W�����f�[�^
�e�t���A�f�[�^�|�C���^
(�K�w��)




�E �e�t���A�f�[�^

 �o������G���X�g
 �G�̊���

 �o������A�C�e�����X�g
 �A�C�e���̊���

 �X�ɏo������A�C�e�����X�g
 �A�C�e���̊���

 Mapinit�ɕK�v�Ȉ����̑S��(�����_���Ȃ�A�����_���ł��邱�Ƃ�������悤�ȃp�����[�^)


*/
