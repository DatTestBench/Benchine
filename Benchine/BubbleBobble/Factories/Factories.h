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
		auto characterSprite = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("Characters/CharacterSprites.png"), 8U, 16U, 16U, 8.f));
		characterSprite->GetTextureWrapper()->SetTarget(50.f, 50.f);
		characterSprite->GetTextureWrapper()->SetRenderPriority(3U);


		auto physicsComponent = pCharacter->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
		physicsComponent->SetCollider(Collider2D{
			glm::vec2(-25, -25),
			glm::vec2(25, -25),
			glm::vec2(25, 25),
			glm::vec2(-25, 25)});

		auto callback = [](PolygonCollisionResult result, PhysicsComponent2D* pSelf, PhysicsComponent2D* pOther){
			if (pOther->GetCollisionMode() == CollisionMode::STATIC)
			{
				if (!(atan2(pSelf->GetVelocity().y, pSelf->GetVelocity().x) > glm::radians(45.f)
				&& atan2(pSelf->GetVelocity().y, pSelf->GetVelocity().x) < glm::radians(135.f)))
				{
					pSelf->GetTransform()->Move(result.minimumTranslationVector);
				}
			}
		};
		physicsComponent->SetCallback(callback ,true);

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
	static GameObject* CreateLevel(const std::string& levelFile)
	{
		// Read the settings from file
		const auto levelSettings = JsonHelper::ReadJson("Levels/" + levelFile);

		// Base gameobject
		const auto pLevel = new GameObject();
		
		// Scale the level to the set proportions
		pLevel->GetTransform()->SetScale(glm::vec2(levelSettings["Level"]["Scale"][0], levelSettings["Level"]["Scale"][1]));

		// Level needs to be drawn (duhh)
		pLevel->AddComponent(new RenderComponent());

		// Load the texture the level needs
		const auto textureFile = levelSettings["Level"]["Texture"].get<std::string>();
		auto pTexture = pLevel->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Levels/" + textureFile)));
		pTexture->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::BOTTOMLEFT); // Default initialization for level pivot
		pTexture->GetTextureWrapper()->SetRenderPriority(static_cast<uint32_t>(RenderDepth::MIDGROUNDLAYER1)); // Default level layer

		// Read Collider from file
		const auto colliderFile = levelSettings["Level"]["Collider"].get<std::string>();
		const auto collider = SvgHelper::ReadSvg("Levels/" + colliderFile);

		// Turn the loaded collider into PhysicsComponents to provide collsion to the level
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