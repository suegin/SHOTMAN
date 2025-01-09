#include "SceneManager.h"
#include "DxLib.h"

#include "Pad.h"

#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"

using namespace std;

SceneManager::SceneManager():
	m_kind(kSceneGame)
{
	
	
	
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle = make_shared<SceneTitle>();
		m_pSceneTitle->Init();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame = make_shared<SceneGame>();
		m_pSceneGame->Init();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver = make_shared<SceneGameOver>();
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
