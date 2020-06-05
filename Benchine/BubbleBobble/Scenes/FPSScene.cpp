#include "BubbleBobblePCH.h"
#include "FPSScene.h"
#include "Scene/GameObject.h"
FPSScene::FPSScene(const std::string_view& sceneName)
	: Scene(sceneName)
{

}

FPSScene::~FPSScene()
{

}

void FPSScene::Initialize()
{
	


	auto font = ResourceManager::GetInstance()->Load<Font>("Lingua.otf");

	m_pFPSCounter = new GameObject();
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = new FPSComponent();
	m_pFPSText = new TextComponent("", font);
	
	m_pFPSCounter->AddComponent(m_pFPSComponent);
	m_pFPSCounter->AddComponent(m_pFPSText);

	AddGameObject(m_pFPSCounter);

	InputManager::GetInstance()->AddInputBinding(InputBinding("Shoot", InputState::Pressed, 'S', -1, GamepadButton::A));
	InputManager::GetInstance()->AddInputBinding(InputBinding("Shoot", InputState::Pressed, 'A', -1, GamepadButton::A));

	//AddGameObject(new Text)

	/*auto& scene = SceneManager::GetInstance().CreateScene("Demo");

auto go = std::make_shared<GameObject>();
go->SetTexture("background.jpg");
scene.Add(go);

go = std::make_shared<GameObject>();
go->SetTexture("logo.png");
go->SetPosition(216, 180);
scene.Add(go);

auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
to->SetPosition(80, 20);
scene.Add(to);*/
}

void FPSScene::Update([[maybe_unused]] float dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));

	if (InputManager::GetInstance()->IsBindingActive("Shoot"))
	{
		Logger::Log<LEVEL_DEBUG>("FPSScene::Update") << "Shoot!";
	}
}

