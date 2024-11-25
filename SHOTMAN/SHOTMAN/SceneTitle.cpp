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
	m_fade.Update();
}

void SceneTitle::Draw()
{
	DrawFormatString(10, 10, 0xffffff, "SceneTitle");

	m_fade.Draw();
}

SceneManager::SceneKind SceneTitle::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		return SceneManager::SceneKind::kSceneGame;
	}

	return SceneManager::SceneKind::kSceneTitle;
}
