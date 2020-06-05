#pragma once


// Wrapper the OpenGL texture system, to work with SDL_Surface

class GLTextureWrapper
{
public:
	GLTextureWrapper(SDL_Surface* pSurface);
	~GLTextureWrapper();
	DEL_ROF(GLTextureWrapper);

	[[nodiscard]] constexpr auto GetId() const noexcept-> GLuint { return m_Id; }
	[[nodiscard]] constexpr auto GetWidth() const noexcept-> float { return m_Width; }
	[[nodiscard]] constexpr auto GetHeight() const noexcept->float { return m_Height; }
	[[nodiscard]] constexpr auto IsCreationOk() const noexcept-> bool { return m_CreationOk; }


private:
	GLuint m_Id;
	float m_Width;
	float m_Height;
	bool m_CreationOk;

	void CreateTextureFromSurface(SDL_Surface* pSurface);
};