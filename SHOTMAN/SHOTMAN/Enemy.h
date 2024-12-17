#pragma once
#include "_base2DGameObject.h"
#include "_baseEnemy.h"
#include "Animation.h"

class Enemy : public _baseEnemy
{
public:
	Enemy();
	~Enemy() override;

	void Init() override;
	void Update() override;
	void Draw() override;

	Vec2 GetPos()const { return m_pos; }

	//“G‚Ìî•ñ‚ğæ“¾‚·‚é
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();

private:
	Vec2 m_velocity;
	bool m_isLeft;

	int m_graphHandle;

	Animation m_anim;
};

