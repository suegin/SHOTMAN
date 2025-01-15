#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();

	float GetW()const { return m_w; }
	void SetW(float w);
	float GetH()const { return m_h; }
	void SetH(float h);
	int GetChipKind()const { return m_chipKind; }
	void SetChipKind(int chipKind);
	Vec2 GetPos()const { return m_pos; }
	void SetPos(Vec2 pos);

private:
	float m_w, m_h;	// •A‚‚³
	int m_chipKind;
	Vec2 m_pos;	// À•W
};
