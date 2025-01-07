#pragma once

#include "Player.h"
#include "Enemy.h"

class Vec2;
class Player;
class Enemy;
class Map;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();
	void Update();
	void PlayerDamageCollisionUpdate();
	void PlayerMapCollisionUpdate(Map& map);
	void Draw();

	bool GetIsHitLeft()const { return m_isHitLeft; }
	bool GetIsHitRight()const { return m_isHitRight; }

private:
	bool m_isDamageCol;
	bool m_isHitLeft;
	bool m_isHitRight;
	bool m_isHitTop;
	bool m_isHitBottom;
	bool m_isLastHitLeft;
	bool m_isLastHitRight;

	Player m_player;
	Enemy m_enemy;
};

