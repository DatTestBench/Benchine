#pragma once
#include "Components/BaseComponent.h"
#include "Helpers/Sat.h"
class PhysicsComponent2D final : public BaseComponent
{
public:
	PhysicsComponent2D();
	virtual ~PhysicsComponent2D() = default;
	DEL_ROF(PhysicsComponent2D);

	[[nodiscard]] constexpr auto GetVelocity() const noexcept-> glm::vec2 { return m_Velocity; };
	[[nodiscard]] auto GetCollider() const noexcept-> const Collider2D& { return m_Collider; }

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override {};

private:
	glm::vec2 m_Velocity;
	Collider2D m_Collider;

};