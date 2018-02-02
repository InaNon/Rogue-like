#ifndef DEF_MapAdmin
#define DEF_MapAdmin

#include "define.h"
#include "Dxlib.h"

#include "map.h"

/*

MapAdmin
Map関係を管理するクラス

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

	void GraphLoad(); // Mainで、一度だけ呼び出す。

	void MakeMap(DungeonData*, int);

	void MapInit(); // Mapを初期作成

	void Draw(Camera*,bool);

	//DEBUG
	void MapAdmin::SetMiniMap(MiniMap*);
};

#endif

/*
メモ　Mapinit

・必要引数

生成部屋数

道生成割合(double)　引くことのできる道の本数に対する、実際の道の本数の割合

部屋の辺最小値
部屋の辺最大値

生成方式
　幅優先
　深さ優先
　深さ優先-大きい部屋分割優先
　外周道式

 削りフラグ
 対部屋削り割合　1部屋のマス数のうち何割を削るか

 画像セットポインタ

 壁種類　実質、斜めの是非

 出現するトラップリスト
 トラップの割合

 店の生成確率




 メモ　ダンジョンデータ

 ダンジョンデータは、各フロアのフロアデータポインタを持つ。
 ダンジョンデータから、すべてのフロアにセットしたり、特定のフロアにだけセットしたりする。

 ・各ダンジョンデータ
各フロアデータポインタ
(階層数)




・ 各フロアデータ

 出現する敵リスト
 敵の割合

 出現するアイテムリスト
 アイテムの割合

 店に出現するアイテムリスト
 アイテムの割合

 Mapinitに必要な引数の全て(ランダムなら、ランダムであることが分かるようなパラメータ)


*/
