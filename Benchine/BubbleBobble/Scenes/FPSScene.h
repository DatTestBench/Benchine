#pragma once
#include "Scene.h"
#include "Components.h"
class FPSScene final : public Scene
{
public:
	FPSScene(const std::string& sceneName);
	virtual ~FPSScene();
	DEL_ROF(FPSScene);

protected:


	void Initialize() override;
	void Update(float dT) override;
	void Draw() const override;

private:
	GameObject* m_pFPSCounter;
	FPSComponent* m_pFPSComponent;
	TextComponent* m_pFPSText;

};

