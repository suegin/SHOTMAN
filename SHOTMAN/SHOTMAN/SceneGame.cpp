#include "SceneGame.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"
#include "Player.h"
#include "Enemy.h"

SceneGame::~SceneGame()
{
	if (m_pPlayer != nullptr)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
	if (m_pEnemy != nullptr)
	{
		delete m_pEnemy;
		m_pEnemy = nullptr;
	}
}

void SceneGame::Init()
{
	m_pPlayer = new Player();
	m_gameObjects.insert(m_pPlayer);
	m_pEnemy = new Enemy();
	m_gameObjects.insert(m_pEnemy);

	m_pPlayer->Init();
	m_pEnemy->Init();
}

void SceneGame::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
	m_fade.Update();
	m_collitionManager.Update();
}

void SceneGame::Draw()
{
	//�w�i
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00bfff, true);
	m_pEnemy->Draw();
	m_pPlayer->Draw();
	DrawFormatString(10, 10, 0xffffff, "SceneGame");
	m_fade.Draw();
}

SceneManager::SceneKind SceneGame::SceneTransition()
{
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	return SceneManager::SceneKind::kSceneGame;
}
