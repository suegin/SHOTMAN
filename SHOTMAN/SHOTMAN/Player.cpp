#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>

namespace
{
	//キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//アニメーションのコマ数
	constexpr int kIdleAnimNum = 11;

	//アニメーションの1コマのフレーム数
	constexpr int kSingleAnimFrame = 5;

	//キャラクターの移動速度
	constexpr float kSpeed = 2.0f;

	//地面の高さ

	//ジャンプ処理
	constexpr float kJumpPower = -8.0f; //ジャンプの加速
	constexpr float kGravity = 0.4f;	//重力

	//ダメージを食らった後の無敵時間
	constexpr int kDmageBlinkFrame = 30;

	//プレイヤーの初期HP
	constexpr int kMacHp = 5;
}

Player::Player() :
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1),
	m_pos(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f),
	m_animFrame(0)
{
}

Player::~Player()
{
	DeleteGraph(m_graphHandleIdle);
}

void Player::Init()
{
	m_graphHandleIdle = LoadGraph("image/Player/Idle_2.png");
	assert(m_graphHandleIdle != -1);
}

void Player::Update()
{
	//アニメーションの更新
	++m_animFrame;
	int totalFrame = kIdleAnimNum * kSingleAnimFrame;

	//アニメーションの合計フレーム数を超えたら最初に戻す
	if (m_animFrame >= totalFrame)
	{
		m_animFrame = 0;
	}
}

void Player::Draw()
{
	int animNo = m_animFrame / kSingleAnimFrame;
	

	DrawRectGraph(static_cast<int>(m_pos.X - kGraphWidth / 2), static_cast<int>(m_pos.Y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		m_graphHandleIdle, true);
	//DrawBox(640-16, 360-16, 640+16, 360+16, 0xffffff, true);
}
