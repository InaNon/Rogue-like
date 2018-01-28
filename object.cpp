#include "object.h"


void Object::Spawn(int spawn_x, int spawn_y) {

	exist = true;

	map_x = spawn_x;
	map_y = spawn_y;

	x = 16 + CHIP_X_SIZE * map_x;
	y = 16 + CHIP_Y_SIZE * map_y;

}


bool Object::GetExist() {

	return exist;
}


void Object::SetExist(bool new_exist) {

	exist = new_exist;
}


string Object::GetObjectName() {

	return object_name;
}


void Object::SetObjectName(string m_object_name) {

	object_name = m_object_name;
}


int Object::GetX() {

	return x;

}


int Object::GetY() {

	return y;

}


int Object::GetMAPX() {

	return map_x;

}


int Object::GetMAPY() {

	return map_y;

}





Object::Object(){
	exist = false;
	map_x = 0;
	map_y = 0;
}

Object::~Object(){}
