#include "trapdata.h"
#include "camera.h"
#include "DxLib.h"

TrapData::TrapData() {
}
TrapData::TrapData(const TrapData &rhs) {
}
TrapData::~TrapData() {
}

void TrapData::TrapDataInit(TRAPTYPE m_traptype) {
	trapType = m_traptype;
}

void TrapData::Draw(Camera* m_camera,int m_cx,int m_cy) {
	int m_x = m_camera->GetDrawX(m_cx*CHIP_X_SIZE);
	int m_y = m_camera->GetDrawY(m_cy*CHIP_Y_SIZE);


	if (!m_camera->GetDrawf(m_cx*CHIP_X_SIZE + CHIP_X_SIZE / 2, m_cy*CHIP_Y_SIZE + CHIP_Y_SIZE / 2, CHIP_X_SIZE, CHIP_Y_SIZE)) {
		return;
	}
	DrawExtendGraph(m_x, m_y, m_x + CHIP_X_SIZE, m_y + CHIP_Y_SIZE, graphichandle, false);
}

void TrapData::LoadFile(std::string m_filename, int m_x, int m_y) {
	int handle = LoadGraph(m_filename.c_str());
	graphichandle = DerivationGraph(m_x*CHIP_X_SIZE, m_y*CHIP_Y_SIZE, CHIP_X_SIZE, CHIP_Y_SIZE, handle);
}




/*ゲッター*/
TrapData::TRAPTYPE TrapData::GetTrapType() { return trapType; }
int TrapData::GetGraphicHandle() { return graphichandle; }

/*セッター*/
void TrapData::SetGraphicHandle(int m_graphichandle) { graphichandle = m_graphichandle; }
void TrapData::SetTrapType(TRAPTYPE m_traptype) { trapType = m_traptype; }
