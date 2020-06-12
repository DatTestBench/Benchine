#include "BenchinePCH.h"
#include "Components/ControllerComponent.h"
#include "Components/TransformComponent.h"
#include "Debugging/DebugRenderer.h"
#include <functional>
ControllerComponent::ControllerComponent()
{

}

void ControllerComponent::Initialize()
{
	INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, 'A', -1, GamepadButton::DPAD_LEFT));
	INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, 'D', -1, GamepadButton::DPAD_RIGHT));
	INPUT->AddInputBinding(InputBinding("MoveUp", std::bind(&ControllerComponent::MoveUp, this), InputState::Down, 'W', -1, GamepadButton::DPAD_UP));
	INPUT->AddInputBinding(InputBinding("MoveDown", std::bind(&ControllerComponent::MoveDown, this), InputState::Down, 'S', -1, GamepadButton::DPAD_DOWN));
}

void ControllerComponent::Update(float dT)
{

	constexpr float velocity = 100;
	GetTransform()->Move(m_Movement * velocity * dT);
	m_Movement = { 0, 0 };


}


void ControllerComponent::MoveLeft()
{
	m_Movement.x -= 1;
}
void ControllerComponent::MoveRight()
{
	m_Movement.x += 1;
}
void ControllerComponent::MoveUp()
{
	m_Movement.y += 1;
}
void ControllerComponent::MoveDown()
{
	m_Movement.y -= 1;
}
