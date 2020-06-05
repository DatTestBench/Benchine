#pragma once
//stl includes
//************
#include <vector>
#include <numeric>


//glm includes
//************
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

//usings
//******
using Collider2D = std::vector<glm::vec2>;
using Polygon2D = std::vector<glm::vec2>;

//struct extentions
//*****************
struct Projection2D : glm::vec2
{
	explicit Projection2D(float val) : glm::vec2(val) {};
	explicit Projection2D(float min, float max) : glm::vec2(min, max) {};
	float& min = x;
	float& max = y;
};

//helper structs
struct FRect
{
	FRect() : FRect(0.f, 0.f, 0.f, 0.f) {}
	explicit FRect(float x, float y, float width, float height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{}

	float x;
	float y;
	float width;
	float height;
};

struct FEllipse
{
	explicit FEllipse(const glm::vec2& center, float radX, float radY)
		: center(center)
		, radX(radX)
		, radY(radY)
	{}

	glm::vec2 center;
	float radX;
	float radY;

};

//math helpers
//************
namespace MathHelper
{
	inline glm::vec2 PolyCenter(const Collider2D& polygon) 	// this actually generates the same asm as a simple for loop, but makes it look like I know what I'm doing: https://godbolt.org/z/Z9WeSx
															// And I know this is clang, but MSVC produces 14k lines on O2 :/ https://godbolt.org/z/wphEjY
	{
    	auto vertexSum = std::accumulate(polygon.cbegin(), polygon.cend(), glm::vec2(), 
    		[](const glm::vec2& v1, const glm::vec2& v2) {return v1 + v2;});
    	return glm::vec2(vertexSum.x / polygon.size(), vertexSum.y / polygon.size());
	}
}
