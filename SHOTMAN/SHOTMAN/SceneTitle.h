#pragma once
#include "_base2DGameObject.h"
#include "_sceneBase.h"
#include <set>
#include "SceneManager.h"
#include "Fade.h"

using namespace std;

class SceneTitle : public _sceneBase
{
public:
	SceneTitle();

	/*メンバ関数*/
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

