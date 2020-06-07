#pragma once
class Texture2D
{
public:
	explicit Texture2D(const std::string& fullPath);
	~Texture2D();
	DEL_ROF(Texture2D);

	[[nodiscard]] constexpr auto GetTexture() const noexcept-> GLTextureWrapper* { return m_pTexture; }


private:
	GLTextureWrapper* m_pTexture;
};

