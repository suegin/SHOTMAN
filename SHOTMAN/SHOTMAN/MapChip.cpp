#include "MapChip.h"

MapChip::MapChip():
	m_top(0),
	m_bottom(0),
	m_left(0),
	m_right(0),
	m_chipNo(0),
	m_w(0.0f),
	m_h(0.0f),
	m_pos(0.0f,0.0f),
	m_posInGraphX(0),
	m_posInGraphY(0)
{
}

MapChip::~MapChip()
{
}

void MapChip::Init()
{
}

void MapChip::Update()
{
}

void MapChip::Draw()
{
}

void MapChip::SetChipNo(int chipNo)
{
	m_chipNo = chipNo;
}

void MapChip::SetMapChipW(float mapChipW)
{
	m_w = mapChipW;
}

void MapChip::SetMapChipH(float mapChipH)
{
	m_h = mapChipH;
}

void MapChip::SetPos(Vec2 pos)
{
	m_pos = pos;
}

void MapChip::SetPosInGraphX(int posInGraphX)
{
	m_posInGraphX = posInGraphX;
}

void MapChip::SetPosInGraphY(int posInGraphY)
{
	m_posInGraphY = posInGraphY;
}

void MapChip::SetTop(int top)
{
	m_top = top;
}

void MapChip::SetBottom(int bottom)
{
	m_bottom = bottom;
}

void MapChip::SetLeft(int left)
{
	m_left = left;
}

void MapChip::SetRight(int right)
{
	m_right = right;
}
