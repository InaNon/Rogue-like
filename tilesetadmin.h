#ifndef DEF_TileSetAdmin
#define DEF_TileSetAdmin

#include "define.h"
#include "Dxlib.h"
#include <vector>

class TileSet;
class TileSetAdmin {
public:
	static const int TILE_SET_NUM;

private:
	std::vector<TileSet*> tile_set;
	//���v�f�͑���
public:

	TileSetAdmin();
	~TileSetAdmin();

	void Init();

	void GraphLoad();

	//tottyuu
	//void MakeGraphic();
	//void SetAutoCellGrahic(int, int, CELLTYPE);
	//void SetCellGrahic(int, int, CELLTYPE);

	TileSet* GetTileSet(int);
};

#endif


/*
�^�C���̎��

�E������
��

�ǂ̃��b�p�[
�ǂ̓y��
1�}�X�p��

���̃��b�p�[
���̓y��
1�}�X�p��

���K�i
�ǊK�i

�E����
�X�̏�

���b�p�[�Ɠy��̃Z�b�g�Ȃ̂��A�������ނ̉摜�����Ȃ����̂ǂ���Ȃ̂��͕�����Ȃ��B
��҂̏ꍇ�͂P�}�X�p�̂�������Ă��\��Ȃ�
��L�̂��̂��Z�b�g�ɂ��Ċi�[���Ă����N���X���~�����B

�I�[�g�^�C�����ǂ����͕�����Ȃ��B
�p���ɂ���ĊǗ����邱�Ƃɂ��A�t���O�Ŕ��ʂ�����A���ʖ����\�b�h�Ȃǂ��g��

*/