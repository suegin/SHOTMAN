#pragma once
#include "_sceneBase.h"
#include "_base2DGameObject.h"
#include <set>

using namespace std;

class GameScene : public _sceneBase
{
public:
	/*ƒƒ“ƒoŠÖ”*/
	void Init();
	void Update();
	void Draw();

private:
	set<_base2DGameObject> m_gameObject;
};

