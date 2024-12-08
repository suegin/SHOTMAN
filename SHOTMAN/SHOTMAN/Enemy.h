#pragma once
#include "_base2DGameObject.h"
#include "_baseEnemy.h"

class Enemy : public _base2DGameObject/*, public _baseEnemy*/
{
public:
	Enemy();
	~Enemy() override;

	void Init() override;
	void Update() override;
	void Draw() override;

	Vec2 GetPos()const { return m_pos; }

	//敵の情報を取得する
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();

private:
	Vec2 m_velocity;
};

