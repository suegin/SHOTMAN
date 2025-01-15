#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "MapChip.h"

using namespace std;

namespace
{
	constexpr int kMapChipSize = 32;						// 一つのチップのサイズ
	constexpr int kMapWidth = 1280 / kMapChipSize;  // マップの横幅
	constexpr int kMapHeight = 752 / kMapChipSize;		// マップの縦幅
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

