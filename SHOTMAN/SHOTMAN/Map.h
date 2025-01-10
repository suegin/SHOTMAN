#pragma once

using namespace std;

class MapChip;

namespace
{
	constexpr int MapChipSize = 32;						// 一つのチップのサイズ
	constexpr int MapWidth = 1280 / MapChipSize;  // マップの横幅
	constexpr int MapHeight = 720 / MapChipSize;		// マップの縦幅
}

class Map
{
public:
	Map();

private:
	MapChip* m_pMapChips[MapWidth][MapHeight];
};

