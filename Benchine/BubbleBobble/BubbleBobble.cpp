#include "BubbleBobblePCH.h"
#include "BubbleBobble.h"
#include "Scenes/FPSScene.h"


// This is the only actual useful function here >_>
void BubbleBobble::Initialize()
{
	SceneManager::GetInstance()->AddScene(new FPSScene("FPSScene"));




	SceneManager::GetInstance()->Initialize();
}

void BubbleBobble::Update(float dT)
{
	UNUSED(dT);
}

void BubbleBobble::Draw() const
{

}


