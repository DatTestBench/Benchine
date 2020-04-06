#pragma once

class GameObject;
class TransformComponent;
class BaseComponent
{
	friend class GameObject;
public:
	BaseComponent();
	virtual ~BaseComponent() = default;
	DEL_ROF(BaseComponent);

	GameObject* GetGameObject() const { return m_pGameObject; }
	TransformComponent* GetTransform() const;

	void BaseInitialize();
	virtual void Update(float dT) = 0;
	virtual void Draw() const = 0;

protected:
	virtual void Initialize() = 0;

	GameObject* m_pGameObject; // object this is attached to
	bool m_IsInitialized;
};

