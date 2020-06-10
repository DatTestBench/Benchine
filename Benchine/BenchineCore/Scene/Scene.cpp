#include "BenchinePCH.h"
#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include "Components/RenderComponent.h"
#include "Helpers/SAT.h"
#include "Components/PhysicsComponent2D.h"
#include "Debugging/DebugRenderer.h"
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
	DoPhysics();
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

	for (auto pRenderComponent : m_pRenderComponents)
	{
		if (pRenderComponent != nullptr)
		{
			pRenderComponent->ClearBuffer();
		}
		else
		{
			Logger::Log<LEVEL_WARNING>("Scene::Render") << "Trying to render deleted RenderComponent, remember to clean up render components when deleting an object that has one";
		}
	}
}

void Scene::DoPhysics() const
{
	for (auto it = m_pPhysicsComponents.cbegin(); it != m_pPhysicsComponents.cend(); ++it)
	{
		if ((std::next(it)) == m_pPhysicsComponents.cend())
			continue;
		for (auto it2 = std::next(it); it2 != m_pPhysicsComponents.cend(); ++it2)
		{
			(*it)->HandleCollision(*it2);
			DEBUGRENDER(DrawPolygon((*it)->GetColliderTransformed()))
			DEBUGRENDER(DrawPolygon((*it2)->GetColliderTransformed()))
		}
	}
}
GameObject* Scene::AddGameObject(GameObject* pGameObject) noexcept
{
	pGameObject->SetParentScene(this);
	m_pGameObjects.push_back(pGameObject);
	return pGameObject;
}

void Scene::AddRenderComponent(RenderComponent* pRenderComponent) noexcept
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void Scene::RemoveRenderComponent(RenderComponent* pRenderComponent) noexcept
{
	m_pRenderComponents.remove(pRenderComponent);
}

void Scene::AddPhysicsObject(PhysicsComponent2D* pPhysicsComponent) noexcept
{
	m_pPhysicsComponents.push_back(pPhysicsComponent);
}