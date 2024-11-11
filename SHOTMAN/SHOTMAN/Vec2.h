#pragma once

#include <cmath>

// 2次元ベクトルクラス
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

	// 演算子のオーバーロード
	// このクラスで+等の演算を行う場合の処理を書くことができる

	// 書式
	// operator[オーバーロードしたい演算子]
	// ↓の例だとオーバーロードしたいのは"+="演算子
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

	// ベクトルの長さを求める
	// スピードを求める
	// 2つの物体間の距離を求める　等に使用できる
	float Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	// 自身の長さを1にする(正規化)
	void Normalize()
	{
		float len = Length();
		if (len <= 0.0f)
		{
			// ゼロベクトルはそのまま
			return;
		}
		X /= len;
		Y /= len;
	}

	// 自身の長さを1にしたベクトルの取得
	// (この関数を呼んでも自身の長さは変化しない)
	Vec2 GetNormalize() const
	{
		float len = Length();
		if (len <= 0.0f)
		{
			return *this;
		}
		return (*this) / len;
	}

	// 内積の計算
	// ベクトルのなす角を計算する時に使う


	// 外積の計算


};