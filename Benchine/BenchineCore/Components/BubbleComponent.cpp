#include "BenchinePCH.h"
#include "Components/BubbleComponent.h"
#include "Components/TransformComponent.h"
BubbleComponent::BubbleComponent(const glm::vec2& throwDirection)
    : m_Velocity(throwDirection * 100.f)
{

}

void BubbleComponent::Initialize()
{

}

void BubbleComponent::Update(const float dT)
{
    GetTransform()->Move(m_Velocity * dT);
}