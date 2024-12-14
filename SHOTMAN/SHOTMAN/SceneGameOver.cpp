#include "SceneGameOver.h"
#include "DxLib.h"
#include "game.h"

#include "Pad.h"

SceneGameOver::SceneGameOver() :
	m_fadeFrameCount(0)
{
}

void SceneGameOver::Init()
{
}

void SceneGameOver::Update()
{
	m_fade.Update();
}

void SceneGameOver::Draw()
{
	DrawFormatString(10, 10, 0xffffff, "SceneGameOver");

	m_fade.Draw();
}

SceneManager::SceneKind SceneGameOver::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	return SceneManager::SceneKind::kSceneGameOver;
}


