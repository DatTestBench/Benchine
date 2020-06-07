#include "BenchinePCH.h"
#include "Resources/Font.h"

Font::Font(const std::string& fullPath, uint32_t size)
	: m_pFont(nullptr)
	, m_Size(size)
	, m_pTexture(nullptr)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		Logger::Log<LEVEL_ERROR>("Font::Font()") << "Failed to load font " << TTF_GetError();
	}
}

Font::~Font()
{
	SafeDelete(m_pTexture);
	TTF_CloseFont(m_pFont);
}


GLTextureWrapper* Font::GenerateFontTexture(const std::string& text, const SDL_Color& color)
{
	SafeDelete(m_pTexture);
	const auto pSurface = TTF_RenderText_Blended(m_pFont, text.c_str(), color);

	if (pSurface == nullptr)
	{
		Logger::Log<LEVEL_ERROR>("Font::GenerateFontTexture()") << TTF_GetError();
	}
	
	m_pTexture = new GLTextureWrapper(pSurface);

	SDL_FreeSurface(pSurface);

	return m_pTexture;
}
