#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"

namespace
{
	//�L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//�A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;

	//�A�j���[�V������1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 6;

	//�L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 5.0f;

	//�n�ʂ̍���

	//�W�����v����
	constexpr float kJumpPower = -8.0f; //�W�����v�̉���
	constexpr float kGravity = 0.4f;	//�d��

	//�_���[�W��H�������̖��G����
	constexpr int kDmageBlinkFrame = 30;

	//�v���C���[�̏���HP
	constexpr int kMacHp = 5;
}

Player::Player() :
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1),
	m_pos(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f),
	m_animFrame(0)
{
}

Player::~Player()
{
	DeleteGraph(m_graphHandleIdle);
}

void Player::Init()
{
	m_graphHandleIdle = LoadGraph("image/Player/Idle.png");
	m_graphHandleRun = LoadGraph("image/Player/Run.png");
	assert(m_graphHandleIdle != -1);
	m_state = 0;
	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, m_animFrame, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight, m_animFrame, kSingleAnimFrame, kRunAnimNum);
}

void Player::Update()
{
	////�A�j���[�V�����̍X�V
	//++m_animFrame;
	//int totalFrame = kIdleAnimNum * kSingleAnimFrame;

	////�A�j���[�V�����̍��v�t���[�����𒴂�����ŏ��ɖ߂�
	//if (m_animFrame >= totalFrame)
	//{
	//	m_animFrame = 0;
	//}

	if (m_state == 0)
	{
		m_animIdle.Update();
	}
	else if (m_state == 1)
	{
		m_animRun.Update();
	}
	else if (m_state == 2)
	{
		m_animRun.Update();
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_pos.X += kSpeed;
		m_state = 1;
	}
	else if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_pos.X -= kSpeed;
		m_state = 2;
	}
	else
	{
		m_state = 0;
	}
}

void Player::Draw()
{
	//int animNo = m_animFrame / kSingleAnimFrame;
	//
	//DrawRectGraph(static_cast<int>(m_pos.X - kGraphWidth / 2), static_cast<int>(m_pos.Y - kGraphHeight),
	//	animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
	//	m_graphHandleIdle, true);
	//DrawBox(640-16, 360-16, 640+16, 360+16, 0xffffff, true);
	if (m_state == 0)
	{
		m_animIdle.Play(m_pos,false);
	}
	else if (m_state == 1)
	{
		m_animRun.Play(m_pos,false);
	}
	else if (m_state == 2)
	{
		m_animRun.Play(m_pos, true);
	}
}
