#pragma once
class AnimationManager
{public:
	AnimationManager();
	~AnimationManager();

	void Init();
	void Update();
	void Draw();

private:
	enum AnimState
	{
		kIdle,
		kRun,
		kJump,
		kShot
	};
};

