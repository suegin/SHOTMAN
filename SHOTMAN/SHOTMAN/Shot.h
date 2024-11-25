#pragma once
#include "_base2DGameObject.h"
#include "Vec2.h"

class Shot : public _base2DGameObject
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

	void SetDir(bool setDir);

	bool m_shotFrag;

private:
	int m_graphHandleShot;

	bool m_isDirLeft;
};

