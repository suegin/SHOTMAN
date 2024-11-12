#pragma once
#include "_sceneBase.h"
#include "_base2DGameObject.h"
#include <set>

#include "SceneManager.h"

using namespace std;

class SceneGame : public _sceneBase
{
public:
	/*ƒƒ“ƒoŠÖ”*/
	void Init();
	void Update();
	void Draw();

	SceneManager::SceneKind SceneTransition();

private:
	set<_base2DGameObject> m_gameObject;
};

