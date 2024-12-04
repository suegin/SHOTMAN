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
	//�v���C���[�̃X�e�[�^�X
	enum PlayerState
	{
		kIdle,
		kRun,
		kJump,
		kShot,
		kDamage,
		kDeath
	};
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

	//�v���C���[�̏����擾����
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	//�v���C���[���_���[�W���󂯂�I�u�W�F�N�g�ɂԂ�����
	void OnDamage();

	//Player��State�ɂ��X�V����A�j���[�V������ύX
	void AnimUpdate(PlayerState state);
	//Player��State�ɂ��Đ�����A�j���[�V������ύX
	void AnimDraw(PlayerState state);

	//�v���C���[�̑��x�̍X�V(PAD���͂��瑬�x�̍쐬)
	void PlayerVelocityUpdate();
	//�W�����v�̏���(PAD���͂���)
	void JumpUpdate();
	//�e�̍X�V(PAD���͂��琶���A�X�V)
	void BulletUpdate();
	void BulletDraw();

	bool GetDir() const { return m_isDirLeft; }

	PlayerState GetPlayerState()const;

private:
	/*�O���t�B�b�N�n���h��*/
	int m_graphHandleIdle;
	int m_graphHandleRun;
	int m_graphHandleJump;
	int m_graphHandleShot;
	int m_graphHandleDamage;
	int m_graphHandleDeath;
	//�v���C���[HP
	int m_hp;
	//�_���[�W���󂯂��ۂ̖��G�Ɠ_�ŗp
	int m_blinkFrameCount;

	bool m_isJump;

	//���������Ă��邩
	bool m_isDirLeft;
	
	float m_jumpSpeed;

	//���݂̑��x
	Vec2 m_velocity;

	PlayerState m_playerState;

	//�Đ�����A�j���[�V����
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;

	Shot* m_shot[kShotAllNum];
};

