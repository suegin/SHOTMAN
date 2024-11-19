#pragma once
#include "Vec2.h"
class Animation
{
public:
	void Init(int drawHandle, int graphW, int graphH, int animFrame, int animSingleFrame, int animNum);
	void Update();
	void Play(Vec2 pos, bool isLeft);

private:
	int m_drawHandle;
	int m_animFrame;
	int m_animSingleFrame;
	int m_graphW;
	int m_graphH;
	int m_animNum;
	int m_totalFrame;
};

