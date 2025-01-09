#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();

};


/// <summary>
/// マップチップ構造体
/// </summary>
struct MapChip
{
	VECTOR pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};

/// <summary>
/// マップ構造体
/// </summary>
struct Map
{
	MapChip mapChips[MapWidth][MapHeight];
};
