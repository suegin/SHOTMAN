#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include "Shot.h"
#include "CollisionManager.h"

namespace
{
	//キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//キャラクターのヒットボックス
	constexpr int kHitBoxW = 45;
	constexpr int kHitBoxH = 65;
	//ヒットボックスの調整
	constexpr int kAdjustmentHitBox = 10;

	//アニメーションのコマ数
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;
	constexpr int kJumpAnimNum = 10;
	constexpr int kShotAnimNum = 4;
	constexpr int kDamageAnimNum = 5;

	//アニメーションの1コマのフレーム数
	constexpr int kSingleAnimFrame = 6;
	constexpr int kShotSingleAnimFrame = 2;

	//キャラクターの移動速度
	constexpr float kSpeed = 5.0f;

	//ジャンプ処理
	constexpr float kJumpPower = -8.0f; //ジャンプの加速
	constexpr float kGravity = 0.4f;	//重力

	//ダメージを食らった後の無敵時間
	constexpr int kDamageBlinkFrame = 30;

	//ダメージを食らった後の吹き飛ばされる速度
	constexpr int kDamageAction = 3;

	//ダメージアクションを徐々に緩める力
	constexpr int kDamageActionControl = 0.2;

	//プレイヤーの初期HP
	constexpr int kMaxHp = 5;

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
	m_hp(kMaxHp),
	m_blinkFrameCount(0),
	m_isJump(false),
	m_isDamage(false),
	m_isShot(false),
	m_isDirLeft(false),
	m_jumpSpeed(0.0f),
	m_velocity(0.0f,0.0f)
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
	//被弾
	m_graphHandleDamage = LoadGraph("image/Player/Damage.png");
	assert(m_graphHandleDamage);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight,kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, kSingleAnimFrame, kJumpAnimNum);
	m_animShot.Init(m_graphHandleShot, kGraphWidth, kGraphHeight, kShotSingleAnimFrame, kShotAnimNum);
	m_animDamage.Init(m_graphHandleDamage, kGraphWidth, kGraphHeight, kSingleAnimFrame, kDamageAnimNum);

	//プレイヤーの位置の初期化
	m_pos.X = kPlayerInitPosX;
	m_pos.Y = kPlayerInitPosY;
}

void Player::Update()
{
	//無敵時間の更新
	--m_blinkFrameCount;
	if (m_blinkFrameCount < 0)
	{
		m_blinkFrameCount = 0;
	}

	GetPlayerState();

	//現在のプレイヤーのステートを取得
	m_playerState = GetPlayerState();

	//ジャンプ
	JumpUpdate();

	//移動処理
	m_pos += m_velocity;

	//弾の更新
	BulletUpdate();

	//Shotの更新
	for (int i = 0; i < kShotAllNum; ++i)
	{
		m_shot[i]->Update();
	}

	if (m_playerState == kDamage)
	{
		return;
	}

	//ステートによってアニメーションの変更
	AnimUpdate(m_playerState);

	/*平行移動*/
	//速度の更新
	PlayerVelocityUpdate();\
}

void Player::Draw()
{
	BulletDraw();

	//点滅処理
	if (m_blinkFrameCount / 2 % 2)
	{
		return;
	}
#if _DEBUG
	if (m_isDirLeft)
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5 + kAdjustmentHitBox, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5, m_pos.Y, 0xffffff, false);
	}
	else
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5 - kAdjustmentHitBox, m_pos.Y, 0xffffff, false);
	}
	
#endif // _DEBUG

	//アニメーション再生
	AnimDraw(m_playerState);
}

float Player::GetLeft() const
{
	if (m_isDirLeft)
	{
		return (m_pos.X - (kHitBoxW * 0.5 - kAdjustmentHitBox));
	}
	else
	{
		return (m_pos.X - (kHitBoxW * 0.5));
	}
	
}

float Player::GetTop() const
{
	return (m_pos.Y - kHitBoxH);
}

