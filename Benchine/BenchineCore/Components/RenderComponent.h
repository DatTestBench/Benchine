#pragma once
#include "Components/BaseComponent.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent();
	DEL_ROF(RenderComponent);

	void Update([[maybe_unused]] float dT) override;
	void SetTexture(Texture2D* pTexture) noexcept { m_pTexture = pTexture; }


	void Render() const;

protected:
	void Initialize() override;

private:
	Texture2D* m_pTexture; //The rendercomponent does not own the texture, obviously
};