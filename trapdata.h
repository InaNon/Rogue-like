#ifndef DEF_Trapdata
#define DEF_Trapdata
#include "define.h"
#include <string>

class Camera;

class TrapData {
protected:
	int graphichandle;
public:

	static const enum TRAPTYPE {
		NEEDLE, //é¿ëï
		WEAPON_WARP,//é¿ëïÅ@by ina
		NO_MOVE,
		BOMB, //é¿ëï
		POISON,
		HUNGER, //é¿ëï
		HALLUC,
		WARP, //é¿ëï
		MANZI,
		BUTTON,
		SURPRISED,
		TRAPTYPE_NUM,
	} trap_type;

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

private:
	TRAPTYPE trapType;
};



#endif
