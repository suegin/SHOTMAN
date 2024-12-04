#pragma once
#include "Vec2.h"

class Player;
class Enemy;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();
	void Update();
	void Draw();

	bool GetIsCollision()const { return m_isCol; }

private:
	bool m_isCol;

	Player* m_pPlayer;
	Enemy* m_pEnemy;
};

