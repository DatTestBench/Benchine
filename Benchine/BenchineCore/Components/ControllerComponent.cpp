#include "BenchinePCH.h"
#include "Components/ControllerComponent.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Debugging/DebugRenderer.h"
#include "Resources/SoundByte.h"
#include "../BubbleBobble/Factories/Factories.h"
#include <functional>
#include <algorithm>
ControllerComponent::ControllerComponent(uint32_t playerId)
	: m_Velocity(0, 0)
	, m_Movement(0, 0)
	, m_pPhysicsComponent(nullptr)
	, m_PlayerId(playerId)
	, m_MovementState(MovementDirection::RIGHT)
{

}

void ControllerComponent::Initialize()
{
	m_pPhysicsComponent = GetGameObject()->GetComponent<PhysicsComponent2D>();
	if (m_pPhysicsComponent == nullptr)
	{
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("ControllerComponent::Initialize()") << "No PhysicsComponent specified, please attach a PhysicsComponent when using a ControllerComponent");
	}

	if (m_PlayerId == 0)
	{
		INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, 'a', -1, GamepadButton::DPAD_LEFT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, 'd', -1, GamepadButton::DPAD_RIGHT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Jump", std::bind(&ControllerComponent::Jump, this), InputState::Pressed, 'w' , -1, GamepadButton::A, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Shoot", std::bind(&ControllerComponent::Shoot, this), InputState::Pressed, 'f', -1, GamepadButton::X, m_PlayerId));
	}
	else if (m_PlayerId == 1)
	{
		INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, SDLK_LEFT, -1, GamepadButton::DPAD_LEFT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, SDLK_RIGHT, -1, GamepadButton::DPAD_RIGHT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Jump", std::bind(&ControllerComponent::Jump, this), InputState::Pressed, SDLK_UP , -1, GamepadButton::A, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Shoot", std::bind(&ControllerComponent::Shoot, this), InputState::Pressed, SDLK_RETURN, -1, GamepadButton::X, m_PlayerId));
	}
}

void ControllerComponent::Update(float dT)
{
	const float velocity = 100.f;
	const float gravity = 750.f;
	const float friction = 500.f;
	if (!m_pPhysicsComponent->IsOnGround())
	{
		m_Velocity.y = std::clamp(m_Velocity.y - gravity * dT, -200.f, 1000.f);
	}

	if (abs(m_Velocity.x) > 0.1f)
	{
		m_Velocity.x = m_Velocity.x < 0 ? std::min(m_Velocity.x + friction * dT, 0.f) : std::max(m_Velocity.x - friction * dT, 0.f);
	}

	m_Velocity += m_Movement * velocity;

	m_pPhysicsComponent->SetVelocity(m_Velocity);
	GetTransform()->Move(m_Velocity * dT);

	if (GetTransform()->GetPosition().y < 0.f)
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition().x, static_cast<float>(RENDERER->GetWindowSettings().Height));
	}
	else if (GetTransform()->GetPosition().y > static_cast<float>(RENDERER->GetWindowSettings().Height))
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition().x, 0.f);
	}

	m_Movement = { 0, 0 };
}


void ControllerComponent::MoveLeft()
{
	m_Movement.x -= 1;
	m_Velocity.x = 0;

	GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunLeft");	
	m_MovementState = MovementDirection::LEFT;
}

void ControllerComponent::MoveRight()
{
	m_Movement.x += 1;
	m_Velocity.x = 0;
	GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunRight");	
	m_MovementState = MovementDirection::RIGHT;
}


void ControllerComponent::Jump()
{
	//if (m_pPhysicsComponent->IsOnGround())
	{
		DEBUGONLY(Logger::Log<LEVEL_INFO>("ControllerComponent::Jump()") << m_Velocity.x << " " << m_Velocity.y);
		m_Velocity.y = 600;
		RESOURCES->Load<SoundByte>("Sounds/Jump.wav")->Play();
	}
}

void ControllerComponent::Shoot()
{
	glm::vec2 direction{0.f};

	if (m_MovementState == MovementDirection::RIGHT)
	{
		direction.x = 1.f;
	} 
	else if (m_MovementState == MovementDirection::LEFT)
	{
		direction.x = -1.f;
	}

	if (m_PlayerId == 0)
	{
		GetGameObject()->GetScene()->AddGameObjectLate(Factories::CreateBubble("GameObjects.json", "BubbleBub", direction, glm::vec2(GetTransform()->GetPosition()), glm::vec2(3.f, 3.f)));
	}
	else if (m_PlayerId == 1)
	{
		GetGameObject()->GetScene()->AddGameObjectLate(Factories::CreateBubble("GameObjects.json", "BubbleBob", direction, glm::vec2(GetTransform()->GetPosition()), glm::vec2(3.f, 3.f)));
	}
}
