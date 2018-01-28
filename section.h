#ifndef DEF_Section
#define DEF_Section

#include "define.h"
#include <vector>

class Room;
//class Map;


/**
�_���W�����̐�������
�E�[���D��`��
�Z�N�V�������ɕ����A���̂��������t�A����������}�����ꂳ���邱�Ƃ��J��Ԃ��B
�p�����[�^���������B�Œ���̐ڑ��̂��߂ɁA�e���q�ԂŐڑ�����

�E���D��`��
�Z�N�V������2�ɕ����A���̂�������}�����ꂳ���邱�Ƃ��J��Ԃ��B
�p�����[�^���������̕�����

�E����������
�O�����h�Z�N�V���������߂��番�����Ă��܂��B
�������m���q�����A�����̖����Z�N�V�����ɂ͓��݂̂������



**/



class Section {
protected:
	int number;

	int depth;

	//int devide;
	//bool devide_wh; //�����c��


	DIRECTION p_direction; //�esection�̑��݂������
	DIRECTION c_direction; //�esection�̑��݂������

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
	//Section* MakeSection(DUNGEON_MAKE_MODE,int, int, int, int, int, Section*); //����: int �̂���쐬Section��,Section* �eSection(�֐����L�q���猩������)�@�Ԃ�l: �qsection

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
