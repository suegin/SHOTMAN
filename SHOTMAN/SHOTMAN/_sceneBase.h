#pragma once
/// <summary>
/// �S�ẴV�[���̊��N���X
/// </summary>
class _sceneBase
{
public:
	virtual ~_sceneBase() {};

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;
};

