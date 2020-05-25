#include "BenchinePCH.h"
#include "Resources/Font.h"

Font::Font(const std::string& fullPath, uint32_t size)
	: m_pFont{ nullptr }
	, m_Size{ size }
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Font::~Font()
{
	TTF_CloseFont(m_pFont);
}
