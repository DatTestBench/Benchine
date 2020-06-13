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
	/*auto playerInfo = JsonHelper::ReadJson("test.json");
	playerInfo["Pos"][0] = m_pCharacter->GetTransform()->GetPosition().x;
	playerInfo["Pos"][1] = m_pCharacter->GetTransform()->GetPosition().y; 
	JsonHelper::WriteJson(playerInfo, "test.json");*/
}

void TestScene::Initialize()
{
	m_pCharacter = AddGameObject(Factories::CreateCharacter());
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

	/*for (int i = 0; i < 200; ++i)
	{
		AddGameObject(Factories::CreateObject());
	}*/
	INPUT->AddInputBinding(InputBinding("ting", std::bind(&TestScene::DeleteTing, this), InputState::Pressed, 'f'));
}

void TestScene::Update([[maybe_unused]] float dT)
{


	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
	//const auto collider = m_pCharacter->GetComponent<PhysicsComponent2D>()->GetColliderTransformed();
	//DEBUGRENDER(DrawPolygon(collider));
	//DEBUGRENDER(DrawRect(glm::vec2(1.f, 1.f), 10, 10));
}

void TestScene::DeleteTing()
{
	m_pObject = RemoveGameObject(m_pObject);
}