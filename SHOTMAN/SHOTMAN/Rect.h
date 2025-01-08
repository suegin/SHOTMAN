#pragma once
#include "Vec2.h"

//��`�̃f�[�^�Ǘ�
class Rect
{
public:
	Rect();

	float GetWidth() const { return right - left; }
	float GetHeight() const { return bottom - top; }

	//�e���W�擾
	Vec2 GetCenter();

	//������(�d�Ȃ�)����
	bool isCol(const Rect& rect);

	void SerTopLeftSize(Vec2 posTopLeft, Vec2 size);

	float top;
	float bottom;
	float left;
	float right;
};

