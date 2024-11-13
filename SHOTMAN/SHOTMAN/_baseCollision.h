#pragma once
/// <summary>
/// ‘S‚Ä‚Ì“–‚½‚è”»’è‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class _baseCollision
{
public:
	virtual ~_baseCollision() {};

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

protected:
	bool m_isHit;
	float m_center;
};

