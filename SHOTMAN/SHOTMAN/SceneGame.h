#pragma once
#include "_sceneBase.h"
#include "_base2DGameObject.h"
#include <set>
#include <string>
#include "SceneManager.h"
#include "Fade.h"
#include <memory>

using namespace std;

class Map;
class Player;
class Enemy;
class CollisionManager;

class SceneGame : public _sceneBase
{
public:
	SceneGame();

	/*ƒƒ“ƒoŠÖ”*/
	void Init() override;
	void Update() override;
	void Draw() override;

	SceneManager::SceneKind SceneTransition();

private:
	set<shared_ptr<_base2DGameObject>> m_gameObjects;
	shared_ptr<Map> m_pMap;
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Enemy> m_pEnemy;
	Fade m_fade;
	shared_ptr<CollisionManager> m_pCollisionManager;

	int hp = 0;
};

