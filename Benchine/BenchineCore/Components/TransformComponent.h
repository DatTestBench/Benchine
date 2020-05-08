#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Components/BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y, float z);

protected:
	void Initialize() override;
	void Update(float dT) override;
	void Draw() const override;
private:
	glm::vec3 m_Position;
};

