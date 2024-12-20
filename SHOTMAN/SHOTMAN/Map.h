#pragma once
#include "PlatinumLoader.h"
#include "MapChip.h"
#include "Vec2.h"

namespace
{
	constexpr int kMapChipSize = 16;
	constexpr int kMapWidth = 416;
	constexpr int kMapHeight = 272;
	const int MapGraphSize = 256;
}

class Map
{
public:
	Map();
	~Map();

	void Init();
	void Update();
	void Draw();

private:
	MapChip m_mapChips[kMapWidth][kMapHeight];
	int m_graphHandle;
	PlatinumLoader m_loader;
	Vec2 m_vec2;
};

