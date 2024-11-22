#include "Shot.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"
#include "Player.h"

Shot::Shot(Player& player):
	m_graphHandleShot(-1),
	m_shotFrag{},
	m_player(player)
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
		if (m_pos.X >= Game::kScreenWidth ||
			m_pos.X <= 0)
		{
			m_shotFrag = false;
		}
	}
}

void Shot::Draw()
{
		DrawCircle(m_pos.X, m_pos.Y, 10, 0xffffff, true);
}