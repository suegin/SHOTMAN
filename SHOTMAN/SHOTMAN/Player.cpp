#include "Player.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include "Shot.h"
#include "CollisionManager.h"
#include "Map.h"

namespace
{
	//�L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 128;
	constexpr int kGraphHeight = 128;

	//�L�����N�^�[�̃q�b�g�{�b�N�X
	constexpr int kHitBoxW = 40;
	constexpr int kHitBoxH = 65;
	//�q�b�g�{�b�N�X�̒���
	constexpr int kAdjustmentHitBox = 10;

	//�A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 10;
	constexpr int kJumpAnimNum = 10;
	constexpr int kShotAnimNum = 4;
	constexpr int kDamageAnimNum = 5;
	constexpr int kDeathAnimNum = 5;

	//�A�j���[�V������1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 6;
	constexpr int kShotSingleAnimFrame = 2;
	constexpr int kDeathSingleAnimFrame = 24;

	//�L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 5.0f;

	//�W�����v����
	constexpr float kJumpPower = -8.0f; //�W�����v�̉���
	constexpr float kGravity = 0.4f;	//�d��

	//�_���[�W��H�������̖��G����
	constexpr int kDamageBlinkFrame = 30;

	//�_���[�W��H�������̐�����΂���鑬�x
	constexpr int kDamageAction = 3;

	//�_���[�W�A�N�V���������X�Ɋɂ߂��
	constexpr int kDamageActionControl = 0.2;

	//�v���C���[�̏���HP
	constexpr int kMaxHp = 5;

	//���S���o�̎���
	constexpr int kDeathFrame = 119;

	//�v���C���[�̏����ʒu
	constexpr int kPlayerInitPosX = 100;
	constexpr int kPlayerInitPosY = 500;
}

Player::Player() :
	m_playerState(kIdle),
	m_graphHandleIdle(-1),
	m_graphHandleRun(-1),
	m_graphHandleJump(-1),
	m_graphHandleShot(-1),
	m_graphHandleDamage(-1),
	m_graphHandleDeath(-1),
	m_hp(kMaxHp),
	m_blinkFrameCount(0),
	m_deathFrameCount(0),
	m_isJump(false),
	m_isDamage(false),
	m_isShot(false),
	m_isDirLeft(false),
	m_isFloor(true),
	m_jumpSpeed(0.0f),
	m_velocity(0.0f,0.0f)
{
	for (auto& shot : m_shot)
	{
		shot = new Shot();
	}
	m_pMap = make_shared<Map>();
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
	//��e
	m_graphHandleDamage = LoadGraph("image/Player/Damage.png");
	assert(m_graphHandleDamage);
	m_graphHandleDeath = LoadGraph("image/Player/Death.png");
	assert(m_graphHandleDeath);

	m_animIdle.Init(m_graphHandleIdle, kGraphWidth, kGraphHeight, kSingleAnimFrame, kIdleAnimNum);
	m_animRun.Init(m_graphHandleRun, kGraphWidth, kGraphHeight,kSingleAnimFrame, kRunAnimNum);
	m_animJump.Init(m_graphHandleJump, kGraphWidth, kGraphHeight, kSingleAnimFrame, kJumpAnimNum);
	m_animShot.Init(m_graphHandleShot, kGraphWidth, kGraphHeight, kShotSingleAnimFrame, kShotAnimNum);
	m_animDamage.Init(m_graphHandleDamage, kGraphWidth, kGraphHeight, kSingleAnimFrame, kDamageAnimNum);
	m_animDeath.Init(m_graphHandleDeath, kGraphWidth, kGraphHeight, kDeathSingleAnimFrame, kDeathAnimNum);

	//�v���C���[�̈ʒu�̏�����
	m_pos.X = kPlayerInitPosX;
	m_pos.Y = kPlayerInitPosY;
}

