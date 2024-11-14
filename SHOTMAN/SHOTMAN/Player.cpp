#include "Player.h"
#include "DxLib.h"
#include "game.h"

Player::Player() :
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	
}

void Player::Draw()
{
	DrawBox(640-16, 360-16, 640+16, 360+16, 0xffffff, true);
}
