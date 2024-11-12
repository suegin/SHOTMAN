#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::Init()
{
}

void SceneTitle::Update()
{
}

void SceneTitle::Draw()
{
	DrawFormatString(10, 10, 0xffffff, "SceneTitle");
}

SceneManager::SceneKind SceneTitle::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind();
	}

	return SceneManager::SceneKind();
}
