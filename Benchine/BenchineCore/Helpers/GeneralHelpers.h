#pragma once
//STL INCLUDES
//************
#include <vector>
#include <numeric>

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

//USINGS
//******
using Collider2D = std::vector<glm::vec2>;
using Polygon2D = std::vector<glm::vec2>;

//DEFINES
//*******
#define INPUT InputManager::GetInstance()
#define RESOURCES ResourceManager::GetInstance()

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
		: X(x)
		, Y(y)
		, Width(width)
		, Height(height)
	{}

	float X;
	float Y;
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
	inline glm::vec2 PolyCenter(const Polygon2D& polygon) 	// this actually generates the same asm as a simple for loop, but makes it look like I know what I'm doing: https://godbolt.org/z/Z9WeSx
															// And I know this is clang, but MSVC produces 14k lines on O2 :/ https://godbolt.org/z/wphEjY
	{
    	auto vertexSum = std::accumulate(polygon.cbegin(), polygon.cend(), glm::vec2(), 
    		[](const glm::vec2& v1, const glm::vec2& v2) {return v1 + v2;});
    	return glm::vec2(vertexSum.x / static_cast<float>(polygon.size()), vertexSum.y / static_cast<float>(polygon.size()));
	}
}

//COLLISION HELPERS
//*****************
namespace CollisionHelper
{
	inline bool IsPointInFRect(const glm::vec2& p, const FRect& r)
	{
		return p.x >= r.X 
		&& p.x <= r.X + r.Width
		&& p.y >= r.Y
		&& p.y <= r.Y + r.Height;
	}
}
