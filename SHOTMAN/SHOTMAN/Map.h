#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "MapChip.h"

using namespace std;

namespace
{
	constexpr int kMapChipSize = 32;						// ��̃`�b�v�̃T�C�Y
	constexpr int kMapWidth = 1280 / kMapChipSize;  // �}�b�v�̉���
	constexpr int kMapHeight = 752 / kMapChipSize;		// �}�b�v�̏c��
}

class Map
{
public:
	
	void Init();
	void Draw();

	bool IsCol(Rect rect, Rect& chipRect);

private:
	MapChip m_mapChips[kMapWidth][kMapHeight];
};

