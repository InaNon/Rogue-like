#ifndef DEF_Section
#define DEF_Section

#include "define.h"
#include <vector>

class Room;
//class Map;


/**
ダンジョンの生成方式
・深さ優先形式
セクションを二つに分け、そのうち一方を葉、もう一方を枝分かれさせることを繰り返す。
パラメータ＝部屋数。最低限の接続のために、親─子間で接続する

・幅優先形式
セクションを2つに分け、そのいずれも枝分かれさせることを繰り返す。
パラメータ＝部屋数の平方根

・等分割方式
グランドセクションを初めから分割してしまう。
部屋同士を繋ぐ時、部屋の無いセクションには道のみが作られる



**/



class Section {
protected:
	int number;

	int depth;

	//int devide;
	//bool devide_wh; //分割縦横


	DIRECTION p_direction; //親sectionの存在する方向
	DIRECTION c_direction; //親sectionの存在する方向

	int x;
	int y;

	int sizex;
	int sizey;

	bool child_f;

	bool room_make_f;

	//std::vector<Section*> c_section;
	Section* p_section;

	Room* room;


public:

	//Section* MakeSection(DUNGEON_MAKE_MODE,int, int, int, int, int);
	//Section* MakeSection(DUNGEON_MAKE_MODE,int, int, int, int, int, Section*); //引数: int のこり作成Section数,Section* 親Section(関数内記述から見た時の)　返り値: 子section

	//void MakeRoom();
	void MakeRoom(int, int);

	//void GetSection(std::vector<Section*>*);

	bool MakeFirstRoad(DIRECTION,int*,int*);

	//void Output(Map*);

	DIRECTION GetSectionDirecion(Section*);

	/* Getter */
	int GetNumber();
	int GetDepth();
	//int GetDevide();
	//bool GetDevideWH();
	DIRECTION GetCDirection();
	DIRECTION GetPDirection();

	int GetX();
	int GetY();

	int GetSizeX();
	int GetSizeY();

	bool GetChildf();
	bool GetRoomf();
	bool GetRoomMakef();

	//Section* GetCSection(int);
	Section* GetPSection();

	Room* GetRoom();


	/* Setter */
	void SetNumber(int);
	void SetDepth(int);
	//void SetDevide(int);
	//void SetDevideWH(bool);
	void SetCDirection(DIRECTION);
	void SetPDirection(DIRECTION);

	void SetX(int);
	void SetY(int);

	void SetSizeX(int);
	void SetSizeY(int);

	void SetChildf(bool);
	void SetRoomMakef(bool);

	//void SetCSection(Section*);
	void SetPSection(Section*);


	Section();
	Section(const Section &rhs);
	~Section();

};

#endif
