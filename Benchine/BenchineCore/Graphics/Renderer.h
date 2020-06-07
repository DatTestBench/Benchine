#pragma once
#include "Helpers/Singleton.h"
#include "Helpers/GeneralHelpers.h"

struct SDL_Window;
class Renderer final : public Singleton<Renderer>
{
public:
	Renderer(token) {};
	virtual ~Renderer();

	void Initialize(const WindowSettings& windowSettings);
	void SetupRender() const;
	void PresentRender() const;


	void RenderTexture(GLTextureWrapper* pTexture, const FRect& dest, const FRect& src = {}) const;
	void RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos, const FRect& src = {}) const;

private:

	void Cleanup();

	WindowSettings m_WindowSettings;
	SDL_GLContext m_pContext;
	SDL_Window* m_pWindow;
};


