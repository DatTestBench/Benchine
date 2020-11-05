#include "BenchinePCH.h"
#include "Components/LifetimeComponent.h"

LifetimeComponent::LifetimeComponent(const float lifeTime)
    : m_LifeTime(lifeTime)
{

}

void LifetimeComponent::Initialize()
{

}

void LifetimeComponent::Update(const float dT)
{
    m_LifeTime -= dT;

    if (m_LifeTime < 0)
    {
        GetGameObject()->MarkForDelete();
    }
}