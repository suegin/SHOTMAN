#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();

private:
	Vec2 pos;	// ���W
	float w, h;	// ���A����
	int chipKind;
};
