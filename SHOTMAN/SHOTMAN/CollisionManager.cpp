#include "CollisionManager.h"
#include "DxLib.h"
#include "Vec2.h"
#include "Rect.h"

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

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

void CollisionManager::Update(Player& player, Enemy& enemy, Map& map)
{
	PlayerDamageCollisionUpdate(player, enemy);
}

void CollisionManager::PlayerDamageCollisionUpdate(Player& player, Enemy& enemy)
{
	//�v���C���[�ƓG�̓����蔻��
	m_isDamageCol = true;  //�ŏ��͈�U�������Ă����ԁA�Ƃ������Ƃɂ���
	m_isHitLeft = true;
	m_isHitRight = true;
	m_isHitTop = true;
	m_isHitBottom = true;

	//��΂ɓ������Ă��Ȃ�������Ƃ�
	if (player.GetLeft() > enemy.GetRight())
	{
		//�v���C���[�̍��͓G�̉E�Ɠ������Ă��Ȃ�
		m_isHitLeft = false;
		m_isDamageCol = false;
	}
	if (player.GetTop() > enemy.GetBottom())
	{
		//�v���C���[�̏�͓G�̉��Ɠ������Ă��Ȃ�
		m_isHitTop = false;
		m_isDamageCol = false;
	}
	if (player.GetRight() < enemy.GetLeft())
	{
		//�v���C���[�̉E�͓G�̍��Ɠ������Ă��Ȃ�
		m_isHitRight = false;
		m_isDamageCol = false;
	}
	if (player.GetBottom() < enemy.GetTop())
	{
		//�v���C���[�̉��͓G�̏�Ɠ������Ă��Ȃ�
		m_isHitBottom = false;
		m_isDamageCol = false;
	}

	if (m_isDamageCol)
	{
		player.OnDamage(m_isHitLeft,m_isHitRight, m_isLastHitLeft, m_isLastHitRight);
	}
	m_isLastHitLeft = m_isHitLeft;
	m_isLastHitRight = m_isHitRight;
}
