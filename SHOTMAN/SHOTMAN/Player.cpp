#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include "Shot.h"
#include "CollisionManager.h"
#include "Map.h"

namespace
{
	//キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//キャラクターのヒットボックス
	constexpr int kHitBoxW = 40;
	constexpr int kHitBoxH = 65;
	//ヒットボックスの調整
	constexpr int kAdjustmentHitBox = 10;

	//アニメーションのコマ数
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;
	constexpr int kJumpAnimNum = 10;
	constexpr int kShotAnimNum = 4;
	constexpr int kDamageAnimNum = 5;
	constexpr int kDeathAnimNum = 5;

	//アニメーションの1コマのフレーム数
	constexpr int kSingleAnimFrame = 6;
	constexpr int kShotSingleAnimFrame = 2;
	constexpr int kDeathSingleAnimFrame = 24;

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

	//死亡演出の時間
	constexpr int kDeathFrame = 119;

	//プレイヤーの初期位置
	constexpr int kPlayerInitPosX = 100;
	constexpr int kPlayerInitPosY = 500;
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
	m_deathFrameCount(0),
	m_isJump(false),
	m_isDamage(false),
	m_isShot(false),
	m_isDirLeft(false),
	m_isFloor(true),
	m_jumpSpeed(0.0f),
	m_velocity(0.0f,0.0f)
{
	for (auto& shot : m_shot)
	{
		shot = new Shot();
	}
	m_pMap = make_shared<Map>();
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
	m_graphHandleDeath = LoadGraph("image/Player/Death.png");
	assert(m_graphHandleDeath);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight,kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, kSingleAnimFrame, kJumpAnimNum);
	m_animShot.Init(m_graphHandleShot, kGraphWidth, kGraphHeight, kShotSingleAnimFrame, kShotAnimNum);
	m_animDamage.Init(m_graphHandleDamage, kGraphWidth, kGraphHeight, kSingleAnimFrame, kDamageAnimNum);
	m_animDeath.Init(m_graphHandleDeath, kGraphWidth, kGraphHeight, kDeathSingleAnimFrame, kDeathAnimNum);

	//プレイヤーの位置の初期化
	m_pos.X = kPlayerInitPosX;
	m_pos.Y = kPlayerInitPosY;
}

void Player::Update()
{
	if (m_playerState != Player::kDeath)
	{
		/*Pad入力の取得*/


	/*現在の状態の取得*/
		if (m_pos.Y >= 624) { m_isFloor = true; }//床の触れているかの判定
		m_playerState = GetPlayerState();


		/*各状態での移動処理*/
		//ダメージ状態の処理
		if (m_playerState == PlayerState::kDamage) { --m_blinkFrameCount; }//無敵時間の更新
		//ジャンプ
		if (m_playerState != Player::kDamage) { JumpUpdate(); }//ダメージを受けていたらジャンプ出来ない
		//if (jump) { Jump(); }
		//if (run) { Run();  }
		//if (damage) { Damage(); }
		//if (shot) { Shot(); }

		/*各状態での特殊処理*/
		//弾丸
		if (m_playerState != Player::kDamage) { BulletUpdate(); }//ダメージを受けていたら撃てない
		//Shotの更新(既に撃っている弾は飛んでいく)
		for (int i = 0; i < kShotAllNum; ++i) { m_shot[i]->Update(); }


		m_deathFrameCount = kDeathFrame;

		/*速度の更新*/
		PlayerVelocityUpdate();

		/*位置の更新*/
		m_pos += m_velocity;
	}

	MapCollisionUpdate();

	if(m_playerState == Player::kDeath)
	{
		Death();
		--m_deathFrameCount;
	}

	/*各状態でのアニメーション処理*/
		//ステートによってアニメーションの変更
	AnimUpdate(m_playerState);
}

void Player::Draw()
{
	BulletDraw();

	//点滅処理
	if (m_blinkFrameCount / 2 % 2 && m_playerState != Player::kDeath)
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

Rect Player::GetRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();
	return rect;
}

