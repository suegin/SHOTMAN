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
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		for (int i = 0; i < kShotAllNum; ++i)
		{
			if (m_shotFrag[i] == false)
			{
				m_shotFrag[i] = true;
			}
		}
	}
}

void Shot::Draw()
{
}
