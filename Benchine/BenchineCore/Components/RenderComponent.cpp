#include "BenchinePCH.h"
#include "RenderComponent.h"
#include "Graphics/Renderer.h"
#include "Scene/GameObject.h"
#include "Components/TransformComponent.h"

RenderComponent::RenderComponent()
{

}

RenderComponent::~RenderComponent()
{
	GetGameObject()->GetScene()->RemoveRenderComponent(this);
}

void RenderComponent::Initialize()
{
	GetGameObject()->GetScene()->AddRenderComponent(this);
	GetGameObject()->SetRenderComponent(this);
}

void RenderComponent::Update([[maybe_unused]] float dT)
{
	
}

void RenderComponent::Render() const
{
	const auto renderPos = GetGameObject()->GetTransform()->GetPosition();

	for (auto texture : m_RenderBuffer)
	{
		Renderer::GetInstance()->RenderTexture(texture.second, renderPos);
	}
}

void RenderComponent::ClearBuffer()
{
	m_RenderBuffer.clear();
}