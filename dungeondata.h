#ifndef DEF_DungeonData
#define DEF_DungeonData

#include "define.h"
#include "Dxlib.h"

#include <vector>


class FloorData;

class DungeonData {
protected:
	std::vector<FloorData*> floordata;

public:
	DungeonData();
	~DungeonData();

	void Init(int);

	int GetFloorNum();
	FloorData* GetFloorData(int);

	void EmplaceFloorData(int);

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