void Player::OnDamage(bool isHitLeft, bool isHitRight, bool isLastHitLeft, bool isLastHitRight)
{
	//既に被弾している場合はreturn
	if (m_blinkFrameCount > 0)
	{
		return;
	}

	//無敵時間付与
	m_blinkFrameCount = kDamageBlinkFrame;

	//プレイヤーの左が敵の右に当たった場合右にヒットバック
	if (isHitLeft && !isLastHitLeft)
	{
		m_velocity.X = 0;
		m_velocity.X = kDamageAction;
	}
	//プレイヤーの右が敵の左に当たった場合左にヒットバック
	if (isHitRight && !isLastHitRight)
	{
		m_velocity.X = 0;
		m_velocity.X = -kDamageAction;
	}

	/*if (m_blinkFrameCount == 0)
	{
		return;
	}*/
	
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
		m_animDeath.Update();
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
		m_animDamage.Play(m_pos, m_isDirLeft);
		break;
	case Player::kDeath:
		m_animDeath.Play(m_pos, m_isDirLeft);
		break;
	default:
		break;
	}
}

void Player::MapCollisionUpdate()
{	
	if (m_isJump)
	{
		Rect chipRect;
		if (m_pMap->IsCol(GetRect(), chipRect))
		{
			//横からぶつかった場合の処理
			if (m_velocity.X > 0.0f)//プレイヤーが右方向に移動している
			{
				m_pos.X = chipRect.left - kHitBoxW * 0.5 - 1; //マップチップの左側ちょうどぶつからない位置に補正
			}
			else if (m_velocity.X < 0.0f)
			{
				m_pos.X = chipRect.right + kHitBoxW * 0.5 + 1; //マップチップの右側ちょうどぶつからない位置に補正
			}
		}
	}
	else
	{
		Rect chipRect;
		if (m_pMap->IsCol(GetRect(), chipRect))
		{
			//横からぶつかった場合の処理
			if (m_velocity.X > 0.0f)//プレイヤーが右方向に移動している
			{
				m_pos.X = chipRect.left - kHitBoxW * 0.5; //マップチップの左側ちょうどぶつからない位置に補正
			}
			else if (m_velocity.X < 0.0f)
			{
				m_pos.X = chipRect.right + kHitBoxW * 0.5; //マップチップの右側ちょうどぶつからない位置に補正
			}
		}
	}
}

void Player::PlayerVelocityUpdate()
{
	//最終的な速度
	Vec2 lastVec;

	//PADフラグチェック
	bool isRightPress = Pad::IsPress(PAD_INPUT_RIGHT);
	bool isLeftPress = Pad::IsPress(PAD_INPUT_LEFT);
	bool isDamage = m_playerState == kDamage;



	if (!isDamage)
	{
		//右速度
		if (isRightPress)
		{
			lastVec.X = kSpeed;
			m_isDirLeft = false;
		}
		//左速度
		if (isLeftPress)
		{
			lastVec.X = -kSpeed;
			m_isDirLeft = true;
		}
	}

	//床に触れいてるならY方向の速度をゼロにする.
	if (m_isFloor)
	{
		lastVec.Y = 0.0f;
		m_pos.Y = 624;//めり込み調整
		m_animJump.ResetAnimFrame();//ジャンプアニメーションを最初に戻す
	}
	//落下しているか
	if (!m_isFloor)
	{
		//落下している場合は、速度に重力加速度を足す
		lastVec.Y = m_velocity.Y + kGravity;
	}
	//ダメージを受けているか
	if (m_playerState == PlayerState::kDamage)
	{
		lastVec.X = m_velocity.X;
	}

	//速度の更新
	m_velocity = lastVec;
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
			m_isFloor = false;
			m_velocity.Y = kJumpPower;
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

void Player::Death()
{
	//すでに死亡演出に入っている場合はreturn
	if (m_deathFrameCount > 0)
	{
		return;
	}
}

Player::PlayerState Player::GetPlayerState() const 
{
	//フラグ出し
	bool isJump = (m_pos.Y != 624);//ジャンプしているか
	bool isRun = (m_velocity.X != 0);//プレイヤーが移動しているか
	bool isDamage = (m_blinkFrameCount > 0);//被弾しているか
	bool isDeath = (m_hp <= 0);//HPが0か

	//待機
	if (!isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kIdle; }
	//Run
	if (isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kRun; }
	//Jump
	if (isJump && !m_isShot && !isDamage) { return PlayerState::kJump; }
	//Shot
	if (m_isShot && !isDamage) { return PlayerState::kShot; }
	//被弾
	if (isDamage && !isDeath) { return PlayerState::kDamage; }
	//死亡
	if (isDeath) { return PlayerState::kDeath; }

	return PlayerState::kIdle;
}
