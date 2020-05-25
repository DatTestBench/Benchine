#pragma once
//#include "Components/TransformComponent.h"
//#include "Components/RenderComponent.h"
#include "Helpers/Utils.h"
#include "Scene/Scene.h"

class TransformComponent;
class RenderComponent;
class BaseComponent;
class GameObject final
{
public:
	GameObject();
	virtual ~GameObject();
	DEL_ROF(GameObject);

	void BaseInitialize();
	void BaseUpdate(float dT);

	void AddComponent(BaseComponent* pComponent);
	void SetParentScene(Scene* pScene);
	void SetParentObject(GameObject* pObject);
	void SetRenderComponent(RenderComponent* pRenderComponent) { m_pRenderComponent = pRenderComponent; }
	[[nodiscard]] constexpr auto GetTransform() const noexcept->TransformComponent* { return m_pTransform;  }
	[[nodiscard]] constexpr auto GetRenderComponent() const noexcept->RenderComponent* { return m_pRenderComponent; }
	Scene* GetScene() const;


template <class T>
	T* GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		return nullptr;
	}



protected:
	// For future use
	virtual void Initialize() {};
	virtual void Update([[maybe_unused]] float dT) { };

private:
	Scene* m_pParentScene;
	GameObject* m_pParentObject;
	std::vector<BaseComponent*> m_pComponents;
	bool m_IsInitialized;
	TransformComponent* m_pTransform;
	RenderComponent* m_pRenderComponent;
};