float Player::GetRight() const
{
	if (m_isDirLeft)
	{
		return (m_pos.X + (kHitBoxW * 0.5));
	}
	else
	{
		return (m_pos.X + (kHitBoxW * 0.5) - kAdjustmentHitBox);
	}
	
}

float Player::GetBottom() const
{
	return m_pos.Y;
}

void Player::OnDamage(bool isHitLeft, bool isHitRight, bool isLastHitLeft, bool isLastHitRight)
{
	if (m_blinkFrameCount > 0)
	{
		return;
	}

	m_blinkFrameCount = kDamageBlinkFrame;

	if (isHitLeft && !isLastHitLeft)
	{
		m_velocity.X = 0;
		m_velocity.X = kDamageAction;
	}
	if (isHitRight && !isLastHitRight)
	{
		m_velocity.X = 0;
		m_velocity.X = -kDamageAction;
	}

	if (m_blinkFrameCount == 0)
	{
		return;
	}
	
	--m_hp;
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
		m_animDamage.Update();
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
		m_animDamage.Play(m_pos,m_isDirLeft);
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
		m_velocity.X = kSpeed;
		m_isDirLeft = false;
	}
	//左速度
	if (IsLeftPress)
	{
		m_velocity.X = -kSpeed;
		m_isDirLeft = true;
	}
	//押されていない
	if (!IsRightPress && !IsLeftPress)
	{
		m_velocity.X = 0;
	}
}

void Player::JumpUpdate()
{
	bool isJumpTrigger = Pad::IsTrigger(PAD_INPUT_2);
	bool isJump = (PlayerState::kJump == m_playerState);

	if (isJumpTrigger)
	{
		if (!isJump)
		{
			isJump = true;
			m_velocity.Y = kJumpPower;
		}
	}

	if (isJump)
	{
		m_velocity.Y += kGravity;
		if (m_pos.Y >= 641)
		{
			isJump = false;
			m_velocity.Y = 0.0f;
			m_pos.Y = 640;
			m_animJump.ResetAnimFrame();
		}
	}
}

void Player::BulletUpdate()
{
	bool isShotTrigger = Pad::IsTrigger(PAD_INPUT_1);

	//弾の生成
	if (isShotTrigger)
	{
		m_isShot = true;
		for (int i = 0; i < kShotAllNum; ++i)
		{
			if (!m_shot[i]->GetFrag())
			{
				m_shot[i]->SetShotFrag(m_isShot);

				m_shot[i]->SetPos(Vec2(m_pos.X + kHitBoxW * 0.5, m_pos.Y - kGraphHeight * 0.5f + 25));

				if (m_isDirLeft)
				{
					m_shot[i]->SetPos(Vec2(m_pos.X - kHitBoxW * 0.5, m_pos.Y - kGraphHeight * 0.5f + 25));
					m_shot[i]->SetDir(m_isDirLeft);
				}

				break;
			}
		}
	}
}

void Player::BulletDraw()
{
	//弾の位置を更新して表示
	for (int i = 0; i < kShotAllNum; ++i)
	{
		if (m_shot[i]->GetFrag())
		{
			m_shot[i]->Draw();
		}
		m_isShot = false;
	}
}

Player::PlayerState Player::GetPlayerState() const 
{
	//フラグ出し
	bool isJump = (m_pos.Y != 640);//ジャンプしているか
	bool isRun = (m_velocity.X != 0);//プレイヤーが移動しているか
	bool isDamage = (m_blinkFrameCount > 0);//被弾しているか

	//待機
	if (!isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kIdle; }
	//Run
	if (isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kRun; }
	//Jump
	if (isJump && !m_isShot && !isDamage) { return PlayerState::kJump; }
	//Shot
	if (m_isShot && !isDamage) { return PlayerState::kShot; }
	//被弾
	if (isDamage) { return PlayerState::kDamage; }

	return PlayerState::kIdle;
}
