#include "BenchinePCH.h"
#include "Core/Benchine.h"

void Benchine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	

	Renderer::GetInstance()->Init(WindowSettings("Window", 1280, 720, true));

}

void Benchine::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void Benchine::Cleanup()
{
	delete m_pGame;
	Renderer::GetInstance()->Destroy();
	SDL_Quit();
}
