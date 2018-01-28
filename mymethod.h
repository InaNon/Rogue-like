#ifndef DEF_MyMethod
#define DEF_MyMethod

#include "Dxlib.h"
#include <vector>

//Ã“IƒNƒ‰ƒX
class MyMethod {
private:
	MyMethod();
public:
	static std::vector<int> RandomSwap(int m_min, int m_max);
	static bool Lottery(double);

};

#endif