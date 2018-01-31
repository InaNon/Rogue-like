#include "camera.h"
#include "define.h"
#include "unit.h"

Camera::Camera() {
};
Camera::~Camera() {
};
void Camera::Init(int m_sizex, int m_sizey) {
	x = 0;
	y = 0;
	sizex = m_sizex;
	sizey = m_sizey;
}


int Camera::GetX() { return x; };
int Camera::GetY() { return y; };
int Camera::GetSizeX() { return sizex; };
int Camera::GetSizeY() { return sizey; };

void Camera::SetX(int m_x) { x = m_x; };
void Camera::SetY(int m_y) { y = m_y; };
void Camera::SetSizeX(int m_sizex) { sizex = m_sizex; };
void Camera::SetSizeY(int m_sizey) { sizey = m_sizey; };

void Camera::UpdatePlayerCenter(Unit* m_unit) {
	
	if (m_unit->GetMoveFlag() != ATTACK) {
		x = m_unit->GetX() - sizex / 2;
		y = m_unit->GetY() - sizey / 2;
	}
	else {
		x = m_unit->GetMAPX()*CHIP_X_SIZE + CHIP_X_SIZE / 2 - sizex / 2;
		y = m_unit->GetMAPY()*CHIP_Y_SIZE + CHIP_Y_SIZE / 2 - sizey / 2;
	}
	
	if (DEBUG_MODE_CAMERA) {
		x = 0;
		y = 0;
	}

}

bool Camera::GetDrawf(int m_x, int m_y, int m_sizex, int m_sizey) {
	//m_x、m_yは、描画対象の中心を示す
	if (
		x < m_x + m_sizex/2 &&
		y < m_y + m_sizey/2 &&
		x + sizex > m_x - m_sizex / 2 &&
		y + sizey > m_y - m_sizey / 2
		) {
		return true;
	}
	return false;
}
bool Camera::GetDrawf_ul(int m_x, int m_y, int m_sizex, int m_sizey) {
	//m_x、m_yは、描画対象の左上を示す
	if (
		x < m_x + m_sizex &&
		y < m_y + m_sizey &&
		x + sizex > m_x &&
		y + sizey > m_y 
		) {
		return true;
	}
	return false;
}



int Camera::GetDrawX(int m_x) { return m_x - x; };
int Camera::GetDrawY(int m_y) { return m_y - y; };