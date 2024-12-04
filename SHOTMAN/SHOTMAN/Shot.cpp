#include "Shot.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"
#include "Player.h"

namespace
{
	constexpr int kSpeed = 8;
}

Shot::Shot():
	m_graphHandleShot(-1),
	m_shotFrag{},
	m_isDirLeft(false),
	m_velocity(0,0)
{
}

Shot::~Shot()
{
}

void Shot::Init()
{
}

void Shot::Update()
{
	BulletVelocityUpdate();

	//’e‚ÌˆÚ“®ˆ—
	m_pos += m_velocity;
}

void Shot::Draw()
{
		DrawCircle(m_pos.X, m_pos.Y, 3, 0xffffff, true);
}

void Shot::SetPos(const Vec2 setPos)
{
	m_pos = setPos;

	return;
}

void Shot::SetShotFrag(bool setShotFrag)
{
	m_shotFrag = setShotFrag;
}

void Shot::SetDir(const bool setDir)
{
	m_isDirLeft = setDir;

	return;
}

void Shot::BulletVelocityUpdate()
{
	if (m_shotFrag)
	{
		if (m_isDirLeft)
		{
			m_velocity.X = -kSpeed;
		}
		else
		{
			m_velocity.X = kSpeed;
		}

		if (m_pos.X >= Game::kScreenWidth ||
			m_pos.X <= 0)
		{
			m_shotFrag = false;
			m_isDirLeft = false;
		}
	}
}
