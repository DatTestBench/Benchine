#include "BubbleBobblePCH.h"
#include "Factories/Factories.h"

GameObject* Factories::CreateCharacter(const std::string& characterFile, const std::string& characterName, const glm::vec2& pos, const glm::vec2& scale)
{
	// Read the settings from file
	const auto characterSettings = JsonHelper::ReadJson("GameObjects/" + characterFile)[characterName];
	// Base gameobject
	const auto pCharacter = new GameObject();
	
	// Scale and move the Character to the set proportions
	pCharacter->GetTransform()->SetPosition(pos.x, pos.y);
	pCharacter->GetTransform()->SetScale(scale);
	if (characterSettings["Type"] == "Player")
	{
		pCharacter->AddComponent(new ControllerComponent(characterSettings["PlayerId"]));
	}
	else if (characterSettings["Type"] == "Enemy")
	{
		pCharacter->AddComponent(new AIControllerComponent());
	}
	// Character needs to be drawn (duhh)
	pCharacter->AddComponent(new RenderComponent());
	// Load the texture the level needs
	const auto spriteSheetFile = characterSettings["SpriteSheet"].get<std::string>();
	auto spriteComponent = pCharacter->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("GameObjects/" + spriteSheetFile), 8U, 16U, 16U, 8.f));
	bool setDefault = false;
	for (auto item : characterSettings["Animations"])
	{
		for (auto& [key, value] : item.items())
		{
			spriteComponent->AddAnimation(key, value);
			if (!setDefault)
			{
				spriteComponent->SetAnimation(key);
				setDefault = true;
			}
		}
	}
	spriteComponent->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::CENTER); // Default initialization for player pivot
	spriteComponent->GetTextureWrapper()->SetRenderPriority(static_cast<uint32_t>(RenderDepth::PLAYERLAYER)); // Default Player
	auto physicsComponent = pCharacter->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
		physicsComponent->SetCollider(Collider2D{
			glm::vec2(-8, -8),
			glm::vec2(8, -8),
			glm::vec2(8, 8),
			glm::vec2(-8, 8)});
	if (characterSettings["Type"] == "Player")
	{
		auto playerCallback = [](PolygonCollisionResult result, PhysicsComponent2D* pSelf, PhysicsComponent2D* pOther){
			if (pOther->GetCollisionMode() == CollisionMode::STATIC)
			{
				if (!(atan2(pSelf->GetVelocity().y, pSelf->GetVelocity().x) > glm::radians(45.f)
				&& atan2(pSelf->GetVelocity().y, pSelf->GetVelocity().x) < glm::radians(135.f)))
				{
					pSelf->GetTransform()->Move(result.minimumTranslationVector);
				}
			}
		};
		physicsComponent->SetCallback(playerCallback, true);
	}
	else if (characterSettings["Type"] == "Enemy")
	{
        const auto dropName = characterSettings["Drop"].get<std::string>();

		auto aiCallback = [dropName](PolygonCollisionResult result, PhysicsComponent2D* pSelf, PhysicsComponent2D* pOther){
			if (pOther->GetCollisionMode() == CollisionMode::STATIC)
			{
				if ((atan2(result.minimumTranslationVector.y, result.minimumTranslationVector.x) < glm::radians(45.f)
				|| atan2(result.minimumTranslationVector.y, result.minimumTranslationVector.x) > glm::radians(315.f)))
				{
					pSelf->GetGameObject()->GetComponent<AIControllerComponent>()->InvertDirection();
				}
				else if ((atan2(result.minimumTranslationVector.y, result.minimumTranslationVector.x) < glm::radians(215.f)
				&& atan2(result.minimumTranslationVector.y, result.minimumTranslationVector.x) > glm::radians(135.f)))
				{
					pSelf->GetGameObject()->GetComponent<AIControllerComponent>()->InvertDirection();
				}
			}

            if (pOther->GetCollisionMode() == CollisionMode::DYNAMIC)
            {
                auto cController = pOther->GetGameObject()->GetComponent<ControllerComponent>();
                if (cController != nullptr)
                {

                    if (pSelf->GetGameObject()->GetComponent<AIControllerComponent>()->GetState() == AIState::CAPTURED)
                    {

	                    pSelf->GetGameObject()->GetScene()->AddDropNextFrame(DropSettings{"GameObjects.json", dropName, glm::vec2(pSelf->GetTransform()->GetPosition()) + glm::vec2(0.f, 60.f), glm::vec2(3.f, 3.f)});
                        pSelf->GetGameObject()->GetComponent<AIControllerComponent>()->SetState(AIState::FREE);
                        pSelf->GetGameObject()->MarkForDelete();
                    }
                }
            }
		};
		physicsComponent->SetCallback(aiCallback);
	}
	return pCharacter;
}


