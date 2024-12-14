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
	m_collisionManager.Update(*m_pPlayer,*m_pEnemy);
	hp = m_pPlayer->GetHp();
}

void SceneGame::Draw()
{
	//”wŒi
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00bfff, true);
	m_pEnemy->Draw();
	m_pPlayer->Draw();
	DrawFormatString(10, 10, 0xffffff, "SceneGame");
	DrawFormatString(10, 30, 0xffffff, "HP:%d", m_pPlayer->GetHp());
	DrawFormatString(10, 50, 0xffffff, "PosX:%.01f, PosY:%.01f", m_pPlayer->GetPos().X, m_pPlayer->GetPos().Y);
	DrawFormatString(10, 70, 0xffffff, "VelocityX:%.02f,VelocityY%.02f", m_pPlayer->GetVelocity().X, m_pPlayer->GetVelocity().Y);
	DrawFormatString(10, 90, 0xffffff, "BlinkFrameCount:%d, DeathFrameCount:%d", m_pPlayer->GetBlinkFrameCount(), m_pPlayer->GetDeathFrameCount());
	DrawFormatString(10, 110, 0xffffff, "isLeft:%d,isRigt:%d", m_collisionManager.GetIsHitLeft(), m_collisionManager.GetIsHitRight());
	DrawFormatString(10, 130, 0xffffff, "PState:%d", m_pPlayer->GetPlayerState());
	m_fade.Draw();
}

SceneManager::SceneKind SceneGame::SceneTransition()
{
	if (m_pPlayer->GetPlayerState() == Player::kDeath && m_pPlayer->GetDeathFrameCount() < 0)
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	return SceneManager::SceneKind::kSceneGame;
}
