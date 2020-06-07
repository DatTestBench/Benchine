#include "BenchinePCH.h"

#include "Components/TextComponent.h"
#include "Graphics/Renderer.h"
#include "Resources/Font.h"
#include "Resources/Texture2D.h"
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"
#include "Scene/GameObject.h"

TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(font)
	, m_pTexture(nullptr)
{

}

TextComponent::~TextComponent()
{
}

void TextComponent::Initialize()
{

}

void TextComponent::Update([[maybe_unused]] float dT)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255, 255, 255 };

		m_pTexture = m_pFont->GenerateFontTexture(m_Text, color);

		GetGameObject()->GetRenderComponent()->SetTexture(m_pTexture);
		m_NeedsUpdate = false;
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text) noexcept
{
	m_Text = text;
	m_NeedsUpdate = true;
}



