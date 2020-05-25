#pragma once
#include "Helpers/Singleton.h"

struct SDL_Window;
struct SDL_Renderer;


class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void SetupRender() const;
	void PresentRender() const;
	void Destroy();

	void RenderTexture(Texture2D* texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	void SetTexture(Texture2D* pTexture) noexcept { m_pCurrentTexture = pTexture;}

	[[nodiscard]] constexpr auto GetSDLRenderer() const noexcept->SDL_Renderer* { return m_pRenderer; }
private:
	SDL_Renderer* m_pRenderer;
	Texture2D* m_pCurrentTexture;
};


