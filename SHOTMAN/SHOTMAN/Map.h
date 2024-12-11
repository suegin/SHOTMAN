#pragma once

namespace
{
	constexpr int kMapChipSize = 16;
	constexpr int kMapWidth = 128;
	constexpr int kMapHeight = 139;
	const int MapGraphSize = 256;
}

class PlatinumLoader;
class MapChip;

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
};

