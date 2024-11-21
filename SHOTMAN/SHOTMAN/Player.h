#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"
#include "Shot.h"

class Player : public _base2DGameObject, public _baseCollision
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	/*�O���t�B�b�N�n���h��*/
	int m_graphHandleIdle;
	int m_graphHandleRun;
	int m_graphHandleJump;
	int m_graphHandleShot;
	int m_graphHandleDamage;
	int m_graphHandleDeath;

	//�v���C���[�̏��
	bool m_isRun;
	bool m_isJump;
	bool m_isShot;

	//���������Ă��邩
	bool m_isDirLeft;
	
	float m_jumpSpeed;

	Vec2 m_pos;

	//�Đ�����A�j���[�V����
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;

	Shot m_shot[3];
};

