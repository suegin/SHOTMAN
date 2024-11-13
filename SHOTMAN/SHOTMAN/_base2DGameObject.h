#pragma once
#include "Vec2.h"
/// <summary>
/// 全ての2Dゲームオブジェクトの基底クラス
/// </summary>
class _base2DGameObject
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~_base2DGameObject() {};

	/*メンバ関数*/
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:
	Vec2 m_pos{ 0.0f, 0.0f };
	int m_drawHandle;
};

