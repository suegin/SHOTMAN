#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();

private:
	Vec2 pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};
