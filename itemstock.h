#ifndef DEF_ItemStock
#define DEF_ItemStock

class ItemData;
 
class ItemStock {
private:
	ItemData* item_data;

	bool exist;
	bool equiped;

public:
	ItemData* GetItemData();
	void SetItemData(ItemData*);
	bool GetExist();
	void SetExist(bool);
	bool GetEquiped();
	void SetEquiped(bool);


	ItemStock();
	~ItemStock();

};


#endif