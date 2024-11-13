#pragma once
#include "Vec2.h"
/// <summary>
/// �S�Ă�2D�Q�[���I�u�W�F�N�g�̊��N���X
/// </summary>
class _base2DGameObject
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~_base2DGameObject() {};

	/*�����o�֐�*/
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:
	Vec2 m_pos{ 0.0f, 0.0f };
	int m_drawHandle;
};

