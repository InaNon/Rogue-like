#include "celldata.h"


CellData::CellData() {
	celltype = NONE_CELLTYPE;

	movef = false;
	slantmovef = false;
	stepf = false;
	roomf = false;
	trapf = false;
	shopf = false;
};
CellData::CellData(const CellData &rhs) {
	/*
	celltype = NONE_CELLTYPE;

	movef = false;
	slantmovef = false;
	stepf = false;
	roomf = false;
	trapf = false;
	shopf = false;
	*/
};

CellData::~CellData() {
};

CELLTYPE CellData::GetCellType() {
	return celltype;
}

bool CellData::GetMovef() {
	return movef;
}
bool CellData::GetSlantMovef() {
	return slantmovef;
}
bool CellData::GetStepf() {
	return stepf;
}
bool CellData::GetRoomf() {
	return roomf;
}
bool CellData::GetTrapf() {
	return trapf;
}
bool CellData::GetShopf() {
	return shopf;
}

bool CellData::GetSpawnf() {
	return movef && !stepf && roomf && !trapf && !shopf;
}


void CellData::CellDataInit(CELLTYPE m_celltype, bool m_movef, bool m_slantmovef, bool m_stepf, bool m_trapf) {
	CellDataInit(m_celltype, m_movef, m_slantmovef, m_stepf, false , m_trapf);
}

void CellData::CellDataInit(CELLTYPE m_celltype, bool m_movef, bool m_slantmovef, bool m_stepf, bool m_roomf, bool m_trapf) {
	celltype = m_celltype;
	movef = m_movef;
	slantmovef = m_slantmovef;
	stepf = m_stepf;
	roomf = m_roomf;
	trapf = m_trapf;
}

void CellData::SetCellType(CELLTYPE m_celltype) {
	celltype = m_celltype;
}

void CellData::SetMovef(bool m_movef) {
	movef = m_movef;
}
void CellData::SetSlantMovef(bool m_slantmovef) {
	slantmovef = m_slantmovef;
}
void CellData::SetStepf(bool m_stepf) {
	stepf = m_stepf;
}
void CellData::SetRoomf(bool m_roomf) {
	roomf = m_roomf;
}
void CellData::SetTrapf(bool m_trapf) {
	trapf = m_trapf;
}
void CellData::SetShopf(bool m_shopf) {
	shopf = m_shopf;
}