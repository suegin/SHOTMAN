#pragma once
#include "_base2DGameObject.h"
#include "_sceneBase.h"
#include <set>

using namespace std;

class TitleScene : public _sceneBase
{
public:
	/*ƒƒ“ƒoŠÖ”*/
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	set<_base2DGameObject> m_gameObjects;
};

