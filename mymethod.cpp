#include "mymethod.h"
#include "math.h"

std::vector<int> MyMethod::RandomSwap(int m_min, int m_max) {
	std::vector<int> buf(m_max - m_min + 1, NULL);
	int rand, t;

	for (int i = 0; i < (signed int)buf.size(); i++) {
		buf[i] = i + m_min;
	}

	for (int i = 0; i < (signed int)buf.size() - 1; i++) {
		rand = GetRand(buf.size() - 1 - i - 1) + i;

		t = buf[rand];
		buf[rand] = buf[i];
		buf[i] = t;
	}
	return buf;
}

bool MyMethod::Lottery(double d) {
	int parent = 10000;
	int i = (int)(d * (double)parent);
	return (GetRand(parent - 1) < i);
}