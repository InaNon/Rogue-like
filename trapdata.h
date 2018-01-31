#ifndef DEF_Trapdata
#define DEF_Trapdata
#include "define.h"
#include <string>

class Camera;

class TrapData {
protected:
	TRAPTYPE traptype;
	int graphichandle;

public:

	TrapData();
	TrapData(const TrapData &rhs);

	~TrapData();

	void LoadFile(std::string,int,int);

	void Draw(Camera*,int,int);

	void TrapDataInit(TRAPTYPE);

	TRAPTYPE GetTrapType();
	int GetGraphicHandle();

	void SetGraphicHandle(int);
	void SetTrapType(TRAPTYPE);

};



#endif
