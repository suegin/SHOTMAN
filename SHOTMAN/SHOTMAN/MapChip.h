#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();
	~MapChip();

	void Init();
	void Update();
	void Draw();

	void SetChipNo(int chipNo);
	int GetChipNo()const { return m_chipNo; }
	void SetMapChipW(float mapChipW);
	void SetMapChipH(float mapChipH);
	float GetMapChipW()const { return m_w; }
	float GetMapChipH()const { return m_h; }
	void SetPos(Vec2 pos);
	Vec2 GetPos()const { return m_pos; }
	void SetPosInGraphX(int posInGraphX);
	void SetPosInGraphY(int posInGraphY);
	int GetPosInGraphX()const { return m_posInGraphX; }
	int GetPosInGraphY()const { return m_posInGraphY; }
	void SetTop(int top);
	void SetBottom(int bottom);
	void SetLeft(int left);
	void SetRight(int right);


private:
	int m_top;
	int m_bottom;
	int m_left;
	int m_right;

	int m_chipNo;
	float m_w, m_h;
	Vec2 m_pos;
	int m_posInGraphX;
	int m_posInGraphY;
};
