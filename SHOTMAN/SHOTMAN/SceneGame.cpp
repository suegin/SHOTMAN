#include "SceneGame.h"
#include "DxLib.h"

#include "Pad.h"

SceneGame::~SceneGame()
{
	if (m_pPlayer != nullptr)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

void SceneGame::Init()
{
	m_pPlayer = new Player();
	m_gameObjects.insert(m_pPlayer);

	m_pPlayer->Init();
}

void SceneGame::Update()
{
	m_pPlayer->Update();
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
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
