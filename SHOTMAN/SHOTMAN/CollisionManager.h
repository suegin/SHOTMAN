#pragma once
#include <memory>

using namespace std;

class Vec2;
class Player;
class Enemy;
class Map;

class CollisionManager
{
public:
	CollisionManager();

	void Update(Player& player, Enemy& enemy, Map& map);
	void PlayerDamageCollisionUpdate(Player& player, Enemy& enemy);
	void PlayerMapCollisionUpdate(Player& player, Map& map);

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
};

