#pragma once
#include "Scene/SceneManager.h"

class GameObject;
class Scene
{
public:
	
	Scene(const std::string& sceneName);
	virtual ~Scene();
	DEL_ROF(Scene);

	void BaseInitialize();
	void BaseUpdate(float dT);
	void BaseDraw() const;

	void AddGameObject(GameObject* pGameObject);

protected:
	virtual void Initialize() = 0;
	virtual void Update(float dT) = 0;
	virtual void Draw() const = 0;

private:

	std::string m_Name;
	std::vector<GameObject*> m_pGameObjects;

	static unsigned int m_IdCounter;
};


