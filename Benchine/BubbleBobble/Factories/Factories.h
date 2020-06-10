#pragma once
#include "Components/Components.h"
#include "Scene/Scene.h"


namespace Factories
{
	/*CHARACTER*/
	static GameObject* CreateCharacter()
	{
		const auto pCharacter = new GameObject();

		pCharacter->AddComponent(new ControllerComponent());
		pCharacter->AddComponent(new RenderComponent());
		auto characterSprite = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("SpritePlayer.png"), 4U, 4U, 1U, 4.f));
		auto flameSprite = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("SpriteExhaust.png"), 5U, 1U, 1U, 4.f));
		flameSprite->GetTexture()->SetPositionOffset(glm::vec2(0.f, -25.f));
		flameSprite->GetTexture()->SetOffsetMode(TextureOffsetMode::TOP);
		characterSprite->GetTexture()->SetTarget(50.f, 50.f);
		characterSprite->GetTexture()->SetRenderPriority(2);
		auto physicsComponent = pCharacter->AddComponent(new PhysicsComponent2D());
		physicsComponent->SetCollider(Collider2D{
			glm::vec2(-25, -25),
			glm::vec2(25, -25),
			glm::vec2(25, 25),
			glm::vec2(-25, 25)});
		return pCharacter;
	}

	/*TESTOBJECT*/
	static GameObject* CreateObject()
	{
		const auto pObject = new GameObject();

		const auto pPhysicsComponent = pObject->AddComponent(new PhysicsComponent2D());
		pPhysicsComponent->SetCollider(Collider2D{
			glm::vec2(-25, -25),
			glm::vec2(25, -25),
			glm::vec2(25, 25),
			glm::vec2(-25, 25)});
		pObject->GetTransform()->Move(glm::vec2(200, 200));

		return pObject;
	}

}