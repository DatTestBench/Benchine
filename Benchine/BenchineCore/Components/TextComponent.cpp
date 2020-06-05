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
	SafeDelete(m_pTexture);
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



		/*SafeDelete(m_pTexture);
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		Texture2D* texture = new Texture2D(SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf));
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = texture;
		m_NeedsUpdate = false;

		GetGameObject()->GetRenderComponent()->SetTexture(m_pTexture);*/
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text) noexcept
{
	m_Text = text;
	m_NeedsUpdate = true;
}



