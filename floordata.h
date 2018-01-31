#ifndef DEF_FloorData
#define DEF_FloorData

#include "define.h"
#include "Dxlib.h"
#include <vector>

class FloorData {
protected:
	std::vector<int> makeroom_num; //�����������l
	double makeroad_rate; //����������

	int floorsizex; //�t���Ax
	int floorsizey; //�t���Ay

	int roomsize_min; //�����ŏ��l
	int roomsize_max; //�����ŏ��l

	int shopsize_min; //�V���b�v�ŏ��l
	int shopsize_max; //�V���b�v�ŏ��l

	int enemy_param;

	DUNGEON_MAKE_MODE makemode; //�_���W������������
	/*
	DEPTH_FIRST_RAND, ���D��
	DEPTH_FIRST_LARGER, �[���D��
	WIDTH_FIRST, �[���D��-�傫�����������D��
	��������������
	�O������
	*/

	double shave_rate; //��藦
	double road_rate; //���꓾�铹�ɑ΂�����ۂ̓��̊���


	//�摜�Z�b�g�|�C���^

	bool wallslant_f; //�ǎ΂�

	//�g���b�v���X�g
	int trap_num;//�g���b�v��

	double shop_rate; //����������

	int element;//�_���W�����̑���

	//�o������G���X�g
	//�G�̊���

	//�o������A�C�e�����X�g
	int item_num;//�A�C�e���̐�

	//�X�ɏo������A�C�e�����X�g
	//�A�C�e���̊���

	double monsterhouse_rate;//�����X�^�[�n�E�X�o���m��


public:
	FloorData();
	FloorData(const FloorData &rhs);
	~FloorData();

	void Init();


	/* �Q�b�^�[ */
	int GetMakeroomNum(int); //�����������l
	double GetMakeroadRate(); //����������

	int GetFloorsizeX();
	int GetFloorsizeY();

	int GetRoomsizeMin(); //�����ŏ��l
	int GetRoomsizeMax(); //�����ő�l

	int GetShopsizeMin();
	int GetShopsizeMax();

	int GetElement();

	int GetEnemyParam();

	DUNGEON_MAKE_MODE GetMakemode(); //�_���W������������

	double GetShaveRate(); //��藦

	bool GetWallSlant_f(); //�ǎ΂�

	int GetTrapNum();
	int GetItemNum();

	double GetShopRate(); //�X������

	double GetMonsterhouseRate();

	/* �Z�b�^�[ */
	void SetMakeroomNum(int); //�����������l
	void SetMakeroadRate(double); //����������

	void SetFloorsizeX(int);
	void SetFloorsizeY(int);

	void SetShopsizeMin(int);
	void SetShopsizeMax(int);

	void SetRoomsizeMin(int); //�������ŏ��l
	void SetRoomsizeMax(int); //���������ő�l

	void SetElement(int);

	void SetEnemyParam(int);

	void SetMakemode(DUNGEON_MAKE_MODE); //�_���W������������

	void SetShaveRate(double); //��藦

	void SetWallSlant_f(bool); //�ǎ΂�

	void SetTrapNum(int);
	void SetItemNum(int);

	void SetShopRate(double); //�X������

	void SetMonsterhouseRate(double);

};

#endif

/*
�����@Mapinit

�E�K�v����

�t���A�̑傫��x
�t���A�̑傫��y

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









	�f�[�^�x�[�X

	������






	*/