void Player::Update()
{
	if (m_playerState != Player::kDeath)
	{
		/*Pad���͂̎擾*/


	/*���݂̏�Ԃ̎擾*/
		if (m_pos.Y >= 624) { m_isFloor = true; }//���̐G��Ă��邩�̔���
		m_playerState = GetPlayerState();


		/*�e��Ԃł̈ړ�����*/
		//�_���[�W��Ԃ̏���
		if (m_playerState == PlayerState::kDamage) { --m_blinkFrameCount; }//���G���Ԃ̍X�V
		//�W�����v
		if (m_playerState != Player::kDamage) { JumpUpdate(); }//�_���[�W���󂯂Ă�����W�����v�o���Ȃ�
		//if (jump) { Jump(); }
		//if (run) { Run();  }
		//if (damage) { Damage(); }
		//if (shot) { Shot(); }

		/*�e��Ԃł̓��ꏈ��*/
		//�e��
		if (m_playerState != Player::kDamage) { BulletUpdate(); }//�_���[�W���󂯂Ă����猂�ĂȂ�
		//Shot�̍X�V(���Ɍ����Ă���e�͔��ł���)
		for (int i = 0; i < kShotAllNum; ++i) { m_shot[i]->Update(); }


		m_deathFrameCount = kDeathFrame;

		/*���x�̍X�V*/
		PlayerVelocityUpdate();

		/*�ʒu�̍X�V*/
		m_pos += m_velocity;
	}

	MapCollisionUpdate();

	if(m_playerState == Player::kDeath)
	{
		Death();
		--m_deathFrameCount;
	}

	/*�e��Ԃł̃A�j���[�V��������*/
		//�X�e�[�g�ɂ���ăA�j���[�V�����̕ύX
	AnimUpdate(m_playerState);
}

void Player::Draw()
{
	BulletDraw();

	//�_�ŏ���
	if (m_blinkFrameCount / 2 % 2 && m_playerState != Player::kDeath)
	{
		return;
	}
#if _DEBUG
	if (m_isDirLeft)
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5 + kAdjustmentHitBox, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5, m_pos.Y, 0xffffff, false);
	}
	else
	{
		DrawBox(m_pos.X - kHitBoxW * 0.5, m_pos.Y - kHitBoxH, m_pos.X + kHitBoxW * 0.5 - kAdjustmentHitBox, m_pos.Y, 0xffffff, false);
	}
	
#endif // _DEBUG

	//�A�j���[�V�����Đ�
	AnimDraw(m_playerState);
}

float Player::GetLeft() const
{
	if (m_isDirLeft)
	{
		return (m_pos.X - (kHitBoxW * 0.5 - kAdjustmentHitBox));
	}
	else
	{
		return (m_pos.X - (kHitBoxW * 0.5));
	}
	
}

float Player::GetTop() const
{
	return (m_pos.Y - kHitBoxH);
}

float Player::GetRight() const
{
	if (m_isDirLeft)
	{
		return (m_pos.X + (kHitBoxW * 0.5));
	}
	else
	{
		return (m_pos.X + (kHitBoxW * 0.5) - kAdjustmentHitBox);
	}
	
}

float Player::GetBottom() const
{
	return m_pos.Y;
}

Rect Player::GetRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();
	return rect;
}

void Player::OnDamage(bool isHitLeft, bool isHitRight, bool isLastHitLeft, bool isLastHitRight)
{
	//���ɔ�e���Ă���ꍇ��return
	if (m_blinkFrameCount > 0)
	{
		return;
	}

	//���G���ԕt�^
	m_blinkFrameCount = kDamageBlinkFrame;

	//�v���C���[�̍����G�̉E�ɓ��������ꍇ�E�Ƀq�b�g�o�b�N
	if (isHitLeft && !isLastHitLeft)
	{
		m_velocity.X = 0;
		m_velocity.X = kDamageAction;
	}
	//�v���C���[�̉E���G�̍��ɓ��������ꍇ���Ƀq�b�g�o�b�N
	if (isHitRight && !isLastHitRight)
	{
		m_velocity.X = 0;
		m_velocity.X = -kDamageAction;
	}

	/*if (m_blinkFrameCount == 0)
	{
		return;
	}*/
	
	--m_hp;
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
		m_animDamage.Update();
		break;
	case Player::kDeath:
		m_animDeath.Update();
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
		m_animDamage.Play(m_pos, m_isDirLeft);
		break;
	case Player::kDeath:
		m_animDeath.Play(m_pos, m_isDirLeft);
		break;
	default:
		break;
	}
}

void Player::MapCollisionUpdate()
{	
	if (m_isJump)
	{
		Rect chipRect;
		if (m_pMap->IsCol(GetRect(), chipRect))
		{
			//������Ԃ������ꍇ�̏���
			if (m_velocity.X > 0.0f)//�v���C���[���E�����Ɉړ����Ă���
			{
				m_pos.X = chipRect.left - kHitBoxW * 0.5 - 1; //�}�b�v�`�b�v�̍������傤�ǂԂ���Ȃ��ʒu�ɕ␳
			}
			else if (m_velocity.X < 0.0f)
			{
				m_pos.X = chipRect.right + kHitBoxW * 0.5 + 1; //�}�b�v�`�b�v�̉E�����傤�ǂԂ���Ȃ��ʒu�ɕ␳
			}
		}
	}
	else
	{
		Rect chipRect;
		if (m_pMap->IsCol(GetRect(), chipRect))
		{
			//������Ԃ������ꍇ�̏���
			if (m_velocity.X > 0.0f)//�v���C���[���E�����Ɉړ����Ă���
			{
				m_pos.X = chipRect.left - kHitBoxW * 0.5; //�}�b�v�`�b�v�̍������傤�ǂԂ���Ȃ��ʒu�ɕ␳
			}
			else if (m_velocity.X < 0.0f)
			{
				m_pos.X = chipRect.right + kHitBoxW * 0.5; //�}�b�v�`�b�v�̉E�����傤�ǂԂ���Ȃ��ʒu�ɕ␳
			}
		}
	}
}

