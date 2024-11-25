#pragma once
class Fade
{
public:
	Fade();
	~Fade();

	void Init();
	void Update();
	void Draw();

	void FadeIn();
	void FadeOut();

private:
	int m_fadeFrameCount;
};

