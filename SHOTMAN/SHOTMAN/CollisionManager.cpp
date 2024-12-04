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
	//�v���C���[�ƓG�̓����蔻��
	m_isCol = true;  //�ŏ��͈�U�������Ă����ԁA�Ƃ������Ƃɂ���

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
