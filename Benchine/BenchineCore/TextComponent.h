#pragma once
#include "BaseComponent.h"

class Font;
class Texture2D;
class TextComponent final : public BaseComponent
{
public:

	TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
	virtual ~TextComponent();
	DEL_ROF(TextComponent);

	void Update(float dT) override;
	void Draw() const override;


	void SetText(const std::string& text);

	


protected:
	void Initialize() override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_Texture;
};

