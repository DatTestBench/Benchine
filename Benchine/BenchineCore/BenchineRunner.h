#pragma once

struct SDL_Window;
#include "BaseGame.h"
class ResourceManager;
class InputManager;
class Renderer;

class BenchineRunner
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();

	template<typename T> // Templated to allow the use of any kind of basegame
	void Run()
	{
		m_pGame = new T();

		Initialize(); // Setup SDL


		ResourceManager* pResourceManager = ResourceManager::GetInstance();
		pResourceManager->Init("../Resources/");

		InputManager* pInput = InputManager::GetInstance();
		Renderer* pRenderer = Renderer::GetInstance();

		LoadGame();

		bool quit = false;

		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.f;

		while (!quit)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			quit = pInput->ProcessInput();

			while (lag >= MsPerFrame / 1000.f)
			{
				m_pGame->BaseUpdate(MsPerFrame / 1000.f);
				lag -= MsPerFrame / 1000.f;
			}


			pRenderer->SetupRender();
			m_pGame->BaseDraw();
			pRenderer->PresentRender();
		}
		Cleanup();
	}

private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_pWindow;
	BaseGame* m_pGame;
};