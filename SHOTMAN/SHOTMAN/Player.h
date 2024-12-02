#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"
#include "Shot.h"

namespace
{
	constexpr int kShotAllNum = 3;
}

class Player : public _base2DGameObject, public _baseCollision
{
public:
	//プレイヤーのステータス
	enum PlayerState
	{
		kIdle,
		kRun,
		kJump,
		kShot,
		kDamage,
		kDeath
	};
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

	//PlayerのStateにより更新するアニメーションを変更
	void AnimUpdate(PlayerState state);
	//PlayerのStateにより再生するアニメーションを変更
	void AnimDraw(PlayerState state);

	//速度の更新(PAD入力から速度の作成)
	void VelocityUpdate();

	bool GetDir() const { return m_isDirLeft; }
	bool GetShot() const { return m_isShot; }

	PlayerState GetPlayerState();

private:
	/*グラフィックハンドル*/
	int m_graphHandleIdle;
	int m_graphHandleRun;
	int m_graphHandleJump;
	int m_graphHandleShot;
	int m_graphHandleDamage;
	int m_graphHandleDeath;

	//プレイヤーの状態
	bool m_isAction;
	bool m_isRun;
	bool m_isJump;
	bool m_isShot;

	//左を向いているか
	bool m_isDirLeft;
	
	float m_jumpSpeed;

	//現在の速度
	Vec2 m_velocity{0,0};

	PlayerState m_playerState;

	//再生するアニメーション
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;

	Shot* m_shot[kShotAllNum];
};

