#ifndef DEF_Menu
#define DEF_Menu

#include "DxLib.h"
#include "String"
#include "selectbox.h"
#include "define.h"


//�I����������{�b�N�X�̒��ł��A���j���[��ʂɂ���
class Menu : public SelectBox {
private:

public:
	BOXNUM NextBox();
	void SetItemData();

	Menu(char*);
	~Menu();

};

#endif