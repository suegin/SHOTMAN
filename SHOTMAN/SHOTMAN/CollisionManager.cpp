#include "CollisionManager.h"
#include "DxLib.h"

#include "Player.h"
#include "Enemy.h"

CollisionManager::CollisionManager() :
	m_isCol(false),
	m_pPlayer(new Player),
	m_pEnemy(new Enemy)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	//ƒvƒŒƒCƒ„[‚Æ“G‚Ì“–‚½‚è”»’è
	m_isCol = true;  //Å‰‚Íˆê’U“–‚½‚Á‚Ä‚¢‚éó‘ÔA‚Æ‚¢‚¤‚±‚Æ‚É‚·‚é

	if (m_pPlayer->GetLeft() > m_pEnemy->GetRight())
	{
		m_isCol = false;
	}
	if (m_pPlayer->GetRight() < m_pEnemy->GetLeft())
	{
		m_isCol = false;
	}
	if (m_pPlayer->GetBottom() > m_pEnemy->GetTop())
	{
		m_isCol = false;
	}
	if (m_pPlayer->GetTop() < m_pEnemy->GetBottom())
	{
		m_isCol = false;
	}

	if (m_isCol)
	{
		m_pPlayer->OnDamage();
	}
}

void CollisionManager::Draw()
{
}
