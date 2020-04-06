#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	
	virtual ~SceneManager();
	void Initialize();
	void Update(float dT);
	void Draw() const;

	void AddScene(Scene* pScene);


private:
	friend class Singleton<SceneManager>;
	SceneManager();
	std::vector<Scene*> m_pScenes;
	bool m_IsInitialized;
};

