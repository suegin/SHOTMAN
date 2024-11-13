#pragma once
/// <summary>
/// 全てのシーンの基底クラス
/// </summary>
class _sceneBase
{
public:
	virtual ~_sceneBase() {};

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;
};

