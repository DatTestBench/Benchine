#pragma once
#include "Helpers/Singleton.h"
#include "Helpers/GeneralHelpers.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Window;
struct SDL_Renderer;

struct WindowSettings
{
	explicit WindowSettings(const std::string& name = "Window", float width = 1280.f, float height = 720.f, bool enableVSync = true)
		: name(name)
		, width(width)
		, height(height)
		, enableVSync(enableVSync)
	{}
	std::string name;
	float width;
	float height;
	bool enableVSync;
};

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(const WindowSettings& windowSettings);
	void SetupRender() const;
	void PresentRender() const;
	void Destroy();


	void RenderTexture(GLTextureWrapper* pTexture, const FRect& dest, const FRect& src = {}) const;
	void RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos, const FRect& src = {}) const;

private:
	WindowSettings m_WindowSettings;
	SDL_GLContext m_pContext;
	SDL_Window* m_pWindow;
};


