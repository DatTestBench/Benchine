#include "BenchinePCH.h"
#include "Benchine.h"


void Benchine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	constexpr int width = 1280;
	constexpr int height = 720;

	m_pWindow = SDL_CreateWindow(
		"Benchine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(m_pWindow);

}

void Benchine::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void Benchine::Cleanup()
{
	delete m_pGame;
	Renderer::GetInstance()->Destroy();
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}
