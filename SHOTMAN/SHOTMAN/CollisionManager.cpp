#include "CollisionManager.h"
#include "DxLib.h"
#include "Vec2.h"

#include "Player.h"
#include "Enemy.h"

CollisionManager::CollisionManager() :
	m_isDamageCol(false),
	m_isHitLeft(false),
	m_isHitRight(false),
	m_isHitTop(false),
	m_isHitBottom(false),
	m_isLastHitLeft(false),
	m_isLastHitRight(false)
	
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
	PlayerDamageCollisionUpdate();
}

void CollisionManager::PlayerDamageCollisionUpdate()
{
	//�v���C���[�ƓG�̓����蔻��
	m_isDamageCol = true;  //�ŏ��͈�U�������Ă����ԁA�Ƃ������Ƃɂ���
	m_isHitLeft = true;
	m_isHitRight = true;
	m_isHitTop = true;
	m_isHitBottom = true;

	//��΂ɓ������Ă��Ȃ�������Ƃ�
	if (m_player.GetLeft() > m_enemy.GetRight())
	{
		//�v���C���[�̍��͓G�̉E�Ɠ������Ă��Ȃ�
		m_isHitLeft = false;
		m_isDamageCol = false;
	}
	if (m_player.GetTop() > m_enemy.GetBottom())
	{
		//�v���C���[�̏�͓G�̉��Ɠ������Ă��Ȃ�
		m_isHitTop = false;
		m_isDamageCol = false;
	}
	if (m_player.GetRight() < m_enemy.GetLeft())
	{
		//�v���C���[�̉E�͓G�̍��Ɠ������Ă��Ȃ�
		m_isHitRight = false;
		m_isDamageCol = false;
	}
	if (m_player.GetBottom() < m_enemy.GetTop())
	{
		//�v���C���[�̉��͓G�̏�Ɠ������Ă��Ȃ�
		m_isHitBottom = false;
		m_isDamageCol = false;
	}

	if (m_isDamageCol)
	{
		m_player.OnDamage(m_isHitLeft,m_isHitRight, m_isLastHitLeft, m_isLastHitRight);
	}
	m_isLastHitLeft = m_isHitLeft;
	m_isLastHitRight = m_isHitRight;
}

void CollisionManager::PlayerMapCollisionUpdate(Map& map)
{

}

void CollisionManager::Draw()
{
}
