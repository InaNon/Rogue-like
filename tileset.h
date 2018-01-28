#ifndef DEF_TileSet
#define DEF_TileSet

#include "define.h"
#include <string>
#include <vector>

class TileImage;

class TileSet {
public:
	static const enum TILETYPE {
		FLOOR,
		WALL,
		WALL_WRAPPER,
		WALL_FOUND,
		WALL_MINI,
		HOLE,
		HOLE_WRAPPER,
		HOLE_FOUND,
		HOLE_MINI,
		STEP_FLOOR,
		STEP_WALL,
		SHOP_FLOOR,
		TILETYPE_NUM,
	} tile_type; //tile_image�̑�ꎟ���w��p

	static const int VAR_NUM;

	static const std::string DIR_NAME;
	static const std::string EXTENSION;
	
private:

	std::vector<std::vector<TileImage*>> tile_image;
	//���v�f = TileType,���v�f = ���

public:

	TileSet();
	TileSet(const TileSet &rhs);
	~TileSet();

	void Init(std::string);

	TileImage* GetTileImage(TileSet::TILETYPE, int);
	TileImage* GetTileImage(int, int);

	//�^�C���摜��ǂ݂��ށB
	void LoadTileImageAll(std::string);

	bool isWrapperWall();
	bool isWrapperHole();

protected:
	bool CompileTileImage(std::string, TileImage**);
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