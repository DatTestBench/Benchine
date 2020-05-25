#include "BenchinePCH.h"
#include "Components/TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position{ 0, 0, 0 }
{

}

void TransformComponent::SetPosition(const float x, const float y, const float z) noexcept
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::Initialize()
{

}
void TransformComponent::Update([[maybe_unused]] float dT)
{

}
