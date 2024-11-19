#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"

#include "Pad.h"

SceneTitle::SceneTitle():
	m_fadeFrameCount(0)
{
}

void SceneTitle::Init()
{
}

void SceneTitle::Update()
{
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}
}

void SceneTitle::Draw()
{
	DrawFormatString(10, 10, 0xffffff, "SceneTitle");

	int fadeAlpha = 0;

	float fadeRate = static_cast<float>((m_fadeFrameCount) / 30.f);
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

SceneManager::SceneKind SceneTitle::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		return SceneManager::SceneKind::kSceneGame;
	}

	return SceneManager::SceneKind::kSceneTitle;
}
