#include "SceneGame.h"
#include "DxLib.h"
#include "Pad.h"

void SceneGame::Init()
{
}

void SceneGame::Update()
{
}

void SceneGame::Draw()
{
	DrawFormatString(10, 10, 0xffffff, "SceneGame");
}

SceneManager::SceneKind SceneGame::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind();
	}

	return SceneManager::SceneKind();
}
