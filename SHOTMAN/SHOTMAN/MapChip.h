#pragma once
#include "Vec2.h"

class MapChip
{
public:
	MapChip();

};


/// <summary>
/// �}�b�v�`�b�v�\����
/// </summary>
struct MapChip
{
	VECTOR pos;	// ���W
	float w, h;	// ���A����
	int chipKind;
};

/// <summary>
/// �}�b�v�\����
/// </summary>
struct Map
{
	MapChip mapChips[MapWidth][MapHeight];
};
