#pragma once
#include <memory>

using namespace std;

class SceneTitle;
class SceneGame;
class SceneGameOver;

class Player;
class Enemy;

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

	shared_ptr<SceneTitle> m_pSceneTitle;
	shared_ptr<SceneGame> m_pSceneGame;
	shared_ptr<SceneGameOver> m_pSceneGameOver;
};

