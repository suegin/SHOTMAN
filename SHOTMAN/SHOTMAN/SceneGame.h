#pragma once
#include "_sceneBase.h"
#include "_base2DGameObject.h"
#include <set>
#include <string>
#include "SceneManager.h"
#include "Fade.h"
#include "CollisionManager.h"

using namespace std;

class Player;
class Enemy;

class SceneGame : public _sceneBase
{
public:
	~SceneGame();

	/*ƒƒ“ƒoŠÖ”*/
	void Init() override;
	void Update() override;
	void Draw() override;

	SceneManager::SceneKind SceneTransition();

private:
	set<_base2DGameObject*> m_gameObjects;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Fade m_fade;
	CollisionManager m_collitionManager;
};

