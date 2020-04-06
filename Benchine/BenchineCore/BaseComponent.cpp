#include "BenchinePCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
	, m_IsInitialized(false)
{

}

void BaseComponent::BaseInitialize()
{
	if (m_IsInitialized)
		return;

	Initialize();

	m_IsInitialized = true;
}

TransformComponent* BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}