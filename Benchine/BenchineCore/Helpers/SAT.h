#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

//Adapted from : https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection
//				 http://www.dyn4j.org/2010/01/sat/
// Structure that stores the results of the PolygonCollision function

using Collider2D = std::vector<glm::vec2>;
class PhysicsComponent2D;
struct PolygonCollisionResult
{
	// Are the polygons going to intersect forward in time?
	bool willIntersect;
	// Are the polygons currently intersecting?
	bool intersect;
	// The translation to apply to the first polygon to push the polygons apart.
	glm::vec2 minimumTranslationVector;
};

namespace sat
{
	PolygonCollisionResult PolygonCollision(PhysicsComponent2D* pActorA, PhysicsComponent2D* pActorB);
	PolygonCollisionResult PolygonCollision(PhysicsComponent2D* pActor, const Collider2D& staticPoly);
	void ProjectPolygon(const glm::vec2& axis, const Collider2D& vertexSet, float& min, float& max);
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	glm::vec2 MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB);
}