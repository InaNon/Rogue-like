#ifndef DEF_SelectBox
#define DEF_SelectBox

#include "DxLib.h"
#include "String"
#include "define.h"
#include "listbox.h"

using namespace std;

class ItemData;

//項目を羅列するボックスの中でも選択が可能なボックス
class SelectBox : public ListBox {

protected:
	int cursor;
	bool first_push_up_flag;
	bool first_push_down_flag;
	int up_count;
	int down_count;
	int long_up_count;
	int long_down_count;


public:
	void Draw();
	void Update();
	void ResetCursor();
	int GetCursor();

	SelectBox();
	~SelectBox();

};

#endif