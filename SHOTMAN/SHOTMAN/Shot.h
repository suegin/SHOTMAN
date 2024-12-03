#pragma once
#include "_base2DGameObject.h"
#include "Vec2.h"

class Shot : public _base2DGameObject
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

	Vec2 GetPos()const { return m_pos; }
	Vec2 GetVelocity()const { return m_velocity; }
	bool GetFrag()const { return m_shotFrag; }

	void SetPos(const Vec2 setPos);
	void SetFrag(bool setShotFrag);
	void SetDir(bool setDir);

	void BulletVelocityUpdate();

private:
	int m_graphHandleShot;
	bool m_shotFrag;
	bool m_isDirLeft;

	Vec2 m_velocity;
};

