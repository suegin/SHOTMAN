#include "Rect.h"

Rect::Rect():
	top(0),
	bottom(0),
	left(0),
	right(0)
{
}

Vec2 Rect::GetCenter()
{
	return Vec2((left + right)/2, (top + bottom)/2);
}

bool Rect::isCol(const Rect& rect)
{
	if (top > rect.bottom) return false;
	if (bottom < rect.top) return false;
	if (left > rect.right) return false;
	if (right < rect.left) return false;

	return true;
}

void Rect::SerTopLeftSize(Vec2 posTopLeft, Vec2 size)
{
	top = posTopLeft.Y;
	bottom = posTopLeft.Y + size.Y;
	left = posTopLeft.X;
	right = posTopLeft.X + size.X;
}
