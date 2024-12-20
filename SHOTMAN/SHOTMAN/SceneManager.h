#pragma once

class SceneTitle;
class SceneGame;
class SceneGameOver;

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
		kSceneGameOver,

		kSceneNum
	};

private:
	SceneKind m_kind;

	SceneTitle* m_pSceneTitle;
	SceneGame* m_pSceneGame;
	SceneGameOver* m_pSceneGameOver;
};

