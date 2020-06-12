#pragma once
#include "Components/Components.h"
#include "Scene/Scene.h"
#include "Helpers/GeneralHelpers.h"
#include "Resources/Resources.h"
namespace Factories
{
	/*CHARACTER*/
	static GameObject* CreateCharacter()
	{
		const auto pCharacter = new GameObject();
		const auto test = JsonHelper::ReadJson("test.json");
		pCharacter->GetTransform()->SetPosition(test["Pos"][0], test["Pos"][1]);
		pCharacter->AddComponent(new ControllerComponent());
		pCharacter->AddComponent(new RenderComponent());
		auto characterSprite = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("SpritePlayer.png"), 4U, 4U, 1U, 4.f));
		auto flameSprite = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("SpriteExhaust.png"), 5U, 1U, 1U, 4.f));
		flameSprite->GetTextureWrapper()->SetPositionOffset(glm::vec2(0.f, -25.f));
		flameSprite->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::TOP);
		characterSprite->GetTextureWrapper()->SetTarget(50.f, 50.f);
		characterSprite->GetTextureWrapper()->SetRenderPriority(2);
		auto physicsComponent = pCharacter->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
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

		const auto pPhysicsComponent = pObject->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
		pPhysicsComponent->SetCollider(Collider2D{
			glm::vec2(-25, -25),
			glm::vec2(25, -25),
			glm::vec2(25, 25),
			glm::vec2(-25, 25)});
		pObject->GetTransform()->Move(glm::vec2(200, 200));

		return pObject;
	}

	/*Level*/
	static GameObject* CreateLevel()
	{
		const auto collider = SvgHelper::ReadSvg("Level1.svg");
		const auto pLevel = new GameObject();
		pLevel->GetTransform()->SetScale(glm::vec2(3.f, 3.f));
		pLevel->AddComponent(new RenderComponent());
		auto pTexture = pLevel->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Level1.png")));
		pTexture->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::BOTTOMLEFT);
		pTexture->GetTextureWrapper()->SetRenderPriority(3U);

		for (auto polygon : collider)
		{
			const auto pPhysicsComponent = pLevel->AddComponent(new PhysicsComponent2D(CollisionMode::STATIC));
			pPhysicsComponent->SetCollider(polygon);
		}
		return pLevel;
	}

}

/*auto pBackground = AddGameObject(new GameObject());
	pBackground->AddComponent(new RenderComponent());
	auto pTexture = pBackground->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Background.jpg")));
	pTexture->GetTexture()->SetOffsetMode(TextureOffsetMode::BOTTOMLEFT);
	const auto windowSettings = RENDERER->GetWindowSettings();
	pTexture->GetTexture()->SetTarget(windowSettings.Width, windowSettings.Height);*/