#include "BenchinePCH.h"
#include "Scene.h"
#include "GameObject.h"



unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }

{

}

Scene::~Scene()
{
	for (auto pGameObject : m_pGameObjects)
	{
		SafeDelete(pGameObject);
	}
}

void Scene::AddGameObject(GameObject* pGameObject)
{
	m_pGameObjects.push_back(pGameObject);
}

void Scene::BaseInitialize()
{
	// User Defined Initialize
	Initialize();

	// Game Object Initialization
	for (auto pGameObject : m_pGameObjects)
	{
		pGameObject->BaseInitialize();
	}

}

void Scene::BaseUpdate(float dT)
{
	// User Defined Update
	Update(dT);

	// Game Object Update
	for (auto pGameObject : m_pGameObjects)
	{
		pGameObject->BaseUpdate(dT);
	}
}

void Scene::BaseDraw() const
{
	// User Defined Draw
	Draw();

	// Game Object Draw
	for (auto pGameObject : m_pGameObjects)
	{
		pGameObject->BaseDraw();
	}
}

