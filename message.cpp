#include "message.h"

string Message::GetText() {

	return text;
}

void Message::SetText(string m_text) {

	text = m_text;
}

void Message::AddEnter() {
	text = text + "(press enter key)";
}

bool Message::GetWaitMode() {

	return wait_mode;
}

void Message::SetWaitMode(bool m_wait_mode) {

	wait_mode = m_wait_mode;

}

Message::Message(){
	wait_mode = false;

}

Message::~Message(){}