#include "Fade.h"
#include "DxLib.h"
#include "game.h"

Fade::Fade():
	m_fadeFrameCount(0)
{
}

Fade::~Fade()
{
}

void Fade::Init()
{
}

void Fade::Update()
{
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}
}

void Fade::Draw()
{
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>((m_fadeFrameCount) / 30.f);
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Fade::FadeIn()
{
}

void Fade::FadeOut()
{
}
