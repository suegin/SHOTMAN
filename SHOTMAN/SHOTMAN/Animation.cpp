#include "Animation.h"
#include "DxLib.h"

void Animation::Init(int drawHandle, int graphW, int graphH, int animSingleFrame, int animNum)
{
	m_animFrame = 0;
	m_drawHandle = drawHandle;
	m_graphW = graphW;
	m_graphH = graphH;
	m_animSingleFrame = animSingleFrame;
	m_animNum = animNum;

	m_totalFrame = m_animNum * m_animSingleFrame;
}

void Animation::Update()
{
	m_animFrame++;

	//アニメーションの合計フレーム数を超えたら最初に戻す
	if (m_animFrame >= m_totalFrame)
	{
		m_animFrame = 0;
	}
}

void Animation::Play(Vec2 pos, bool isLeft)
{
	int animNo = m_animFrame / m_animSingleFrame;
	DrawRectGraph(static_cast<int>(pos.X - m_graphW / 2), static_cast<int>(pos.Y - m_graphH),
		animNo * m_graphW, 0, m_graphW, m_graphH,
		m_drawHandle, true, isLeft);
}
