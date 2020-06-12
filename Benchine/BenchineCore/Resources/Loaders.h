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
		Font* pFont = new Font(fullPath, 32);
		
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
		Texture2D* pTexture = new Texture2D(fullPath);

		return pTexture;
	}

	void Release(Texture2D* pResource) override
	{
		SafeDelete(pResource);
	}
};