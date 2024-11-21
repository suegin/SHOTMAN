#pragma once
#include "_base2DGameObject.h"
#include "Vec2.h"

namespace
{
	constexpr int kShotAllNum = 3;
}

class Shot : public _base2DGameObject
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

	bool m_shotFrag;

private:
	int m_graphHandleShot;
};

