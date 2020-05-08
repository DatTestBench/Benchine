#pragma once
#include <string>
#include "Resources/ResourceLoader.h"

/*Resource Types*/
#include "Resources/Font.h"
#include "Resources/Texture2D.h"



class Font;
class FontLoader final : public ResourceLoader<Font>
{
public:
	Font* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		Font* pFont = new Font(fullPath, 16);
		//m_Resources.try_emplace(filePath, pFont);
		
		return pFont;
	}

	void Release(Font* pResource) override
	{
		SafeDelete(pResource);
	}
};

class Texture2D;
class TextureLoader final : public ResourceLoader<Texture2D>
{
public:
	Texture2D* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		Texture2D* pTexture = new Texture2D(IMG_LoadTexture(Renderer::GetInstance()->GetSDLRenderer(), fullPath.c_str()));
		if (pTexture == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}
		//m_Resources.try_emplace(filePath, pTexture);

		return pTexture;
	}

	void Release(Texture2D* pResource) override
	{
		SafeDelete(pResource);
	}
};