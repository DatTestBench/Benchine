#pragma once
#include "Scene/Scene.h"
#include "Components/Components.h"
class FPSScene final : public Scene
{
public:
	FPSScene(const std::string_view& sceneName);
	virtual ~FPSScene() override;
	DEL_ROF(FPSScene)

protected:


	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:
	GameObject* m_pFPSCounter;
	FPSComponent* m_pFPSComponent;
	TextComponent* m_pFPSText;


};

