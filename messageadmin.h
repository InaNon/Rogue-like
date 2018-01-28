#ifndef DEF_MessageAdmin
#define	DEF_MessageAdmin

#include "DxLib.h"
#include <string>

#include "define.h"

#include "modemanage.h"

class Message;


using namespace std;


class MessageAdmin {
private:
	bool wait_check_flag;
	string active_text;
	char* key;
	Message* message[MESSAGE_MAX];
	ModeManage* mode_manage;
	int push;
	int pop;
	int count;
	int last_count;

public:
	void Init(char*, ModeManage*);
	void Draw();
	void Update();
	void AnyMessage(string, bool);
	void AttackMessage(string, string, int);
	void CrushMessage(string, string);
	void ExpMessage(string, int);

	MessageAdmin();
	~MessageAdmin();
};

#endif
