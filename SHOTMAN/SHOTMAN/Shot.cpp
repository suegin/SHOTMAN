#include "Shot.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"
#include "Player.h"

Shot::Shot():
	m_graphHandleShot(-1),
	m_shotFrag{},
	m_isDirLeft(false)
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
	if (m_shotFrag)
	{
		if (m_isDirLeft)
		{
			m_pos.X -= 8;
		}
		else
		{
			m_pos.X += 8;
		}

		if (m_pos.X >= Game::kScreenWidth ||
			m_pos.X <= 0)
		{
			m_shotFrag = false;
			m_isDirLeft = false;
		}
	}
}

void Shot::Draw()
{
		DrawCircle(m_pos.X, m_pos.Y, 10, 0xffffff, true);
}

void Shot::SetPos(const Vec2 setPos)
{
	m_pos = setPos;

	return;
}

void Shot::SetDir(bool setDir)
{
	m_isDirLeft = setDir;

	return;
}
