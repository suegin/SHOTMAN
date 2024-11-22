#pragma once
#include "_base2DGameObject.h"
#include "Vec2.h"

namespace
{
	constexpr int kShotAllNum = 3;
}

class Player;

class Shot : public _base2DGameObject
{
public:
	Shot(Player& player);
	~Shot();

	void Init();
	void Update();
	void Draw();

	bool m_shotFrag;

private:
	int m_graphHandleShot;

	Player& m_player;
};

