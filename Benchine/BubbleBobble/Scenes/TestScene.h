#pragma once
#include "Scene/Scene.h"
#include "Components/Components.h"

class TestScene final : public Scene
{
public:
	explicit TestScene(const std::string_view& sceneName);
	virtual ~TestScene() override;
	DEL_ROF(TestScene)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:

	GameObject* m_pScoreBoard;
	TextComponent* m_pScoreText;
	ScoreComponent* m_pScoreComponent1;
	ScoreComponent* m_pScoreComponent2;


	GameObject* m_pCharacter1;
	GameObject* m_pCharacter2;
	GameObject* m_pFPSCounter;
	FPSComponent* m_pFPSComponent;
	TextComponent* m_pFPSText;



	GameObject* m_pCurrentlevel;
	int m_CurrentLevel;

	void ChangeLevel();
};