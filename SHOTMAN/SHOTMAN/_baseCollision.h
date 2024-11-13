#pragma once
/// <summary>
/// �S�Ă̓����蔻��̊��N���X
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

