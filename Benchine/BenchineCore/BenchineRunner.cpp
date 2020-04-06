#include "BenchinePCH.h"
#include "BenchineRunner.h"


void BenchineRunner::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Benchine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(m_pWindow);
}

void BenchineRunner::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void BenchineRunner::Cleanup()
{
	delete m_pGame;
	Renderer::GetInstance()->Destroy();

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}
