#include "SceneManager.h"
#include "DxLib.h"

#include "Pad.h"

#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"

SceneManager::SceneManager():
	m_kind(kSceneGame),
	m_pSceneTitle(nullptr),
	m_pSceneGame(nullptr),
	m_pSceneGameOver(nullptr)
{
}

SceneManager::~SceneManager()
{
	if (m_pSceneTitle != nullptr)
	{
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
	}

	if (m_pSceneGame != nullptr)
	{
		delete m_pSceneGame;
		m_pSceneGame = nullptr;
	}

	if (m_pSceneGameOver != nullptr)
	{
		delete m_pSceneGameOver;
		m_pSceneGameOver = nullptr;
	}
}

void SceneManager::Init()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle = new SceneTitle();
		m_pSceneTitle->Init();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame = new SceneGame();
		m_pSceneGame->Init();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver = new SceneGameOver();
		m_pSceneGameOver->Init();
	case SceneManager::kSceneNum:
	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	SceneKind nextKind = m_kind;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Update();
		nextKind = m_pSceneTitle->SceneTransition();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Update();
		nextKind = m_pSceneGame->SceneTransition();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver->Update();
		nextKind = m_pSceneGameOver->SceneTransition();
		break;
	case SceneManager::kSceneNum:
	default:
		break;
	}

	if (nextKind != m_kind)
	{
		m_kind = nextKind;

		Init();
	}
}

void SceneManager::Draw()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Draw();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver->Draw();
		break;
	case SceneManager::kSceneNum:
		break;
	default:
		break;
	}
}
