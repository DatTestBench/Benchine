#pragma once
struct SDL_Texture;
/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D
{
public:
	explicit Texture2D(const std::string& fullPath);
	~Texture2D();
	DEL_ROF(Texture2D);

	//[[nodiscard]] constexpr auto GetSDLTexture() const noexcept->SDL_Texture* { return m_pTexture; }

	[[nodiscard]] constexpr auto GetTexture() const noexcept-> GLTextureWrapper* { return m_pTexture; }


private:
	GLTextureWrapper* m_pTexture;
};

