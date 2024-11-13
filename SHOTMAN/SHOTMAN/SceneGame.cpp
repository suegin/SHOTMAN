#include "SceneGame.h"
#include "DxLib.h"

#include "Pad.h"

void SceneGame::Init()
{
	m_player = new Player();
	m_gameObjects.insert(m_player);
}

void SceneGame::Update()
{

	for (_base2DGameObject* temp : m_gameObjects)
	{
		temp->Update();
	}
}

void SceneGame::Draw()
{
	m_player->Draw();
	DrawFormatString(10, 10, 0xffffff, "SceneGame");
}

SceneManager::SceneKind SceneGame::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	return SceneManager::SceneKind::kSceneGame;
}
