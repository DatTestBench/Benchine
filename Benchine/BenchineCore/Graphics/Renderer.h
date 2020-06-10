#pragma once
#include "Helpers/Singleton.h"
#include "Helpers/GeneralHelpers.h"

struct SDL_Window;
class GLTextureWrapper;
class Renderer final : public Singleton<Renderer>
{
public:
	Renderer(token) {}
	virtual ~Renderer();

	void Initialize(const WindowSettings& windowSettings);
	void SetupRender() const;
	void PresentRender() const;


	void RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos) const;
	//void RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos, const FRect& src = {}) const;

private:

	void Cleanup();

	WindowSettings m_WindowSettings;
	SDL_GLContext m_pContext;
	SDL_Window* m_pWindow;



	const std::array<std::pair<glm::vec2, glm::vec2>, 4> CreateRenderParams(GLTextureWrapper* pTexture, const glm::vec2& pos) const;
};

