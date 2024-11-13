#pragma once

class _sceneBase
{
public:
	virtual ~_sceneBase() {};

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;
};

