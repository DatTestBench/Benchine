#include "BubbleBobblePCH.h"
#include "TestScene.h"
#include "Debugging/DebugRenderer.h"
TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
{

}

TestScene::~TestScene()
{

}

void TestScene::Initialize()
{
	
}

void TestScene::Update([[maybe_unused]] float dT)
{
	DebugRenderer::DrawRect(glm::vec2(1.f, 1.f), 10, 10);
}