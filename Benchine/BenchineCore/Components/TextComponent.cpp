#include "BenchinePCH.h"

#include "Components/TextComponent.h"
#include "Graphics/Renderer.h"
#include "Resources/Font.h"
#include "Resources/Texture2D.h"
#include "Components/TransformComponent.h"

TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
{

}

TextComponent::~TextComponent()
{
	SafeDelete(m_Texture);
}


void TextComponent::Initialize()
{

}

void TextComponent::Update(float dT)
{
	UNUSED(dT);
	if (m_NeedsUpdate)
	{
		SafeDelete(m_Texture);
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
		m_Texture = texture;
		m_NeedsUpdate = false;
	}
}

void TextComponent::Draw() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetTransform()->GetPosition();
		Renderer::GetInstance()->RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}



