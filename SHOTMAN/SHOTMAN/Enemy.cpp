#include "Enemy.h"
#include "Vec2.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//エネミーの当たり判定(仮)
	constexpr int kHitBoxW = 20;
	constexpr int kHitBoxH = 20;

	//エネミーの初期位置
	constexpr int kEnemyInitPosX = 640;
	constexpr int kEnemyInitPosY = 620;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_pos.X = kEnemyInitPosX;
	m_pos.Y = kEnemyInitPosY;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawBox(m_pos.X - kHitBoxW*0.5, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5, m_pos.Y, 0xff0000, true);
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
