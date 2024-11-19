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

	//アニメーションのフレームを数える
	int m_animFrame;

	//プレイヤーの状態
	bool m_isRun;
	bool m_isJump;

	//左を向いているか
	bool m_isDirLeft;
	
	float m_jumpSpeed;

	Vec2 m_pos;

	//再生するアニメーション
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
};

