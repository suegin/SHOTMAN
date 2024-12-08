#pragma once
#include "Vec2.h"

#include "Player.h"
#include "Enemy.h"

class Player;
class Enemy;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();
	void Update(Player& player, Enemy& enemy);
	void Draw();

	bool GetIsHitLeft()const { return m_isHitLeft; }
	bool GetIsHitRight()const { return m_isHitRight; }

private:
	bool m_isCol;
	bool m_isHitLeft;
	bool m_isHitRight;
	bool m_isHitTop;
	bool m_isHitBottom;
	bool m_isLastHitLeft;
	bool m_isLastHitRight;
};

