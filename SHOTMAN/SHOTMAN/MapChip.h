#pragma once
#include "Vec2.h"

class Vec2;

class MapChip
{
public:
	MapChip();
	~MapChip();

	void Init();
	void Update();
	void Draw();

	int GetChipNo()const { return m_chipNo; }
	float GetMapChipW()const { return m_w; }
	float GetMapChipH()const { return m_h; }

private:
	int m_chipNo;
	float m_w, m_h;
	Vec2 m_pos;
	int m_posInGraphX;
	int m_posInGraphY;
};

