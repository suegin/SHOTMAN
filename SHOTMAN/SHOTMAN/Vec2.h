#pragma once

#include <cmath>

// 2�����x�N�g���N���X
class Vec2
{
public:
	float x;
	float y;

public:
	Vec2() 
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	// ���Z�q�̃I�[�o�[���[�h
	// ���̃N���X��+���̉��Z���s���ꍇ�̏������������Ƃ��ł���

	// ����
	// operator[�I�[�o�[���[�h���������Z�q]
	// ���̗Ⴞ�ƃI�[�o�[���[�h�������̂�"+="���Z�q
	Vec2 operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	Vec2 operator+(const Vec2& vec) const
	{
		Vec2 temp{ x + vec.x, y + vec.y };
		return temp;
	}

	Vec2 operator-=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	Vec2 operator-(const Vec2& vec) const
	{
		Vec2 temp{ x - vec.x, y - vec.y };
		return temp;
	}

	Vec2 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	Vec2 operator*(float scale) const
	{
		Vec2 temp{ x * scale, y * scale };
		return temp;
	}

	Vec2 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
	Vec2 operator/(float scale) const
	{
		Vec2 temp{ x / scale, y / scale };
		return temp;
	}

	// �x�N�g���̒��������߂�
	// �X�s�[�h�����߂�
	// 2�̕��̊Ԃ̋��������߂�@���Ɏg�p�ł���
	float Length() const
	{
		return sqrtf(x * x + y * y);
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
		x /= len;
		y /= len;
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