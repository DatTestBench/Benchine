#include "BubbleBobblePCH.h"
#include "TestScene.h"
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
	m_pCharacter = AddGameObject(Factories::CreateCharacter());
	AddGameObject(Factories::CreateObject());

	auto pBackground = AddGameObject(new GameObject());
	pBackground->AddComponent(new RenderComponent());
	pBackground->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Background.jpg")));

}

void TestScene::Update([[maybe_unused]] float dT)
{
	//const auto collider = m_pCharacter->GetComponent<PhysicsComponent2D>()->GetColliderTransformed();
	//DEBUGRENDER(DrawPolygon(collider));
	//DEBUGRENDER(DrawRect(glm::vec2(1.f, 1.f), 10, 10));
}