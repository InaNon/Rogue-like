#include "putoff.h"

BOXNUM PutOff::NextBox() { return NOBOX; }

PutOff::PutOff(char* m_key) {

	content[0] = "‚Í‚¸‚·";
	content[1] = "‚¹‚Â‚ß‚¢";

	box_up_left_x = 300;
	box_up_left_y = 200;
	box_down_right_x = 450;
	box_down_right_y = 350;
	content_num = 2;

	key = m_key;

}
PutOff::~PutOff() {}