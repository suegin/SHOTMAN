#pragma once
#include "_base2DGameObject.h"

class _baseEnemy : public _base2DGameObject
{
public:
	virtual ~_baseEnemy() {};

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

private:
	int m_hp;
	int m_attack;
};

