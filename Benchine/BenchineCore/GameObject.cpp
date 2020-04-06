#include "BenchinePCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

GameObject::GameObject()
	: m_IsInitialized{ false }
	, m_pTransform{ nullptr }
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for(auto& pComponent : m_pComponents)
	{
		SafeDelete(pComponent);
	}
}

void GameObject::AddComponent(BaseComponent* pComponent)
{
	// TODO: check for duplicate components

	m_pComponents.push_back(pComponent);
	pComponent->m_pGameObject = this;
}

void GameObject::BaseInitialize()
{
	if (m_IsInitialized)
		return;

	// User Defined Initialization (for prefabs in the future)
	Initialize();

	// Component Initialization
	for (auto& pComponent : m_pComponents)
	{
		pComponent->BaseInitialize();
	}

	m_IsInitialized = true;
}
void GameObject::BaseUpdate(float dT)
{
	// User Defined Update
	Update(dT);

	// Component Update
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update(dT);
	}
}
void GameObject::BaseDraw() const
{
	// User Defined Draw
	Draw();

	// Component Draw
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
}
