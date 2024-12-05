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
	//プレイヤーと敵の当たり判定
	m_isCol = true;  //最初は一旦当たっている状態、ということにする
	m_isHitLeft = true;
	m_isHitRight = true;
	m_isHitTop = true;
	m_isHitBottom = true;

	//絶対に当たっていない判定をとる
	if (player.GetLeft() > enemy.GetRight())
	{
		//プレイヤーの左は敵の右と当たっていない
		m_isHitLeft = false;
		m_isCol = false;
	}
	if (player.GetTop() > enemy.GetBottom())
	{
		//プレイヤーの上は敵の下と当たっていない
		m_isHitTop = false;
		m_isCol = false;
	}
	if (player.GetRight() < enemy.GetLeft())
	{
		//プレイヤーの右は敵の左と当たっていない
		m_isHitRight = false;
		m_isCol = false;
	}
	if (player.GetBottom() < enemy.GetTop())
	{
		//プレイヤーの下は敵の上と当たっていない
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
