#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"
#include "Shot.h"
#include "Rect.h"

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
		kIdle = 1,
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

	Rect GetRect();

	//プレイヤーがダメージを受けるオブジェクトにぶつかった
	void OnDamage(bool isHitLeft, bool isHitRight, bool isLastHitLeft, bool isLastHitRight);

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

	//死亡した場合の処理
	void Death();

	bool GetDir()const { return m_isDirLeft; }
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetVelocity()const { return m_velocity; }
	int GetHp()const { return m_hp; }
	int GetBlinkFrameCount()const { return m_blinkFrameCount; }
	int GetDeathFrameCount()const { return m_deathFrameCount; }

	//現在のPlayerの状態を取得する
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
	//死亡時のアニメーション用
	int m_deathFrameCount;
	//プレイヤーの状態
	bool m_isJump;
	bool m_isDamage;
	bool m_isShot;

	//左を向いているか
	bool m_isDirLeft;

	//床と触れているか
	bool m_isFloor;
	
	float m_jumpSpeed;

	//現在の速度
	Vec2 m_velocity;

	PlayerState m_playerState;

	//再生するアニメーション
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;
	Animation m_animDamage;
	Animation m_animDeath;

	Shot* m_shot[kShotAllNum];
};

