#pragma once
#include "Components/BaseComponent.h"
#include "Helpers/Sat.h"
#include "Helpers/GeneralHelpers.h"
class PhysicsComponent2D final : public BaseComponent
{
public:
	PhysicsComponent2D();
	virtual ~PhysicsComponent2D() override;
	DEL_ROF(PhysicsComponent2D)

	[[nodiscard]] constexpr auto GetVelocity() const noexcept-> glm::vec2 { return m_Velocity; }
	[[nodiscard]] auto GetCollider() const noexcept-> const Collider2D& { return m_Collider; }
	Collider2D GetColliderTransformed();

	void SetCollider(const Collider2D& collider) { m_Collider = collider; }

	void HandleCollision(PhysicsComponent2D* pOtherActor);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override {}

private:
	glm::vec2 m_Velocity;
	Collider2D m_Collider;

};