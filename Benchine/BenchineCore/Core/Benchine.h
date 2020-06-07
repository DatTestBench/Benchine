#pragma once

struct SDL_Window;
#include "Core/BaseGame.h"


class Benchine
{
public:
	

	template<typename T> // Templated to allow the use of any kind of basegame
	void Run()
	{
		m_pGame = new T();

		Initialize(); // Setup SDL

		ResourceManager::GetInstance()->Initialize("../Resources/");

		InputManager* pInput = InputManager::GetInstance();
		Renderer* pRenderer = Renderer::GetInstance();
		Logger* pLogger = Logger::GetInstance();

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

			
			
			
			pRenderer->SetupRender();
			m_pGame->BaseUpdate(deltaTime);

			/*while (lag >= MsPerFrame / 1000.f)
			{
				m_pGame->BaseUpdate(MsPerFrame / 1000.f);
				lag -= MsPerFrame / 1000.f;
			}*/
		
			SceneManager::GetInstance()->RenderCurrentScene();
			pLogger->OutputLog();
			pRenderer->PresentRender();
		}
		Cleanup();

		
	}

private:
	void Initialize();
	void LoadGame() const;
	void Cleanup();

	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps

	BaseGame* m_pGame;
};