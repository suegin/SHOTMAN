#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"

class Player : public _base2DGameObject, public _baseCollision
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	/*グラフィックハンドル*/
	int m_graphHandleIdle;
	int m_graphHandleRun;
	int m_graphHandleJump;
	int m_graphHandleShot;
	int m_graphHandleDamage;
	int m_graphHandleDeath;

	int m_animFrame;

	int m_state;

	bool m_isRun;

	bool m_isDirLeft;

	Vec2 m_pos;
	Animation m_animIdle;
	Animation m_animRun;
};

