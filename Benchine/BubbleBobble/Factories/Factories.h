#pragma once
#include "Components/Components.h"
#include "Scene/Scene.h"


namespace Factories
{
	/*CHARACTER*/
	void CreateCharacter(Scene* pScene)
	{
		const auto pCharacter = new GameObject();

		pCharacter->AddComponent(new ControllerComponent());
		pCharacter->AddComponent(new RenderComponent());
		pCharacter->AddComponent(new TextComponent());

		pScene->AddGameObject(pCharacter);

	}



}