#ifndef DEF_Menu
#define DEF_Menu

#include "DxLib.h"
#include "String"
#include "selectbox.h"
#include "define.h"


//選択肢があるボックスの中でも、メニュー画面について
class Menu : public SelectBox {
private:

public:
	BOXNUM NextBox();
	void SetItemData();

	Menu(char*);
	~Menu();

};

#endif