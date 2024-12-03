#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include "Shot.h"

namespace
{
	//キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//キャラクターのヒットボックス
	constexpr int kHitBoxW = 50;
	constexpr int kHitBoxH = 70;

	//アニメーションのコマ数
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;
	constexpr int kJumpAnimNum = 10;
	constexpr int kShotAnimNum = 4;

	//アニメーションの1コマのフレーム数
	constexpr int kSingleAnimFrame = 6;
	constexpr int kShotSingleAnimFrame = 2;

	//キャラクターの移動速度
	constexpr float kSpeed = 5.0f;

	//ジャンプ処理
	constexpr float kJumpPower = -8.0f; //ジャンプの加速
	constexpr float kGravity = 0.4f;	//重力

	//ダメージを食らった後の無敵時間
	constexpr int kDmageBlinkFrame = 30;

	//プレイヤーの初期HP
	constexpr int kMacHp = 5;

	//プレイヤーの初期位置
	constexpr int kPlayerInitPosX = 100;
	constexpr int kPlayerInitPosY = 640;
}

Player::Player() :
	m_playerState(kIdle),
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1),
	m_isAction(false),
	m_isRun(false),
	m_isJump(false),
	m_isShot(false),
	m_isDirLeft(false),
	m_jumpSpeed(0.0f),
	m_playerVelocity(0,0)
{
	for (auto& shot : m_shot)
	{
		shot = new Shot();
	}
}

Player::~Player()
{
	for (auto& shot : m_shot)
	{
		delete shot;
	}
	DeleteGraph(m_graphHandleIdle);
	DeleteGraph(m_graphHandleRun);
	DeleteGraph(m_graphHandleJump);
	DeleteGraph(m_graphHandleShot);
}

void Player::Init()
{
	//待機
	m_graphHandleIdle = LoadGraph("image/Player/Idle.png");
	assert(m_graphHandleIdle != -1);
	//移動
	m_graphHandleRun = LoadGraph("image/Player/Run.png");
	assert(m_graphHandleRun != -1);
	//ジャンプ
	m_graphHandleJump = LoadGraph("image/Player/Jump.png");
	assert(m_graphHandleJump);
	//発射
	m_graphHandleShot = LoadGraph("image/Player/Shot.png");
	assert(m_graphHandleShot);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight,kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, kSingleAnimFrame, kJumpAnimNum);
	m_animShot.Init(m_graphHandleShot, kGraphWidth, kGraphHeight, kShotSingleAnimFrame, kShotAnimNum);

	//プレイヤーのの位置の初期化
	m_pos.X = kPlayerInitPosX;
	m_pos.Y = kPlayerInitPosY;
}

void Player::Update()
{
	//現在のプレイヤーのステートを取得
	m_playerState = GetPlayerState();

	//ステートによってアニメーションの変更
	AnimUpdate(m_playerState);

	/*平行移動*/
	//速度の更新
	PlayerVelocityUpdate();

	//移動処理
	m_pos += m_playerVelocity;

	//ジャンプ

	
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (!m_isJump)
		{
			m_isJump = true;
			m_isAction = true;
			m_jumpSpeed = kJumpPower;
		}
	}

	if (m_isJump)
	{
		m_pos.Y += m_jumpSpeed;
		m_jumpSpeed += kGravity;
		if (m_pos.Y >= 640)
		{
			m_isJump = false;
			m_isAction = false;
			m_jumpSpeed = 0.0f;
			m_pos.Y = 640;
			m_animJump.ResetAnimFrame();
		}
	}

	for (int i = 0; i < kShotAllNum; ++i)
	{
		m_shot[i]->Update();
	}

	BulletUpdate();
}

void Player::Draw()
{
#if _DEBUG
	if (m_isDirLeft)
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5 + 10, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5, m_pos.Y, 0xffffff, false);
	}
	else
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5 - 10, m_pos.Y, 0xffffff, false);
	}
	
#endif // _DEBUG

	

	//アニメーション再生
	AnimDraw(m_playerState);
}

void Player::AnimUpdate(PlayerState state)
{
	switch (m_playerState)
	{
	case Player::kIdle:
		m_animIdle.Update();
		break;
	case Player::kRun:
		m_animRun.Update();
		break;
	case Player::kJump:
		m_animJump.Update();
		break;
	case Player::kShot:
		m_animShot.Update();
		break;
	case Player::kDamage:
		break;
	case Player::kDeath:
		break;
	default:
		break;
	}
}

void Player::AnimDraw(PlayerState state)
{
	switch (m_playerState)
	{
	case Player::kIdle:
		m_animIdle.Play(m_pos, m_isDirLeft);
		break;
	case Player::kRun:
		m_animRun.Play(m_pos, m_isDirLeft);
		break;
	case Player::kJump:
		m_animJump.Play(m_pos, m_isDirLeft);
		break;
	case Player::kShot:
		m_animShot.Play(m_pos, m_isDirLeft);
		break;
	case Player::kDamage:
		break;
	case Player::kDeath:
		break;
	default:
		break;
	}
}

void Player::PlayerVelocityUpdate()
{
	//PADフラグチェック
	bool IsRightPress = Pad::IsPress(PAD_INPUT_RIGHT);
	bool IsLeftPress = Pad::IsPress(PAD_INPUT_LEFT);

	//右速度
	if (IsRightPress)
	{
		m_playerVelocity.X = kSpeed;
		m_isDirLeft = false;
	}
	//左速度
	if (IsLeftPress)
	{
		m_playerVelocity.X = -kSpeed;
		m_isDirLeft = true;
	}
	//押されていない
	if (!IsRightPress && !IsLeftPress)
	{
		m_playerVelocity.X = 0;
	}
}

void Player::BulletUpdate()
{
	bool isShotTrigger = Pad::IsTrigger(PAD_INPUT_1);
	bool isShot = false;

	//弾の生成
	if (isShotTrigger)
	{
		isShot = true;
		for (int i = 0; i < kShotAllNum; ++i)
		{
			if (!m_shot[i]->GetFrag())
			{
				m_shot[i]->SetFrag(isShot);

				m_shot[i]->SetPos(Vec2(m_pos.X + 15.0f, m_pos.Y));
				m_shot[i]->SetPos(Vec2(m_pos.X, m_pos.Y - kGraphHeight * 0.5f + 25));

				if (m_isDirLeft)
				{
					m_shot[i]->SetDir(m_isDirLeft);
				}

				break;
			}
		}
	}

	//弾の位置を更新して表示
	for (int i = 0; i < kShotAllNum; ++i)
	{
		if (m_shot[i]->GetFrag())
		{
			m_shot[i]->Draw();
		}
	}
}

Player::PlayerState Player::GetPlayerState() const 
{
	PlayerState state = kIdle;

	//フラグ出し
	bool isJump = (m_pos.Y != 640);//ジャンプしているか
	bool isRun = (m_playerVelocity.X != 0);//プレイヤーが移動しているか

	//待機
	if (!isRun && !isJump) { return PlayerState::kIdle; }
	//Run
	if (isRun && !isJump) { return PlayerState::kRun; }
	//Jump
	if (isJump) { return PlayerState::kJump; }

	return PlayerState::kIdle;
}
