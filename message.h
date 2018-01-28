#ifndef DEF_Message
#define	DEF_Message

#include "DxLib.h"
#include "string.h"
#include <string>

#include "define.h"

using namespace std;


class Message {
private:
	string text;
	bool wait_mode;

public:
	string GetText();
	void SetText(string);
	void AddEnter();
	bool GetWaitMode();
	void SetWaitMode(bool);

	Message::Message();
	Message::~Message();

};

#endif
