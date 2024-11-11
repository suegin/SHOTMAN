#pragma once

#include <cmath>

// 2�����x�N�g���N���X
class Vec2
{
public:
	float X;
	float Y;

public:
	Vec2() 
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vec2(float _x, float _y) :
		X(_x),
		Y(_y)
	{
	}

	// ���Z�q�̃I�[�o�[���[�h
	// ���̃N���X��+���̉��Z���s���ꍇ�̏������������Ƃ��ł���

	// ����
	// operator[�I�[�o�[���[�h���������Z�q]
	// ���̗Ⴞ�ƃI�[�o�[���[�h�������̂�"+="���Z�q
	Vec2 operator+=(const Vec2& vec)
	{
		X += vec.X;
		Y += vec.Y;
		return *this;
	}
	Vec2 operator+(const Vec2& vec) const
	{
		Vec2 temp{ X + vec.X, Y + vec.Y };
		return temp;
	}

	Vec2 operator-=(const Vec2& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		return *this;
	}
	Vec2 operator-(const Vec2& vec) const
	{
		Vec2 temp{ X - vec.X, Y - vec.Y };
		return temp;
	}

	Vec2 operator*=(float scale)
	{
		X *= scale;
		Y *= scale;
		return *this;
	}
	Vec2 operator*(float scale) const
	{
		Vec2 temp{ X * scale, Y * scale };
		return temp;
	}

	Vec2 operator/=(float scale)
	{
		X /= scale;
		Y /= scale;
		return *this;
	}
	Vec2 operator/(float scale) const
	{
		Vec2 temp{ X / scale, Y / scale };
		return temp;
	}

	// �x�N�g���̒��������߂�
	// �X�s�[�h�����߂�
	// 2�̕��̊Ԃ̋��������߂�@���Ɏg�p�ł���
	float Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	// ���g�̒�����1�ɂ���(���K��)
	void Normalize()
	{
		float len = Length();
		if (len <= 0.0f)
		{
			// �[���x�N�g���͂��̂܂�
			return;
		}
		X /= len;
		Y /= len;
	}

	// ���g�̒�����1�ɂ����x�N�g���̎擾
	// (���̊֐����Ă�ł����g�̒����͕ω����Ȃ�)
	Vec2 GetNormalize() const
	{
		float len = Length();
		if (len <= 0.0f)
		{
			return *this;
		}
		return (*this) / len;
	}

	// ���ς̌v�Z
	// �x�N�g���̂Ȃ��p���v�Z���鎞�Ɏg��


	// �O�ς̌v�Z


};