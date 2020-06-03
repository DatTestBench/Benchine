#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <vector>
#include <numeric>

using Collider2D = std::vector<glm::vec2>;


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
