#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"
#include "Shot.h"

namespace
{
	constexpr int kShotAllNum = 3;
}

class Player : public _base2DGameObject, public _baseCollision
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

	bool GetDir() const { return m_isDirLeft; }
	bool GetShot() const { return m_isShot; }

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

	float m_shotDirSpeed;

	Vec2 m_pos;

	//�Đ�����A�j���[�V����
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;

	Shot* m_shot[kShotAllNum];
};

