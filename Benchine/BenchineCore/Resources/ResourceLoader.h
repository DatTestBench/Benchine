#pragma once
#include <unordered_map>
#include <string_view>

#include <filesystem>
#include "Debugging/Logger.h"
#include "Resources/ResourceManager.h"
class BaseLoader
{
public:
	BaseLoader() = default;
	virtual ~BaseLoader() = default;
	DEL_ROF(BaseLoader);

	static void SetDataPath(const std::string& dataPath) { m_DataPath = dataPath; }
	static const std::string GetDataPath() { return m_DataPath; }
	virtual void ReleaseResources() = 0;
protected:
	static std::string m_DataPath;
private:

};

template <class T>
class ResourceLoader : public BaseLoader
{
public:
	ResourceLoader() = default;
	virtual ~ResourceLoader() = default;
	DEL_ROF(ResourceLoader);

	T* GetResource(const std::string(filePath))
	{
		for (std::pair<std::string_view, T*> resource : m_Resources)
		{
			if (resource.first.compare(filePath) == 0)
				return resource.second;
		}

		// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
		if (!std::filesystem::exists(m_DataPath + filePath))
		{
			Logger::Log<LEVEL_ERROR>("ContentManager::GetResource()") << "file at following location not found\n" << m_DataPath + filePath;
			return nullptr;
		}

		T* resource = Load(filePath);
		if (resource != nullptr)
		{
			m_Resources.try_emplace(filePath, resource);
		}
		return resource;
	}

	void ReleaseResources() override
	{
		for (std::pair<std::string_view, T*> resource : m_Resources)
		{
			Release(resource.second);
		}
		m_Resources.clear();
	}
	
protected:
	virtual T* Load(const std::string& filePath) = 0;
	virtual void Release(T* pResource) = 0;
	static std::unordered_map<std::string_view, T*> m_Resources;
};

template <class T>
std::unordered_map<std::string_view, T*> ResourceLoader<T>::m_Resources = std::unordered_map<std::string_view, T*>();