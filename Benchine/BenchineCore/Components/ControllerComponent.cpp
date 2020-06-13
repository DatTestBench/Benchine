#include "BenchinePCH.h"
#include "Components/ControllerComponent.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include "Debugging/DebugRenderer.h"
#include <functional>
#include <algorithm>
ControllerComponent::ControllerComponent()
	: m_Velocity(0, 0)
	, m_Movement(0, 0)
	, m_pPhysicsComponent(nullptr)
{

}

void ControllerComponent::Initialize()
{
	m_pPhysicsComponent = GetGameObject()->GetComponent<PhysicsComponent2D>();
	if (m_pPhysicsComponent == nullptr)
	{
		Logger::Log<LEVEL_ERROR>("ControllerComponent::Initialize()") << "No PhysicsComponent specified, please attach a PhysicsComponent when using a ControllerComponent";
	}

	INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, 'a', -1, GamepadButton::DPAD_LEFT));
	INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, 'd', -1, GamepadButton::DPAD_RIGHT));
	INPUT->AddInputBinding(InputBinding("Jump", std::bind(&ControllerComponent::Jump, this), InputState::Pressed, SDLK_SPACE , -1, GamepadButton::A));
}

void ControllerComponent::Update(float dT)
{
	//Logger::Log<LEVEL_INFO>("ControllerComponent::Update()") << GetTransform()->GetPosition().x << " " << GetTransform()->GetPosition().y;
	//ogger::Log<LEVEL_INFO>("ControllerComponent::Update()") << m_Velocity.x << " " << m_Velocity.y ;

	constexpr float velocity = 100.f;
	constexpr float gravity = 750.f;
	constexpr float friction = 500.f;
	if (!m_pPhysicsComponent->IsOnGround())
	{
		m_Velocity.y = std::clamp(m_Velocity.y - gravity * dT, -200.f, 1000.f);
	}
	else
	{
		//m_Velocity.y = 0;
	}

	if (abs(m_Velocity.x) > 0.1f)
	{
		m_Velocity.x = m_Velocity.x < 0 ? std::min(m_Velocity.x + friction * dT, 0.f) : std::max(m_Velocity.x - friction * dT, 0.f);
	}

	m_Velocity += m_Movement * velocity;

	m_pPhysicsComponent->SetVelocity(m_Velocity);
	GetTransform()->Move(m_Velocity * dT);

	m_Movement = { 0, 0 };
}


void ControllerComponent::MoveLeft()
{
	m_Movement.x -= 1;
	m_Velocity.x = 0;
}
void ControllerComponent::MoveRight()
{
	m_Movement.x += 1;
	m_Velocity.x = 0;
}

void ControllerComponent::Jump()
{
	//if (m_pPhysicsComponent->IsOnGround())
	{
		Logger::Log<LEVEL_INFO>("ControllerComponent::Jump()") << m_Velocity.x << " " << m_Velocity.y;
		m_Velocity.y = 500;
	}
}
