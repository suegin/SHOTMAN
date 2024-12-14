#pragma once
#include "_base2DGameObject.h"
#include "_sceneBase.h"
#include <set>
#include "SceneManager.h"
#include "Fade.h"

using namespace std;

class SceneGameOver : public _sceneBase
{
public:
	SceneGameOver();

	/*ƒƒ“ƒoŠÖ”*/
	void Init() override;
	void Update() override;
	void Draw() override;

	SceneManager::SceneKind SceneTransition();

private:
	int m_fadeFrameCount;

private:
	set<_base2DGameObject> m_gameObjects;
	Fade m_fade;
};