#include "BenchinePCH.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: m_pScenes{  }
	, m_IsInitialized{ false }
{

}

SceneManager::~SceneManager()
{
	for (auto pScene : m_pScenes)
	{
		SafeDelete(pScene);
	}
}

void SceneManager::Initialize()
{
	if (m_IsInitialized)
		return;

	for (auto pScene : m_pScenes)
	{
		pScene->BaseInitialize();
	}

	m_IsInitialized = true;
}

void SceneManager::Update(float dT)
{
	for (auto pScene : m_pScenes)
	{
		pScene->BaseUpdate(dT);
	}
}

void SceneManager::Draw() const
{
	for (auto pScene : m_pScenes)
	{
		pScene->BaseDraw();
	}
}

void SceneManager::AddScene(Scene* pScene)
{
	m_pScenes.push_back(pScene);
}
