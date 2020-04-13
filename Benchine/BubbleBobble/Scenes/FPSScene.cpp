#include "BubbleBobblePCH.h"
#include "FPSScene.h"
#include "GameObject.h"
FPSScene::FPSScene(const std::string& sceneName)
	: Scene{ sceneName }
{

}

FPSScene::~FPSScene()
{

}

void FPSScene::Initialize()
{

	auto font = ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36);

	m_pFPSCounter = new GameObject();
	m_pFPSComponent = new FPSComponent();
	m_pFPSText = new TextComponent("", font);
	
	m_pFPSCounter->AddComponent(m_pFPSComponent);
	m_pFPSCounter->AddComponent(m_pFPSText);

	AddGameObject(m_pFPSCounter);

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

void FPSScene::Update(float dT)
{
	UNUSED(dT);
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
}

void FPSScene::Draw() const
{
	ImGui::Begin("Test");

	ImGui::End();
}