#include "BenchinePCH.h"
#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include "Components/RenderComponent.h"



Scene::Scene(const std::string_view& name)
	: m_Name{ name }
	, m_pGameObjects{  }
	, m_pRenderComponents{  }
{

}

Scene::~Scene()
{
	for (auto pGameObject : m_pGameObjects)
	{
		SafeDelete(pGameObject);
	}
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

void Scene::Render() const
{
	for (auto pRenderComponent : m_pRenderComponents)
	{
		if (pRenderComponent != nullptr)
		{
			pRenderComponent->Render();
		}
		else
		{
			Logger::Log<LEVEL_WARNING>("Scene::Render") << "Trying to render deleted RenderComponent, remember to clean up render components when deleting an object that has one";
		}
	}
}

void Scene::AddGameObject(GameObject* pGameObject)
{
	pGameObject->SetParentScene(this);
	m_pGameObjects.push_back(pGameObject);
}

void Scene::AddRenderComponent(RenderComponent* pRenderComponent)
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void Scene::RemoveRenderComponent(RenderComponent* pRenderComponent)
{
	m_pRenderComponents.remove(pRenderComponent);
}