GameObject* Factories::CreateDrop(const std::string& dropFile, const std::string& dropName, const glm::vec2& pos, const glm::vec2& scale)
{
	// Read the settings from file
	const auto dropSettings = JsonHelper::ReadJson("GameObjects/" + dropFile)[dropName];
	// Base object
	const auto pDrop = new GameObject();
	// Scale and move the Drop to the set proportions
	pDrop->GetTransform()->SetPosition(pos.x, pos.y);
	pDrop->GetTransform()->SetScale(scale);
	// Character needs to be drawn (duhh)
	pDrop->AddComponent(new RenderComponent());
	// Load the texture the drop needs
	const auto dropSpriteFile = dropSettings["SpriteSheet"].get<std::string>();
	auto spriteComponent = pDrop->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("GameObjects/" + dropSpriteFile), 1U, 2U, 2U, 1U));
	spriteComponent->SetCurrentZone(dropSettings["Cell"]);
	spriteComponent->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::CENTER);
	spriteComponent->GetTextureWrapper()->SetRenderPriority(static_cast<uint32_t>(RenderDepth::FOREGROUNDLAYER));
	const auto physicsComponent = pDrop->AddComponent(new PhysicsComponent2D(CollisionMode::TRIGGER));
	physicsComponent->SetCollider(Collider2D{
		glm::vec2(-8, -8),
		glm::vec2(8, -8),
		glm::vec2(8, 8),
		glm::vec2(-8, 8)});
	auto callback = [dropSettings](PolygonCollisionResult, PhysicsComponent2D* pSelf, PhysicsComponent2D* pOther){
		auto scoreComp = pOther->GetGameObject()->GetComponent<ScoreComponent>();
		if (scoreComp != nullptr)
		{
			scoreComp->AddScore(dropSettings["Value"]);
			pSelf->GetGameObject()->MarkForDelete();
		}
	};
	physicsComponent->SetCallback(callback, true);
	return pDrop;
}


GameObject* Factories::CreateBubble(const std::string& bubbleFile, const std::string& bubbleName, const glm::vec2& direction, const glm::vec2& pos, const glm::vec2& scale)
{
	// Read the settings from file
	const auto bubbleSettings = JsonHelper::ReadJson("GameObjects/" + bubbleFile)[bubbleName];
	// Base objects
	const auto pBubble = new GameObject();
	// Scale and move the Bubble to the set proportions
	pBubble->GetTransform()->SetPosition(pos.x, pos.y);
	pBubble->GetTransform()->SetScale(scale);
	pBubble->AddComponent(new RenderComponent());
	// Load the texture the drop needs
	const auto bubbleSpriteFile = bubbleSettings["SpriteSheet"].get<std::string>();
	const auto spriteComponent = pBubble->AddComponent(new SpriteComponent(RESOURCES->Load<Texture2D>("GameObjects/" + bubbleSpriteFile), 8U, 16U, 16U, 8.f));
	spriteComponent->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::CENTER);
	spriteComponent->GetTextureWrapper()->SetRenderPriority(static_cast<uint32_t>(RenderDepth::MIDGROUNDLAYER2));

	spriteComponent->AddAnimation("Default", bubbleSettings["Animations"][0]["Default"]);
	spriteComponent->SetAnimation("Default");
	pBubble->AddComponent(new BubbleComponent(direction));
	const auto physicsComponent = pBubble->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
	physicsComponent->SetCollider(Collider2D{
		glm::vec2(-8, -8),
		glm::vec2(8, -8),
		glm::vec2(8, 8),
		glm::vec2(-8, 8)});
	
	auto callback = [](PolygonCollisionResult, PhysicsComponent2D* pSelf, PhysicsComponent2D* pOther){
		auto aiController = pOther->GetGameObject()->GetComponent<AIControllerComponent>();
		if (aiController != nullptr)
		{
			aiController->BubbleHit();
			pSelf->GetGameObject()->MarkForDelete();
		}
	};
	physicsComponent->SetCallback(callback);

    pBubble->AddComponent(new LifetimeComponent(5.f));
	return pBubble;

}	

GameObject* Factories::CreateObject()
{
	const auto pObject = new GameObject();
	const auto pPhysicsComponent = pObject->AddComponent(new PhysicsComponent2D(CollisionMode::DYNAMIC));
	pPhysicsComponent->SetCollider(Collider2D{
		glm::vec2(-25, -25),
		glm::vec2(25, -25),
		glm::vec2(25, 25),
		glm::vec2(-25, 25)});
	pObject->GetTransform()->Move(glm::vec2(200, 200));
	pObject->AddComponent(new LifetimeComponent(5.f));
	return pObject;
}

GameObject* Factories::CreateLevel(const std::string& levelFile, const std::string& levelName)
{
	// Read the settings from file
	const auto levelSettings = JsonHelper::ReadJson("Levels/" + levelFile)[levelName];
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