#ifndef DEF_Camera
#define DEF_Camera

class Unit;

class Camera {
protected:
	/*ƒJƒƒ‰’†S*/
	int x; 
	int y;
	int sizex;
	int sizey;
	int mapzoom;

public:

	Camera();
	~Camera();

	void Init(int, int);

	int GetX();
	int GetY();
	int GetSizeX();
	int GetSizeY();
	int GetMapZoom();

	void SetX(int);
	void SetY(int);
	void SetSizeX(int);
	void SetSizeY(int);
	void SetMapZoom(int);

	int GetDrawX(int m_x);
	int GetDrawY(int m_y);

	void UpdatePlayerCenter(Unit*);

	bool GetDrawf(int, int, int, int);
	bool GetDrawf_ul(int, int, int, int);

};

#endif