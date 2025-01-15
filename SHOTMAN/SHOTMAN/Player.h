#pragma once
#include "_base2DGameObject.h"
#include "_baseCollision.h"
#include "Vec2.h"
#include "Animation.h"
#include "Shot.h"
#include "Rect.h"

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
		kIdle = 1,
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

	Rect GetRect();

	//�v���C���[���_���[�W���󂯂�I�u�W�F�N�g�ɂԂ�����
	void OnDamage(bool isHitLeft, bool isHitRight, bool isLastHitLeft, bool isLastHitRight);

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

	//���S�����ꍇ�̏���
	void Death();

	bool GetDir()const { return m_isDirLeft; }
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetVelocity()const { return m_velocity; }
	int GetHp()const { return m_hp; }
	int GetBlinkFrameCount()const { return m_blinkFrameCount; }
	int GetDeathFrameCount()const { return m_deathFrameCount; }

	//���݂�Player�̏�Ԃ��擾����
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
	//���S���̃A�j���[�V�����p
	int m_deathFrameCount;
	//�v���C���[�̏��
	bool m_isJump;
	bool m_isDamage;
	bool m_isShot;

	//���������Ă��邩
	bool m_isDirLeft;

	//���ƐG��Ă��邩
	bool m_isFloor;
	
	float m_jumpSpeed;

	//���݂̑��x
	Vec2 m_velocity;

	PlayerState m_playerState;

	//�Đ�����A�j���[�V����
	Animation m_animIdle;
	Animation m_animRun;
	Animation m_animJump;
	Animation m_animShot;
	Animation m_animDamage;
	Animation m_animDeath;

	Shot* m_shot[kShotAllNum];
};

