#ifndef DEF_Camera
#define DEF_Camera

class Unit;

class Camera {
protected:
	/*ƒJƒƒ‰¶ãÀ•W*/
	int x; 
	int y;
	int sizex;
	int sizey;

public:

	Camera();
	~Camera();

	void Init(int, int);

	int GetX();
	int GetY();
	int GetSizeX();
	int GetSizeY();

	void SetX(int);
	void SetY(int);
	void SetSizeX(int);
	void SetSizeY(int);

	int GetDrawX(int m_x);
	int GetDrawY(int m_y);

	void UpdatePlayerCenter(Unit*);

	bool GetDrawf(int, int, int, int);
	bool GetDrawf_ul(int, int, int, int);

};

#endif