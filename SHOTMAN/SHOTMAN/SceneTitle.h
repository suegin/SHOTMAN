#pragma once
#include "_base2DGameObject.h"
#include "_sceneBase.h"
#include <set>
#include "SceneManager.h"

using namespace std;

class SceneTitle : public _sceneBase
{
public:
	/*ƒƒ“ƒoŠÖ”*/
	void Init() override;

	void Update() override;

	void Draw() override;

	SceneManager::SceneKind SceneTransition();

private:
	set<_base2DGameObject> m_gameObjects;
};

