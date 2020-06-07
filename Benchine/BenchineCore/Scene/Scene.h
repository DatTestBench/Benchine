#pragma once
#include "Scene/SceneManager.h"

class GameObject;
class RenderComponent;
class Scene
{
public:
	
	Scene(const std::string_view& sceneName);
	virtual ~Scene();
	DEL_ROF(Scene);

	void BaseInitialize();
	void BaseUpdate(float dT);
	void Render() const;
	void AddGameObject(GameObject* pGameObject);

	void AddRenderComponent(RenderComponent* pRenderComponent);
	void RemoveRenderComponent(RenderComponent* pRenderComponent);

	[[nodiscard]] constexpr auto GetSceneName() const noexcept-> std::string_view { return m_Name; }

protected:
	virtual void Initialize() = 0;
	virtual void Update(float dT) = 0;

private:

	std::string_view m_Name;
	std::list<GameObject*> m_pGameObjects;
	std::list<RenderComponent*> m_pRenderComponents; // Caching the render components to prevent having to do GetComponent every frame;
};


