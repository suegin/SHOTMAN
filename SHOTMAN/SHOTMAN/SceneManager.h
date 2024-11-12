#pragma once

class SceneTitle;
class SceneGame;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();

public:
	enum SceneKind
	{
		kSceneTitle,
		kSceneGame,

		kSceneNum
	};

private:
	SceneKind m_kind;

	SceneTitle* m_pSceneTitle;
	SceneGame* m_pSceneGame;
};

