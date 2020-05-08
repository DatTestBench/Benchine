#include "BenchinePCH.h"
#include "Components/TransformComponent.h"

void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::Initialize()
{

}
void TransformComponent::Update(float dT)
{
	UNUSED(dT);
}

void TransformComponent::Draw() const
{
	
}
