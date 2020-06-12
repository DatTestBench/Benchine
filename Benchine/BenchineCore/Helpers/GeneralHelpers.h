#pragma once
//STL INCLUDES
//************
#include <vector>
#include <numeric>
#include <string>
#include <fstream>
#include <filesystem>
//GLM INCLUDES
//************
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <glm/mat3x2.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

//MISC INCLUDES
//*************
#include "Helpers/json.hpp"
//USINGS
//******
using Collider2D = std::vector<glm::vec2>;
using Polygon2D = std::vector<glm::vec2>;
using json  = nlohmann::json;

//DEFINES
//*******
#define INPUT InputManager::GetInstance()
#define RESOURCES ResourceManager::GetInstance()
#define RENDERER Renderer::GetInstance()

//MACROS
//******
#ifdef _DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x) do{}while(0)
#endif

//ENUMS
//*****


//STRUCT EXTENTIONS
//*****************
struct Projection2D
{
	explicit Projection2D(float val)
		: Min(val)
		, Max(val)
	{}
	explicit Projection2D(float min, float max)
		: Min(min)
		, Max(max)
	{}
	float Min;
	float Max;
};

//HELPER STRUCTS
//**************
struct WindowSettings
{
	explicit WindowSettings(const std::string& name = "Window", uint32_t width = 1280U, uint32_t height = 720U, bool enableVSync = true)
		: Name(name)
		, Width(width)
		, Height(height)
		, EnableVSync(enableVSync)
	{}
	std::string Name;
	uint32_t Width;
	uint32_t Height;
	bool EnableVSync;
};

struct FRect
{
	FRect() : FRect(0.f, 0.f, 0.f, 0.f) {}
	explicit FRect(float x, float y, float width, float height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{}
	explicit FRect(glm::vec2 pos, float width, float height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{}

	glm::vec2 Pos;
	float Width;
	float Height;
};

struct FEllipse
{
	explicit FEllipse(const glm::vec2& center, float radX, float radY)
		: Center(center)
		, RadX(radX)
		, RadY(radY)
	{}

	glm::vec2 Center;
	float RadX;
	float RadY;

};

//MATH HELPERS
//************
namespace MathHelper
{
	[[nodiscard]] auto PolyCenter(const Polygon2D& polygon) noexcept-> const glm::vec2;
}

//COLLISION HELPERS
//*****************
namespace CollisionHelper
{
	[[nodiscard]] constexpr auto IsPointInFRect(const glm::vec2& p, const FRect& r) noexcept-> bool;
}

//JSON HELPER
//***********
namespace JsonHelper
{
	[[nodiscard]] auto ReadJson(const std::string& filePath) noexcept-> json;
	void WriteJson(const json& j, const std::string& filePath) noexcept;
}

//SVG HELPER
namespace SvgHelper
{
	[[nodiscard]] auto ReadSvg(const std::string& filePath) noexcept-> std::vector<Polygon2D>;
}