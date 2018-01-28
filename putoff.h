#ifndef DEF_PutOff
#define DEF_PutOff

#include "define.h"

#include "selectbox.h"

class PutOff : public SelectBox {
private:

public:
	BOXNUM NextBox();

	PutOff(char*);
	~PutOff();

};


#endif