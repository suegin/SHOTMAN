#pragma once
#include "Enemy.h"
class FlyEnemy : public Enemy
{
public:
	FlyEnemy();
	~FlyEnemy();

	void Init();
	void Update();
	void Draw();

private:

};