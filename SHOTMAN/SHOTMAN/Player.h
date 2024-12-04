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

	//プレイヤーの情報を取得する
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	//プレイヤーがダメージを受けるオブジェクトにぶつかった
	void OnDamage();

	//PlayerのStateにより更新するアニメーションを変更
	void AnimUpdate(PlayerState state);
	//PlayerのStateにより再生するアニメーションを変更
	void AnimDraw(PlayerState state);

	//プレイヤーの速度の更新(PAD入力から速度の作成)
	void PlayerVelocityUpdate();
	//ジャンプの処理(PAD入力から)
	void JumpUpdate();
	//弾の更新(PAD入力から生成、更新)
	void BulletUpdate();
	void BulletDraw();

	bool GetDir() const { return m_isDirLeft; }

	PlayerState GetPlayerState()const;

private:
	/*グラフィックハンドル*/
	int m_graphHandleIdle;
	int m_graphHandleRun;
	int m_graphHandleJump;
	int m_graphHandleShot;
	int m_graphHandleDamage;
	int m_graphHandleDeath;
	//プレイヤーHP
	int m_hp;
	//ダメージを受けた際の無敵と点滅用
	int m_blinkFrameCount;

	bool m_isJump;

	//左を向いているか
	bool m_isDirLeft;
	
	float m_jumpSpeed;

	//現在の速度
	Vec2 m_velocity;

	PlayerState m_playerState;

	//再生するアニメーション
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;

	Shot* m_shot[kShotAllNum];
};

