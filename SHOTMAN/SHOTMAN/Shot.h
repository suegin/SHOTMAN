#pragma once

#include "Vec2.h"

namespace
{
	constexpr int kShotAllNum = 3;
}

class Shot
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

private:
	int m_graphHandleShot;
	bool m_shotFrag[kShotAllNum];
};

