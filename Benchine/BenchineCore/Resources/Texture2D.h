#pragma once
struct SDL_Texture;

/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D
{
public:
	explicit Texture2D(SDL_Texture* pTexture);
	~Texture2D();
	DEL_ROF(Texture2D);

	[[nodiscard]] constexpr auto GetSDLTexture() const noexcept->SDL_Texture* { return m_pTexture; }

private:
	SDL_Texture* m_pTexture;
};

