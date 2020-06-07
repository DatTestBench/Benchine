#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Components/BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;
	DEL_ROF(TransformComponent);


	void SetPosition(const float x, const float y, const float z) noexcept;
	void Move(const float x, const float y, const float z) noexcept;
	void Move(const glm::vec2& movementVec) noexcept;
	[[nodiscard]] constexpr auto GetPosition() const noexcept-> glm::vec3 { return m_Position; }

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;
private:
	glm::vec3 m_Position;
};

