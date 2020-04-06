#pragma once
#include "TransformComponent.h"
#include "Utils.h"

class BaseComponent;
class GameObject final
{
public:
	GameObject();
	virtual ~GameObject();
	DEL_ROF(GameObject);

	void BaseInitialize();
	void BaseUpdate(float dT);
	void BaseDraw() const;

	void AddComponent(BaseComponent* pComponent);
	TransformComponent* GetTransform() const { return m_pTransform;  }

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
	virtual void Update(float dT) { UNUSED(dT); };
	virtual void Draw() const {};

private:

	std::vector<BaseComponent*> m_pComponents;
	bool m_IsInitialized;
	TransformComponent* m_pTransform;
};

