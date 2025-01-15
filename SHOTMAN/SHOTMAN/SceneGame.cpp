#include "SceneGame.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"
#include "CollisionManager.h"

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

SceneGame::SceneGame()
{
	m_pMap = make_shared<Map>();
	m_pPlayer = make_shared<Player>();
	m_pEnemy = make_shared<Enemy>();
	m_pCollisionManager = make_shared<CollisionManager>();
}

void SceneGame::Init()
{
	m_gameObjects.insert(m_pPlayer);
	m_gameObjects.insert(m_pEnemy);
	m_pMap->Init();
	m_pPlayer->Init();
	m_pEnemy->Init();
}

void SceneGame::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
	m_fade.Update();
	m_pCollisionManager->Update(*m_pPlayer, *m_pEnemy, *m_pMap);
	hp = m_pPlayer->GetHp();
}

void SceneGame::Draw()
{
	//”wŒi
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00bfff, true);
	m_pMap->Draw();
	m_pEnemy->Draw();
	m_pPlayer->Draw();
	DrawFormatString(10, 10, 0xffffff, "SceneGame");
	DrawFormatString(10, 30, 0xffffff, "HP:%d", m_pPlayer->GetHp());
	DrawFormatString(10, 50, 0xffffff, "PosX:%.01f, PosY:%.01f", m_pPlayer->GetPos().X, m_pPlayer->GetPos().Y);
	DrawFormatString(10, 70, 0xffffff, "VelocityX:%.02f,VelocityY%.02f", m_pPlayer->GetVelocity().X, m_pPlayer->GetVelocity().Y);
	DrawFormatString(10, 90, 0xffffff, "BlinkFrameCount:%d, DeathFrameCount:%d", m_pPlayer->GetBlinkFrameCount(), m_pPlayer->GetDeathFrameCount());
	DrawFormatString(10, 110, 0xffffff, "isLeft:%d,isRigt:%d", m_pCollisionManager->GetIsHitLeft(), m_pCollisionManager->GetIsHitRight());
	DrawFormatString(10, 130, 0xffffff, "PState:%d", m_pPlayer->GetPlayerState());
	DrawFormatString(10, 150, 0xffffff, "PRightPos:%.01f,ELeftPos:%.01f", m_pPlayer->GetRight(), m_pEnemy->GetLeft());
	m_fade.Draw();
}

SceneManager::SceneKind SceneGame::SceneTransition()
{
	if (m_pPlayer->GetPlayerState() == Player::kDeath && m_pPlayer->GetDeathFrameCount() < 0)
	{
		return SceneManager::SceneKind::kSceneGameOver;
	}

	return SceneManager::SceneKind::kSceneGame;
}
