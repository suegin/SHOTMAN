#pragma once
#include "_sceneBase.h"
#include "_base2DGameObject.h"
#include <set>
#include "SceneManager.h"
#include "Player.h"
#include <string>

using namespace std;

class SceneGame : public _sceneBase
{
public:
	/*�����o�֐�*/
	void Init() override;
	void Update() override;
	void Draw() override;

	SceneManager::SceneKind SceneTransition();

private:
	set<_base2DGameObject*> m_gameObjects;
	Player* m_player;
};

