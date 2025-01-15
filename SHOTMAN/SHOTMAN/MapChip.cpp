#include "MapChip.h"




MapChip::MapChip() :
	m_w(0.0f),
	m_h(0.0f),
	m_chipKind(0),
	m_pos(0.0f, 0.0f)
{
}

void MapChip::SetW(float w)
{
	m_w = w;
}

void MapChip::SetH(float h)
{
	m_h = h;
}

void MapChip::SetChipKind(int chipKind)
{
	m_chipKind = chipKind;
}

void MapChip::SetPos(Vec2 pos)
{
	m_pos = pos;
}
