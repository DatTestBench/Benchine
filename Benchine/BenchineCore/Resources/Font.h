#pragma once

struct _TTF_Font;

/**
 * Simple RAII wrapper for an _TTF_Font
 */
class Font
{
public:
	explicit Font(const std::string& fullPath, uint32_t size);
	~Font();
	[[nodiscard]] constexpr auto GetFont() const noexcept->_TTF_Font* { return m_pFont; };

	DEL_ROF(Font);
private:
	_TTF_Font* m_pFont;
	uint32_t m_Size;
};

