#ifndef DEF_ListBox
#define DEF_ListBox

#include "DxLib.h"
#include "String"
#include "define.h"

using namespace std;

class ItemData;

class ListBox {

protected:
	int box_up_left_x;
	int box_up_left_y;
	int box_down_right_x;
	int box_down_right_y;
	int content_num;
	string content[MAX_CONTENT_NUM];
	char* key;


public:
	virtual void Draw();
	virtual void Update();
	virtual void ResetCursor();
	virtual BOXNUM NextBox() = 0;
	virtual int GetCursor();
	virtual void SetItemData(ItemData*);
	virtual void SetText();
	virtual void ResetContent();

	ListBox();
	~ListBox();

};

#endif