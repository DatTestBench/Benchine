#include "BenchinePCH.h"
#include "BenchineRunner.h"


void BenchineRunner::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	constexpr int width = 640;
	constexpr int height = 480;

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
	const auto pRenderer = Renderer::GetInstance()->GetSDLRenderer();

	ImGui::CreateContext();
	ImGuiSDL::Initialize(pRenderer, width, height);


}

void BenchineRunner::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void BenchineRunner::Cleanup()
{
	delete m_pGame;
	Renderer::GetInstance()->Destroy();
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}
