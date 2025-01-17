#pragma once
/// <summary>
/// 全ての当たり判定の基底クラス
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