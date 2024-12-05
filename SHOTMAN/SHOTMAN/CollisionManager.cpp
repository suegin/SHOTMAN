#include "CollisionManager.h"
#include "DxLib.h"

CollisionManager::CollisionManager() :
	m_isCol(false),
	m_isHitLeft(false),
	m_isHitRight(false),
	m_isHitTop(false),
	m_isHitBottom(false)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Update(Player& player, Enemy& enemy)
{
	//�v���C���[�ƓG�̓����蔻��
	m_isCol = true;  //�ŏ��͈�U�������Ă����ԁA�Ƃ������Ƃɂ���
	m_isHitLeft = true;
	m_isHitRight = true;
	m_isHitTop = true;
	m_isHitBottom = true;

	//��΂ɓ������Ă��Ȃ�������Ƃ�
	if (player.GetLeft() > enemy.GetRight())
	{
		//�v���C���[�̍��͓G�̉E�Ɠ������Ă��Ȃ�
		m_isHitLeft = false;
		m_isCol = false;
	}
	if (player.GetTop() > enemy.GetBottom())
	{
		//�v���C���[�̏�͓G�̉��Ɠ������Ă��Ȃ�
		m_isHitTop = false;
		m_isCol = false;
	}
	if (player.GetRight() < enemy.GetLeft())
	{
		//�v���C���[�̉E�͓G�̍��Ɠ������Ă��Ȃ�
		m_isHitRight = false;
		m_isCol = false;
	}
	if (player.GetBottom() < enemy.GetTop())
	{
		//�v���C���[�̉��͓G�̏�Ɠ������Ă��Ȃ�
		m_isHitBottom = false;
		m_isCol = false;
	}

	if (m_isCol)
	{
		player.OnDamage(m_isHitLeft,m_isHitRight);
	}
}

void CollisionManager::Draw()
{
}
