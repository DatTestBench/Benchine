#include "BenchinePCH.h"
#include "Components/ControllerComponent.h"
#include "Components/TransformComponent.h"
#include "Debugging/DebugRenderer.h"

ControllerComponent::ControllerComponent()
{

}

void ControllerComponent::Initialize()
{
	INPUT->AddInputBinding(InputBinding("MoveLeft", InputState::Down, 'A'));
	INPUT->AddInputBinding(InputBinding("MoveRight", InputState::Down, 'D'));
	INPUT->AddInputBinding(InputBinding("MoveUp", InputState::Down, 'W'));
	INPUT->AddInputBinding(InputBinding("MoveDown", InputState::Down, 'S'));
}

void ControllerComponent::Update(float dT)
{

	constexpr float velocity = 100;
	glm::vec2 movement{};
	if (INPUT->IsBindingActive("MoveLeft"))
	{
		movement.x -= 1;
	}
	if (INPUT->IsBindingActive("MoveRight"))
	{
		movement.x += 1;
	}
	if (INPUT->IsBindingActive("MoveUp"))
	{
		movement.y += 1;
	}
	if (INPUT->IsBindingActive("MoveDown"))
	{
		movement.y -= 1;
	}

	GetTransform()->Move(movement * velocity * dT);

	DEBUGRENDER(DrawRectC(GetTransform()->GetPosition(), 10, 10));


}