void Player::PlayerVelocityUpdate()
{
	//�ŏI�I�ȑ��x
	Vec2 lastVec;

	//PAD�t���O�`�F�b�N
	bool isRightPress = Pad::IsPress(PAD_INPUT_RIGHT);
	bool isLeftPress = Pad::IsPress(PAD_INPUT_LEFT);
	bool isDamage = m_playerState == kDamage;



	if (!isDamage)
	{
		//�E���x
		if (isRightPress)
		{
			lastVec.X = kSpeed;
			m_isDirLeft = false;
		}
		//�����x
		if (isLeftPress)
		{
			lastVec.X = -kSpeed;
			m_isDirLeft = true;
		}
	}

	//���ɐG�ꂢ�Ă�Ȃ�Y�����̑��x���[���ɂ���.
	if (m_isFloor)
	{
		lastVec.Y = 0.0f;
		m_pos.Y = 624;//�߂荞�ݒ���
		m_animJump.ResetAnimFrame();//�W�����v�A�j���[�V�������ŏ��ɖ߂�
	}
	//�������Ă��邩
	if (!m_isFloor)
	{
		//�������Ă���ꍇ�́A���x�ɏd�͉����x�𑫂�
		lastVec.Y = m_velocity.Y + kGravity;
	}
	//�_���[�W���󂯂Ă��邩
	if (m_playerState == PlayerState::kDamage)
	{
		lastVec.X = m_velocity.X;
	}

	//���x�̍X�V
	m_velocity = lastVec;
}

void Player::JumpUpdate()
{
	bool isJumpTrigger = Pad::IsTrigger(PAD_INPUT_2);
	bool isJump = (PlayerState::kJump == m_playerState);

	if (isJumpTrigger)
	{
		if (!isJump)
		{
			isJump = true;
			m_isFloor = false;
			m_velocity.Y = kJumpPower;
		}
	}

	
}

void Player::BulletUpdate()
{
	bool isShotTrigger = Pad::IsTrigger(PAD_INPUT_1);

	//�e�̐���
	if (isShotTrigger)
	{
		m_isShot = true;
		for (int i = 0; i < kShotAllNum; ++i)
		{
			if (!m_shot[i]->GetFrag())
			{
				m_shot[i]->SetShotFrag(m_isShot);

				m_shot[i]->SetPos(Vec2(m_pos.X + kHitBoxW * 0.5, m_pos.Y - kGraphHeight * 0.5f + 25));

				if (m_isDirLeft)
				{
					m_shot[i]->SetPos(Vec2(m_pos.X - kHitBoxW * 0.5, m_pos.Y - kGraphHeight * 0.5f + 25));
					m_shot[i]->SetDir(m_isDirLeft);
				}

				break;
			}
		}
	}
}

void Player::BulletDraw()
{
	//�e�̈ʒu���X�V���ĕ\��
	for (int i = 0; i < kShotAllNum; ++i)
	{
		if (m_shot[i]->GetFrag())
		{
			m_shot[i]->Draw();
		}
		m_isShot = false;
	}
}

void Player::Death()
{
	//���łɎ��S���o�ɓ����Ă���ꍇ��return
	if (m_deathFrameCount > 0)
	{
		return;
	}
}

Player::PlayerState Player::GetPlayerState() const 
{
	//�t���O�o��
	bool isJump = (m_pos.Y != 624);//�W�����v���Ă��邩
	bool isRun = (m_velocity.X != 0);//�v���C���[���ړ����Ă��邩
	bool isDamage = (m_blinkFrameCount > 0);//��e���Ă��邩
	bool isDeath = (m_hp <= 0);//HP��0��

	//�ҋ@
	if (!isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kIdle; }
	//Run
	if (isRun && !isJump && !m_isShot && !isDamage) { return PlayerState::kRun; }
	//Jump
	if (isJump && !m_isShot && !isDamage) { return PlayerState::kJump; }
	//Shot
	if (m_isShot && !isDamage) { return PlayerState::kShot; }
	//��e
	if (isDamage && !isDeath) { return PlayerState::kDamage; }
	//���S
	if (isDeath) { return PlayerState::kDeath; }

	return PlayerState::kIdle;
}
