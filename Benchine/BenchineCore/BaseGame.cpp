#include "BenchinePCH.h"
#include "BaseGame.h"

void BaseGame::BaseInitialize()
{
	// User Definined Initialize
	Initialize();
}

void BaseGame::BaseUpdate(float dT)
{
	SceneManager::GetInstance()->Update(dT);
	// User Defined Update
	Update(dT);
}

void BaseGame::BaseDraw() const
{
	SceneManager::GetInstance()->Draw();
	// User Defined Draw
	Draw();
}