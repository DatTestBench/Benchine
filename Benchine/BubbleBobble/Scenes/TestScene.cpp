#include "BubbleBobblePCH.h"
#include "Scenes/TestScene.h"
#include "Debugging/DebugRenderer.h"
#include "Factories/Factories.h"
TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_pScoreBoard(nullptr)
	, m_pScoreText(nullptr)
	, m_pScoreComponent1(nullptr)
	, m_pScoreComponent2(nullptr)
	, m_pCharacter1(nullptr)
	, m_pCharacter2(nullptr)
	, m_pFPSComponent(nullptr)
	, m_pFPSCounter(nullptr)
	, m_pFPSText(nullptr)
	, m_pCurrentlevel(nullptr)
{

}

TestScene::~TestScene()
{

}

void TestScene::Initialize()
{
	m_pCharacter1 = AddGameObject(Factories::CreateCharacter("GameObjects.json", "Bub", glm::vec2(200, 200), glm::vec2(3.f, 3.f)));
	m_pScoreComponent1 = m_pCharacter1->AddComponent(new ScoreComponent());

	m_pCharacter2 = AddGameObject(Factories::CreateCharacter("GameObjects.json", "Bob", glm::vec2(400, 200), glm::vec2(3.f, 3.f)));
	m_pScoreComponent2 = m_pCharacter2->AddComponent(new ScoreComponent());

	AddGameObject(Factories::CreateCharacter("GameObjects.json", "Maita", glm::vec2(500, 300), glm::vec2(3.f, 3.f)));
	AddGameObject(Factories::CreateCharacter("GameObjects.json", "Zen-Chan", glm::vec2(500, 400), glm::vec2(3.f, 3.f)));
	AddGameObject(Factories::CreateCharacter("GameObjects.json", "Maita", glm::vec2(600, 200), glm::vec2(3.f, 3.f)));
	AddGameObject(Factories::CreateCharacter("GameObjects.json", "Zen-Chan", glm::vec2(500, 500), glm::vec2(3.f, 3.f)));

	auto font = RESOURCES->Load<Font>("Lingua.otf");

	
	// FPS
	m_pFPSCounter = AddGameObject(new GameObject());
	m_pFPSCounter->GetTransform()->SetPosition(1000.f, static_cast<float>(RENDERER->GetWindowSettings().Height));
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = m_pFPSCounter->AddComponent(new FPSComponent());
	m_pFPSText = m_pFPSCounter->AddComponent(new TextComponent("a", font));
	m_pFPSText->SetColor(0, 255, 0);
	m_pFPSText->GetTexture()->SetOffsetMode(TextureOffsetMode::TOPLEFT);
	m_pFPSText->GetTexture()->SetRenderPriority(10U);

	m_pScoreBoard = AddGameObject(new GameObject());
	m_pScoreBoard->GetTransform()->SetPosition(1000.f, static_cast<float>(RENDERER->GetWindowSettings().Height) / 2.f);
	m_pScoreBoard->AddComponent(new RenderComponent());
	m_pScoreText = m_pScoreBoard->AddComponent(new TextComponent("0", font));
	m_pScoreText->SetColor(0, 0, 255);
	m_pScoreText->GetTexture()->SetOffsetMode(TextureOffsetMode::TOPLEFT);
	m_pScoreText->GetTexture()->SetRenderPriority(8U);

	//Score
	//INPUT->AddInputBinding(InputBinding("ChangeLevel", std::bind(&TestScene::ChangeLevel, this), InputState::Pressed, 'n', -1, GamepadButton::B, 0));
	//INPUT->AddInputBinding(InputBinding("ChangeLevel", std::bind(&TestScene::ChangeLevel, this), InputState::Pressed, 'n', -1, GamepadButton::B, 1));

	m_pCurrentlevel = AddGameObject(Factories::CreateLevel("Levels.json", "Level2"));

}

void TestScene::Update([[maybe_unused]] float dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
	const auto totalScore = m_pScoreComponent1->GetScore() + m_pScoreComponent2->GetScore();

	m_pScoreText->SetText(std::to_string(totalScore));
}

void TestScene::ChangeLevel()	
{
	m_CurrentLevel++;

	if (m_CurrentLevel >= 3)
	{
		m_CurrentLevel = 1;
	}

	m_pCurrentlevel->MarkForDelete();
	m_pCurrentlevel = AddGameObject(Factories::CreateLevel("Levels.json", "Level" + std::to_string(m_CurrentLevel)));
}