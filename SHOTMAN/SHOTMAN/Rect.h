#pragma once
#include "Vec2.h"

//矩形のデータ管理
class Rect
{
public:
	Rect();

	float GetWidth() const { return right - left; }
	float GetHeight() const { return bottom - top; }

	//各座標取得
	Vec2 GetCenter();

	//当たり(重なり)判定
	bool isCol(const Rect& rect);

	void SerTopLeftSize(Vec2 posTopLeft, Vec2 size);

	float top;
	float bottom;
	float left;
	float right;
};

