#include "BubbleBobblePCH.h"
#include "FPSScene.h"
#include "Scene/GameObject.h"
#include "Resources/Font.h"
FPSScene::FPSScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_pFPSCounter(nullptr)
	, m_pFPSComponent(nullptr)
	, m_pFPSText(nullptr)
{

}

FPSScene::~FPSScene()
{

}

void FPSScene::Initialize()
{
	auto font = RESOURCES->Load<Font>("Lingua.otf");

	m_pFPSCounter = new GameObject();
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = new FPSComponent();
	m_pFPSText = new TextComponent("b", font);
	
	m_pFPSCounter->AddComponent(m_pFPSComponent);
	m_pFPSCounter->AddComponent(m_pFPSText);

	AddGameObject(m_pFPSCounter);
}

void FPSScene::Update([[maybe_unused]] float dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
}

