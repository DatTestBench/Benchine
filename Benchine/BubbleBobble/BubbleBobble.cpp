#include "BubbleBobblePCH.h"
#include "BubbleBobble.h"
#include "Scenes/FPSScene.h"
#include "Scenes/TestScene.h"


// This is the only actual useful function here >_>
void BubbleBobble::Initialize()
{
	SceneManager::GetInstance()->AddScene(new FPSScene("FPSScene"));
	SceneManager::GetInstance()->AddScene(new TestScene("TestScene"));

	SceneManager::GetInstance()->SetStartScene("TestScene");

	SceneManager::GetInstance()->Initialize();
	
}

void BubbleBobble::Update([[maybe_unused]] float dT)
{
}



