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
	constexpr int kJumpAnimNum = 10;

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
	m_pos(Game::kScreenWidth * 0.5f, 640),
	m_animFrame(0),
	m_isRun(false),
	m_isJump(false),
	m_isDirLeft(false),
	m_jumpSpeed(0.0)
{
}

Player::~Player()
{
	DeleteGraph(m_graphHandleIdle);
}

void Player::Init()
{
	m_graphHandleIdle = LoadGraph("image/Player/Idle.png");
	assert(m_graphHandleIdle != -1);
	m_graphHandleRun = LoadGraph("image/Player/Run.png");
	assert(m_graphHandleRun != -1);
	m_graphHandleJump = LoadGraph("image/Player/Jump.png");
	assert(m_graphHandleJump);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, m_animFrame, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight, m_animFrame, kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, m_animFrame, kSingleAnimFrame, kJumpAnimNum);
}

void Player::Update()
{
    if (m_isJump)
	{
		m_animJump.Update();
	}
	else if (m_isRun)
	{
		m_animRun.Update();
	}
	else
	{
		m_animIdle.Update();
	}
	
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_pos.X += kSpeed;
		m_isRun = true;
		m_isDirLeft = false;
	}
	else if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_pos.X -= kSpeed;
		m_isRun = true;
		m_isDirLeft = true;
	}
	else
	{
		m_isRun = false;
	}
	
	
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (!m_isJump)
		{
			m_isJump = true;
			m_jumpSpeed = kJumpPower;
		}
	}

	if (m_isJump)
	{
		m_pos.Y += m_jumpSpeed;
		m_jumpSpeed += kGravity;
		if (m_pos.Y >= 640)
		{
			m_isJump = false;
			m_jumpSpeed = 0.0f;
			m_pos.Y = 640;
			m_animFrame = 0;
		}
	}
}

void Player::Draw()
{
	if (m_isJump)
	{
		m_animJump.Play(m_pos, m_isDirLeft);
	}
	else if (m_isRun)
	{
		m_animRun.Play(m_pos, m_isDirLeft);
	}
	else
	{
		m_animIdle.Play(m_pos, m_isDirLeft);
	}
}