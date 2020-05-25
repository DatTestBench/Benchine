#pragma once
#include <map>
#include <typeindex>
#include "Helpers/Singleton.h"
#include "Resources/ResourceLoader.h"
#include "Resources/Resources.h"


class ResourceManager final : public Singleton<ResourceManager>
{
public:

	virtual ~ResourceManager();

	void Init(const std::string& data);

	template <typename T>
	static void AddLoader(BaseLoader* pLoader)
	{
		m_Loaders[std::type_index(typeid(T))] = pLoader;
	}

	template <class T>
	static T* Load(const std::string& resourcePath)
	{
		return (static_cast<ResourceLoader<T>*>(m_Loaders.at(std::type_index(typeid(T)))))->GetResource(resourcePath);
	}

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	static std::map<std::type_index, BaseLoader*> m_Loaders;
};
