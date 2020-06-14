#include "BubbleBobblePCH.h"
#include "Scenes/TestScene.h"
#include "Debugging/DebugRenderer.h"
#include "Factories/Factories.h"
TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
{

}

TestScene::~TestScene()
{

}

void TestScene::Initialize()
{
	m_pCharacter = AddGameObject(Factories::CreateCharacter("GameObjects.json", "Bub", glm::vec2(200, 200), glm::vec2(3.f, 3.f)));
	m_pObject = AddGameObject(Factories::CreateObject());

	auto pBackground = AddGameObject(new GameObject());
	pBackground->AddComponent(new RenderComponent());
	auto pTexture = pBackground->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Background.jpg")));
	pTexture->GetTextureWrapper()->SetOffsetMode(TextureOffsetMode::BOTTOMLEFT);
	const auto windowSettings = RENDERER->GetWindowSettings();
	pTexture->GetTextureWrapper()->SetTarget(windowSettings.Width, windowSettings.Height);

	auto font = RESOURCES->Load<Font>("Lingua.otf");

	m_pFPSCounter = AddGameObject(new GameObject());
	m_pFPSCounter->GetTransform()->SetPosition(0, static_cast<float>(RENDERER->GetWindowSettings().Height));
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = m_pFPSCounter->AddComponent(new FPSComponent());
	m_pFPSText = m_pFPSCounter->AddComponent(new TextComponent("a", font));
	m_pFPSText->SetColor(0, 255, 0);
	m_pFPSText->GetTexture()->SetOffsetMode(TextureOffsetMode::TOPLEFT);
	m_pFPSText->GetTexture()->SetRenderPriority(10U);

	AddGameObject(Factories::CreateLevel("Level1.json"));

	INPUT->AddInputBinding(InputBinding("ting", std::bind(&TestScene::DeleteTing, this), InputState::Pressed, 'f'));
}

void TestScene::Update([[maybe_unused]] float dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
}

void TestScene::DeleteTing()
{
	m_pObject = RemoveGameObject(m_pObject);
}