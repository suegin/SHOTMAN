#pragma once
#include "_base2DGameObject.h"
#include "_baseEnemy.h"

class Enemy : public _base2DGameObject, public _baseEnemy
{
public:
	Enemy();
	~Enemy() override;

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	int m_speed;
};

