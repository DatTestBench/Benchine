#pragma once
#include "Components/BaseComponent.h"

class Font;
class GLTextureWrapper;
class TextComponent final : public BaseComponent
{
public:

	TextComponent(const std::string& text, Font* font);
	virtual ~TextComponent();
	DEL_ROF(TextComponent);

	void Update([[maybe_unused]] float dT) override;

	void SetText(const std::string& text) noexcept;

protected:
	void Initialize() override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Font* m_pFont;
	GLTextureWrapper* m_pTexture;
};

