#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include "Shot.h"

namespace
{
	//�L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//�A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;
	constexpr int kJumpAnimNum = 10;
	constexpr int kShotAnimNum = 4;

	//�A�j���[�V������1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 6;
	constexpr int kShotSingleAnimFrame = 2;

	//�L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 5.0f;

	//�W�����v����
	constexpr float kJumpPower = -8.0f; //�W�����v�̉���
	constexpr float kGravity = 0.4f;	//�d��

	//�_���[�W��H�������̖��G����
	constexpr int kDmageBlinkFrame = 30;

	//�v���C���[�̏���HP
	constexpr int kMacHp = 5;

	//�v���C���[�̏����ʒu
	constexpr int kPlayerInitPosX = 100;
	constexpr int kPlayerInitPosY = 640;
}

Player::Player() :
	m_playerState(kIdle),
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1),
	m_isAction(false),
	m_isRun(false),
	m_isJump(false),
	m_isShot(false),
	m_isDirLeft(false),
	m_jumpSpeed(0.0f)
{
	for (auto& shot : m_shot)
	{
		shot = new Shot();
	}
}

Player::~Player()
{
	for (auto& shot : m_shot)
	{
		delete shot;
	}
	DeleteGraph(m_graphHandleIdle);
	DeleteGraph(m_graphHandleRun);
	DeleteGraph(m_graphHandleJump);
	DeleteGraph(m_graphHandleShot);
}

void Player::Init()
{
	//�ҋ@
	m_graphHandleIdle = LoadGraph("image/Player/Idle.png");
	assert(m_graphHandleIdle != -1);
	//�ړ�
	m_graphHandleRun = LoadGraph("image/Player/Run.png");
	assert(m_graphHandleRun != -1);
	//�W�����v
	m_graphHandleJump = LoadGraph("image/Player/Jump.png");
	assert(m_graphHandleJump);
	//����
	m_graphHandleShot = LoadGraph("image/Player/Shot.png");
	assert(m_graphHandleShot);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight,kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, kSingleAnimFrame, kJumpAnimNum);
	m_animShot.Init(m_graphHandleShot, kGraphWidth, kGraphHeight, kShotSingleAnimFrame, kShotAnimNum);

	//�v���C���[�̂̈ʒu�̏�����
	m_pos.X = kPlayerInitPosX;
	m_pos.Y = kPlayerInitPosY;
}

void Player::Update()
{
	//���݂̃v���C���[�̃X�e�[�g���擾
	m_playerState = GetPlayerState();

	//�X�e�[�g�ɂ���ăA�j���[�V�����̕ύX
	AnimUpdate(m_playerState);

	/*���s�ړ�*/
	//���x�̍X�V
	VelocityUpdate();

	//�ړ�����
	m_pos += m_velocity;

	//�W�����v

	
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (!m_isJump)
		{
			m_playerState = kJump;
			m_isJump = true;
			m_isAction = true;
			m_jumpSpeed = kJumpPower;
		}
	}

	if (m_isJump)
	{
		m_pos.Y += m_jumpSpeed;
		m_jumpSpeed += kGravity;
		if (m_pos.Y >= 640)
		{
			m_playerState = kIdle;
			m_isJump = false;
			m_isAction = false;
			m_jumpSpeed = 0.0f;
			m_pos.Y = 640;
			m_animJump.ResetAnimFrame();
		}
	}

	for (int i = 0; i < kShotAllNum; ++i)
	{
		m_shot[i]->Update();
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		for (int i = 0; i < kShotAllNum; ++i)
		{
			if (!m_shot[i]->m_shotFrag)
			{
				m_shot[i]->m_shotFrag = true;
				m_isAction = true;

				m_shot[i]->SetPos(Vec2(m_pos.X + 15.0f, m_pos.Y));
				m_shot[i]->SetPos(Vec2(m_pos.X, m_pos.Y - kGraphHeight * 0.5f + 25));

				if (m_isDirLeft)
				{
					m_shot[i]->SetDir(m_isDirLeft);
				}

				break;
			}
		}
	}

	for (int i = 0; i < kShotAllNum; ++i)
	{
		if (m_shot[i]->m_shotFrag)
		{
			if (m_shot[i]->GetPos().X >= Game::kScreenWidth ||
				m_shot[i]->GetPos().X <= 0)
			{
				m_shot[i]->m_shotFrag = false;
				m_isAction = false;
			}
			m_shot[i]->Draw();
		}
	}
}

void Player::Draw()
{
	//�A�j���[�V�����Đ�
	AnimDraw(m_playerState);

}

void Player::AnimUpdate(PlayerState state)
{
	switch (m_playerState)
	{
	case Player::kIdle:
		m_animIdle.Update();
		break;
	case Player::kRun:
		m_animRun.Update();
		break;
	case Player::kJump:
		m_animJump.Update();
		break;
	case Player::kShot:
		m_animShot.Update();
		break;
	case Player::kDamage:
		break;
	case Player::kDeath:
		break;
	default:
		break;
	}
}

void Player::AnimDraw(PlayerState state)
{
	switch (m_playerState)
	{
	case Player::kIdle:
		m_animIdle.Play(m_pos, m_isDirLeft);
		break;
	case Player::kRun:
		m_animRun.Play(m_pos, m_isDirLeft);
		break;
	case Player::kJump:
		m_animJump.Play(m_pos, m_isDirLeft);
		break;
	case Player::kShot:
		m_animShot.Play(m_pos, m_isDirLeft);
		break;
	case Player::kDamage:
		break;
	case Player::kDeath:
		break;
	default:
		break;
	}
}

void Player::VelocityUpdate()
{
	//PAD�t���O�`�F�b�N
	bool IsRightPress = Pad::IsPress(PAD_INPUT_RIGHT);
	bool IsLeftPress = Pad::IsPress(PAD_INPUT_LEFT);

	//�E���x
	if (IsRightPress)
	{
		m_velocity.X = kSpeed;
		m_isDirLeft = false;
		m_isAction = true;
	}
	//�����x
	if (IsLeftPress)
	{
		m_velocity.X = -kSpeed;
		m_isDirLeft = true;
		m_isAction = true;
	}
	//������Ă��Ȃ�
	if (!IsRightPress && !IsLeftPress)
	{
		m_velocity.X = 0;
	}
}

Player::PlayerState Player::GetPlayerState()
{
	PlayerState state;

	//�t���O�o��
	bool isJump = (m_pos.Y != 640);//�W�����v���Ă��邩
	bool isWalk = (m_velocity.X != 0);//�ړ����Ă��邩

	//Jump
	if (isJump) { return PlayerState::kJump; }
	//�ҋ@
	if (!isJump && !isWalk) { return PlayerState::kIdle; }
	//Walk
	if (!isJump && isWalk) { return PlayerState::kRun; }

	return PlayerState::kIdle;
}
