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
	PlayerMapCollisionUpdate(player, map);
}

void CollisionManager::PlayerDamageCollisionUpdate(Player& player, Enemy& enemy)
{
	//プレイヤーと敵の当たり判定
	m_isDamageCol = true;  //最初は一旦当たっている状態、ということにする
	m_isHitLeft = true;
	m_isHitRight = true;
	m_isHitTop = true;
	m_isHitBottom = true;

	//絶対に当たっていない判定をとる
	if (player.GetLeft() > enemy.GetRight())
	{
		//プレイヤーの左は敵の右と当たっていない
		m_isHitLeft = false;
		m_isDamageCol = false;
	}
	if (player.GetTop() > enemy.GetBottom())
	{
		//プレイヤーの上は敵の下と当たっていない
		m_isHitTop = false;
		m_isDamageCol = false;
	}
	if (player.GetRight() < enemy.GetLeft())
	{
		//プレイヤーの右は敵の左と当たっていない
		m_isHitRight = false;
		m_isDamageCol = false;
	}
	if (player.GetBottom() < enemy.GetTop())
	{
		//プレイヤーの下は敵の上と当たっていない
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

void CollisionManager::PlayerMapCollisionUpdate(Player& player, Map& map)
{
	Rect chipRect;
	bool isHitLeft = false;
	bool isHitRight = false;
	bool isHitTop = false;
	bool isHitBottom = false;

	if (map.IsCol(player.GetRect(), chipRect))
	{
		//めり込み対策で1ドットずらしたポジションで取る
		if (player.GetLeft()+1.0f <= chipRect.right)
		{
			//プレイヤーの左が壁と接触している
			isHitLeft = true;
		}
		if (player.GetTop()-1.0f <= chipRect.bottom)
		{
			//プレイヤーの上が天井と接触している
			isHitTop = true;
		}
		if (player.GetRight()+1.0 >= chipRect.left)
		{
			//プレイヤーの右が壁と接触している
			isHitRight = true;
		}
		if (player.GetBottom()-1.0f >= chipRect.top)
		{
			//プレイヤーの下が床と接触している
			isHitBottom = true;
		}

		player.IsMapCollision(isHitLeft, isHitRight, isHitTop, isHitBottom);
	}
}
