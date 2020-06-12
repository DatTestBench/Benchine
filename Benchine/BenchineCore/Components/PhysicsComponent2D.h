#pragma once
#include "Components/BaseComponent.h"
#include "Helpers/Sat.h"
#include "Helpers/GeneralHelpers.h"
#include "Debugging/DebugRenderer.h"
#include <functional>
enum class CollisionMode
{
	STATIC,
	DYNAMIC,
	TRIGGER
};

class PhysicsComponent2D final : public BaseComponent
{
public:
	PhysicsComponent2D(CollisionMode collisionMode = CollisionMode::STATIC);
	virtual ~PhysicsComponent2D() override;
	DEL_ROF(PhysicsComponent2D)

	[[nodiscard]] constexpr auto GetVelocity() const noexcept-> glm::vec2 { return m_Velocity; }
	[[nodiscard]] constexpr auto GetBaseCollider() const noexcept-> const Collider2D& { return m_BaseCollider; }
	[[nodiscard]] constexpr auto GetCollider() const noexcept-> const Collider2D& { return m_Collider; }
	[[nodiscard]] constexpr auto GetCollisionMode() const noexcept-> CollisionMode { return m_CollisionMode; }
	
	void SetCollider(const Collider2D& collider) noexcept { m_BaseCollider = collider; m_Collider = collider; }
	void SetCallback(std::function<void()> callback) noexcept { m_PhysicsCallback = callback; }
	void HandleCollision(PhysicsComponent2D* pOtherActor);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:

	CollisionMode m_CollisionMode;
	std::function<void()> m_PhysicsCallback;
	glm::vec2 m_Velocity;
	Collider2D m_Collider;
	Collider2D m_BaseCollider;


};