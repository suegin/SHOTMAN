#include "Enemy.h"
#include "Vec2.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>

namespace
{
	//エネミーの当たり判定(仮)
	constexpr int kHitBoxW = 20;
	constexpr int kHitBoxH = 20;

	//エネミーの初期位置
	constexpr int kEnemyInitPosX = 640;
	constexpr int kEnemyInitPosY = 620;

	constexpr int kGrpahW = 46;
	constexpr int kGraphH = 30;
}

Enemy::Enemy():
	m_graphHandle(-1),
	m_isLeft(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_graphHandle = LoadGraph("image/Enemy/Enemy001.png");
	assert(m_graphHandle != -1);

	m_anim.Init(m_graphHandle, kGrpahW, kGraphH, 5, 7);

	m_pos.X = kEnemyInitPosX;
	m_pos.Y = kEnemyInitPosY;
}

void Enemy::Update()
{
	m_anim.Update();
}

void Enemy::Draw()
{
	m_anim.Play(m_pos, m_isLeft);
}

float Enemy::GetLeft()
{
	return (m_pos.X - kHitBoxW*0.5);
}

float Enemy::GetTop()
{
	return (m_pos.Y - kHitBoxH);
}

float Enemy::GetRight()
{
	return (m_pos.X + kHitBoxW*0.5);
}

float Enemy::GetBottom()
{
	return m_pos.Y;
}
