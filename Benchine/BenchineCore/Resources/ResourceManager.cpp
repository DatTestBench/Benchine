#include "BenchinePCH.h"
#include "Resources/ResourceManager.h"
#include "Resources/Texture2D.h"
#include "Resources/Font.h"
#include "Resources/Loaders.h"

//std::string ResourceManager::m_DataPath = std::string{};
std::map<std::type_index, BaseLoader*> ResourceManager::m_Loaders = std::map<std::type_index, BaseLoader*>();

ResourceManager::~ResourceManager()
{
	for (auto loader : m_Loaders)
	{
		loader.second->ReleaseResources();
		SafeDelete(loader.second);
	}
}

void ResourceManager::Init(const std::string& dataPath)
{
	BaseLoader::SetDataPath(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}


	// load SDL_Mixer support
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error(std::string("Failed to load support for sound: ") + SDL_GetError());
	}

	AddLoader<Font>(new FontLoader());
	//AddLoader<Texture2D>(new TextureLoader());

}