#include "Shot.h"
#include "DxLib.h"
#include "Pad.h"

Shot::Shot():
	m_graphHandleShot(-1),
	m_shotFrag{}
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
	
}

void Shot::Draw()
{
	if (m_shotFrag)
	{
		DrawCircle(m_pos.X, m_pos.Y, 100, 0xffffff, true);
	}
}
